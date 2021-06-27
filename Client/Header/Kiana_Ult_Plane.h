#pragma once
#include "MeshEffect_Client.h"

class CKiana_Ult_Plane : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CKiana_Ult_Plane();
	~CKiana_Ult_Plane();

public:
	static SP(CKiana_Ult_Plane) Create(_bool isStatic, Engine::CScene* pScene);
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
};

