#include "stdafx.h"
#include "BronyaStunPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

CBronyaStunPattern::CBronyaStunPattern()
{
}

CBronyaStunPattern::~CBronyaStunPattern()
{
}

void CBronyaStunPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	if (true == m_onStun)
	{
		m_accTime += GET_DT;

		if (m_accTime >= m_stunTime)
		{
			m_accTime = 0.f;
			m_timeEnd = true;
		}
	}

	// 내가 break guage가 0이고
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		false == m_onStun)
	{
		// 약공격을 받았으면
		if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
		{
			fsm->ChangeState(Name_Weak_Start_L);
		}
		// 강공격을 받았으면
		else if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
		{
			fsm->ChangeState(Name_Weak_Start_H);
		}
		
		m_onStun = true;
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// 내가 Weak_Start 상태가 끝났다면
	else if ((Name_Weak_Start_L == fsm->GetCurStateString() ||
		Name_Weak_Start_H == fsm->GetCurStateString()) &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_onStun)
	{
		fsm->ChangeState(Name_Weak);
	}
	// 내가 Weak 상태가 끝나고, 시간도 끝났다면
	else if (Name_Weak == fsm->GetCurStateString() &&
		true == m_timeEnd)
	{
		// idle 상태로 변경
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);
	}
}

SP(CBronyaStunPattern) CBronyaStunPattern::Create()
{
	SP(CBronyaStunPattern) spInstance(new CBronyaStunPattern, Engine::SmartDeleter<CBronyaStunPattern>);

	return spInstance;
}