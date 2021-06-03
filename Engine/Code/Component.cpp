#include "EngineStdafx.h"
#include "Component.h"
#include "Object.h"

USING(Engine)
CComponent::CComponent(void)
{
}
CComponent::~CComponent(void)
{
}

void CComponent::InitClone(SP(CComponent) spClone, CObject * pOwner)
{
	spClone->SetOwner(pOwner);
	spClone->SetName(m_name);
	spClone->SetIsAwaked(m_isAwaked);
	spClone->SetComponentID(m_componentID);
	spClone->SetIsEnabled(m_isEnabled);
}

void CComponent::Awake(void)
{
	m_isAwaked = true;
	m_name = GetCurClassName(this);
}

void CComponent::Start(SP(CComponent) spThis)
{
	m_isStarted = true;
}

void CComponent::OnEnable(void)
{
	m_isEnabled = true;
}

void CComponent::OnDisable(void)
{
	m_isEnabled = false;
}

void CComponent::SetIsEnabled(_bool var)
{
	if (m_isEnabled == var)
		return;

	if (var == true)
		OnEnable();
	else
		OnDisable();
}
