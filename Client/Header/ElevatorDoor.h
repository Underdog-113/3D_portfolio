#pragma once
#include "Object.h"

class CElevatorDoor : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CElevatorDoor();
	~CElevatorDoor();

public:
	static		SP(CElevatorDoor)			Create(_bool isStatic, Engine::CScene* pScene);

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
		
private:
	static		_uint m_s_uniqueID;

private:
	_bool m_bCheck;
};

