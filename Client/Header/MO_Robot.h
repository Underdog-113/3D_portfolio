#pragma once
#include "Monster.h"

class CMO_Robot : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMO_Robot();
	virtual ~CMO_Robot();

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

	virtual	void OnCollisionEnter(Engine::_CollisionInfo ci);
	virtual	void OnCollisionStay(Engine::_CollisionInfo ci);
	virtual	void OnCollisionExit(Engine::_CollisionInfo ci);

	virtual void SetBasicName(void) override;

	virtual void ApplyHitInfo(HitInfo info) override;
public:
	static		SP(CMO_Robot)	Create(_bool isStatic, Engine::CScene* pScene);
	void						SetStatus(BaseStat stat);
	void						UpdatePivotMatrices(void);
	void						MonsterDead() override;

private:
	static		_uint				m_s_uniqueID;
	
	GETTOR_SETTOR(_bool, m_checkCol, false, CheckCol)
	GETTOR(SP(Engine::CObject), m_spPlane, {}, Plane)
};
