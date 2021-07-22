#include "stdafx.h"
#include "..\Header\Shot_BlackFadeOut.h"


CShot_BlackFadeOut::CShot_BlackFadeOut()
{
}


CShot_BlackFadeOut::~CShot_BlackFadeOut()
{
}

_bool CShot_BlackFadeOut::CheckOnTake(_float takeTimer)
{
	if (CShot::CheckOnTake(takeTimer))
	{
		if (GetTimeline() < m_desc.alphaLimit)
			return false;

		return true;
	}

	return false;
}

void CShot_BlackFadeOut::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));
}

void CShot_BlackFadeOut::Enter()
{
	m_desc.pBlackFade->SetAlpha(0.f);
}

void CShot_BlackFadeOut::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	m_desc.pBlackFade->SetAlpha(timeline);
}

void CShot_BlackFadeOut::Cut()
{
	m_desc.pBlackFade->SetAlpha(1.f);
}

void CShot_BlackFadeOut::Rollback()
{
	m_desc.pBlackFade->SetAlpha(0.f);
}
