#pragma once
#include "MeshEffect_Client.h"

class CMB_Ganesha;

class CGanesha_Charge_Eff : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CGanesha_Charge_Eff();
	~CGanesha_Charge_Eff();

public:
	static		SP(CGanesha_Charge_Eff)			Create(_bool isStatic, Engine::CScene* pScene);

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

	GETTOR_SETTOR(Engine::CObject*, m_pOwner, nullptr, Owner)
};

