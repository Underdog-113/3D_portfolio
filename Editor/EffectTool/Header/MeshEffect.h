#pragma once
class CMeshEffect : public Engine::CObject
{
	SMART_DELETER_REGISTER

protected:
	CMeshEffect();
	virtual ~CMeshEffect() = default;

public:
	SP(CObject) MakeClone()PURE;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void PreRender()PURE;
	void PreRender(LPD3DXEFFECT pEffect)PURE;

	void Render()PURE;
	void Render(LPD3DXEFFECT pEffect)PURE;

	void PostRender()PURE;
	void PostRender(LPD3DXEFFECT pEffect)PURE;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()PURE;

protected:
	_float m_fTrailAlpha = 0.f;

private:
	GETTOR(SP(Engine::CMeshC), m_spMesh, nullptr, Mesh)
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)
	GETTOR(_float,  m_fAlpha, 1.f, Alpha)
    GETTOR(_float, m_fTime, 0.f, Time)
    

};

