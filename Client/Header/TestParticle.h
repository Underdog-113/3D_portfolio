#pragma once
#include "Object.h"

class CTestParticle : public Engine::CObject
{
	SMART_DELETER_REGISTER

public:
	CTestParticle();
	~CTestParticle();

public:
	static	SP(CTestParticle)	Create(_bool isStatic, Engine::CScene* pScene);

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
	GETTOR_SETTOR(SP(Engine::CParticleSystemC), m_spParticleSystem, nullptr, ParticleSystem)

private:
	_float m_fLiftTime;
};

