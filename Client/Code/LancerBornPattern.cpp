#include "stdafx.h"
#include "LancerBornPattern.h"

#include "FSM_LancerC.h"
#include "FSMDefine_Lancer.h"
#include "MO_Lancer.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CLancerBornPattern::CLancerBornPattern()
{
}

CLancerBornPattern::~CLancerBornPattern()
{
}

void CLancerBornPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_LancerC) fsm = pOwner->GetComponent<CFSM_LancerC>();

	// 내가 born 상태이고, 애니가 끝났다면
	if (Name_APPEAR == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
		fsm->ChangeState(Name_STAND);
	}
}

SP(CLancerBornPattern) CLancerBornPattern::Create()
{
	SP(CLancerBornPattern) spInstance(new CLancerBornPattern, Engine::SmartDeleter<CLancerBornPattern>);

	return spInstance;
}