#pragma once
#include "MeshEffect_Client.h"

class CKiana_Ult_Eff : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CKiana_Ult_Eff();
	~CKiana_Ult_Eff();

public:
	static SP(CKiana_Ult_Eff) Create(_bool isStatic, Engine::CScene* pScene);
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

	SP(CMeshEffect_Client) m_spKianaUltPlane = nullptr;
	SP(CMeshEffect_Client) m_spKianaUltRing = nullptr;
	SP(CMeshEffect_Client) m_spKianaUltShield = nullptr;

};

