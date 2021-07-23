#include "stdafx.h"
#include "..\Header\Shot.h"

#include "StageControlTower.h"

CShot::CShot()
{
	auto pCT = CStageControlTower::GetInstance();
	m_pMovieDirector = pCT->GetMovieDirector();
	m_pCameraMan = pCT->GetCameraMan();
	m_spCamera = m_pCameraMan->GetCamera();
}

CShot::~CShot()
{
}

void CShot::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	m_pOnAirTake = pTake;
	m_startTimeline = startTimeline;
	m_endTimeline = endTimeline;
	m_enterTimeline = enterTimeline;

	m_isEnterAction = false;
	m_isExitAction = false;
}

void CShot::Action()
{
	if (!m_isEnterAction)
	{
		Enter();
		m_isEnterAction = true;
	}
}

void CShot::Rollback()
{
}

_bool CShot::CheckOnTake(_float takeTimer)
{
	if (m_startTimeline <= takeTimer && (m_isEndless || takeTimer <= m_endTimeline))
		return true;

	if (!m_isEnterAction && takeTimer > m_enterTimeline)
	{
		Enter();
		m_isEnterAction = true;
	}
	return false;
}

void CShot::CheckShotRollback(_float takeTimer)
{
	if (takeTimer <= m_startTimeline && takeTimer <= m_enterTimeline)
	{
		Rollback();
		m_isEnterAction = false;
	}
}

_bool CShot::CheckShotEnd(_float takeTimer)
{
	if (m_endTimeline <= takeTimer && !m_isEndless)
	{
		if (!m_isExitAction)
		{
			Cut();
			m_isExitAction = true;
		}

		return true;
	}

	return false;
}

_float CShot::GetTimeline()
{
	_float curtime = m_pOnAirTake->GetPlayTimer();
	
	if (curtime < m_startTimeline)
	{
		return 0.f;
	}
	else if(m_isEndless || curtime < m_endTimeline)
	{
		return (curtime - m_startTimeline) / (m_endTimeline - m_startTimeline);
	}
	else
	{
		return 1.f;
	}
}
