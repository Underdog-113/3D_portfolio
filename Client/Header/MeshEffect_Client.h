#pragma once
class CMeshEffect_Client : public Engine::CObject
{
	SMART_DELETER_REGISTER

protected:
	CMeshEffect_Client();
	virtual	~CMeshEffect_Client() = default;

public:
	SP(Engine::CObject) MakeClone()PURE;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void PreRender(LPD3DXEFFECT pEffect)PURE;
	void Render(LPD3DXEFFECT pEffect)PURE;
	void PostRender(LPD3DXEFFECT pEffect)PURE;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()PURE;

protected:
	GETTOR(_float, m_fTrailAlpha,0.f, TrailAlpha);
	GETTOR(SP(Engine::CMeshC), m_spMesh, nullptr, Mesh)
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)
	GETTOR(SP(Engine::CRigidBodyC), m_spRigidC, nullptr, Rigid)

	GETTOR_SETTOR(_float, m_fAlpha, 1.f, Alpha)
	GETTOR_SETTOR(_float, m_fUVSpeed, 1.f, UVSpeed)
	GETTOR(_float, m_fTime, 0.f, Time)
};

