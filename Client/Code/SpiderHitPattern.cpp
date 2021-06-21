#include "stdafx.h"
#include "SpiderHitPattern.h"

#include "FSM_SpiderC.h"
#include "FSMDefine_Spider.h"
#include "MO_Spider.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CSpiderHitPattern::CSpiderHitPattern()
{
}

CSpiderHitPattern::~CSpiderHitPattern()
{
}

void CSpiderHitPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_SpiderC) fsm = pOwner->GetComponent<CFSM_SpiderC>();

	// 내가 피격 당했다면
	if (Name_Hit_L != fsm->GetCurStateString() &&
		Name_Attack_1 != fsm->GetCurStateString() &&
		true == pOwner->GetComponent<CPatternMachineC>()->GetOnHit())
	{
		fsm->ChangeState(Name_Hit_L);
	}
	else if (Name_Hit_L == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_StandBy);
		pOwner->GetComponent<CPatternMachineC>()->SetOnHit(false);
	}
}

SP(CSpiderHitPattern) CSpiderHitPattern::Create()
{
	SP(CSpiderHitPattern) spInstance(new CSpiderHitPattern, Engine::SmartDeleter<CSpiderHitPattern>);

	return spInstance;
}