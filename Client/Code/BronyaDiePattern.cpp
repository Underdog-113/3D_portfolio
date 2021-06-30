#include "stdafx.h"
#include "BronyaDiePattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"

CBronyaDiePattern::CBronyaDiePattern()
{
}

CBronyaDiePattern::~CBronyaDiePattern()
{
}

void CBronyaDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	// 내가 die 상태가 아니면
	if (Name_Die != fsm->GetCurStateString())
	{
		fsm->ChangeState(Name_Die);
	}
	// 내가 die 상태가 끝났다면
	else if (Name_Die == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->SetDeleteThis(true);
	}
}

SP(CBronyaDiePattern) CBronyaDiePattern::Create()
{
	SP(CBronyaDiePattern) spInstance(new CBronyaDiePattern, Engine::SmartDeleter<CBronyaDiePattern>);

	return spInstance;
}