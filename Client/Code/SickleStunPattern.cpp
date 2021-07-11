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

	// ���� break guage�� 0�̰�, airborne ����, standup ���°� �ƴ϶��
	if (Name_Sickle_Throw_01 != fsm->GetCurStateString() && // ���
		Name_Sickle_Throw_02 != fsm->GetCurStateString() && // ���� ���
		Name_Sickle_StandUp != fsm->GetCurStateString() &&
		Name_Sickle_Hit_Throw != fsm->GetCurStateString()) // �Ĵ��Ĵ�
	{
		fsm->ChangeState(Name_Sickle_Hit_H);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Hit_Stun ���°� �����ٸ�
	else if (Name_Sickle_Hit_H == fsm->GetCurStateString())
	{
		// Stun ���·� ����
		fsm->ChangeState(Name_Sickle_Stun);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Hit_Stun ���°� ������, �ð��� �� �Ǿ��ٸ�
	//else if (Name_)
}

SP(CSickleStunPattern) CSickleStunPattern::Create()
{
	SP(CSickleStunPattern) spInstance(new CSickleStunPattern, Engine::SmartDeleter<CSickleStunPattern>);

	return spInstance;
}