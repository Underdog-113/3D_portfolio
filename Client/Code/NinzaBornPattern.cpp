#include "stdafx.h"
#include "NinzaBornPattern.h"

#include "FSM_NinzaC.h"
#include "FSMDefine_Ninza.h"
#include "MO_Ninza.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CNinzaBornPattern::CNinzaBornPattern()
{
}

CNinzaBornPattern::~CNinzaBornPattern()
{
}

void CNinzaBornPattern::Pattern(Engine::CObject* pOwner)
{
 	SP(CFSM_NinzaC) fsm = pOwner->GetComponent<CFSM_NinzaC>();
 
 	// 내가 born 상태이고, 애니가 끝났다면
 	if (Name_born == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
 	{
 		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
 		fsm->ChangeState(Name_standby);
 	}
}

SP(CNinzaBornPattern) CNinzaBornPattern::Create()
{
	SP(CNinzaBornPattern) spInstance(new CNinzaBornPattern, Engine::SmartDeleter<CNinzaBornPattern>);

	return spInstance;
}