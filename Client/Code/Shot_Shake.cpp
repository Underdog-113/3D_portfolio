#include "stdafx.h"
#include "..\Header\Shot_Shake.h"


CShot_Shake::CShot_Shake()
{
}


CShot_Shake::~CShot_Shake()
{
}

void CShot_Shake::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_pCameraMan->GetCameraShake()->SetIsMovieOn(true);
	m_pCameraMan->GetCameraShake()->SetMovieChannel(m_desc.shakeChannel);
}

void CShot_Shake::Enter()
{
	m_pCameraMan->GetCameraShake()->PlayChannelOnMovie(0.f);
}

void CShot_Shake::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();
	m_pCameraMan->GetCameraShake()->PlayChannelOnMovie(timeline);
}

void CShot_Shake::Cut()
{
	m_pCameraMan->GetCameraShake()->PlayChannelOnMovie(1.f);
	m_pCameraMan->GetCameraShake()->SetIsMovieOn(false);
	m_pCameraMan->GetCameraShake()->SetMovieChannel(nullptr);
}

void CShot_Shake::Rollback()
{
}
