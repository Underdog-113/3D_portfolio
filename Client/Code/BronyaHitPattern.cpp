#include "stdafx.h"
#include "BronyaHitPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

CBronyaHitPattern::CBronyaHitPattern()
{
}

CBronyaHitPattern::~CBronyaHitPattern()
{
}

void CBronyaHitPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();
	static_cast<CMB_Bronya*>(pOwner)->UnActiveAttackBall();

	pOwner->GetComponent<CPatternMachineC>()->SetOnStun(true);
	//pOwner->GetComponent<CPatternMachineC>()->SetOnHitL(false);
	//pOwner->GetComponent<CPatternMachineC>()->SetOnHitH(false);
}

SP(CBronyaHitPattern) CBronyaHitPattern::Create()
{
	SP(CBronyaHitPattern) spInstance(new CBronyaHitPattern, Engine::SmartDeleter<CBronyaHitPattern>);

	return spInstance;
}