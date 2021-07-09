#pragma once
#include "SoftEffect.h"

class CLancer_Impact : public CSoftEffect
{
	SMART_DELETER_REGISTER

public:
	CLancer_Impact();
	~CLancer_Impact();

public:
	static		SP(CLancer_Impact)			Create(_bool isStatic, Engine::CScene* pScene);

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
	_float      m_fSpeed;
private:
	void UpdateFrame(_float _frmSpeed);
};

