#include "stdafx.h"
#include "SliderComponent.h"


CSliderComponent::CSliderComponent()
{
}


CSliderComponent::~CSliderComponent()
{
}

SP(Engine::CComponent) CSliderComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CSliderComponent) spClone(new CSliderComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CSliderComponent::Awake()
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;
}

void CSliderComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);

}

void CSliderComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
}

void CSliderComponent::Update(SP(Engine::CComponent) spThis)
{
}

void CSliderComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CSliderComponent::OnDestroy()
{
}

void CSliderComponent::OnEnable()
{
	__super::OnEnable();

}

void CSliderComponent::OnDisable()
{
	__super::OnDisable();

}
