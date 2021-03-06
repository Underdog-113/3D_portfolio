#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CTextManager final : public CEngine
{
	DECLARE_SINGLETON(CTextManager)
public:
	void		Awake				(void) override;
	void		Start				(void);

	void		PreRender			(void);
	void		Render				(void);
	void		PostRender			(void);

	void		OnDestroy			(void);
	void		ClearForScene		(void);

public:
	_Text*		AddText				(std::wstring textKey, std::wstring msg,
									 _float2 position, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color);

	void		ResetText			(std::wstring textKey, std::wstring msg, _float2 position, D3DXCOLOR color);
	void		RewriteText			(std::wstring textKey, std::wstring msg);
	void		MoveText			(std::wstring textKey, _float2 position);
	void		ChangeColorText		(std::wstring textKey, D3DXCOLOR color);
	void		DeleteText			(std::wstring textKey);

private:
	void		DrawMyText			(_Text* pText);
private:
	typedef std::unordered_map<std::wstring, _Text*> _TEXTS;

	_TEXTS		m_mTexts;
	LPD3DXFONT	m_pFont;

};
END
#endif	