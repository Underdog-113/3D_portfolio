#include "stdafx.h"
#include "ImageComponent.h"


CImageComponent::CImageComponent()
{
}


CImageComponent::~CImageComponent()
{
}

SP(Engine::CComponent) CImageComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CImageComponent) spClone(new CImageComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CImageComponent::Awake()
{
	__super::Awake();
	//m_componentID = (_int)m_s_componentID;
}

void CImageComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);

}

void CImageComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
}

void CImageComponent::Update(SP(Engine::CComponent) spThis)
{
}

void CImageComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CImageComponent::OnDestroy()
{
}

void CImageComponent::OnEnable()
{
	__super::OnEnable();

}

void CImageComponent::OnDisable()
{
	__super::OnDisable();

}
