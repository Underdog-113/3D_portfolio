#pragma once
#include "SoftEffect.h"

class CScoutMeteor : public CSoftEffect
{
	SMART_DELETER_REGISTER

public:
	CScoutMeteor();
	~CScoutMeteor();

public:
	static	SP(CScoutMeteor) Create(_bool isStatic, Engine::CScene* pScene);
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

	void OnCollisionEnter(Engine::_CollisionInfo ci);
	void OnCollisionStay(Engine::_CollisionInfo ci);
	void OnCollisionExit(Engine::_CollisionInfo ci);

private:
	static _uint m_s_uniqueID;

};

