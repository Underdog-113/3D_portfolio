#include "stdafx.h"
#include "TwoStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"
#include "MovieDirector.h"

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
	case (_int)ETwoStagePhase::BeforeBoss:
		break;

		//After being collided with PhaseChanger0
	case (_int)ETwoStagePhase::BossBegin:
		if (false == m_isSoundChange)
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->PlayBGM(L"GaneShaBGM_2.mp3");
			Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
			m_isSoundChange = true;

			// movie
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_GaneshBorn();
		}
		break;

		//After killing Boss
	case (_int)ETwoStagePhase::BossEnd:
		m_isSoundChange = false;
		++m_curPhase;
		break;

		//Result screen
	case (_int)ETwoStagePhase::StageResult:
		++m_curPhase;
		OpenStageResult();
		break;

		// Wait Change Scene
	case (_int)ETwoStagePhase::StageResult_Idle:
		if (false == m_isSoundChange)
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->StartSound(L"Victory.mp3", (_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
			m_isSoundChange = true;
		}
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
	Engine::CInputManager::GetInstance()->SetKeyInputEnabled(false);

	CStageControlTower::GetInstance()->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Victory");
	CBattleUiManager::GetInstance()->BattleEnd();
	Engine::CCameraManager::GetInstance()->ChangeCameraMode(Engine::ECameraMode::Edit);
	ShowCursor(true);
}
