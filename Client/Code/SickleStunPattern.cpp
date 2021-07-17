#include "stdafx.h"
#include "SickleStunPattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "AniCtrl.h"

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

	// ���� break guage�� 0�̰�, stun ���°� �ƴϰ�, ���� �ִϰ� �����ٸ�
	if (0.f >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurBreakGauge() &&
		Name_Sickle_Stun != fsm->GetCurStateString() &&
		true == fsm->GetDM()->IsAnimationEnd())
	{
		// ���� ���·� ����
		//fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		fsm->ChangeState(Name_Sickle_Stun);
		m_onStun = true;

		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Stun ���°� ������, �ð��� �� �Ǿ��ٸ�
	else if (Name_Sickle_Stun == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onStun)
	{
		// standby ���·� ����
		fsm->ChangeState(Name_Sickle_StandBy);
		m_initAniSpd = false;
		pOwner->GetComponent<CPatternMachineC>()->SetOnStun(false);
	}
 }

SP(CSickleStunPattern) CSickleStunPattern::Create()
{
	SP(CSickleStunPattern) spInstance(new CSickleStunPattern, Engine::SmartDeleter<CSickleStunPattern>);

	return spInstance;
}