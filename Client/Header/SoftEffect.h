#pragma once

class CSoftEffect abstract : public Engine::CObject
{
	SMART_DELETER_REGISTER

protected:
	CSoftEffect();
	~CSoftEffect();

public:
	SP(Engine::CObject) MakeClone(void) PURE;

	virtual void Awake(void) override;
	virtual void Start(void) override;

	virtual void FixedUpdate(void) override;
	virtual void Update(void) override;
	virtual void LateUpdate(void) override;

	virtual void PreRender(LPD3DXEFFECT pEffect) PURE;
	virtual void Render(LPD3DXEFFECT pEffect) PURE;
	virtual void PostRender(LPD3DXEFFECT pEffect) PURE;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;
	virtual void OnDisable(void) override;

	virtual void SetBasicName(void) override;

private:
	static _uint m_s_uniqueID;

protected:
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, {}, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, {}, Texture)
	GETTOR(SP(Engine::CRectTexC), m_spRectTex, {}, RectTex)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)
	GETTOR(SP(Engine::CCollisionC), m_spCollision, nullptr, Collision)

	GETTOR_SETTOR(_float, m_fAlphaWidth, 0.f, AlphaWIdth)
	GETTOR_SETTOR(_float, m_fAlphaHeight, 0.f, AlphaHeight)
	GETTOR_SETTOR(_int, m_maxXIndex, 0, maxXIndex)
	GETTOR_SETTOR(_int, m_maxYIndex, 0, maxYIndex)
	GETTOR_SETTOR(_bool, m_AnimisPlay, false, AnimisPlay)
	GETTOR_SETTOR(_int, m_TilingX, 0, TilingX)
	GETTOR_SETTOR(_int, m_TilingY, 0, TilingY)

protected:
	_float m_fTIme;
};

