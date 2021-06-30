#pragma once
#include "Monster.h"

class CMB_Bronya final : public CMonster
{
	SMART_DELETER_REGISTER

private:
	CMB_Bronya();
	~CMB_Bronya();

public:
			SP(CObject) MakeClone(void) override;

			void Awake(void) override;

			void Start(void) override;

			void FixedUpdate(void) override;

			void Update(void) override;

			void LateUpdate(void) override;

			void PreRender(LPD3DXEFFECT pEffect) override;
			void Render(LPD3DXEFFECT pEffect) override;
			void PostRender(LPD3DXEFFECT pEffect) override;

			void OnDestroy(void) override;

			void OnEnable(void) override;

			void OnDisable(void) override;

			virtual			void			OnCollisionEnter(Engine::_CollisionInfo ci);
			virtual			void			OnCollisionStay(Engine::_CollisionInfo ci);
			virtual			void			OnCollisionExit(Engine::_CollisionInfo ci);

			virtual			void			OnTriggerEnter(Engine::CCollisionC const* pCollisionC);
			virtual			void			OnTriggerStay(Engine::CCollisionC const* pCollisionC);
			virtual			void			OnTriggerExit(Engine::CCollisionC const* pCollisionC);

			void SetBasicName(void) override;

			void ApplyHitInfo(HitInfo info) override;
			virtual void MonsterDead() override;
private:
	void   EquipWeapon();

private:
	static _uint m_s_uniqueID;

	const _mat*  m_pParentBoneMat = nullptr;
	const _mat*  m_pParentWorldMat = nullptr;
	_float3		 m_vDir;

public:
	static		SP(CMB_Bronya)			Create(_bool isStatic, Engine::CScene* pScene);
	void ChaseTarget(_float3 targetPos);
};

