#include "Stdafx.h"
#include "SkillCollTimcC.h"
#include "Object.h"

CSkillCollTimcC::CSkillCollTimcC()
{
}

CSkillCollTimcC::~CSkillCollTimcC()
{
	OnDestroy();
}

SP(Engine::CComponent) CSkillCollTimcC::MakeClone(Engine::CObject *pObject)
{
	SP(CSkillCollTimcC) spClone(new CSkillCollTimcC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CSkillCollTimcC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CSkillCollTimcC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_spSlider = static_cast<Engine::CSlider*>(GetOwner());

}

void CSkillCollTimcC::FixedUpdate(SP(CComponent) spThis)
{

}

void CSkillCollTimcC::Update(SP(CComponent) spThis)
{
	m_spSlider->SetValue(m_spSlider->GetValue() - GET_DT);

	if (m_spSlider->GetValue() >= 0)
	{
		std::cout << m_spSlider->GetValue() << std::endl;
	}
}

void CSkillCollTimcC::LateUpdate(SP(CComponent) spThis)
{

}

void CSkillCollTimcC::OnDestroy()
{
}

void CSkillCollTimcC::OnEnable()
{
	__super::OnEnable();
}

void CSkillCollTimcC::OnDisable()
{
	__super::OnDisable();
}
