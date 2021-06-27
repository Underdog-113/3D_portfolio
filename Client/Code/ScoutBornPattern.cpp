#include "stdafx.h"
#include "ScoutBornPattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CScoutBornPattern::CScoutBornPattern()
{
}

CScoutBornPattern::~CScoutBornPattern()
{
}

void CScoutBornPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	// 내가 born 상태이고, 애니가 끝났다면
	if (Name_APPEAR == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
		fsm->ChangeState(Name_IDLE);
	}
}

SP(CScoutBornPattern) CScoutBornPattern::Create()
{
	SP(CScoutBornPattern) spInstance(new CScoutBornPattern, Engine::SmartDeleter<CScoutBornPattern>);

	return spInstance;
}