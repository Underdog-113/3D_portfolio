#pragma once
class CImageObject final : public Engine::CObject
{
private:
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, {}, Graphics);
	GETTOR(SP(Engine::CTextureC), m_spTexture, {}, Texture);
	GETTOR(SP(Engine::CBitmapC), m_spBitmap, {}, Bitmap);
public:
	CImageObject();
	~CImageObject();

	// CObject을(를) 통해 상속됨
	static	SP(CImageObject) Create(_bool isStatic, Engine::CScene* pScene);
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

private:

};

