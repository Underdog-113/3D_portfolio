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
			m_onStun = false;
			std::cout << "Time over" << std::endl;
		}
	}



	// 내가 break guage가 0이고 stun 상태가 아직 시작 하지 않았다면
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		false == m_onStun &&
		false == m_timeEnd)
	{
		// 약 공격을 받았다면
		if (pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
		{
			fsm->ChangeState(Name_Weak_Start_L);
			pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		}
		// 강 공격을 받았다면
		else if (pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
		{
			fsm->ChangeState(Name_Weak_Start_H);
			pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
		}

		std::cout << "Weak_Start" << std::endl;
		m_onStun = true;
		static_cast<CMB_Bronya*>(pOwner)->GetStat()->SetOnBPShield(true);

		return;
	}
	// stun 시간이 끝났다면
	else if (true == m_timeEnd &&
			 false == m_onStun &&
			 fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태 변경, stun 상태 종료
		fsm->ChangeState(Name_IDLE);
		std::cout << "Weak_IDLE" << std::endl;
		m_timeEnd = false;
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);
		static_cast<CMB_Bronya*>(pOwner)->GetStat()->SetOnBPShield(false);

		return;
	}
	// Weak_Start 상태가 끝났다면
	else if (Name_Weak_Start_L == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// Weak_Loop 상태로 변경
		fsm->ChangeState(Name_Weak);
		std::cout << "Weak_Loop" << std::endl;

		return;
	}

	// Weak_Hit 에서 Weak_Loop 상태로 변경
	if ((Name_Weak_Hit_L == fsm->GetCurStateString() ||
		 Name_Weak_Hit_H == fsm->GetCurStateString()) &&
		 fsm->GetDM()->IsAnimationEnd())	
	{
		fsm->ChangeState(Name_Weak);
		std::cout << "Weak_Loop" << std::endl;

		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// 공격을 받았으면
	else if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
			 true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
	{
		// 내가 Weak_Hit 또는 Weak_Loop 상태라면
		if ((Name_Weak_Hit_L == fsm->GetCurStateString() || 
			 Name_Weak_Hit_H == fsm->GetCurStateString()) &&
			 Name_Weak == fsm->GetCurStateString())
		{
			// 약 공격을 받았다면
			if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
			{
				fsm->ChangeState(Name_Weak_Hit_L);
			}
			// 강 공격을 받았다면
			else if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
			{
				fsm->ChangeState(Name_Weak_Hit_H);
			}
			std::cout << "Weak_Hit" << std::endl;
		}
	}
}

SP(CBronyaStunPattern) CBronyaStunPattern::Create()
{
	SP(CBronyaStunPattern) spInstance(new CBronyaStunPattern, Engine::SmartDeleter<CBronyaStunPattern>);

	return spInstance;
}