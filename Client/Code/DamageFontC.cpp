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
	GetOwner()->GetTransform()->AddPositionY(m_upSpeed * GET_DT);

	m_lifeTime -= GET_DT;

	_float alphaValue = m_lifeTime / m_oldLifeTime;

	GetOwner()->GetComponent<Engine::CShaderC>()->GetShaders()[0]->GetEffect()->SetFloat("g_alphaValue", alphaValue);

	if (m_lifeTime <= 0)
	{
		GetOwner()->SetIsEnabled(false);
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

void CDamageFontC::AddDamageFontInit(_float upSpped, _float lifeTime, _int damage, std::wstring color)
{
	GetOwner()->SetIsEnabled(true);
	m_upSpeed = upSpped;
	m_lifeTime = lifeTime;
	m_oldLifeTime = m_lifeTime;
	m_damage = damage;

	GetOwner()->GetComponent<Engine::CTextureC>()->ChangeTexture(color + std::to_wstring(damage), 0);
}
