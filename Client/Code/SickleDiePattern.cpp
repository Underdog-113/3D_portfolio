#include "stdafx.h"
#include "SickleDiePattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CSickleDiePattern::CSickleDiePattern()
{
}

CSickleDiePattern::~CSickleDiePattern()
{
}

void CSickleDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();

	// ���� hp�� 0�� �Ǹ�
	if (Name_Sickle_Die != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		fsm->ChangeState(Name_Sickle_Die);
	}
	// die �ִϰ� ������
	else if (Name_Sickle_Die == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
	{
		pOwner->SetDeleteThis(true);
	}
}

SP(CSickleDiePattern) CSickleDiePattern::Create()
{
	SP(CSickleDiePattern) spInstance(new CSickleDiePattern, Engine::SmartDeleter<CSickleDiePattern>);

	return spInstance;
}