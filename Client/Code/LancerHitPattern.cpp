#include "stdafx.h"
#include "LancerHitPattern.h"

#include "FSM_LancerC.h"
#include "FSMDefine_Lancer.h"
#include "MO_Lancer.h"

CLancerHitPattern::CLancerHitPattern()
{
}

CLancerHitPattern::~CLancerHitPattern()
{
}

void CLancerHitPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_LancerC) fsm = pOwner->GetComponent<CFSM_LancerC>();
	
	static_cast<CMO_Lancer*>(pOwner)->UnActiveAttackBall();

	// 내가 약피격 당했다면
	if (Name_HIT_L != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
	{
		fsm->ChangeState(Name_HIT_L);
		PatternPlaySound(L"Lencer_Hit.wav", pOwner);
	}
	else if (Name_HIT_L == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_STAND);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
	}
	// 내가 강피격 당했다면
	if (Name_HIT_H != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
	{
		fsm->ChangeState(Name_HIT_H);
		PatternPlaySound(L"Lencer_Hit.wav", pOwner);
	}
	else if (Name_HIT_H == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_STAND);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
}

SP(CLancerHitPattern) CLancerHitPattern::Create()
{
	SP(CLancerHitPattern) spInstance(new CLancerHitPattern, Engine::SmartDeleter<CLancerHitPattern>);

	return spInstance;
}