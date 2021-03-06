#pragma once
#include "MeshEffect_Client.h"

class CMB_Ganesha;

class CGanesha_Dome_Impact : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CGanesha_Dome_Impact();
	~CGanesha_Dome_Impact();

public:
	static		SP(CGanesha_Dome_Impact)			Create(_bool isStatic, Engine::CScene* pScene);

	SP(Engine::CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void PreRender(LPD3DXEFFECT pEffect) override;
	void Render(LPD3DXEFFECT pEffect) override;
	void PostRender(LPD3DXEFFECT pEffect) override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()override;

private:
	static		_uint m_s_uniqueID;

private:
	GETTOR(SP(Engine::CObject), m_spDomeObject, nullptr, DomeObject)

	GETTOR_SETTOR(CMB_Ganesha*, m_pOwner, nullptr, Owner)
};
