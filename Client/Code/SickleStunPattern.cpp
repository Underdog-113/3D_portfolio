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

	if (true == m_onStun)
	{
		m_accTime += GET_DT;

		if (m_accTime >= m_stunTime)
		{
			m_accTime = 0.f;
			m_onStun = false;
		}
	}

	// 내가 break guage가 0이고, airborne 상태, standup 상태가 아니라면
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		Name_Sickle_StandBy != fsm->GetCurStateString() &&
		Name_Sickle_Stun != fsm->GetCurStateString())
	{
		fsm->ChangeState(Name_Sickle_Stun);
		m_onStun = true;
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	//// 내가 Hit_Stun 상태가 끝났다면
	//else if (Name_Sickle_Hit_H == fsm->GetCurStateString())
	//{
	//	// Stun 상태로 변경
	//	fsm->ChangeState(Name_Sickle_Stun);
	//	m_onStun = true;
	//	pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
	//	pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	//}
	// 내가 Stun 상태가 끝났고, 시간이 다 되었다면
	else if (Name_Sickle_Stun == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onStun)
	{
		// standby 상태로 변경
		fsm->ChangeState(Name_Sickle_StandBy);
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);
	}
}

SP(CSickleStunPattern) CSickleStunPattern::Create()
{
	SP(CSickleStunPattern) spInstance(new CSickleStunPattern, Engine::SmartDeleter<CSickleStunPattern>);

	return spInstance;
}