#include "stdafx.h"
#include "SickleBornPattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CSickleBornPattern::CSickleBornPattern()
{
}

CSickleBornPattern::~CSickleBornPattern()
{
}

void CSickleBornPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();

	// 내가 born 상태이고, 애니가 끝났다면
	if (Name_Sickle_Born == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
		fsm->ChangeState(Name_Sickle_StandBy);
	}
}

SP(CSickleBornPattern) CSickleBornPattern::Create()
{
	SP(CSickleBornPattern) spInstance(new CSickleBornPattern, Engine::SmartDeleter<CSickleBornPattern>);

	return spInstance;
}