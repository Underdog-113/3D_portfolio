#pragma once
#include "Object.h"

class CSakura_DashShade : public  Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CSakura_DashShade();
	~CSakura_DashShade();

public:
	static SP(CSakura_DashShade) Create(_bool isStatic, Engine::CScene* pScene);

	SP(Engine::CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void PreRender(LPD3DXEFFECT pEffect) override;
	void Render(LPD3DXEFFECT pEffect) override;
	void PostRender(LPD3DXEFFECT pEffect) override;

	void RenderPerShader(void) override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()override;

private:
	static		_uint m_s_uniqueID;
	GETTOR(SP(Engine::CMeshC), m_spMesh, nullptr, Mesh)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)

private:
	_float m_fAlpha;
	GETTOR_SETTOR(_int, m_iAnimIdx, 0, AnimIdx)

};

