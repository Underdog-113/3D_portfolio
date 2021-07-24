#include "stdafx.h"
#include "GaneshaStunPattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

CGaneshaStunPattern::CGaneshaStunPattern()
{
}

CGaneshaStunPattern::~CGaneshaStunPattern()
{
}

void CGaneshaStunPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	if (true == m_onStun)
	{
		m_accTime += GET_DT;

		if (m_accTime >= m_stunTime)
		{
			m_accTime = 0.f;
			m_timeEnd = true;
			m_onStun = false;
		}
	}

	// 내가 break guage가 0이고 stun 상태가 아직 시작 하지 않았다면
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		false == m_onStun &&
		false == m_timeEnd)
	{
		// Weak 상태가 아니라면 Weak 상태 시작
		if (Name_Ganesha_Weak_Start != fsm->GetCurStateString() &&
			Name_Ganesha_Weak_End != fsm->GetCurStateString() &&
			Name_Ganesha_Weak_Loop != fsm->GetCurStateString() &&
			Name_Ganesha_Weak_Start != fsm->GetCurStateString())
		{
			fsm->ChangeState(Name_Ganesha_Weak_Start);
			std::cout << "Weak_Start" << std::endl;

			m_onStun = true;
			pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
			pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
			return;
		}
	}
	// stun 시간이 끝났다면
	else if (Name_Ganesha_Weak_End != fsm->GetCurStateString() &&
		true == m_timeEnd &&
		false == m_onStun)
	{
		// Weak_End 상태로 변경
		fsm->ChangeState(Name_Ganesha_Weak_End);
		std::cout << "Weak_End" << std::endl;

		return;
	}
	// Weak_End 상태가 끝났다면
	else if (Name_Ganesha_Weak_End == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태 변경, stun 상태 종료
		fsm->ChangeState(Name_Ganesha_StandBy);
		std::cout << "Weak_StandBy" << std::endl;
		m_timeEnd = false;
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);

		return;
	}
	// Weak_Start 상태가 끝났다면
	else if (Name_Ganesha_Weak_Start == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// Weak_Loop 상태로 변경
		fsm->ChangeState(Name_Ganesha_Weak_Loop);
		std::cout << "Weak_Loop" << std::endl;

		return;
	}

	// 공격을 받았으면
	if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
	{
		// 내가 Weak_Hit 또는 Weak_Loop 상태라면
		if (Name_Ganesha_Weak_Hit == fsm->GetCurStateString() ||
			Name_Ganesha_Weak_Loop == fsm->GetCurStateString())

		{
			fsm->ChangeState(Name_Ganesha_Weak_Hit);
			std::cout << "Weak_Hit" << std::endl;
		}
	}
}

SP(CGaneshaStunPattern) CGaneshaStunPattern::Create()
{
	SP(CGaneshaStunPattern) spInstance(new CGaneshaStunPattern, Engine::SmartDeleter<CGaneshaStunPattern>);

	return spInstance;
}