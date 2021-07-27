#pragma once

#include "StateMachineC.h"

class CFSM_BronyaC final : public Engine::CStateMachineC
{
public:
	CFSM_BronyaC();
	~CFSM_BronyaC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

private:
	void RegisterAllStage();
	void FixRootMotionOffset(_uint index);

private:
	GETTOR_SETTOR(Engine::CDynamicMeshData*, m_pDM, nullptr, DM)

		_bool m_shake = false;
public:
	// <Animation List>

	// IDLE
	void IDLE_Init(void);
	void IDLE_Enter(void);
	void IDLE_Update(float deltaTime);
	void IDLE_End(void);

	// Run
	void Run_Init(void);
	void Run_Enter(void);
	void Run_Update(float deltaTime);
	void Run_End(void);

	// DashBack
	void DashBack_Init(void);
	void DashBack_Enter(void);
	void DashBack_Update(float deltaTime);
	void DashBack_End(void);

	// Arsenal_Charge
	void Arsenal_Charge_Init(void);
	void Arsenal_Charge_Enter(void);
	void Arsenal_Charge_Update(float deltaTime);
	void Arsenal_Charge_End(void);

	// Arsenal_Loop
	void Arsenal_Loop_Init(void);
	void Arsenal_Loop_Enter(void);
	void Arsenal_Loop_Update(float deltaTime);
	void Arsenal_Loop_End(void);

	// Arsenal_End
	void Arsenal_End_Init(void);
	void Arsenal_End_Enter(void);
	void Arsenal_End_Update(float deltaTime);
	void Arsenal_End_End(void);

	// Escape_Out
	void Escape_Out_Init(void);
	void Escape_Out_Enter(void);
	void Escape_Out_Update(float deltaTime);
	void Escape_Out_End(void);

	// Escape_In
	void Escape_In_Init(void);
	void Escape_In_Enter(void);
	void Escape_In_Update(float deltaTime);
	void Escape_In_End(void);

	// Evade_Left
	void Evade_Left_Init(void);
	void Evade_Left_Enter(void);
	void Evade_Left_Update(float deltaTime);
	void Evade_Left_End(void);

	// Evade_Right
	void Evade_Right_Init(void);
	void Evade_Right_Enter(void);
	void Evade_Right_Update(float deltaTime);
	void Evade_Right_End(void);

	// Attack_1
	void Attack_1_Init(void);
	void Attack_1_Enter(void);
	void Attack_1_Update(float deltaTime);
	void Attack_1_End(void);

	// Shoot_1
	void Shoot_1_Init(void);
	void Shoot_1_Enter(void);
	void Shoot_1_Update(float deltaTime);
	void Shoot_1_End(void);

	// Shoot_2
	void Shoot_2_Init(void);
	void Shoot_2_Enter(void);
	void Shoot_2_Update(float deltaTime);
	void Shoot_2_End(void);

	// Shoot_3
	void Shoot_3_Init(void);
	void Shoot_3_Enter(void);
	void Shoot_3_Update(float deltaTime);
	void Shoot_3_End(void);

	// Shock_1
	void Shock_1_Init(void);
	void Shock_1_Enter(void);
	void Shock_1_Update(float deltaTime);
	void Shock_1_End(void);

	// Shock_2
	void Shock_2_Init(void);
	void Shock_2_Enter(void);
	void Shock_2_Update(float deltaTime);
	void Shock_2_End(void);

	// Shock_2_Boom
	void Shock_2_Boom_Init(void);
	void Shock_2_Boom_Enter(void);
	void Shock_2_Boom_Update(float deltaTime);
	void Shock_2_Boom_End(void);

	// Shock_2_Miss
	void Shock_2_Miss_Init(void);
	void Shock_2_Miss_Enter(void);
	void Shock_2_Miss_Update(float deltaTime);
	void Shock_2_Miss_End(void);

	// Stealth_BACK
	void Stealth_BACK_Init(void);
	void Stealth_BACK_Enter(void);
	void Stealth_BACK_Update(float deltaTime);
	void Stealth_BACK_End(void);

	// Snealth
	void Snealth_Init(void);
	void Snealth_Enter(void);
	void Snealth_Update(float deltaTime);
	void Snealth_End(void);

	// Summon
	void Summon_Init(void);
	void Summon_Enter(void);
	void Summon_Update(float deltaTime);
	void Summon_End(void);

	// Throw_1
	void Throw_1_Init(void);
	void Throw_1_Enter(void);
	void Throw_1_Update(float deltaTime);
	void Throw_1_End(void);

	// Throw_2
	void Throw_2_Init(void);
	void Throw_2_Enter(void);
	void Throw_2_Update(float deltaTime);
	void Throw_2_End(void);

	// Throw_3
	void Throw_3_Init(void);
	void Throw_3_Enter(void);
	void Throw_3_Update(float deltaTime);
	void Throw_3_End(void);

	// Skill_Ultra
	void Skill_Ultra_Init(void);
	void Skill_Ultra_Enter(void);
	void Skill_Ultra_Update(float deltaTime);
	void Skill_Ultra_End(void);

	// Weak
	void Weak_Init(void);
	void Weak_Enter(void);
	void Weak_Update(float deltaTime);
	void Weak_End(void);

	// Weak_Hit_L
	void Weak_Hit_L_Init(void);
	void Weak_Hit_L_Enter(void);
	void Weak_Hit_L_Update(float deltaTime);
	void Weak_Hit_L_End(void);

	// Weak_Hit_H
	void Weak_Hit_H_Init(void);
	void Weak_Hit_H_Enter(void);
	void Weak_Hit_H_Update(float deltaTime);
	void Weak_Hit_H_End(void);

	// Weak_Start_L
	void Weak_Start_L_Init(void);
	void Weak_Start_L_Enter(void);
	void Weak_Start_L_Update(float deltaTime);
	void Weak_Start_L_End(void);

	// Weak_Start_H
	void Weak_Start_H_Init(void);
	void Weak_Start_H_Enter(void);
	void Weak_Start_H_Update(float deltaTime);
	void Weak_Start_H_End(void);

	// Hit_H
	void Hit_H_Init(void);
	void Hit_H_Enter(void);
	void Hit_H_Update(float deltaTime);
	void Hit_H_End(void);

	// Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);
};
