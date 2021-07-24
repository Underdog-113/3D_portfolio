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

	// ���� break guage�� 0�̰� stun ���°� ���� ���� ���� �ʾҴٸ�
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		false == m_onStun &&
		false == m_timeEnd)
	{
		// Weak ���°� �ƴ϶�� Weak ���� ����
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
	// stun �ð��� �����ٸ�
	else if (Name_Ganesha_Weak_End != fsm->GetCurStateString() &&
		true == m_timeEnd &&
		false == m_onStun)
	{
		// Weak_End ���·� ����
		fsm->ChangeState(Name_Ganesha_Weak_End);
		std::cout << "Weak_End" << std::endl;

		return;
	}
	// Weak_End ���°� �����ٸ�
	else if (Name_Ganesha_Weak_End == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���� ����, stun ���� ����
		fsm->ChangeState(Name_Ganesha_StandBy);
		std::cout << "Weak_StandBy" << std::endl;
		m_timeEnd = false;
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);

		return;
	}
	// Weak_Start ���°� �����ٸ�
	else if (Name_Ganesha_Weak_Start == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// Weak_Loop ���·� ����
		fsm->ChangeState(Name_Ganesha_Weak_Loop);
		std::cout << "Weak_Loop" << std::endl;

		return;
	}

	// ������ �޾�����
	if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
	{
		// ���� Weak_Hit �Ǵ� Weak_Loop ���¶��
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