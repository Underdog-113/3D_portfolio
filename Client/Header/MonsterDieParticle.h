#pragma once
#include "SoftEffect.h"

class CMonsterDieParticle : public CSoftEffect
{
	SMART_DELETER_REGISTER

public:
	CMonsterDieParticle();
	~CMonsterDieParticle();

public:
	static SP(CMonsterDieParticle) Create(_bool isStatic, Engine::CScene* pScene);
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
	static		_uint m_s_uniqueID;
	_float3 m_tmpScale;

private:
	void InitParticle();
	void movement();
};

