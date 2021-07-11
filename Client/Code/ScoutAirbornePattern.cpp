#include "stdafx.h"
#include "ScoutAirbornePattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CScoutAirbornePattern::CScoutAirbornePattern()
{
}

CScoutAirbornePattern::~CScoutAirbornePattern()
{
}

void CScoutAirbornePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	// ���� break guage�� 0�̰�, airborne ����, standup ���°� �ƴ϶��
	if (Name_Throw_1 != fsm->GetCurStateString() &&
		Name_Throw_2 != fsm->GetCurStateString() &&
		Name_StandUp != fsm->GetCurStateString() &&
		Name_Throw_0 != fsm->GetCurStateString())
	{
		fsm->ChangeState(Name_Throw_1);
		//PatternPlaySound(L"Sickle_Dead.wav", pOwner);
	}
	// ���� Throw_01, Throw_02 ����, Hit_Throw �߿� ������ ������
	else if ((Name_Throw_1 == fsm->GetCurStateString() ||
			  Name_Throw_2 == fsm->GetCurStateString() ||
			  Name_Throw_0 == fsm->GetCurStateString()) &&
			 (pOwner->GetComponent<CPatternMachineC>()->GetOnHitL() ||
			  pOwner->GetComponent<CPatternMachineC>()->GetOnHitH()))
	{
		fsm->ChangeState(Name_Throw_0);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
	}
	// ���� Hit_Throw ���°� �����ٸ�
	else if (Name_Throw_0 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Throw_2);
	}
	// ���� Throw_01, Throw_02 ���°� ������
	else if ((Name_Throw_1 == fsm->GetCurStateString() ||
		Name_Throw_2 == fsm->GetCurStateString()) &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_StandUp);
	}
	// StandBy
	else if (Name_StandUp == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnAirBorne(false);
	}
}

SP(CScoutAirbornePattern) CScoutAirbornePattern::Create()
{
	SP(CScoutAirbornePattern) spInstance(new CScoutAirbornePattern, Engine::SmartDeleter<CScoutAirbornePattern>);

	return spInstance;
}