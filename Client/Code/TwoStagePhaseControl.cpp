#include "stdafx.h"
#include "TwoStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"

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

	case (_int)ETwoStagePhase::PlayerSummon:
		if (m_pCT->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->CompareState(L"Appear") == false)
			++m_curPhase;
		break;

		//Before being collided with PhaseChanger0
	case (_int)ETwoStagePhase::BeforeFirstFight:
		break;

		//After being collided with PhaseChanger0
	case (_int)ETwoStagePhase::FirstFightBegin:
		break;

		//After killing all the enemies
	case (_int)ETwoStagePhase::FirstFightEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger1
	case (_int)ETwoStagePhase::BeforeSecondFight:
		break;

		//After being collided with PhaseChanger1
	case (_int)ETwoStagePhase::SecondFightBegin:
		break;

		//After killing all the enemies
	case (_int)ETwoStagePhase::SecondFightEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger2
	case (_int)ETwoStagePhase::BeforeMidBoss:
		break;

		//After being collided with PhaseChanger2
	case (_int)ETwoStagePhase::MidBossBegin:
		break;

		//After killing MidBoss
	case (_int)ETwoStagePhase::MidBossEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger3
	case (_int)ETwoStagePhase::BeforeBoss:
		break;

		//After being collided with PhaseChanger3
	case (_int)ETwoStagePhase::BossBegin:
		break;

		//After killing Boss
	case (_int)ETwoStagePhase::BossEnd:
		++m_curPhase;
		break;

		//Result screen
	case (_int)ETwoStagePhase::StageResult:
		++m_curPhase;
		OpenStageResult();
		break;

		// Wait Change Scene
	case (_int)ETwoStagePhase::StageResult_Idle:
		break;
	default:
		break;
	}
}


void CTwoStagePhaseControl::OpenStageResult(void)
{
	Engine::CInputManager::GetInstance()->SetKeyInputEnabled(false);

	CStageControlTower::GetInstance()->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Victory");
	CBattleUiManager::GetInstance()->BattleEnd();
	Engine::CCameraManager::GetInstance()->ChangeCameraMode(Engine::ECameraMode::Edit);
}
