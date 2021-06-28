#include "stdafx.h"
#include "RobotDiePattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CRobotDiePattern::CRobotDiePattern()
{
}

CRobotDiePattern::~CRobotDiePattern()
{
}

void CRobotDiePattern::Pattern(Engine::CObject* pOwner)
{
// 	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();
// 
// 	// ���� hp�� 0�� �Ǹ�
// 	if (Name_Sickle_Die != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
// 	{
// 		fsm->ChangeState(Name_Sickle_Die);
// 		PatternPlaySound(L"Sickle_Dead.wav", pOwner);
// 	}
// 	// die �ִϰ� ������
// 	else if (Name_Sickle_Die == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
// 	{
// 		pOwner->SetDeleteThis(true);
// 	}
}

SP(CRobotDiePattern) CRobotDiePattern::Create()
{
	SP(CRobotDiePattern) spInstance(new CRobotDiePattern, Engine::SmartDeleter<CRobotDiePattern>);

	return spInstance;
}