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

			void PreRender(void) override;
			void Render(void) override;
			void PostRender(void) override;

			void OnDestroy(void) override;

			void OnEnable(void) override;

			void OnDisable(void) override;

			void SetBasicName(void) override;

private:
	void   EquipWeapon();

private:
	const _mat*  m_pParentBoneMat = nullptr;
	const _mat*  m_pParentWorldMat = nullptr;
	_float3		 m_vDir;

public:
	static		SP(CMB_Bronya)			Create(_bool isStatic, Engine::CScene* pScene);
};

