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
// 	// 내가 약피격 당했다면
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
// 	// 내가 강피격 당했다면
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
// 	// 내가 hit_front_l 당했다면
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
// 	// 내가 hit_front 당했다면
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