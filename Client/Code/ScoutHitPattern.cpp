#include "stdafx.h"
#include "ScoutHitPattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

CScoutHitPattern::CScoutHitPattern()
{
}

CScoutHitPattern::~CScoutHitPattern()
{
}

void CScoutHitPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();
	static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBall();

	// ���� ���ǰ� ���ߴٸ�
	if (Name_HIT_L != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
	{
		fsm->ChangeState(Name_HIT_L);
	}
	else if (Name_HIT_L == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
	}
	// ���� ���ǰ� ���ߴٸ�
	if (Name_HIT_H != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
	{
		fsm->ChangeState(Name_HIT_H);
	}
	else if (Name_HIT_H == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� hit_front ���ߴٸ�
	if (Name_HIT_FRONT != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitFront())
	{
		fsm->ChangeState(Name_HIT_FRONT);
	}
	else if (Name_HIT_FRONT == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitFront(false);
	}
	// ���� hit_back ���ߴٸ�
	if (Name_HIT_BACK != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitBack())
	{
		fsm->ChangeState(Name_HIT_BACK);
	}
	else if (Name_HIT_BACK == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitBack(false);
	}

	//// ���� hit_back ���ߴٸ�
	//if (Name_HIT_FRONT != fsm->GetCurStateString() &&
	//	Name_IDLE != fsm->GetCurStateString() &&
	//	true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitFront())
	//{
	//	fsm->ChangeState(Name_Sickle_Hit_Front);
	//}
	//else if (Name_Sickle_Hit_Front == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	//{
	//	fsm->ChangeState(Name_Sickle_StandUp);
	//}
	//else if (Name_Sickle_StandUp == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	//{
	//	fsm->ChangeState(Name_Sickle_StandBy);
	//	pOwner->GetComponent<CPatternMachineC>()->SetOnHitFront(false);
	//}
}

SP(CScoutHitPattern) CScoutHitPattern::Create()
{
	SP(CScoutHitPattern) spInstance(new CScoutHitPattern, Engine::SmartDeleter<CScoutHitPattern>);

	return spInstance;
}