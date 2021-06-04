#include "EngineStdafx.h"
#include "TextC.h"

USING(Engine)
CTextC::CTextC()
{
}

CTextC::~CTextC()
{
	OnDestroy();
}

SP(CComponent) CTextC::MakeClone(CObject *pObject)
{
	SP(CTextC) spClone(new CTextC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CTextC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;

	AddFontResourceEx(L"..\\..\\Resource\\Font\\KCCChassam.ttf", FR_PRIVATE, 0);
}

void CTextC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	if (FAILED(D3DXCreateFont(GET_DEVICE, 0, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"SohoGothicProMedium", &m_pFont)))
	{
		MSG_BOX(__FILE__, L"CFontObject.cpp / 45");
	}
}

void CTextC::FixedUpdate(SP(CComponent) spThis)
{
	
}

void CTextC::Update(SP(CComponent) spThis)
{
}

void CTextC::LateUpdate(SP(CComponent) spThis)
{

}

void CTextC::OnDestroy()
{
}

void CTextC::OnEnable()
{
	__super::OnEnable();
}

void CTextC::OnDisable()
{
	__super::OnDisable();
}

void CTextC::AddFontData(std::wstring text, _float2 offset, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color)
{
	m_offset = offset;

	m_textData.m_message = text;
	m_textData.m_boxSize = boxSize;
	m_textData.m_fontSize = fontSize;
	m_textData.m_alignment = alignment;
	m_textData.m_color = color;
}

void CTextC::RenderText()
{
	if (!m_pFont)
		return;

	std::basic_string<WCHAR> msg = m_textData.m_message.c_str();

	_float2 pos = GetOwner()->GetTransform()->GetPosition();
	pos += m_offset;

	RECT rect = { _int(pos.x), _int(pos.y),
		_int(pos.x + m_textData.m_boxSize.x), _int(pos.y + m_textData.m_boxSize.y) };

	m_pFont->DrawText(NULL, msg.c_str(), -1, &rect, m_textData.m_alignment, m_textData.m_color);
}
