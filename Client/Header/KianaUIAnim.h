#pragma once

class CKianaUIAnim : public Engine::CObject
{
public:
	CKianaUIAnim();
	~CKianaUIAnim();

public:
	static			SP(CKianaUIAnim)				Create(_bool isStatic, Engine::CScene* pScene);

public:
	SP(Engine::CObject)		MakeClone(void) override;

	void					Awake(void) override;
	void					Start(void) override;

	void					FixedUpdate(void) override;
	void					Update(void) override;
	void					LateUpdate(void) override;

	void					PreRender(LPD3DXEFFECT pEffect) override;
	void					Render(LPD3DXEFFECT pEffect) override;
	void					PostRender(LPD3DXEFFECT pEffect) override;

	void					RenderPerShader(void) override;

	void					OnDestroy(void) override;

	void					OnEnable(void) override;
	void					OnDisable(void) override;

	void					SetBasicName(void) override;

	static		_uint						m_s_uniqueID;

	GETTOR(SP(Engine::CMeshC), m_spMesh, nullptr, Mesh)
		GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
		GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
		GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)
		GETTOR_SETTOR(std::wstring, m_textureName, L"Kiana_NoWp", TextureName);
};

