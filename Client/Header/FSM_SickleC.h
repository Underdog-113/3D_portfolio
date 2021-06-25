#pragma once
#include "StateMachineC.h"

class CStageControlTower;
class CFSM_SickleC final : public Engine::CStateMachineC
{
public:
	CFSM_SickleC();
	~CFSM_SickleC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake() override;
	void Start(SP(CComponent)spThis) override;

private:
	void RegisterAllStage();
	void FixRootMotionOffset(_uint index);

private:
	GETTOR_SETTOR(Engine::CDynamicMeshData*, m_pDM, nullptr, DM);

public:
	// <Animation List>
	// StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

	// Walk_Forward
	void Walk_Forward_Init(void);
	void Walk_Forward_Enter(void);
	void Walk_Forward_Update(float deltaTime);
	void Walk_Forward_End(void);

	// Walk_back
	void Walk_Back_Init(void);
	void Walk_Back_Enter(void);
	void Walk_Back_Update(float deltaTime);
	void Walk_Back_End(void);

	// Walk_Left
	void Walk_Left_Init(void);
	void Walk_Left_Enter(void);
	void Walk_Left_Update(float deltaTime);
	void Walk_Left_End(void);

	// Walk_Right
	void Walk_Right_Init(void);
	void Walk_Right_Enter(void);
	void Walk_Right_Update(float deltaTime);
	void Walk_Right_End(void);

	// Attack_1
	void Attack_1_Init(void);
	void Attack_1_Enter(void);
	void Attack_1_Update(float deltaTime);
	void Attack_1_End(void);

	// Attack_2
	void Attack_2_Init(void);
	void Attack_2_Enter(void);
	void Attack_2_Update(float deltaTime);
	void Attack_2_End(void);

	// Attack_2_1
	void Attack_2_1_Init(void);
	void Attack_2_1_Enter(void);
	void Attack_2_1_Update(float deltaTime);
	void Attack_2_1_End(void);

	// Attack_2_Loop
	void Attack_2_Loop_Init(void);
	void Attack_2_Loop_Enter(void);
	void Attack_2_Loop_Update(float deltaTime);
	void Attack_2_Loop_End(void);

	// Attack_3
	void Attack_3_Init(void);
	void Attack_3_Enter(void);
	void Attack_3_Update(float deltaTime);
	void Attack_3_End(void);

	// Attack_4_Start
	void Attack_4_Start_Init(void);
	void Attack_4_Start_Enter(void);
	void Attack_4_Start_Update(float deltaTime);
	void Attack_4_Start_End(void);

	// Attack_4_Loop
	void Attack_4_Loop_Init(void);
	void Attack_4_Loop_Enter(void);
	void Attack_4_Loop_Update(float deltaTime);
	void Attack_4_Loop_End(void);

	// Attack_4_End
	void Attack_4_End_Init(void);
	void Attack_4_End_Enter(void);
	void Attack_4_End_Update(float deltaTime);
	void Attack_4_End_End(void);

	// Attack_Unique01
	void Attack_Unique01_Init(void);
	void Attack_Unique01_Enter(void);
	void Attack_Unique01_Update(float deltaTime);
	void Attack_Unique01_End(void);

	// Born
	void Born_Init(void);
	void Born_Enter(void);
	void Born_Update(float deltaTime);
	void Born_End(void);

	// Die
	void Die_Init(void);
	void Die_Enter(void);
	void Die_Update(float deltaTime);
	void Die_End(void);

	// Die_Back
	void Die_Back_Init(void);
	void Die_Back_Enter(void);
	void Die_Back_Update(float deltaTime);
	void Die_Back_End(void);

	// Die_Fly
	void Die_Fly_Init(void);
	void Die_Fly_Enter(void);
	void Die_Fly_Update(float deltaTime);
	void Die_Fly_End(void);

	// KnockDown
	void KnockDown_Init(void);
	void KnockDown_Enter(void);
	void KnockDown_Update(float deltaTime);
	void KnockDown_End(void);

	// Stun
	void Stun_Init(void);
	void Stun_Enter(void);
	void Stun_Update(float deltaTime);
	void Stun_End(void);

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

	// Throw_Blow
	void Throw_Blow_Init(void);
	void Throw_Blow_Enter(void);
	void Throw_Blow_Update(float deltaTime);
	void Throw_Blow_End(void);

	// Hit_Front
	void Hit_Front_Init(void);
	void Hit_Front_Enter(void);
	void Hit_Front_Update(float deltaTime);
	void Hit_Front_End(void);

	// Hit_Front_L
	void Hit_Front_L_Init(void);
	void Hit_Front_L_Enter(void);
	void Hit_Front_L_Update(float deltaTime);
	void Hit_Front_L_End(void);

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

	// Hit_L
	void Hit_L_Init(void);
	void Hit_L_Enter(void);
	void Hit_L_Update(float deltaTime);
	void Hit_L_End(void);

	// Hit_Shake
	void Hit_Shake_Init(void);
	void Hit_Shake_Enter(void);
	void Hit_Shake_Update(float deltaTime);
	void Hit_Shake_End(void);

	// Hit_Shake_1
	void Hit_Shake_1_Init(void);
	void Hit_Shake_1_Enter(void);
	void Hit_Shake_1_Update(float deltaTime);
	void Hit_Shake_1_End(void);

	// Defend
	void Defend_Init(void);
	void Defend_Enter(void);
	void Defend_Update(float deltaTime);
	void Defend_End(void);
};
