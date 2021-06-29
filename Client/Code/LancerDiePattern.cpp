#include "stdafx.h"
#include "LancerDiePattern.h"

#include "FSM_LancerC.h"
#include "FSMDefine_Lancer.h"
#include "MO_Lancer.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CLancerDiePattern::CLancerDiePattern()
{
}

CLancerDiePattern::~CLancerDiePattern()
{
}

void CLancerDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_LancerC) fsm = pOwner->GetComponent<CFSM_LancerC>();

	// 내가 hp가 0이 되면
	if (Name_DIE != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		fsm->ChangeState(Name_DIE);
		PatternPlaySound(L"Lancer_Dead.wav", pOwner);
	}
	// die 애니가 끝나면
	else if (Name_DIE == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
	{
		pOwner->SetDeleteThis(true);
	}
}

SP(CLancerDiePattern) CLancerDiePattern::Create()
{
	SP(CLancerDiePattern) spInstance(new CLancerDiePattern, Engine::SmartDeleter<CLancerDiePattern>);

	return spInstance;
}