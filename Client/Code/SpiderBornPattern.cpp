#include "stdafx.h"
#include "SpiderBornPattern.h"

#include "FSM_SpiderC.h"
#include "FSMDefine_Spider.h"

#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CSpiderBornPattern::CSpiderBornPattern()
{
}

CSpiderBornPattern::~CSpiderBornPattern()
{
}

void CSpiderBornPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_SpiderC) fsm = pOwner->GetComponent<CFSM_SpiderC>();

	// 내가 born 상태이고, 애니가 끝났다면
	if (Name_Born == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
		fsm->ChangeState(Name_StandBy);
	}
}

SP(CSpiderBornPattern) CSpiderBornPattern::Create()
{
	SP(CSpiderBornPattern) spInstance(new CSpiderBornPattern, Engine::SmartDeleter<CSpiderBornPattern>);

	return spInstance;
}