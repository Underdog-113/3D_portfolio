#pragma once
#include "Monster.h"

class CMO_Sickle : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMO_Sickle();
	~CMO_Sickle();

public:
	virtual SP(CObject) MakeClone(void) override;

	virtual void Awake(void) override;

	virtual void Start(void) override;

	virtual void FixedUpdate(void) override;

	virtual void Update(void) override;

	virtual void LateUpdate(void) override;

	virtual void PreRender(void) override;
	virtual void PreRender(LPD3DXEFFECT pEffect) override;

	virtual void Render(void) override;
	virtual void Render(LPD3DXEFFECT pEffect) override;

	virtual void PostRender(void) override;
	virtual void PostRender(LPD3DXEFFECT pEffect) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;

	virtual void OnDisable(void) override;

	virtual void SetBasicName(void) override;

public:
	static		SP(CMO_Sickle)			Create(_bool isStatic, Engine::CScene* pScene);
	void ChaseTarget(_float3 targetPos);

private:
	static		_uint				m_s_uniqueID;
};
