#include "stdafx.h"
#include "TextComponent.h"

CTextComponent::CTextComponent()
{
}


CTextComponent::~CTextComponent()
{
}

SP(Engine::CComponent) CTextComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CTextComponent) spClone(new CTextComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CTextComponent::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;;
}

void CTextComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);
	Engine::CTextManager::GetInstance()->AddText(GetOwner()->GetName(), m_text, GetOwner()->GetTransform()->GetPosition(), m_color);
}

void CTextComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
	
}

void CTextComponent::Update(SP(Engine::CComponent) spThis)
{
	
}

void CTextComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CTextComponent::OnDestroy()
{
}

void CTextComponent::OnEnable()
{
	__super::OnEnable();

}

void CTextComponent::OnDisable()
{
	__super::OnDisable();

}
