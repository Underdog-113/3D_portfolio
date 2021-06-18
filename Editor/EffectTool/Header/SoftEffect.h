#pragma once

class CSoftEffect final : public Engine::CObject
{
	SMART_DELETER_REGISTER

private:
	CSoftEffect();
	~CSoftEffect();

public:
	static	SP(CSoftEffect) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;
	void Awake(void) override;
	void Start(void) override;

	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;

	void PreRender(void) override;
	void PreRender(LPD3DXEFFECT pEffect)override;

	void Render(void) override;
	void Render(LPD3DXEFFECT pEffect)override;

	void PostRender(void) override;
	void PostRender(LPD3DXEFFECT pEffect)override;


	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

	void SetBasicName(void) override;

private:
	static _uint m_s_uniqueID;

	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, {}, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, {}, Texture)
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, {}, RectTex)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)
	GETTOR_SETTOR(_float, m_fAlphaWidth, 0.f, AlphaWIdth)
	GETTOR_SETTOR(_float, m_fAlphaHeight, 0.f, AlphaHeight)

private:
	_float m_fTIme;
	_int   m_xIndex;
	_int   m_yIndex;
	_bool  m_isPlayingAnim;
};

