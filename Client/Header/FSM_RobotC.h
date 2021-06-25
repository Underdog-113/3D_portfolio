#pragma once
#include "StateMachineC.h"

class FSM_RobotC final : public Engine::CStateMachineC
{
public:
	FSM_RobotC();
	~FSM_RobotC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

public:
	// <Animation List>

	// ATTACK_1_Left
	void ATTACK_1_Left_Init(void);
	void ATTACK_1_Left_Enter(void);
	void ATTACK_1_Left_Update(float deltaTime);
	void ATTACK_1_Left_End(void);

	// ATTACK_1_Right
	void ATTACK_1_Right_Init(void);
	void ATTACK_1_Right_Enter(void);
	void ATTACK_1_Right_Update(float deltaTime);
	void ATTACK_1_Right_End(void);

	// ATTACK_2
	void ATTACK_2_Init(void);
	void ATTACK_2_Enter(void);
	void ATTACK_2_Update(float deltaTime);
	void ATTACK_2_End(void);

	// RUN_ATTACK_BS
	void RUN_ATTACK_BS_Init(void);
	void RUN_ATTACK_BS_Enter(void);
	void RUN_ATTACK_BS_Update(float deltaTime);
	void RUN_ATTACK_BS_End(void);

	// ATTACK_RUN_LOOP
	void ATTACK_RUN_LOOP_Init(void);
	void ATTACK_RUN_LOOP_Enter(void);
	void ATTACK_RUN_LOOP_Update(float deltaTime);
	void ATTACK_RUN_LOOP_End(void);

	// DIE
	void DIE_Init(void);
	void DIE_Enter(void);
	void DIE_Update(float deltaTime);
	void DIE_End(void);

	// DIE_BACK
	void DIE_BACK_Init(void);
	void DIE_BACK_Enter(void);
	void DIE_BACK_Update(float deltaTime);
	void DIE_BACK_End(void);

	// FASTRUN_LOOP
	void FASTRUN_LOOP_Init(void);
	void FASTRUN_LOOP_Enter(void);
	void FASTRUN_LOOP_Update(float deltaTime);
	void FASTRUN_LOOP_End(void);

	// FREE_FALL
	void FREE_FALL_Init(void);
	void FREE_FALL_Enter(void);
	void FREE_FALL_Update(float deltaTime);
	void FREE_FALL_End(void);

	// FREE_FALL_Low
	void FREE_FALL_Low_Init(void);
	void FREE_FALL_Low_Enter(void);
	void FREE_FALL_Low_Update(float deltaTime);
	void FREE_FALL_Low_End(void);

	// Hit_Back
	void Hit_Back_Init(void);
	void Hit_Back_Enter(void);
	void Hit_Back_Update(float deltaTime);
	void Hit_Back_End(void);

	// Hit_H
	void Hit_H_Init(void);
	void Hit_H_Enter(void);
	void Hit_H_Update(float deltaTime);
	void Hit_H_End(void);

	// Hit_L_1
	void Hit_L_1_Init(void);
	void Hit_L_1_Enter(void);
	void Hit_L_1_Update(float deltaTime);
	void Hit_L_1_End(void);

	// Hit_L_1_Light
	void Hit_L_1_Light_Init(void);
	void Hit_L_1_Light_Enter(void);
	void Hit_L_1_Light_Update(float deltaTime);
	void Hit_L_1_Light_End(void);

	// Hit_L_2
	void Hit_L_2_Init(void);
	void Hit_L_2_Enter(void);
	void Hit_L_2_Update(float deltaTime);
	void Hit_L_2_End(void);

	// Hit_L_1_Light
	void Hit_L_2_Light_Init(void);
	void Hit_L_2_Light_Enter(void);
	void Hit_L_2_Light_Update(float deltaTime);
	void Hit_L_2_Light_End(void);

	// Hit_Shake
	void Hit_Shake_Init(void);
	void Hit_Shake_Enter(void);
	void Hit_Shake_Update(float deltaTime);
	void Hit_Shake_End(void);

	// Hit_Throw
	void Hit_Throw_Init(void);
	void Hit_Throw_Enter(void);
	void Hit_Throw_Update(float deltaTime);
	void Hit_Throw_End(void);

	// Hit_Throw_Low
	void Hit_Throw_Low_Init(void);
	void Hit_Throw_Low_Enter(void);
	void Hit_Throw_Low_Update(float deltaTime);
	void Hit_Throw_Low_End(void);

	// KnockDown
	void KnockDown_Init(void);
	void KnockDown_Enter(void);
	void KnockDown_Update(float deltaTime);
	void KnockDown_End(void);

	// Attack_1_Left
	void Attack_1_Left_Init(void);
	void Attack_1_Left_Enter(void);
	void Attack_1_Left_Update(float deltaTime);
	void Attack_1_Left_End(void);

	// Attack_1_Right
	void Attack_1_Right_Init(void);
	void Attack_1_Right_Enter(void);
	void Attack_1_Right_Update(float deltaTime);
	void Attack_1_Right_End(void);

	// Run_AS
	void Run_AS_Init(void);
	void Run_AS_Enter(void);
	void Run_AS_Update(float deltaTime);
	void Run_AS_End(void);

	// Run_Attack
	void Run_Attack_Init(void);
	void Run_Attack_Enter(void);
	void Run_Attack_Update(float deltaTime);
	void Run_Attack_End(void);

	// Run_Attack_Quick
	void Run_Attack_Quick_Init(void);
	void Run_Attack_Quick_Enter(void);
	void Run_Attack_Quick_Update(float deltaTime);
	void Run_Attack_Quick_End(void);

	// StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

	// StandUp
	void StandUp_Init(void);
	void StandUp_Enter(void);
	void StandUp_Update(float deltaTime);
	void StandUp_End(void);

	// Throw_01
	void Throw_01_Init(void);
	void Throw_01_Enter(void);
	void Throw_01_Update(float deltaTime);
	void Throw_01_End(void);

	// Throw_02
	void Throw_02_Init(void);
	void Throw_02_Enter(void);
	void Throw_02_Update(float deltaTime);
	void Throw_02_End(void);

	// Throw_Blow
	void Throw_Blow_Init(void);
	void Throw_Blow_Enter(void);
	void Throw_Blow_Update(float deltaTime);
	void Throw_Blow_End(void);

	// Walk_Backward
	void Walk_Backward_Init(void);
	void Walk_Backward_Enter(void);
	void Walk_Backward_Update(float deltaTime);
	void Walk_Backward_End(void);

	// Walk_Forward
	void Walk_Forward_Init(void);
	void Walk_Forward_Enter(void);
	void Walk_Forward_Update(float deltaTime);
	void Walk_Forward_End(void);

private:
	HRESULT Init_FSM_Setting();

};

