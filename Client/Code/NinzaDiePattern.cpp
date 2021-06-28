#include "stdafx.h"
#include "NinzaDiePattern.h"

#include "FSM_NinzaC.h"
#include "FSMDefine_Ninza.h"
#include "MO_Ninza.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CNinzaDiePattern::CNinzaDiePattern()
{
}

CNinzaDiePattern::~CNinzaDiePattern()
{
}

void CNinzaDiePattern::Pattern(Engine::CObject* pOwner)
{
// 	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();
// 
// 	// ���� hp�� 0�� �Ǹ�
// 	if (Name_Sickle_Die != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
// 	{
// 		fsm->ChangeState(Name_Sickle_Die);
// 		PatternPlaySound(L"Sickle_Dead.wav", pOwner);
// 	}
// 	// die �ִϰ� ������
// 	else if (Name_Sickle_Die == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
// 	{
// 		pOwner->SetDeleteThis(true);
// 	}
}

SP(CNinzaDiePattern) CNinzaDiePattern::Create()
{
	SP(CNinzaDiePattern) spInstance(new CNinzaDiePattern, Engine::SmartDeleter<CNinzaDiePattern>);

	return spInstance;
}