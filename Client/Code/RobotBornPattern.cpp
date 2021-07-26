#include "stdafx.h"
#include "RobotBornPattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CRobotBornPattern::CRobotBornPattern()
{
}

CRobotBornPattern::~CRobotBornPattern()
{
}

void CRobotBornPattern::Pattern(Engine::CObject* pOwner)
{
 	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();
 
 	// 내가 born 상태이고, 애니가 끝났다면
 	if (Name_StandBy == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
 	{
 		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
 		fsm->ChangeState(Name_StandBy);
 	}
}

SP(CRobotBornPattern) CRobotBornPattern::Create()
{
	SP(CRobotBornPattern) spInstance(new CRobotBornPattern, Engine::SmartDeleter<CRobotBornPattern>);

	return spInstance;
}