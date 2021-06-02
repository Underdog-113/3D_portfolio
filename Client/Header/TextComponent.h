#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

class CTextComponent final : public Engine::CComponent
{
public:
	static const	EComponentID	m_s_componentID = EComponentID::Image;
private:
	GETTOR_SETTOR(std::wstring, m_text, {}, Text);
	GETTOR_SETTOR(std::wstring, m_font, {}, Font);
	GETTOR_SETTOR(DWORD, m_alignment, {}, Alignment);
	GETTOR_SETTOR(D3DXCOLOR, m_color, D3DXCOLOR(255,255,255,255), Color);

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
};

#endif