#include "stdafx.h"
#include "TextComponent.h"
#include "ImageObject.h"

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

	m_componentID = (_int)m_s_componentID;
}

void CTextComponent::Start(SP(Engine::CComponent) spThis)
{
	__super::Start(spThis);
}

void CTextComponent::FixedUpdate(SP(Engine::CComponent) spThis)
{
	
}

void CTextComponent::Update(SP(Engine::CComponent) spThis)
{
	_float3 pos = GetOwner()->GetTransform()->GetPosition();
	_int value = 0;

	for (auto object : m_imageObject)
	{
		object->GetTransform()->SetPosition(pos);

		wchar_t textKey = m_text[value++];
		pos.x += m_interval;

		if (textKey == '\\')
		{
			pos.y += m_kerning;
		}

	}
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

void CTextComponent::SetText(std::wstring text)
{
	m_text = text;

	if (m_text.size() >= m_textSize)
	{
		for (int i = 0; i < m_textSize - m_text.size(); i++)
		{
			SP(CImageObject) object = std::dynamic_pointer_cast<CImageObject>(m_pOwner->GetScene()->GetObjectFactory()->AddClone(L"ImageObject", true));
			object->GetTransform()->SetSize(_float3(m_fontSize, m_fontSize, 0));
			m_imageObject.emplace_back(object);
		}
	}

	m_textSize = m_text.size();

	TextImageInput();
}

void CTextComponent::AddFontData(std::wstring text, _float interval, _float kerning, _int fontSize, D3DXCOLOR color)
{
	m_text = text;
	m_interval = interval;
	m_kerning = kerning;
	m_fontSize = fontSize;
	m_color = color;
	m_textSize = m_text.size();

	for (int i = 0; i < m_textSize; i++)
	{
		SP(CImageObject) object = std::dynamic_pointer_cast<CImageObject>(m_pOwner->GetScene()->GetObjectFactory()->AddClone(L"ImageObject", true));
		object->GetTransform()->SetSize(_float3(m_fontSize, m_fontSize, 0));
		m_imageObject.emplace_back(object);
	}

	TextImageInput();
}

void CTextComponent::TextImageInput()
{
	int value = 0;
	for (auto object : m_imageObject)
	{
		std::wstring textKey = m_text.substr(value++, 1);
		object->GetTexture()->AddTexture(textKey, m_sortLayer);
	}
}
