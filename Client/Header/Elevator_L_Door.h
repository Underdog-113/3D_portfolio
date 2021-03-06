#pragma once
#include "Object.h"
class CElevator_L_Door : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CElevator_L_Door();
	~CElevator_L_Door();

public:
	static		SP(CElevator_L_Door)			Create(_bool isStatic, Engine::CScene* pScene);

	SP(Engine::CObject)			MakeClone(void) override;

	void						Awake(void) override;
	void						Start(void) override;

	void						FixedUpdate(void) override;
	void						Update(void) override;
	void						LateUpdate(void) override;

	void						PreRender(LPD3DXEFFECT pEffect) override;
	void						Render(LPD3DXEFFECT pEffect) override;
	void						PostRender(LPD3DXEFFECT pEffect) override;

	void						OnDestroy(void) override;

	void						OnEnable(void) override;
	void						OnDisable(void) override;

	void						SetBasicName(void)  override;

	GETTOR(SP(Engine::CMeshC), m_spMesh, nullptr, Mesh)
	GETTOR(SP(Engine::CGraphicsC), m_spGraphics, nullptr, Graphics)
	GETTOR(SP(Engine::CTextureC), m_spTexture, nullptr, Texture)
	GETTOR(SP(Engine::CShaderC), m_spShader, nullptr, Shader)
	GETTOR_SETTOR(_float, m_fAlpha, 1.f, Alpha)
	GETTOR_SETTOR(_bool, m_bDoorCheck, false, DoorCheck)

private:
	static		_uint m_s_uniqueID;
};

