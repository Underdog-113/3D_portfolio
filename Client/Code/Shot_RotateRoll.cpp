#include "stdafx.h"
#include "..\Header\Shot_RotateRoll.h"


CShot_RotateRoll::CShot_RotateRoll()
{
}


CShot_RotateRoll::~CShot_RotateRoll()
{
}

void CShot_RotateRoll::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedLookAngleForward = m_spCamera->GetLookAngleForward();
}

void CShot_RotateRoll::Enter()
{
	m_spCamera->SetLookAngleForward(D3DXToRadian(m_desc.startEulerAngle));
}

void CShot_RotateRoll::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	_float curAngle = GetLerpFloat(m_desc.startEulerAngle, m_desc.endEulerAngle, timeline);

	m_spCamera->SetLookAngleForward(D3DXToRadian(curAngle));
}

void CShot_RotateRoll::Cut()
{
	m_spCamera->SetLookAngleForward(D3DXToRadian(m_desc.endEulerAngle));
}

void CShot_RotateRoll::Rollback()
{
	m_spCamera->SetLookAngleForward(m_savedLookAngleForward);
}
