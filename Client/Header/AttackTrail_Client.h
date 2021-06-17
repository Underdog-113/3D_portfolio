#pragma once
#include "MeshEffect_Client.h"

class CAttackTrail_Client : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CAttackTrail_Client();
	~CAttackTrail_Client();

public:
	static		SP(CAttackTrail_Client)			Create(_bool isStatic, Engine::CScene* pScene);

	SP(Engine::CObject) MakeClone() override;

	void Awake() override;
	void Start() override;
	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void PreRender() override;
	void PreRender(LPD3DXEFFECT pEffect) override;

	void Render() override;
	void Render(LPD3DXEFFECT pEffect) override;

	void PostRender() override;
	void PostRender(LPD3DXEFFECT pEffect) override;

	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void SetBasicName()override;

private:
	static		_uint m_s_uniqueID;
};

