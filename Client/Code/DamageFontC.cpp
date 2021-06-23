#include "Stdafx.h"
#include "DamageFontC.h"

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

	_float3 pos2d = Engine::GET_MAIN_CAM->WorldToScreenPoint(m_target->GetTransform()->GetPosition());
	pos2d.z = 0.f;
	

	GetOwner()->GetTransform()->SetPosition(pos2d + m_offSet);

	m_lifeTime -= GET_DT;

	_float alphaValue = m_lifeTime / m_oldLifeTime;

	GetOwner()->GetComponent<Engine::CTextureC>()->SetColor(_float4(1, 1, 1, alphaValue));

	if (m_lifeTime <= 0)
	{
		GetOwner()->SetIsEnabled(false);
		m_offSet = _float3(0, 0, 0);
	}
}

void CDamageFontC::LateUpdate(SP(CComponent) spThis)
{

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

void CDamageFontC::AddDamageFontInit(Engine::CObject* target, _float offSetX, _float upSpped, _float lifeTime, _int damage, std::wstring color)
{
	GetOwner()->SetIsEnabled(true);
	m_upSpeed = upSpped;
	m_lifeTime = lifeTime;
	m_oldLifeTime = m_lifeTime;
	m_damage = damage;
	m_target = target;
	m_offSet.x = offSetX;
	GetOwner()->GetComponent<Engine::CTextureC>()->ChangeTexture(color + std::to_wstring(damage), 0);
}
