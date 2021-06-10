#pragma once
class CEffectMesh final: public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CEffectMesh();
	~CEffectMesh();

public:
	static		SP(CEffectMesh)			Create(_bool isStatic, Engine::CScene* pScene);

	SP(CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void PreRender() override;
	void PreRender(LPD3DXEFFECT pEffect) override;

	void Render() override;
	void Render(LPD3DXEFFECT pEffect) override;

	void PostRender() override;
	void PostRender(LPD3DXEFFECT pEffect) override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()override;
		
private:
	void	PickComponentToRender(void);

protected:
	static		_uint						m_s_uniqueID;
	GETTOR(SP(Engine::CRenderComponent), m_spComponentToRender, nullptr, ComponentToRender)
	GETTOR(SP(Engine::CMeshC), m_spMesh, nullptr, Mesh)
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
};

