#pragma once
#ifndef THERESA_H
#define THERESA_H

#define Axe_0	5
#define Axe_1	6
#define Axe_2	7
#define Sword_0 3
#define Sword_1 4

#include "Valkyrie.h"
class CTheresa final : public CValkyrie
{
	SMART_DELETER_REGISTER

private:
	CTheresa();
	~CTheresa();

public:
	static			SP(CTheresa)				Create(_bool isStatic, Engine::CScene* pScene);

public:
					SP(Engine::CObject)		MakeClone			(void) override;
		
					void					Awake				(void) override;
					void					Start				(void) override;
		
					void					FixedUpdate			(void) override;
					void					Update				(void) override;
					void					LateUpdate			(void) override;

					void					PreRender			(LPD3DXEFFECT pEffect) override;
					void					Render				(LPD3DXEFFECT pEffect) override;
					void					PostRender			(LPD3DXEFFECT pEffect) override;
		
					void					OnDestroy			(void) override;
		
					void					OnEnable			(void) override;
					void					OnDisable			(void) override;

					void					SetBasicName		(void) override;

					void					ApplyHitInfo		(HitInfo info) override;
public:
					void					On_Sword			(void);
					void					Off_Sword			(void);
					void					On_Axe				(void);
					void					Off_Axe				(void);
					
					void					SetChargeMode		(bool value);
					

private:
	std::vector<Engine::_DerivedD3DXMESHCONTAINER*> m_vMeshContainers;
	_uint idx = 0;
	
	GETTOR			(_bool,			m_chargeMode,			false,		ChargeMode)

private:
	
	GETTOR			(_mat*,			m_pLeftHand_World,		nullptr,	LeftHandWorldMatrix)
	GETTOR			(_mat*,			m_pRightHand_World,		nullptr,	RightHandWorldMatrix)
	Engine::D3DXFRAME_DERIVED*	m_pLeftHand_Frame = nullptr;
	Engine::D3DXFRAME_DERIVED*	m_pRightHand_Frame = nullptr;

	GETTOR			(CAttackBall*,	m_pAttackBall_LeftHand,		nullptr,	AttackBall_LeftHand)
	GETTOR			(CAttackBall*,	m_pAttackBall_RightHand,	nullptr,	AttackBall_RightHand)

};


#endif