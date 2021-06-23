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
