#include "stdafx.h"
#include "OneStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"

COneStagePhaseControl::COneStagePhaseControl()
{
}


COneStagePhaseControl::~COneStagePhaseControl()
{
}

void COneStagePhaseControl::Update(void)
{
	switch (m_curPhase)
	{
	case UNDEFINED:
		++m_curPhase;
		break;

	case (_int)EOneStagePhase::PlayerSummon:
		if (m_pCT->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->CompareState(L"Appear") == false)
			++m_curPhase;
		break;

		//Before being collided with PhaseChanger0
	case (_int)EOneStagePhase::BeforeFirstFight:
		break;

		//After being collided with PhaseChanger0
	case (_int)EOneStagePhase::FirstFightBegin:
		break;

		//After killing all the enemies
	case (_int)EOneStagePhase::FirstFightEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger1
	case (_int)EOneStagePhase::BeforeSecondFight:
		break;

		//After being collided with PhaseChanger1
	case (_int)EOneStagePhase::SecondFightBegin:
		break;

		//After killing all the enemies
	case (_int)EOneStagePhase::SecondFightEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger2
	case (_int)EOneStagePhase::BeforeMidBoss:
		break;

		//After being collided with PhaseChanger2
	case (_int)EOneStagePhase::MidBossBegin:
		break;

		//After killing MidBoss
	case (_int)EOneStagePhase::MidBossEnd:
		++m_curPhase;
		break;

		//Before being collised with PhaseChanger3
	case (_int)EOneStagePhase::BeforeBoss:
		break;

		//After being collided with PhaseChanger3
	case (_int)EOneStagePhase::BossBegin:
		break;

		//After killing Boss
	case (_int)EOneStagePhase::BossEnd:
		++m_curPhase;
		break;
		//Result screen
	case (_int)EOneStagePhase::StageResult:
		++m_curPhase;
		OpenStageResult();
		break;
		// Wait Change Scene
	case (_int)EOneStagePhase::StageResult_Idle:
		break;
	default:
		break;
	}
}


void COneStagePhaseControl::OpenStageResult(void)
{
	uint64_t ssss = StageKey_AllOut;
	uint64_t keyyy = StageKey_Move_Left;
	uint64_t keyyyaa = KEY_A;
	uint64_t keyyyaasdfbbba = 0;
	int zerrrr = 0;
	uint64_t keyyyabbba = zerrrr;

	StageKeyAllOut(true)
	
	uint64_t keyyyyy = StageKey_Move_Left;

	CStageControlTower::GetInstance()->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Victory");
	CBattleUiManager::GetInstance()->BattleEnd();
	Engine::CCameraManager::GetInstance()->ChangeCameraMode(Engine::ECameraMode::Edit);
}
