#include "stdafx.h"
#include "..\Header\Shot_RotateAround.h"

#include "StageCameraMan.h"

CShot_RotateAround::CShot_RotateAround()
{
}


CShot_RotateAround::~CShot_RotateAround()
{
}

void CShot_RotateAround::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc);

	SetIsEndless(true);
	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedPivotPos = m_pCameraMan->GetPivot()->GetTransform()->GetPosition();
	m_savedLookAngleUp = m_spCamera->GetLookAngleUp();
}

void CShot_RotateAround::Enter()
{
	m_pCameraMan->GetPivot()->GetTransform()->SetPosition(m_savedPivotPos + m_desc.offset);
	m_spCamera->SetLookAngleUp(D3DXToRadian(m_desc.startEulerRotate));
}


void CShot_RotateAround::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();
	timeline -= (_uint)timeline;

	_float curLookAngleUp = D3DXToRadian(m_desc.startEulerRotate + 360.f * timeline * m_desc.rotateSpeed);
	
	m_spCamera->SetLookAngleUp(curLookAngleUp);

}

void CShot_RotateAround::Cut()
{
}

void CShot_RotateAround::Rollback()
{
	m_spCamera->SetLookAngleUp(m_savedLookAngleUp);
	m_pCameraMan->GetPivot()->GetTransform()->SetPosition(m_savedPivotPos);
}
