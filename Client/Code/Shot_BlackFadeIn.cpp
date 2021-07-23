#include "stdafx.h"
#include "..\Header\Shot_BlackFadeIn.h"


CShot_BlackFadeIn::CShot_BlackFadeIn()
{
}

CShot_BlackFadeIn::~CShot_BlackFadeIn()
{
}

_bool CShot_BlackFadeIn::CheckOnTake(_float takeTimer)
{
	if (CShot::CheckOnTake(takeTimer))
	{
		if (GetTimeline() > m_desc.alphaLimit)
			return false;

		return true;
	}

	return false;
}

void CShot_BlackFadeIn::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));
}

void CShot_BlackFadeIn::Enter()
{
	m_desc.pBlackFade->SetAlpha(1.f);
}

void CShot_BlackFadeIn::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	m_desc.pBlackFade->SetAlpha(1.f - timeline);
}

void CShot_BlackFadeIn::Cut()
{
	m_desc.pBlackFade->SetAlpha(0.f);
}

void CShot_BlackFadeIn::Rollback()
{
	m_desc.pBlackFade->SetAlpha(1.f);	
}
