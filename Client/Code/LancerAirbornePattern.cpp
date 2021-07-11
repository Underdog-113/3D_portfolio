#include "stdafx.h"
#include "LancerAirbornePattern.h"

#include "FSM_LancerC.h"
#include "FSMDefine_Lancer.h"
#include "MO_Lancer.h"

CLancerAirbornePattern::CLancerAirbornePattern()
{
}

CLancerAirbornePattern::~CLancerAirbornePattern()
{
}

void CLancerAirbornePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_LancerC) fsm = pOwner->GetComponent<CFSM_LancerC>();

	// ���� break guage�� 0�̰�, airborne ����, standup ���°� �ƴ϶��
	if (Name_THROW_1 != fsm->GetCurStateString() &&
		/*Name_THROW_2 != fsm->GetCurStateString() &&*/
		/*Name_STAND_UP != fsm->GetCurStateString() &&*/
		Name_THROW_LOW != fsm->GetCurStateString())
	{
		fsm->ChangeState(Name_THROW_1);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Throw_01, Throw_02 ����, Hit_Throw �߿� ������ ������
	else if ((Name_THROW_1 == fsm->GetCurStateString() ||
			  /*Name_THROW_2 == fsm->GetCurStateString() ||*/
			  Name_THROW_LOW == fsm->GetCurStateString()) &&
			 (pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
			  pOwner->GetComponent<CPatternMachineC>()->GetOnHitH()))
	{
		fsm->ChangeState(Name_THROW_LOW);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Hit_Throw ���°� �����ٸ�
	else if (Name_THROW_LOW == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_STAND_UP);
	}
	// ���� Throw_01, Throw_02 ���°� ������
	//else if ((Name_THROW_1 == fsm->GetCurStateString() ||
	//	Name_THROW_2 == fsm->GetCurStateString()) &&
	//	fsm->GetDM()->IsAnimationEnd())
	//{
	//	fsm->ChangeState(Name_STAND_UP);
	//}
	// StandBy
	else if ((Name_THROW_1 == fsm->GetCurStateString() ||
		Name_STAND_UP == fsm->GetCurStateString()) &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_STAND);
		pOwner->GetComponent<CPatternMachineC>()->SetOnAirBorne(false);
	}
}

SP(CLancerAirbornePattern) CLancerAirbornePattern::Create()
{
	SP(CLancerAirbornePattern) spInstance(new CLancerAirbornePattern, Engine::SmartDeleter<CLancerAirbornePattern>);

	return spInstance;
}