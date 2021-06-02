#pragma once
class CTextObject final : public Engine::CObject
{
	SP(Engine::CTextureC) spTexture;
	SP(Engine::CBitmapC) spBitmap;
public:
	CTextObject();
	~CTextObject();

	// CObject을(를) 통해 상속됨
	virtual SP(Engine::CObject) MakeClone(void) override;
	virtual void Awake(void) override;
	virtual void Start(void) override;
	virtual void FixedUpdate(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void OnDestroy(void) override;
	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;
	virtual void SetBasicName(void) override;

	void AddFontData(std::wstring text, _float2 boxSize, _int fontSize, DWORD alignment, D3DXCOLOR color);

private:

};

