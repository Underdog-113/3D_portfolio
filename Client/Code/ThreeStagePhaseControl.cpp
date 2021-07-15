#include "stdafx.h"
#include "ThreeStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"

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
	case (_int)EThreeStagePhase::FirstFightEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger1
	case (_int)EThreeStagePhase::BeforeSecondFight:
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
	case (_int)EThreeStagePhase::ThirdFightEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger3
	case (_int)EThreeStagePhase::BeforeBoss:
		break;

		//After being collided with PhaseChanger3
	case (_int)EThreeStagePhase::BossBegin:
		break;

		//After killing Boss
	case (_int)EThreeStagePhase::BossEnd:
		++m_curPhase;
		break;

		//Result screen
	case (_int)EThreeStagePhase::StageResult:
		++m_curPhase;
		OpenStageResult();
		break;

		// Wait Change Scene
	case (_int)EThreeStagePhase::StageResult_Idle:
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


void CThreeStagePhaseControl::OpenStageResult(void)
{
	Engine::CInputManager::GetInstance()->SetKeyInputEnabled(false);

	CStageControlTower::GetInstance()->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Victory");
	CBattleUiManager::GetInstance()->BattleEnd();
	Engine::CCameraManager::GetInstance()->ChangeCameraMode(Engine::ECameraMode::Edit);
	ShowCursor(true);
}
