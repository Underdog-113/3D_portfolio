#pragma once
#include "MeshEffect_Client.h"

class CMonsterSpawnEff : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CMonsterSpawnEff();
	~CMonsterSpawnEff();

public:
	static SP(CMonsterSpawnEff) Create(_bool isStatic, Engine::CScene* pScene);
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

