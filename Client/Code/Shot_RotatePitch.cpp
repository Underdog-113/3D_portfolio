#include "stdafx.h"
#include "..\Header\Shot_RotatePitch.h"


CShot_RotatePitch::CShot_RotatePitch()
{
}


CShot_RotatePitch::~CShot_RotatePitch()
{
}

void CShot_RotatePitch::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedLookAngleRight = m_spCamera->GetLookAngleRight();
}

void CShot_RotatePitch::Enter()
{
	m_spCamera->SetLookAngleRight(D3DXToRadian(m_desc.startEulerAngle));
}

void CShot_RotatePitch::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	_float curAngle = GetLerpFloat(m_desc.startEulerAngle, m_desc.endEulerAngle, timeline);

	m_spCamera->SetLookAngleRight(D3DXToRadian(curAngle));
}

void CShot_RotatePitch::Cut()
{
	m_spCamera->SetLookAngleRight(D3DXToRadian(m_desc.endEulerAngle));
}

void CShot_RotatePitch::Rollback()
{
	m_spCamera->SetLookAngleRight(m_savedLookAngleRight);
}
