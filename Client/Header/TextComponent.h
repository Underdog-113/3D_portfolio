#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

class CTextObject;
class CTextComponent final : public Engine::CComponent
{
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	GETTOR(std::wstring, m_text, L"NULL", Text);
	GETTOR_SETTOR(_int, m_fontSize, 1, FontSize);
	GETTOR_SETTOR(_float, m_interval, 1.0f, Interval);
	GETTOR_SETTOR(_float, m_kerning, 1.0f, Kerning);
	GETTOR_SETTOR(D3DXCOLOR, m_color, D3DXCOLOR(1, 1, 1, 1), Color);

	GETTOR_SETTOR(_int, m_sortLayer, 0, SortLayer);
	GETTOR_SETTOR(std::list<SP(Engine::CObject)>, m_textObject, {}, TextObject);
	_int m_textSize;
public:
	explicit CTextComponent();
	~CTextComponent();

	// CComponent을(를) 통해 상속됨
	virtual SP(Engine::CComponent) MakeClone(Engine::CObject *pObject);
	virtual void Awake();
	virtual void Start(SP(Engine::CComponent) spThis);
	virtual void FixedUpdate(SP(Engine::CComponent) spThis);
	virtual void Update(SP(Engine::CComponent) spThis);
	virtual void LateUpdate(SP(Engine::CComponent) spThis);
	virtual void OnDestroy();
	virtual void OnEnable();
	virtual void OnDisable();

	void SetText(std::wstring text);
	void AddFontData(std::wstring text, _float interval, _float kerning, _int fontSize, D3DXCOLOR color);

private:
	void TextImageInput();
};

#endif