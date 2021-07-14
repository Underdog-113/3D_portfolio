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

	// ���� break guage�� 0�̰�
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		false == m_onStun)
	{
		// ������� �޾�����
		if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
		{
			fsm->ChangeState(Name_Weak_Start_L);
		}
		// �������� �޾�����
		else if (true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
		{
			fsm->ChangeState(Name_Weak_Start_H);
		}
		
		m_onStun = true;
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Weak_Start ���°� �����ٸ�
	else if ((Name_Weak_Start_L == fsm->GetCurStateString() ||
		Name_Weak_Start_H == fsm->GetCurStateString()) &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_onStun)
	{
		fsm->ChangeState(Name_Weak);
	}
	// ���� Weak ���°� ������, �ð��� �����ٸ�
	else if (Name_Weak == fsm->GetCurStateString() &&
		true == m_timeEnd)
	{
		// idle ���·� ����
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);
	}
}

SP(CBronyaStunPattern) CBronyaStunPattern::Create()
{
	SP(CBronyaStunPattern) spInstance(new CBronyaStunPattern, Engine::SmartDeleter<CBronyaStunPattern>);

	return spInstance;
}