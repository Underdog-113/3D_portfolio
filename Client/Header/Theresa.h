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
public:
					void					UseSkill			(void) override;
					void					UseUltra			(void) override;

private:
					void					CreateCross			(void);

private:
	std::vector<Engine::_DerivedD3DXMESHCONTAINER*> m_vMeshContainers;
	_uint idx = 0;
	
	GETTOR			(_bool,			m_chargeMode,			false,		ChargeMode)

private:
	
	GETTOR			(SP(Engine::CObject),	m_spCrossBloodyHug,	nullptr,	CrossBloodyHug)

private:	
	GETTOR			(_mat*,			m_pLeftHand_World,		nullptr,	LeftHandWorldMatrix)
	GETTOR			(_mat*,			m_pRightHand_World,		nullptr,	RightHandWorldMatrix)
	Engine::D3DXFRAME_DERIVED*	m_pLeftHand_Frame = nullptr;
	Engine::D3DXFRAME_DERIVED*	m_pRightHand_Frame = nullptr;
	
	GETTOR			(_mat*,			m_pAxePivot_World,		nullptr,	AxePivotWorldMatrix)
	Engine::D3DXFRAME_DERIVED*	m_pAxePivot_Frame = nullptr;
	
	GETTOR			(CAttackBall*,	m_pAttackBall_LeftHand,		nullptr,	AttackBall_LeftHand)
	GETTOR			(CAttackBall*,	m_pAttackBall_RightHand,	nullptr,	AttackBall_RightHand)
	GETTOR			(CAttackBall*,	m_pAttackBall_Axe,			nullptr,	AttackBall_Axe)
	GETTOR			(CAttackBall*,	m_pAttackBall_AxeStick,		nullptr,	AttackBall_AxeStick)
	GETTOR			(CAttackBall*,	m_pAttackBall_AxeImpact,	nullptr,	AttackBall_AxeImpact)


public:

	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack1, nullptr, Effect_Attack1)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack2, nullptr, Effect_Attack2)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack3, nullptr, Effect_Attack3)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack4, nullptr, Effect_Attack4)
		
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Charge0, nullptr, Effect_Charge0)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Charge1, nullptr, Effect_Charge1)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Charge2, nullptr, Effect_Charge2)
		
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Ultra, nullptr, Effect_Ultra)

};


#endif