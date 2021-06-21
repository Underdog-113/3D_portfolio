#include "stdafx.h"
#include "GaneshaBornPattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"

#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CGaneshaBornPattern::CGaneshaBornPattern()
{
}

CGaneshaBornPattern::~CGaneshaBornPattern()
{
}

void CGaneshaBornPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	// 내가 born 상태이고, 애니가 끝났다면
	if (Name_Ganesha_Born == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
		fsm->ChangeState(Name_Ganesha_StandBy);
	}
}

SP(CGaneshaBornPattern) CGaneshaBornPattern::Create()
{
	SP(CGaneshaBornPattern) spInstance(new CGaneshaBornPattern, Engine::SmartDeleter<CGaneshaBornPattern>);

	return spInstance;
}