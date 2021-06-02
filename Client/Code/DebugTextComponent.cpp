#include "stdafx.h"
#include "DebugTextComponent.h"

CDebugTextComponent::CDebugTextComponent()
{
}

CDebugTextComponent::~CDebugTextComponent()
{
}

SP(Engine::CComponent) CDebugTextComponent::MakeClone(Engine::CObject *pObject)
{
	SP(CDebugTextComponent) spClone(new CDebugTextComponent);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CDebugTextComponent::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CDebugTextComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);

	_float2 pos = _float2(GetOwner()->GetTransform()->GetPosition().x, GetOwner()->GetTransform()->GetPosition().y);
	m_textData = Engine::CTextManager::GetInstance()->AddText(GetOwner()->GetName(), m_text, pos, m_boxSize, m_fontSize, m_alignment, m_color);
}

void CDebugTextComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
	
}

void CDebugTextComponent::Update(SP(Engine::CComponent) spThis)
{
}

void CDebugTextComponent::LateUpdate(SP(Engine::CComponent) spThis)
{
}

void CDebugTextComponent::OnDestroy()
{
}

void CDebugTextComponent::OnEnable()
{
	__super::OnEnable();

}

void CDebugTextComponent::OnDisable()
{
	__super::OnDisable();

}

void CDebugTextComponent::AddFontData(std::wstring text, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color)
{
	m_text = text;
	m_boxSize = boxSize;
	m_fontSize = fontSize;
	m_alignment = alignment;
	m_color = color;
}
