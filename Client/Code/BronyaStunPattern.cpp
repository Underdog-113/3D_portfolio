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



	// ���� break guage�� 0�̰� stun ���°� ���� ���� ���� �ʾҴٸ�
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		false == m_onStun &&
		false == m_timeEnd)
	{
		// �� ������ �޾Ҵٸ�
		if (pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
		{
			fsm->ChangeState(Name_Weak_Start_L);
			pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		}
		// �� ������ �޾Ҵٸ�
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
	// stun �ð��� �����ٸ�
	else if (true == m_timeEnd &&
			 false == m_onStun &&
			 fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���� ����, stun ���� ����
		fsm->ChangeState(Name_IDLE);
		std::cout << "Weak_IDLE" << std::endl;
		m_timeEnd = false;
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);
		static_cast<CMB_Bronya*>(pOwner)->GetStat()->SetOnBPShield(false);

		return;
	}
	// Weak_Start ���°� �����ٸ�
	else if (Name_Weak_Start_L == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// Weak_Loop ���·� ����
		fsm->ChangeState(Name_Weak);
		std::cout << "Weak_Loop" << std::endl;

		return;
	}

	// Weak_Hit ���� Weak_Loop ���·� ����
	if ((Name_Weak_Hit_L == fsm->GetCurStateString() ||
		 Name_Weak_Hit_H == fsm->GetCurStateString()) &&
		 fsm->GetDM()->IsAnimationEnd())	
	{
		fsm->ChangeState(Name_Weak);
		std::cout << "Weak_Loop" << std::endl;

		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ������ �޾�����
	else if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
			 true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
	{
		// ���� Weak_Hit �Ǵ� Weak_Loop ���¶��
		if ((Name_Weak_Hit_L == fsm->GetCurStateString() || 
			 Name_Weak_Hit_H == fsm->GetCurStateString()) &&
			 Name_Weak == fsm->GetCurStateString())
		{
			// �� ������ �޾Ҵٸ�
			if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
			{
				fsm->ChangeState(Name_Weak_Hit_L);
			}
			// �� ������ �޾Ҵٸ�
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