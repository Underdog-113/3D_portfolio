#pragma once
#include "Monster.h"

class CAttackBall;
class CBronyaBullet;
class CBronyaGrenade;

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

			virtual void OnCollisionEnter(Engine::_CollisionInfo ci);
			virtual void OnCollisionStay(Engine::_CollisionInfo ci);
			virtual void OnCollisionExit(Engine::_CollisionInfo ci);
						 
			virtual void OnTriggerEnter(Engine::CCollisionC const* pCollisionC);
			virtual void OnTriggerStay(Engine::CCollisionC const* pCollisionC);
			virtual void OnTriggerExit(Engine::CCollisionC const* pCollisionC);

			void SetBasicName(void) override;
			
private:
	void EquipWeapon();
	void ArsenalEffectPosLoad();
	void BulletReload();
	void EquipBomb();
	void EquipGrenade();
	void SetupEscapePos();
	void ApplyHitInfo(HitInfo info) override;
	virtual void MonsterDead() override;

private:
	static _uint m_s_uniqueID;
	const _mat* m_pParentBoneMat = nullptr;
	const _mat* m_pParentWorldMat = nullptr;
	_mat m_actualBoneMat;
	_float3 m_vDir;

	GETTOR(_int, m_maxArsenalEffectCnt, 0, MaxArsenalEffectCnt)
	GETTOR(_int, m_maxEscapePos, 0, MaxEscapePos)
	GETTOR(SP(Engine::CObject), m_spWeapon, nullptr, Weapon)
	GETTOR(std::vector<SP(CBronyaBullet)>, m_vBullets, {}, Bullets) // Shoot1 Skill
	GETTOR(std::vector<SP(CBronyaBullet)>, m_vExplosions, {}, Explosions) // Arsenal Skill
	GETTOR(std::vector<SP(CBronyaGrenade)>, m_vGrenades, {}, Grenades) // Throw1 Skill
	GETTOR(std::vector<_float3>, m_vEscapePos, {}, EscapePos) // Escape Skill
	GETTOR(std::vector<_float3>, m_vRingEffectPos, {}, RingEffectPos)
	GETTOR(std::vector<_float3>, m_vRangeEffectPos, {}, RangeEffectPos)
private:
	GETTOR_SETTOR(_float, m_fAlpha, 1.f, Alpha)
public:
	static SP(CMB_Bronya) Create(_bool isStatic, Engine::CScene* pScene);
	void ChaseTarget(_float3 targetPos);
};
