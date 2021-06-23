#include "stdafx.h"
#include "OneStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

COneStagePhaseControl::COneStagePhaseControl()
{
}


COneStagePhaseControl::~COneStagePhaseControl()
{
}

void COneStagePhaseControl::Update(void)
{
	switch (m_curPhase)
	{
	case -1:
		++m_curPhase;
		break;
	case 0:
		if (m_pCT->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->CompareState(L"Appear") == false)
			++m_curPhase;
		break;
	case 2:
		break;
	}
}
