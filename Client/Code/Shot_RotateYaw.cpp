#include "stdafx.h"
#include "..\Header\Shot_RotateYaw.h"


CShot_RotateYaw::CShot_RotateYaw()
{
}


CShot_RotateYaw::~CShot_RotateYaw()
{
}

void CShot_RotateYaw::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedLookAngleUp = m_spCamera->GetLookAngleUp();
}

void CShot_RotateYaw::Enter()
{
	m_spCamera->SetLookAngleUp(D3DXToRadian(m_desc.startEulerAngle));
}

void CShot_RotateYaw::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	_float curAngle = GetLerpFloat(m_desc.startEulerAngle, m_desc.endEulerAngle, timeline);

	m_spCamera->SetLookAngleUp(D3DXToRadian(curAngle));
}

void CShot_RotateYaw::Cut()
{
	m_spCamera->SetLookAngleUp(D3DXToRadian(m_desc.endEulerAngle));
}

void CShot_RotateYaw::Rollback()
{
	m_spCamera->SetLookAngleUp(m_savedLookAngleUp);
}
