#include "EngineStdafx.h"
#include "TextC.h"
#include "WndApp.h"

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

	AddFontResourceEx(_SOLUTIONDIR L"Resource\\Font\\koverwatch.ttf", FR_PRIVATE, 0);
}

void CTextC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	if (m_pOwner->GetComponent<CGraphicsC>() == nullptr)
		m_pOwner->AddComponent<CGraphicsC>()->SetRenderID((_int)ERenderID::UI);

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

void CTextC::PreRender(SP(CGraphicsC) spGC)
{
}

void CTextC::Render(SP(CGraphicsC) spGC)
{
	RenderText();
}

void CTextC::PostRender(SP(CGraphicsC) spGC)
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

void CTextC::AddFontData(std::wstring message, _float2 position, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color, _bool isVisible)
{
	_float2 correction = _float2(CWndApp::GetInstance()->GetWndWidth() * 0.5f, CWndApp::GetInstance()->GetWndHeight() * 0.5f);
	_TextCom t(message, position + correction, boxSize, fontSize, alignment, color, isVisible);

	if (FAILED(D3DXCreateFont(GET_DEVICE, fontSize, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"koverwatch", &t.m_pFont)))
	{
		MSG_BOX(__FILE__, L"CTextC.cpp / AddFontData");
	}

	

	m_message = message;
	m_position = position;
	m_boxSize = boxSize;
	m_fontSize = fontSize;
	m_alignment = alignment;
	m_color = color;
	m_isVisible = isVisible;

	m_textData = t;
}

void CTextC::ChangeMessage(std::wstring message)
{
	_float2 correction = _float2(CWndApp::GetInstance()->GetWndWidth() * 0.5f, CWndApp::GetInstance()->GetWndHeight() * 0.5f);
	_TextCom t(message, m_position + correction, m_boxSize, m_fontSize, m_alignment, m_color, m_isVisible);

	if (FAILED(D3DXCreateFont(GET_DEVICE, m_fontSize, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"SohoGothicProMedium", &t.m_pFont)))
	{
		MSG_BOX(__FILE__, L"CTextC.cpp / AddFontData");
	}

	m_message = message;
	m_textData.m_pFont->Release();
	m_textData = t;
}

void CTextC::RenderText()
{
	std::basic_string<WCHAR> msg = m_textData.m_text.m_message.c_str();

	_float2 pos = GetOwner()->GetTransform()->GetPosition();
	pos.y *= -1;
	pos += m_textData.m_text.m_position;

	_float2 boxSize = m_textData.m_text.m_boxSize;
	RECT rect = { _int(pos.x), _int(pos.y),
		_int(pos.x + boxSize.x), _int(pos.y + boxSize.y) };

	m_textData.m_pFont->DrawText(NULL, msg.c_str(), -1, &rect, m_textData.m_text.m_alignment, m_textData.m_text.m_color);
}
