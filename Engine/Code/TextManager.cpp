#include "EngineStdafx.h"
 
#include "DeviceManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTextManager)
void CTextManager::Awake(void)
{
	__super::Awake();
	AddFontResourceEx(_SOLUTIONDIR L"Resource\\Font\\KCCChassam.ttf", FR_PRIVATE, 0);
}

void CTextManager::Start(void)
{

	if (FAILED(D3DXCreateFont(GET_DEVICE, 0, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"SohoGothicProMedium", &m_pFont)))
	{
		MSG_BOX(__FILE__, L"TextManager.cpp / 19");
	}
}

void CTextManager::PreRender(void)
{
	GET_DEVICE->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 125, 125, 125),
		1.f, 0);

	GET_DEVICE->BeginScene();
}

void CTextManager::Render(void)
{
	for (auto& text : m_mTexts)
	{
		DrawMyText(text.second);
	}
}

void CTextManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	GET_DEVICE->Present(NULL, NULL, NULL, NULL);
}

void CTextManager::OnDestroy(void)
{
	for (auto& text : m_mTexts)
	{
		delete text.second;
		text.second = nullptr;
	}

	m_mTexts.clear();
}

void CTextManager::ClearForScene(void)
{
	for (auto& text : m_mTexts)
	{
		delete text.second;
	}

	m_mTexts.clear();
}

_Text* CTextManager::AddText(std::wstring textKey, std::wstring msg, _float2 position, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color)
{
	_Text* pNewText = new _Text;
	
	pNewText->m_message		= msg;
	pNewText->m_position	= position;
	pNewText->m_boxSize		= boxSize;
	pNewText->m_fontSize	= fontSize;
	pNewText->m_alignment	= alignment;
	pNewText->m_color		= color;
	pNewText->m_isVisible	= true;
	m_mTexts[textKey] = pNewText;

	return pNewText;
}

void CTextManager::ResetText(std::wstring textKey, std::wstring msg, _float2 position, D3DXCOLOR color)
{
	m_mTexts[textKey]->m_message	= msg;
	m_mTexts[textKey]->m_position	= position;
	m_mTexts[textKey]->m_color		= color;
}

void CTextManager::RewriteText(std::wstring textKey, std::wstring msg)
{
	m_mTexts[textKey]->m_message = msg;
}

void CTextManager::MoveText(std::wstring textKey, _float2 position)
{
	m_mTexts[textKey]->m_position = _float2(position.x, position.y);
}

void CTextManager::ChangeColorText(std::wstring textKey, D3DXCOLOR color)
{
	m_mTexts[textKey]->m_color = color;
}

void CTextManager::DeleteText(std::wstring textKey)
{
	auto& it = m_mTexts.find(textKey);
	delete (*it).second;
	m_mTexts.erase(it);
}

void CTextManager::DrawMyText(_Text* pText) // 여기서 텍스쳐와 글을써주면되는데 어떻게 써주지?
{
	/*if (FAILED(D3DXCreateFont(GET_DEVICE, pText->m_fontSize * -1, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"SohoGothicProMedium", &m_pFont)))
	{
		MSG_BOX(__FILE__, L"TextManager.cpp / 106");
		m_pFont = nullptr;
	}*/

	if (!m_pFont)

		return;

	std::basic_string<WCHAR> msg = pText->m_message.c_str();

	RECT rect = { _int(pText->m_position.x), _int(pText->m_position.y), 
				  _int(pText->m_position.x + pText->m_boxSize.x), _int(pText->m_position.y + pText->m_boxSize.y) };

	m_pFont->DrawText(NULL, msg.c_str(), -1, &rect, pText->m_alignment, pText->m_color);
}
