#pragma once
#include "MeshEffect_Client.h"

class CScoutBall
	: public CMeshEffect_Client
{
	SMART_DELETER_REGISTER
public:
	CScoutBall();
	~CScoutBall();

public:
	static		SP(CScoutBall)			Create(_bool isStatic, Engine::CScene* pScene);

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

public:
	GETTOR_SETTOR(_bool, m_bFlyingBall, false, FlyingBall)
	GETTOR_SETTOR(_bool, m_ready,		false,	Ready)
	GETTOR_SETTOR(_float3, m_direction, ZERO_VECTOR, Direction)
};

