#pragma once
#include "Monster.h"

class CMB_Ganesha : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMB_Ganesha();
	~CMB_Ganesha();

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

	virtual			void			OnCollisionEnter	(Engine::_CollisionInfo ci) {}
	virtual			void			OnCollisionStay		(Engine::_CollisionInfo ci) {}
	virtual			void			OnCollisionExit		(Engine::_CollisionInfo ci) {}

	virtual			void			OnTriggerEnter		(Engine::CCollisionC const* pCollisionC) {}
	virtual			void			OnTriggerStay		(Engine::CCollisionC const* pCollisionC) {}
	virtual			void			OnTriggerExit		(Engine::CCollisionC const* pCollisionC) {}


	virtual void SetBasicName(void) override;

	virtual void ApplyHitInfo(HitInfo info) override;
	virtual void MonsterDead() override;

public:
	static SP(CMB_Ganesha) Create(_bool isStatic, Engine::CScene* pScene);

	void DoubleJump(_float3 mPos);

private:
	static _uint m_s_uniqueID;

	GETTOR_SETTOR(_int, m_jumpCnt, 2, JumpCnt)
};

