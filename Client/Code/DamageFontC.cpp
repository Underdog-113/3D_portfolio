#include "Stdafx.h"
#include "DamageFontC.h"

#include<iostream>
#include<cstdlib>
#include<ctime>

CDamageFontC::CDamageFontC()
{
}

CDamageFontC::~CDamageFontC()
{
	OnDestroy();
}

SP(Engine::CComponent) CDamageFontC::MakeClone(Engine::CObject *pObject)
{
	SP(CDamageFontC) spClone(new CDamageFontC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CDamageFontC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
	m_offSet = _float3(0, 0, GetOwner()->GetTransform()->GetPosition().z);
}

void CDamageFontC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CDamageFontC::FixedUpdate(SP(CComponent) spThis)
{

}

void CDamageFontC::Update(SP(CComponent) spThis)
{
	m_offSet.y += (m_upSpeed * GET_DT);
	_float3 pos = m_target->GetTransform()->GetPosition() + m_pos;

	_float3 pos2d = Engine::GET_MAIN_CAM->WorldToScreenPoint(pos);
	pos2d.z = 0.f;
	

	GetOwner()->GetTransform()->SetPosition(pos2d + m_offSet);

	m_lifeTime -= GET_DT;

	_float alphaValue = m_lifeTime / m_oldLifeTime;

	GetOwner()->GetComponent<Engine::CTextureC>()->SetColor(_float4(1, 1, 1, alphaValue));

	if (m_lifeTime <= 0)
	{
		GetOwner()->SetIsEnabled(false);
		m_offSet = _float3(0, 0, 0);
		m_target = nullptr;
	}
}

void CDamageFontC::LateUpdate(SP(CComponent) spThis)
{
	if (m_target->GetDeleteThis())
	{
		GetOwner()->SetIsEnabled(false);
		m_offSet = _float3(0, 0, 0);
		m_target = nullptr;
	}
}

void CDamageFontC::OnDestroy()
{
}

void CDamageFontC::OnEnable()
{
	__super::OnEnable();
}

void CDamageFontC::OnDisable()
{
	__super::OnDisable();
}

void CDamageFontC::AddDamageFontInit(Engine::CObject* target, _float3 hitPoint, _float offSetX, _float upSpped, _float lifeTime, _int damage, std::wstring color, _float3 pos)
{
	GetOwner()->SetIsEnabled(true);
	m_upSpeed = upSpped;
	m_lifeTime = lifeTime;
	m_oldLifeTime = m_lifeTime;
	m_damage = damage;
	m_target = target;
	m_offSet.x = offSetX;
	m_hitPointOffset = hitPoint - target->GetTransform()->GetPosition();
	m_hitPointOffsetLength = D3DXVec3Length(&m_hitPointOffset);
	GetOwner()->GetComponent<Engine::CTextureC>()->ChangeTexture(color + std::to_wstring(damage), 0);
	m_pos = pos;
}
