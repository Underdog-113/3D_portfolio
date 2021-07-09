#pragma once
#include "MeshEffect_Client.h"

class CLancer_OutSideEff : public CMeshEffect_Client
{
	SMART_DELETER_REGISTER

public:
	CLancer_OutSideEff();
	~CLancer_OutSideEff();

public:
	static		SP(CLancer_OutSideEff)			Create(_bool isStatic, Engine::CScene* pScene);

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
	_float m_fTimer;

private:
	_uint m_iCnt;

};

