#include "stdafx.h"
#include "..\Header\Take.h"

#include "Shot.h"

CTake::CTake()
{
}


CTake::~CTake()
{
}

void CTake::StartTake()
{
	m_pCurShot = m_vShotList[0];
	m_pCurShot->Ready();
}

void CTake::ActCurrentShot()
{
	m_pCurShot->Action();
}

void CTake::EndTake()
{
}
