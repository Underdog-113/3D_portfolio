#pragma once
#include "MeshEffect_Client.h"

class CAttackTrail_Client : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

protected:
	CAttackTrail_Client();
	virtual ~CAttackTrail_Client() = default;

public:
	SP(Engine::CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void PreRender(LPD3DXEFFECT pEffect) PURE;
	void Render(LPD3DXEFFECT pEffect) PURE;
	void PostRender(LPD3DXEFFECT pEffect) PURE;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()override;

protected:
	GETTOR(SP(Engine::CMeshC), m_spMesh, nullptr, Mesh)
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)
	static		_uint m_s_uniqueID;
};

