#include "stdafx.h"
#include "SickleAirbornePattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CSickleAirbornePattern::CSickleAirbornePattern()
{
}

CSickleAirbornePattern::~CSickleAirbornePattern()
{
}

void CSickleAirbornePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();

	// ���� break guage�� 0�̰�, airborne ����, standup ���°� �ƴ϶��
	if (Name_Sickle_Throw_01 != fsm->GetCurStateString() &&
		Name_Sickle_Throw_02 != fsm->GetCurStateString() &&
		Name_Sickle_StandUp != fsm->GetCurStateString() &&
		Name_Sickle_Hit_Throw != fsm->GetCurStateString() &&
		0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetbreakGauge())
	{
		fsm->ChangeState(Name_Sickle_Throw_01);
		//PatternPlaySound(L"Sickle_Dead.wav", pOwner);
	}
	// ���� Throw_01, Throw_02 ����, Hit_Throw �߿� ������ ������
	else if ((Name_Sickle_Throw_01 == fsm->GetCurStateString() ||
			  Name_Sickle_Throw_02 == fsm->GetCurStateString() ||
			  Name_Sickle_Hit_Throw == fsm->GetCurStateString()) &&
			 (pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
			  pOwner->GetComponent<CPatternMachineC>()->GetOnHitH()))
	{
		fsm->ChangeState(Name_Sickle_Hit_Throw);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Hit_Throw ���°� �����ٸ�
	else if (Name_Sickle_Hit_Throw == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Sickle_Throw_02);
	}
	// ���� Throw_01, Throw_02 ���°� ������
	else if ((Name_Sickle_Throw_01 == fsm->GetCurStateString() ||
		Name_Sickle_Throw_02 == fsm->GetCurStateString()) &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Sickle_StandUp);
	}
	// StandBy
	else if (Name_Sickle_StandUp == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Sickle_StandBy);
		pOwner->GetComponent<CPatternMachineC>()->SetOnAirBorne(false);
	}
}

SP(CSickleAirbornePattern) CSickleAirbornePattern::Create()
{
	SP(CSickleAirbornePattern) spInstance(new CSickleAirbornePattern, Engine::SmartDeleter<CSickleAirbornePattern>);

	return spInstance;
}