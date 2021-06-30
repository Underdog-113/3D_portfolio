#pragma once
#include "MeshEffect_Client.h"

class CTheresaCharge_Att : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CTheresaCharge_Att();
	~CTheresaCharge_Att();

public:
	static SP(CTheresaCharge_Att) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void PreRender(LPD3DXEFFECT pEffect)override;
	void Render(LPD3DXEFFECT pEffect)override;
	void PostRender(LPD3DXEFFECT pEffect)override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;
	void SetBasicName()override;

private:
	SP(CMeshEffect_Client) m_spTheresaSmoke = nullptr;
	_float m_fUVSpeed;
};

