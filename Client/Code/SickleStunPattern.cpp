#include "stdafx.h"
#include "SickleStunPattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

CSickleStunPattern::CSickleStunPattern()
{
}

CSickleStunPattern::~CSickleStunPattern()
{
}

void CSickleStunPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();

	// 내가 break guage가 0이고, airborne 상태, standup 상태가 아니라면
	if (Name_Sickle_Throw_01 != fsm->GetCurStateString() && // 에어본
		Name_Sickle_Throw_02 != fsm->GetCurStateString() && // 작은 에어본
		Name_Sickle_StandUp != fsm->GetCurStateString() &&
		Name_Sickle_Hit_Throw != fsm->GetCurStateString()) // 파닥파닥
	{
		fsm->ChangeState(Name_Sickle_Hit_H);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// 내가 Hit_Stun 상태가 끝났다면
	else if (Name_Sickle_Hit_H == fsm->GetCurStateString())
	{
		// Stun 상태로 변경
		fsm->ChangeState(Name_Sickle_Stun);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// 내가 Hit_Stun 상태가 끝났고, 시간이 다 되었다면
	//else if (Name_)
}

SP(CSickleStunPattern) CSickleStunPattern::Create()
{
	SP(CSickleStunPattern) spInstance(new CSickleStunPattern, Engine::SmartDeleter<CSickleStunPattern>);

	return spInstance;
}