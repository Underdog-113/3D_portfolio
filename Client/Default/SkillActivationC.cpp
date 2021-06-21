#include "Stdafx.h"
#include "SkillActivationC.h"
#include "Object.h"

CSkillActivationC::CSkillActivationC()
{
}

CSkillActivationC::~CSkillActivationC()
{
	OnDestroy();
}

SP(Engine::CComponent) CSkillActivationC::MakeClone(Engine::CObject *pObject)
{
	SP(CSkillActivationC) spClone(new CSkillActivationC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CSkillActivationC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CSkillActivationC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_dir = -1.0f;
	m_alpha = 1;
}

void CSkillActivationC::FixedUpdate(SP(CComponent) spThis)
{

}

void CSkillActivationC::Update(SP(CComponent) spThis)
{
	if (m_alpha >= 1)
	{
		m_dir = m_speed * -1;
	}
	else if (m_alpha <= 0.4)
	{
		m_dir = m_speed * 1;
	}
	m_alpha += GET_DT * m_dir;
	std::cout << m_alpha << std::endl;
	GetOwner()->GetComponent<Engine::CTextureC>()->SetColor(_float4(1, 1, 1, m_alpha));
}

void CSkillActivationC::LateUpdate(SP(CComponent) spThis)
{

}

void CSkillActivationC::OnDestroy()
{
}

void CSkillActivationC::OnEnable()
{
	__super::OnEnable();
}

void CSkillActivationC::OnDisable()
{
	__super::OnDisable();
}
