#include "stdafx.h"
#include "ButtonComponent.h"


CButtonComponent::CButtonComponent()
{
}


CButtonComponent::~CButtonComponent()
{
}

SP(Engine::CComponent) CButtonComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CButtonComponent) spClone(new CButtonComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CButtonComponent::Awake()
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;
}

void CButtonComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);

}

void CButtonComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
}

void CButtonComponent::Update(SP(Engine::CComponent) spThis)
{
}

void CButtonComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CButtonComponent::OnDestroy()
{
}

void CButtonComponent::OnEnable()
{
	__super::OnEnable();

}

void CButtonComponent::OnDisable()
{
	__super::OnDisable();

}
