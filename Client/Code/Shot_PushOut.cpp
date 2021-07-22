#include "stdafx.h"
#include "..\Header\Shot_PushOut.h"


CShot_PushOut::CShot_PushOut()
{
}


CShot_PushOut::~CShot_PushOut()
{
}

void CShot_PushOut::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedMaxDistance = m_spCamera->GetMaxDistTPS();
}

void CShot_PushOut::Enter()
{
	m_spCamera->SetTargetDist(m_desc.startDistance);
	m_spCamera->SetMaxDistTPS(m_desc.startDistance);
}

void CShot_PushOut::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	_float curDistance = GetLerpFloat(m_desc.startDistance, m_desc.endDistance, timeline);
	
	m_spCamera->SetTargetDist(curDistance);
	m_spCamera->SetMaxDistTPS(curDistance);
}

void CShot_PushOut::Cut()
{
	m_spCamera->SetTargetDist(m_desc.endDistance);
	m_spCamera->SetMaxDistTPS(m_desc.endDistance);
}

void CShot_PushOut::Rollback()
{
	m_spCamera->SetTargetDist(m_savedMaxDistance);
	m_spCamera->SetMaxDistTPS(m_savedMaxDistance);
}
