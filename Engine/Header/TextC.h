#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

BEGIN(Engine)
class CObject;
class ENGINE_DLL CTextC  final : public CComponent
{
public:
	explicit CTextC();
	~CTextC();

	// CComponent을(를) 통해 상속됨
	SP(CComponent) MakeClone(CObject *pObject) override;
	void Awake()override;
	void Start(SP(CComponent) spThis)override;
	void FixedUpdate(SP(CComponent) spThis)override;
	void Update(SP( CComponent) spThis)override;
	void LateUpdate(SP( CComponent) spThis)override;
	void OnDestroy()override;
	void OnEnable()override;
	void OnDisable()override;

	void AddFontData(std::wstring text, _float2 offset, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color);
	void RenderText();
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	LPD3DXFONT	m_pFont;
	_Text m_textData;

	GETTOR_SETTOR(_float2, m_offset, _float2(0, 0), OffSet)
};
END
#endif