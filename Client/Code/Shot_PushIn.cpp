#include "stdafx.h"
#include "..\Header\Shot_PushIn.h"


CShot_PushIn::CShot_PushIn()
{
}


CShot_PushIn::~CShot_PushIn()
{
}

void CShot_PushIn::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedMaxDistance = m_spCamera->GetMaxDistTPS();
}

void CShot_PushIn::Enter()
{
	m_spCamera->SetTargetDist(m_desc.startDistance);
	m_spCamera->SetMaxDistTPS(m_desc.startDistance);
}

void CShot_PushIn::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	_float curDistance;

	if (m_desc.isPowLerp)
	{
		float inverseRate = 1.f - timeline;
		float sLerpTimer = 1.f - inverseRate * inverseRate;
		curDistance = GetLerpFloat(m_desc.startDistance, m_desc.endDistance, sLerpTimer);
	}
	else
		curDistance = GetLerpFloat(m_desc.startDistance, m_desc.endDistance, timeline);

	m_spCamera->SetTargetDist(curDistance);
	m_spCamera->SetMaxDistTPS(curDistance);
}

void CShot_PushIn::Cut()
{
	m_spCamera->SetTargetDist(m_desc.endDistance);
	m_spCamera->SetMaxDistTPS(m_desc.endDistance);
}

void CShot_PushIn::Rollback()
{
	m_spCamera->SetTargetDist(m_savedMaxDistance);
	m_spCamera->SetMaxDistTPS(m_savedMaxDistance);
}
