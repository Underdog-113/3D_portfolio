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

	if (Name_Ganesha_Born == fsm->GetCurStateString() && 0.75f > fsm->GetDM()->GetAniTimeline())
	{
		pOwner->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
		pOwner->GetComponent<Engine::CCollisionC>()->SetIsEnabled(false);
	}

	// 내가 born 상태이고, 애니가 끝났다면
	if (Name_Ganesha_Born == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
		fsm->ChangeState(Name_Ganesha_StandBy);

		pOwner->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(true);
		pOwner->GetComponent<Engine::CCollisionC>()->SetIsEnabled(true);
	}
}

SP(CGaneshaBornPattern) CGaneshaBornPattern::Create()
{
	SP(CGaneshaBornPattern) spInstance(new CGaneshaBornPattern, Engine::SmartDeleter<CGaneshaBornPattern>);

	return spInstance;
}