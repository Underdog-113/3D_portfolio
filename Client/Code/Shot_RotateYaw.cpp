#include "stdafx.h"
#include "..\Header\Shot_RotateYaw.h"

#include "Valkyrie.h"

CShot_RotateYaw::CShot_RotateYaw()
{
}


CShot_RotateYaw::~CShot_RotateYaw()
{
}

void CShot_RotateYaw::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	Engine::CTransformC* pTr = nullptr;

	if (m_desc.pTargetTransform)
		pTr = m_desc.pTargetTransform;
	else
		pTr = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform().get();

	_float3 actorForward = pTr->GetForward();
	_float3 actorRight = pTr->GetRight();
	actorForward.y = 0.f;
	actorRight.y = 0.f;

	D3DXVec3Normalize(&actorForward, &actorForward);
	D3DXVec3Normalize(&actorRight, &actorRight);

	_float3 rotAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&rotAxis, &FORWARD_VECTOR, &actorForward);
	D3DXVec3Normalize(&rotAxis, &rotAxis);
	
	_float actorForwardCos = D3DXVec3Dot(&FORWARD_VECTOR, &actorForward);
	_float radStartAngle = acosf(actorForwardCos);

	if (rotAxis.y > 0.f) 
	{
		m_startActorForwardAngle = D3DXToRadian(180) + radStartAngle;
	}
	else
	{
		m_startActorForwardAngle = D3DXToRadian(180) - radStartAngle;
	}

	//m_startActorForwardAngle *= -1.f;  // mesh 180
	
	m_savedLookAngleUp = m_spCamera->GetLookAngleUp();
}

void CShot_RotateYaw::Enter()
{
	m_spCamera->SetLookAngleUp(m_startActorForwardAngle + D3DXToRadian(m_desc.startEulerAngle));
}

void CShot_RotateYaw::Action()
{
	CShot::Action();

	_float timeline = GetTimeline();

	_float curAngle = GetLerpFloat(m_desc.startEulerAngle, m_desc.endEulerAngle, timeline);

	m_spCamera->SetLookAngleUp(m_startActorForwardAngle + D3DXToRadian(curAngle));
}

void CShot_RotateYaw::Cut()
{
	m_spCamera->SetLookAngleUp(m_startActorForwardAngle + D3DXToRadian(m_desc.endEulerAngle));
}

void CShot_RotateYaw::Rollback()
{
	m_spCamera->SetLookAngleUp(m_savedLookAngleUp);
}
