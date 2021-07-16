#pragma once
#include "MeshEffect_Client.h"

class CSakura_WSkill_Twist : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CSakura_WSkill_Twist();
	~CSakura_WSkill_Twist();

public:
	static SP(CSakura_WSkill_Twist) Create(_bool isStatic, Engine::CScene* pScene);

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
	GETTOR_SETTOR(_float3, m_MoveDir, _float3(0.f,0.f,0.f), MoveDir)

private:
	_float m_fLifeTime;
	SP(Engine::CObject) m_spTwistWind;
};

