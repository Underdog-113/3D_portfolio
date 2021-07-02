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

	// ���� die ���°� �ƴϸ�
	if (Name_Die != fsm->GetCurStateString())
	{
		fsm->ChangeState(Name_Die);
	}
	// ���� die ���°� �����ٸ�
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