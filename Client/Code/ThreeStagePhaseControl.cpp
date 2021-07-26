#include "stdafx.h"
#include "ThreeStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"

#include "Portal.h"
#include "StageCameraMan.h"
#include "MovieDirector.h"

CThreeStagePhaseControl::CThreeStagePhaseControl()
{
}


CThreeStagePhaseControl::~CThreeStagePhaseControl()
{
}

void CThreeStagePhaseControl::Update(void)
{
	switch (m_curPhase)
	{
	case UNDEFINED:
		++m_curPhase;
		break;

		
	case (_int)EThreeStagePhase::PlayerSummon:
		if (m_pCT->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->CompareState(L"Appear") == false)
			++m_curPhase;
		break;

		//Before being collided with PhaseChanger0
	case (_int)EThreeStagePhase::BeforeFirstFight:
		break;

		//After being collided with PhaseChanger0
	case (_int)EThreeStagePhase::FirstFightBegin:
		break;

		//After killing all the enemies
// 	case (_int)EThreeStagePhase::FirstFightEnd:
// 		++m_curPhase;
// 		break;

		//Before being collised with PhaseChanger1
	case (_int)EThreeStagePhase::BeforeSecondFight:
		break;

	case (_int)EThreeStagePhase::GotoSecondFloor:
		if (!m_portalEnter)
		{
			CStageControlTower::GetInstance()->SetDirectorMode(true);
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_BlackFadeOut();
			m_portalEnter = true;
		}

		if (!m_portalEnd)
		{
			m_warpTimer += GET_DT;
			if (m_warpTimer > 0.5f)
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
				}
			}

			if (m_warpTimer > 1.1f)
			{
				m_portalEnd = true;
				CStageControlTower::GetInstance()->SetDirectorMode(false);
			}
		}
		break;

		//After being collided with PhaseChanger1
	case (_int)EThreeStagePhase::SecondFightBegin:
		
		break;

		//After killing all the enemies
	case (_int)EThreeStagePhase::SecondFightEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger2
	case (_int)EThreeStagePhase::BeforeThirdFight:
		break;

		//After being collided with PhaseChanger2
	case (_int)EThreeStagePhase::ThirdFightBegin:
		break;

		//After killing MidBoss
// 	case (_int)EThreeStagePhase::ThirdFightEnd:
// 		++m_curPhase;
// 		break;

		//Before being collised with PhaseChanger3
	case (_int)EThreeStagePhase::BeforeBoss:
		break;
	case (_int)EThreeStagePhase::WarningAlarm:
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

		//After being collided with PhaseChanger3
	case (_int)EThreeStagePhase::BossBegin:
		break;

		//After killing Boss
	case (_int)EThreeStagePhase::BossEnd:
		++m_curPhase;
		break;

		//Result screen
	case (_int)EThreeStagePhase::WinningSlow:
		if (!CStageControlTower::GetInstance()->GetMovieDirector()->GetIsOnAir())
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			m_victoryTimer = 0.f;
			++m_curPhase;
		}
		break;
	case (_int)EThreeStagePhase::WaitVictoryMovie:
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
	case (_int)EThreeStagePhase::VictoryMovie:
		m_victoryTimer += GET_DT;
		if (m_victoryTimer > 4.f)
		{
			OpenStageResult();
			++m_curPhase;
		}
		break;
	default:
		break;
	}
}


void CThreeStagePhaseControl::OpenStageResult(void)
{
	CBattleUiManager::GetInstance()->BattleEnd();
}
