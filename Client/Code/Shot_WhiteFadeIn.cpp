#include "stdafx.h"
#include "..\Header\Shot_WhiteFadeIn.h"

#include "FadeInOutC.h"

CShot_WhiteFadeIn::CShot_WhiteFadeIn()
{
}

CShot_WhiteFadeIn::~CShot_WhiteFadeIn()
{
}

void CShot_WhiteFadeIn::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_desc.pWhiteFade->SetAlpha(1.f);
}

void CShot_WhiteFadeIn::Enter()
{
}

void CShot_WhiteFadeIn::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	m_desc.pWhiteFade->SetAlpha(1.f - timeline);
}

void CShot_WhiteFadeIn::Cut()
{
}

void CShot_WhiteFadeIn::Rollback()
{
	m_desc.pWhiteFade->SetAlpha(1.f);
}


