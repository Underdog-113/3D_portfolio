#pragma once
#include "Monster.h"

class CMO_Lancer : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMO_Lancer();
	~CMO_Lancer();

public:
	virtual SP(CObject) MakeClone(void) override;

	virtual void Awake(void) override;

	virtual void Start(void) override;

	virtual void FixedUpdate(void) override;

	virtual void Update(void) override;

	virtual void LateUpdate(void) override;

	virtual void PreRender(LPD3DXEFFECT pEffect) override;
	virtual void Render(LPD3DXEFFECT pEffect) override;
	virtual void PostRender(LPD3DXEFFECT pEffect) override;

	virtual void OnDestroy(void) override;

	virtual void OnEnable(void) override;

	virtual void OnDisable(void) override;

	virtual void SetBasicName(void) override;

	virtual void ApplyHitInfo(HitInfo info) override;
public:
	static		SP(CMO_Lancer)			Create(_bool isStatic, Engine::CScene* pScene);
	void						SetStatus(BaseStat stat);
	void						MonsterDead() override;

private:
	static		_uint						m_s_uniqueID;
};

