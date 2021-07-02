#include "stdafx.h"
#include "..\Header\PhaseControl.h"


CPhaseControl::CPhaseControl()
{
}


CPhaseControl::~CPhaseControl()
{
}

void CPhaseControl::IncreasePhase(void)
{
	++m_curPhase;
}

void CPhaseControl::ChangePhase(_int phaseNum)
{
	m_curPhase = phaseNum;
}
