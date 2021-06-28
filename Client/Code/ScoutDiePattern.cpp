#include "stdafx.h"
#include "ScoutDiePattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CScoutDiePattern::CScoutDiePattern()
{
}

CScoutDiePattern::~CScoutDiePattern()
{
}

void CScoutDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	// ���� hp�� 0�� �Ǹ�
	if (Name_DIE != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		fsm->ChangeState(Name_DIE);
		PatternPlaySound(L"Scout_Dead.wav", pOwner);
	}
	// die �ִϰ� ������
	else if (Name_DIE == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
	{
		pOwner->SetDeleteThis(true);
	}
}

SP(CScoutDiePattern) CScoutDiePattern::Create()
{
	SP(CScoutDiePattern) spInstance(new CScoutDiePattern, Engine::SmartDeleter<CScoutDiePattern>);

	return spInstance;
}