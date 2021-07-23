#include "stdafx.h"
#include "..\Header\Shot_RotatePitch_Spline.h"

#include "SplineCurve.h"

CShot_RotatePitch_Spline::CShot_RotatePitch_Spline()
{
}


CShot_RotatePitch_Spline::~CShot_RotatePitch_Spline()
{
}

void CShot_RotatePitch_Spline::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedLookAngleRight = m_spCamera->GetLookAngleRight();
}

void CShot_RotatePitch_Spline::Enter()
{
	m_spCamera->SetLookAngleRight(D3DXToRadian(m_desc.angleCurve->GetPoint(0.f).y));
}

void CShot_RotatePitch_Spline::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	//_float curAngle = GetLerpFloat(m_desc.startEulerAngle, m_desc.endEulerAngle, timeline);
	_float curAngle = m_desc.angleCurve->GetPoint(timeline).y;

	m_spCamera->SetLookAngleRight(D3DXToRadian(curAngle));
}

void CShot_RotatePitch_Spline::Cut()
{
	m_spCamera->SetLookAngleRight(D3DXToRadian(m_desc.angleCurve->GetPoint(1.f).y));
}

void CShot_RotatePitch_Spline::Rollback()
{
	m_spCamera->SetLookAngleRight(m_savedLookAngleRight);
}
