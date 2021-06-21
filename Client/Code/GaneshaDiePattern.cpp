#include "stdafx.h"
#include "GaneshaDiePattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CGaneshaDiePattern::CGaneshaDiePattern()
{
}

CGaneshaDiePattern::~CGaneshaDiePattern()
{
}

void CGaneshaDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	// 내가 die 상태가 아니면
	if (Name_Ganesha_Die != fsm->GetCurStateString())
	{
		fsm->ChangeState(Name_Ganesha_Die);
	}
	// 내가 die 상태면
	else if (Name_Ganesha_Die == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->SetDeleteThis(true);
	}
}

SP(CGaneshaDiePattern) CGaneshaDiePattern::Create()
{
	SP(CGaneshaDiePattern) spInstance(new CGaneshaDiePattern, Engine::SmartDeleter<CGaneshaDiePattern>);

	return spInstance;
}