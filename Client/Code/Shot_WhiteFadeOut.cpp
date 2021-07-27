#include "stdafx.h"
#include "..\Header\Shot_WhiteFadeOut.h"

#include "FadeInOutC.h"

CShot_WhiteFadeOut::CShot_WhiteFadeOut()
{
}

CShot_WhiteFadeOut::~CShot_WhiteFadeOut()
{
}

void CShot_WhiteFadeOut::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));
}

void CShot_WhiteFadeOut::Enter()
{
	m_desc.pWhiteFade->SetAlpha(0.f);
}

void CShot_WhiteFadeOut::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	m_desc.pWhiteFade->SetAlpha(timeline);
}

void CShot_WhiteFadeOut::Cut()
{
/*	m_desc.pWhiteFade->SetAlpha(1.f);*/
}

void CShot_WhiteFadeOut::Rollback()
{
	m_desc.pWhiteFade->SetAlpha(0.f);
}
