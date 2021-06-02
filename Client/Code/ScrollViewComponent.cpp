#include "stdafx.h"
#include "ScrollViewComponent.h"


CScrollViewComponent::CScrollViewComponent()
{
}


CScrollViewComponent::~CScrollViewComponent()
{
}

SP(Engine::CComponent) CScrollViewComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CScrollViewComponent) spClone(new CScrollViewComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CScrollViewComponent::Awake()
{
	__super::Awake();
	//m_componentID = (_int)m_s_componentID;
}

void CScrollViewComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);

}

void CScrollViewComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
}

void CScrollViewComponent::Update(SP(Engine::CComponent) spThis)
{
}

void CScrollViewComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CScrollViewComponent::OnDestroy()
{
}

void CScrollViewComponent::OnEnable()
{
	__super::OnEnable();

}

void CScrollViewComponent::OnDisable()
{
	__super::OnDisable();

}
