#ifndef DEBUGTEXTCOMPONENT_H
#define DEBUGTEXTCOMPONENT_H

class CDebugTextComponent final : public Engine::CComponent
{
public:
	static const	EComponentID	m_s_componentID = EComponentID::DebugText;
private:
	Engine::_Text* m_textData;

	GETTOR_SETTOR(std::wstring, m_text, L"NULL", Text);
	GETTOR_SETTOR(_float2, m_boxSize, _float2(200, 200), BoxSize);
	GETTOR_SETTOR(_int, m_fontSize, 50, FontSize);
	GETTOR_SETTOR(DWORD, m_alignment, {}, Alignment);
	GETTOR_SETTOR(D3DXCOLOR, m_color, D3DXCOLOR(1, 1, 1, 1), Color);
public:
	explicit CDebugTextComponent();
	~CDebugTextComponent();

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

	void AddFontData(std::wstring text, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color);
};

#endif