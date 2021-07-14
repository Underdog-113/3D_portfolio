#include "stdafx.h"
#include "LancerAirbornePattern.h"

#include "FSM_LancerC.h"
#include "FSMDefine_Lancer.h"
#include "MO_Lancer.h"

CLancerAirbornePattern::CLancerAirbornePattern()
{
}

CLancerAirbornePattern::~CLancerAirbornePattern()
{
}

void CLancerAirbornePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_LancerC) fsm = pOwner->GetComponent<CFSM_LancerC>();

	// 내가 break guage가 0이고, airborne 상태, standup 상태가 아니라면
	if (Name_THROW_1 != fsm->GetCurStateString() &&
		/*Name_THROW_2 != fsm->GetCurStateString() &&*/
		/*Name_STAND_UP != fsm->GetCurStateString() &&*/
		Name_THROW_LOW != fsm->GetCurStateString())
	{
		fsm->ChangeState(Name_THROW_1);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// 내가 Throw_01, Throw_02 상태, Hit_Throw 중에 공격을 받으면
	else if ((Name_THROW_1 == fsm->GetCurStateString() ||
			  /*Name_THROW_2 == fsm->GetCurStateString() ||*/
			  Name_THROW_LOW == fsm->GetCurStateString()) &&
			 (pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
			  pOwner->GetComponent<CPatternMachineC>()->GetOnHitH()))
	{
		fsm->ChangeState(Name_THROW_LOW);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// 내가 Hit_Throw 상태가 끝났다면
	else if (Name_THROW_LOW == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_STAND_UP);
	}
	// 내가 Throw_01, Throw_02 상태가 끝나면
	//else if ((Name_THROW_1 == fsm->GetCurStateString() ||
	//	Name_THROW_2 == fsm->GetCurStateString()) &&
	//	fsm->GetDM()->IsAnimationEnd())
	//{
	//	fsm->ChangeState(Name_STAND_UP);
	//}
	// StandBy
	else if ((Name_THROW_1 == fsm->GetCurStateString() ||
		Name_STAND_UP == fsm->GetCurStateString()) &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_STAND);
		pOwner->GetComponent<CPatternMachineC>()->SetOnAirBorne(false);
	}
}

SP(CLancerAirbornePattern) CLancerAirbornePattern::Create()
{
	SP(CLancerAirbornePattern) spInstance(new CLancerAirbornePattern, Engine::SmartDeleter<CLancerAirbornePattern>);

	return spInstance;
}