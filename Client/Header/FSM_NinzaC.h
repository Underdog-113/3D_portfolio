#pragma once
#include "StateMachineC.h"

class FSM_NinzaC final : public Engine::CStateMachineC
{
public:
	FSM_NinzaC();
	~FSM_NinzaC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake() override;
	void Start(SP(CComponent) spThis) override;

public:
	// <Animation List>

	//StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

	//Attack_1_as
	void Attack_1_as_Init(void);
	void Attack_1_as_Enter(void);
	void Attack_1_as_Update(float deltaTime);
	void Attack_1_as_End(void);

	//Attack_1_atk
	void Attack_1_atk_Init(void);
	void Attack_1_atk_Enter(void);
	void Attack_1_atk_Update(float deltaTime);
	void Attack_1_atk_End(void);

	//Attack_1_bs
	void Attack_1_bs_Init(void);
	void Attack_1_bs_Enter(void);
	void Attack_1_bs_Update(float deltaTime);
	void Attack_1_bs_End(void);

	//Attack_2_atk_1
	void Attack_2_atk_1_Init(void);
	void Attack_2_atk_1_Enter(void);
	void Attack_2_atk_1_Update(float deltaTime);
	void Attack_2_atk_1_End(void);

	//Attack_2_atk_2
	void Attack_2_atk_2_Init(void);
	void Attack_2_atk_2_Enter(void);
	void Attack_2_atk_2_Update(float deltaTime);
	void Attack_2_atk_2_End(void);

	//Attack_2_atk_3
	void Attack_2_atk_3_Init(void);
	void Attack_2_atk_3_Enter(void);
	void Attack_2_atk_3_Update(float deltaTime);
	void Attack_2_atk_3_End(void);

	//Attack_2_atk_as_long
	void Attack_2_atk_as_long_Init(void);
	void Attack_2_atk_as_long_Enter(void);
	void Attack_2_atk_as_long_Update(float deltaTime);
	void Attack_2_atk_as_long_End(void);

	//Born
	void Born_Init(void);
	void Born_Enter(void);
	void Born_Update(float deltaTime);
	void Born_End(void);

	//Defend
	void Defend_Init(void);
	void Defend_Enter(void);
	void Defend_Update(float deltaTime);
	void Defend_End(void);

	//DefendAttack
	void DefendAttack_Init(void);
	void DefendAttack_Enter(void);
	void DefendAttack_Update(float deltaTime);
	void DefendAttack_End(void);

	//Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);

	//Die_back
	void Die_back_Init(void);
	void Die_back_Enter(void);
	void Die_back_Update(float deltaTime);
	void Die_back_End(void);

	//Die_fly
	void Die_fly_Init(void);
	void Die_fly_Enter(void);
	void Die_fly_Update(float deltaTime);
	void Die_fly_End(void);

	//Hit_back
	void Hit_back_Init(void);
	void Hit_back_Enter(void);
	void Hit_back_Update(float deltaTime);
	void Hit_back_End(void);

	//Hit_front
	void Hit_front_Init(void);
	void Hit_front_Enter(void);
	void Hit_front_Update(float deltaTime);
	void Hit_front_End(void);

	//Hit_front_L
	void Hit_front_L_Init(void);
	void Hit_front_L_Enter(void);
	void Hit_front_L_Update(float deltaTime);
	void Hit_front_L_End(void);

	//Hit_H
	void Hit_H_Init(void);
	void Hit_H_Enter(void);
	void Hit_H_Update(float deltaTime);
	void Hit_H_End(void);

	//Hit_Left
	void Hit_Left_Init(void);
	void Hit_Left_Enter(void);
	void Hit_Left_Update(float deltaTime);
	void Hit_Left_End(void);

	//Hit_Right
	void Hit_Right_Init(void);
	void Hit_Right_Enter(void);
	void Hit_Right_Update(float deltaTime);
	void Hit_Right_End(void);

	//Hit_Shake
	void Hit_Shake_Init(void);
	void Hit_Shake_Enter(void);
	void Hit_Shake_Update(float deltaTime);
	void Hit_Shake_End(void);

	//Hit_Throw
	void Hit_Throw_Init(void);
	void Hit_Throw_Enter(void);
	void Hit_Throw_Update(float deltaTime);
	void Hit_Throw_End(void);

	//Hit_Throw_L
	void Hit_Throw_L_Init(void);
	void Hit_Throw_L_Enter(void);
	void Hit_Throw_L_Update(float deltaTime);
	void Hit_Throw_L_End(void);

	//KnockDown
	void KnockDown_Init(void);
	void KnockDown_Enter(void);
	void KnockDown_Update(float deltaTime);
	void KnockDown_End(void);

	//Run
	void Run_Init(void);
	void Run_Enter(void);
	void Run_Update(float deltaTime);
	void Run_End(void);

	//StandUp
	void StandUp_Init(void);
	void StandUp_Enter(void);
	void StandUp_Update(float deltaTime);
	void StandUp_End(void);

	//Stay
	void Stay_Init(void);
	void Stay_Enter(void);
	void Stay_Update(float deltaTime);
	void Stay_End(void);

	//Stun
	void Stun_Init(void);
	void Stun_Enter(void);
	void Stun_Update(float deltaTime);
	void Stun_End(void);

	//Teleport
	void Teleport_Init(void);
	void Teleport_Enter(void);
	void Teleport_Update(float deltaTime);
	void Teleport_End(void);

	//Throw_01
	void Throw_01_Init(void);
	void Throw_01_Enter(void);
	void Throw_01_Update(float deltaTime);
	void Throw_01_End(void);

	//Throw_02
	void Throw_02_Init(void);
	void Throw_02_Enter(void);
	void Throw_02_Update(float deltaTime);
	void Throw_02_End(void);

	//Throw_Blow
	void Throw_Blow_Init(void);
	void Throw_Blow_Enter(void);
	void Throw_Blow_Update(float deltaTime);
	void Throw_Blow_End(void);

	//Walk_B
	void Walk_B_Init(void);
	void Walk_B_Enter(void);
	void Walk_B_Update(float deltaTime);
	void Walk_B_End(void);

	//Walk_F
	void Walk_F_Init(void);
	void Walk_F_Enter(void);
	void Walk_F_Update(float deltaTime);
	void Walk_F_End(void);

	//Walk_L
	void Walk_L_Init(void);
	void Walk_L_Enter(void);
	void Walk_L_Update(float deltaTime);
	void Walk_L_End(void);

	//Walk_R
	void Walk_R_Init(void);
	void Walk_R_Enter(void);
	void Walk_R_Update(float deltaTime);
	void Walk_R_End(void);

private:
	HRESULT Init_FSM_Setting();
};

