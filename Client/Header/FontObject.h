#pragma once
class CFontObject final : public Engine::CObject
{
private:
	LPD3DXFONT m_font;

	Engine::_Text* m_textData;

	GETTOR_SETTOR(std::wstring, m_text, L"NULL", Text)
	GETTOR_SETTOR(_float2, m_boxSize, _float2(200, 200), BoxSize)
	GETTOR_SETTOR(_int, m_fontSize, 50, FontSize)
	GETTOR_SETTOR(DWORD, m_alignment, 0, Alignment)
	GETTOR_SETTOR(D3DXCOLOR, m_color, D3DXCOLOR(1, 1, 1, 1), Color)
public:
	CFontObject();
	~CFontObject();

	// CObject을(를) 통해 상속됨
	static	SP(CFontObject) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;
	void Awake(void) override;
	void Start(void) override;
	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;
	void OnDestroy(void) override;
	void OnEnable(void) override;
	void OnDisable(void) override;
	void SetBasicName(void) override;

	void AddFontData(std::wstring text, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color);
private:


};

