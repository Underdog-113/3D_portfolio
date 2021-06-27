#include "stdafx.h"
#include "NinzaHitPattern.h"

#include "FSM_NinzaC.h"
#include "FSMDefine_Ninza.h"
#include "MO_Ninza.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"
#include "AniCtrl.h"

CNinzaHitPattern::CNinzaHitPattern()
{
}

CNinzaHitPattern::~CNinzaHitPattern()
{
}

void CNinzaHitPattern::Pattern(Engine::CObject* pOwner)
{
// 	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();
// 
// 	// ���� ���ǰ� ���ߴٸ�
// 	if (Name_Sickle_Hit_L != fsm->GetCurStateString() &&
// 		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitL())
// 	{
// 		fsm->ChangeState(Name_Sickle_Hit_L);
// 	}
// 	else if (Name_Sickle_Hit_L == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
// 	{
// 		fsm->ChangeState(Name_Sickle_StandBy);
// 		pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
// 	}
// 	// ���� ���ǰ� ���ߴٸ�
// 	if (Name_Sickle_Hit_H != fsm->GetCurStateString() &&
// 		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitH())
// 	{
// 		fsm->ChangeState(Name_Sickle_Hit_H);
// 	}
// 	else if (Name_Sickle_Hit_H == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
// 	{
// 		fsm->ChangeState(Name_Sickle_StandBy);
// 		pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
// 	}
// 	// ���� hit_front_l ���ߴٸ�
// 	if (Name_Sickle_Hit_Front_L != fsm->GetCurStateString() &&
// 		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitFrontL())
// 	{
// 		fsm->ChangeState(Name_Sickle_Hit_Front_L);
// 	}
// 	else if (Name_Sickle_Hit_Front_L == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
// 	{
// 		fsm->ChangeState(Name_Sickle_StandBy);
// 		pOwner->GetComponent<CPatternMachineC>()->SetOnHitFrontL(false);
// 	}
// 	// ���� hit_front ���ߴٸ�
// 	if (Name_Sickle_Hit_Front != fsm->GetCurStateString() &&
// 		Name_Sickle_StandUp != fsm->GetCurStateString() &&
// 		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHitFront())
// 	{
// 		fsm->ChangeState(Name_Sickle_Hit_Front);
// 	}
// 	else if (Name_Sickle_Hit_Front == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
// 	{
// 		fsm->ChangeState(Name_Sickle_StandUp);
// 	}
// 	else if (Name_Sickle_StandUp == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
// 	{
// 		fsm->ChangeState(Name_Sickle_StandBy);
// 		pOwner->GetComponent<CPatternMachineC>()->SetOnHitFront(false);
// 	}
}

SP(CNinzaHitPattern) CNinzaHitPattern::Create()
{
	SP(CNinzaHitPattern) spInstance(new CNinzaHitPattern, Engine::SmartDeleter<CNinzaHitPattern>);

	return spInstance;
}