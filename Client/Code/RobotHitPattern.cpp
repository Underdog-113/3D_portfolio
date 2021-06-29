#include "stdafx.h"
#include "RobotHitPattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"
#include "AniCtrl.h"

CRobotHitPattern::CRobotHitPattern()
{
}

CRobotHitPattern::~CRobotHitPattern()
{
}

void CRobotHitPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	// 내가 약피격 당했다면
	if (Name_Hit_L_1 != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
	{
		fsm->ChangeState(Name_Hit_L_1);
	}
	else if (Name_Hit_L_1 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_StandBy);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
	}

	// 내가 강피격 당했다면
	if (Name_Hit_H != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
	{
		fsm->ChangeState(Name_Hit_H);
	}
	else if (Name_Hit_H == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_StandBy);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
}

SP(CRobotHitPattern) CRobotHitPattern::Create()
{
	SP(CRobotHitPattern) spInstance(new CRobotHitPattern, Engine::SmartDeleter<CRobotHitPattern>);

	return spInstance;
}