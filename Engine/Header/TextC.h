#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

BEGIN(Engine)
class CObject;
class ENGINE_DLL CTextC  final : public CRenderComponent
{
public:
	explicit CTextC();
	~CTextC();

	// CComponent¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	SP(CComponent) MakeClone(CObject *pObject) override;
	void Awake() override;
	void Start(SP(CComponent) spThis) override;
	void FixedUpdate(SP(CComponent) spThis) override;
	void Update(SP( CComponent) spThis) override;
	void LateUpdate(SP( CComponent) spThis) override;
	void PreRender(SP(CGraphicsC) spGC) override;
	void Render(SP(CGraphicsC) spGC) override;
	void PostRender(SP(CGraphicsC) spGC) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void AddFontData(std::wstring message, _float2 position, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color, _bool isVisible);
	void ChangeMessage(std::wstring message);
	void RenderText();
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	GETTOR_SETTOR(std::wstring, m_font, L"µ∏¿Ω", Font);
	_TextCom m_textData;

	std::wstring m_message;
	_float2 m_position;
	_float2 m_boxSize;
	_int m_fontSize;
	DWORD m_alignment;
	D3DXCOLOR m_color;
	_bool m_isVisible;
};
END
#endif
