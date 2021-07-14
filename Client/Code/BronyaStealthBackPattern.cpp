#include "stdafx.h"
#include "BronyaStealthBackPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "Valkyrie.h"

CBronyaStealthBackPattern::CBronyaStealthBackPattern()
{
}

CBronyaStealthBackPattern::~CBronyaStealthBackPattern()
{
}

void CBronyaStealthBackPattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	

	
}

SP(CBronyaStealthBackPattern) CBronyaStealthBackPattern::Create()
{
	SP(CBronyaStealthBackPattern) spInstance(new CBronyaStealthBackPattern, Engine::SmartDeleter<CBronyaStealthBackPattern>);

	return spInstance;
}