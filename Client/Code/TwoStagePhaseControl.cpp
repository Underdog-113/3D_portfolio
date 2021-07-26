#include "stdafx.h"
#include "TwoStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"
#include "Portal.h"
#include "Monster.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"
#include "MovieDirector.h"
#include "PhaseChanger.h"
#include "PatternMachineC.h"
#include "ActorController.h"
#include "StageCameraMan.h"

CTwoStagePhaseControl::CTwoStagePhaseControl()
{
}


CTwoStagePhaseControl::~CTwoStagePhaseControl()
{
}

void CTwoStagePhaseControl::Update(void)
{
	switch (m_curPhase)
	{
	case UNDEFINED:
		++m_curPhase;
		break;

	case (_int)ETwoStagePhase::ReadyStage:
		CStageControlTower::GetInstance()->SetDirectorMode(true);
		++m_curPhase;
		break;

	case (_int)ETwoStagePhase::PlayerSummon:
		if (m_pCT->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->CompareState(L"Appear") == false)
		{
			EnterConversationPhase();
			++m_curPhase;
		}
		break;

	case (_int)ETwoStagePhase::Conversation:
		if (m_spConversation->IsEnd())
		{
			CStageControlTower::GetInstance()->SetDirectorMode(false);
			++m_curPhase;
		}
		break;
		//Before being collised with PhaseChanger0
	case (_int)ETwoStagePhase::BeforeEnterBoss:

		break;
	case (_int)ETwoStagePhase::PotalWarp:
		//CStageControlTower::GetInstance()->GetActorController()->SetDirectorMode(true);
		if (!m_portalEnter)
		{
			CStageControlTower::GetInstance()->SetDirectorMode(true);
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_BlackFadeOut();
			m_portalEnter = true;
		}

		m_warpTimer += GET_DT;
		if (m_warpTimer > 0.6f)
		{
			if (!m_portalMove)
			{
				_float3 warpPos = ((CPortal*)Engine::GET_CUR_SCENE->FindObjectWithKey(L"Portal").get())->GetDestPos();
				CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->SetPosition(warpPos - _float3(0.f, 0.5f, 0.f));
				CStageControlTower::GetInstance()->GetCameraMan()->GetPivot()->GetTransform()->SetPosition(warpPos - _float3(0.f, 0.5f, 0.f));
				CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_BlackFadeIn();
				m_portalMove = true;
			}
			if (!m_portalEnd && m_warpTimer > 1.1f)
			{
				m_portalEnd = true;

				++m_curPhase;
			}			
		}
		break;
	case (_int)ETwoStagePhase::WarningAlarm:
		m_warningTimer += GET_DT;

		if (!m_warningSpawn && m_warningTimer > 0.5f)
		{
			SP(Engine::CObject) spObj;
			spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Warning_Ring", true, (_uint)Engine::ELayerID::Effect);

			CValkyrie* pActor = CStageControlTower::GetInstance()->GetCurrentActor();
			spObj->GetTransform()->SetParent(pActor->GetTransform());
			spObj->GetTransform()->AddPositionY(pActor->GetMesh()->GetHalfYOffset());
			spObj->GetTransform()->SetSize(1.5f, 1.5f, 1.5f);

			m_warningSpawn = true;
		}

		if (m_warningTimer > 4.f)
		{
			++m_curPhase;
		}
		break;
	case (_int)ETwoStagePhase::CreateBoss:
		m_spGanesha = std::dynamic_pointer_cast<CMonster>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha"));
		m_spGanesha->GetTransform()->SetPosition(0.f, 0.f, 0.f);
		m_spGanesha->SelectChannelID();
		m_spGanesha->SetIsEnabled(true);

		//ui off
		static_cast<Engine::CCanvas*>(Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas").get())->SetIsEnabled(false);
		++m_curPhase;
		break;
	case (_int)ETwoStagePhase::BossMovie:
		if (false == m_isBossMovieOn)
		{
			m_spGanesha->SetIsEnabled(false);
			m_spGanesha->GetTransform()->SetPosition(-46.f, 14.5f, 0.f);

			// movie
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_GaneshBorn();
			m_isBossMovieOn = true;
		}

		break;
		//After being collided with PhaseChanger0
	case (_int)ETwoStagePhase::Boss:
		if (!m_isBossMovieOff)
		{
			//CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_BlackFadeIn();
			CStageControlTower::GetInstance()->SetDirectorMode(false);
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->PlayBGM(L"GaneShaBGM_2.mp3");
			Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
			m_isBossMovieOff = true;
		}


		m_uiOnTimer += GET_DT;
		if (!m_uiOn && m_uiOnTimer > 0.5f)
		{
			// ui on
			Engine::GET_CUR_SCENE->FindObjectByName(L"MainCanvas")->SetIsEnabled(true);
			CBattleUiManager::GetInstance()->QteOff(0);
			CBattleUiManager::GetInstance()->QteOff(1);
			CBattleUiManager::GetInstance()->SquadOff(Engine::GET_CUR_SCENE);
			CBattleUiManager::GetInstance()->WaitingPlayerSetting();

			m_uiOn = true;
		}

		if (m_spGanesha->GetComponent<CPatternMachineC>()->GetOnDie())
			++m_curPhase;

		break;
		//After killing Boss
	case (_int)ETwoStagePhase::BossEnd:
		// movie
		CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_WinningSlow();
		++m_curPhase;
		break;
	case (_int)ETwoStagePhase::WinningSlow:
		if (!CStageControlTower::GetInstance()->GetMovieDirector()->GetIsOnAir())
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			m_victoryTimer = 0.f;
			++m_curPhase;
		}
		break;
	case (_int)ETwoStagePhase::WaitVictoryMovie:
		m_victoryTimer += GET_DT;

		if (m_victoryTimer > 1.f)
		{
			m_victoryTimer = 0.f;
			// movie
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_Victory();

			Engine::CSoundManager::GetInstance()->StartSound(L"Victory.mp3", (_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
			++m_curPhase;
		}
		break;
	case (_int)ETwoStagePhase::VictoryMovie:
		m_victoryTimer += GET_DT;
		if (m_victoryTimer > 4.f)
		{
			OpenStageResult();
			++m_curPhase;
		}
		break;
		//Result screen
	case (_int)ETwoStagePhase::StageResult:
		break;
	default:
		break;
	}
}


void CTwoStagePhaseControl::EnterConversationPhase(void)
{
	SP(Engine::CObject) spConversation = Engine::GET_CUR_SCENE->ADD_CLONE(L"EmptyObject", true, (_uint)ELayerID::Player, L"");
	spConversation->AddComponent<CTwoConversationC>();

	m_spConversation = spConversation->GetComponent<CTwoConversationC>();
}

void CTwoStagePhaseControl::OpenStageResult(void)
{
	//Engine::CInputManager::GetInstance()->SetKeyInputEnabled(false);
	
	CBattleUiManager::GetInstance()->BattleEnd();
}
