#pragma once
#include "SoftEffect.h"

class CBronya_Teleport_Ring : public CSoftEffect
{
	SMART_DELETER_REGISTER

public:
	CBronya_Teleport_Ring();
	~CBronya_Teleport_Ring();

public:
	static	SP(CBronya_Teleport_Ring) Create(_bool isStatic, Engine::CScene* pScene);
	SP(Engine::CObject) MakeClone(void) override;
	void Awake(void) override;
	void Start(void) override;

	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;

	void PreRender(LPD3DXEFFECT pEffect)override;
	void Render(LPD3DXEFFECT pEffect)override;
	void PostRender(LPD3DXEFFECT pEffect)override;


	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

	void SetBasicName(void) override;

private:
	static _uint m_s_uniqueID;

	void UpdateFrame(_float _frmSpeed);

};

