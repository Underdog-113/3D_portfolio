#pragma once
#include "StateMachine.h"
#define Cool_End		0.75f


class CStageController;
class CFSM_SpiderC final : public Engine::CStateMachineC
{
public:
	CFSM_SpiderC();
	~CFSM_SpiderC() = default;

public:
	SP(Engine::CComponent)		MakeClone		(Engine::CObject* pOwner) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

private:
	void RegisterAllState();
	void FixRootMotionOffset(_uint index);

private: /* Normal Actions */
	_bool CheckAction_Idle(_float coolTime = Cool_End);
	_bool CheckAction_Run();

private:
	Engine::CDynamicMeshData* m_pDM = nullptr;
	CStageController* m_pStageController = nullptr; // test

public:
	// <Animation List>
	// ATTACK_1
	void ATTACK_1_Init(void);
	void ATTACK_1_Enter(void);
	void ATTACK_1_Update(float deltaTime);
	void ATTACK_1_End(void);

	// ATTACK_2
	void ATTACK_2_Init(void);
	void ATTACK_2_Enter(void);
	void ATTACK_2_Update(float deltaTime);
	void ATTACK_2_End(void);

	// ATTACK_2_BS
	void ATTACK_2_BS_Init(void);
	void ATTACK_2_BS_Enter(void);
	void ATTACK_2_BS_Update(float deltaTime);
	void ATTACK_2_BS_End(void);

	// ATTACK_2_Run
	void ATTACK_2_Run_Init(void);
	void ATTACK_2_Run_Enter(void);
	void ATTACK_2_Run_Update(float deltaTime);
	void ATTACK_2_Run_End(void);

	// ATTACK_3
	void ATTACK_3_Init(void);
	void ATTACK_3_Enter(void);
	void ATTACK_3_Update(float deltaTime);
	void ATTACK_3_End(void);

	// ATTACK_3_AS
	void ATTACK_3_AS_Init(void);
	void ATTACK_3_AS_Enter(void);
	void ATTACK_3_AS_Update(float deltaTime);
	void ATTACK_3_AS_End(void);

	// ATTACK_3_BS
	void ATTACK_3_BS_Init(void);
	void ATTACK_3_BS_Enter(void);
	void ATTACK_3_BS_Update(float deltaTime);
	void ATTACK_3_BS_End(void);

	// ATTACK_DIE
	void ATTACK_DIE_Init(void);
	void ATTACK_DIE_Enter(void);
	void ATTACK_DIE_Update(float deltaTime);
	void ATTACK_DIE_End(void);

	// BORN
	void BORN_Init(void);
	void BORN_Enter(void);
	void BORN_Update(float deltaTime);
	void BORN_End(void);

	// Bury_AS
	void Bury_AS_Init(void);
	void Bury_AS_Enter(void);
	void Bury_AS_Update(float deltaTime);
	void Bury_AS_End(void);

	// Bury_BS
	void Bury_BS_Init(void);
	void Bury_BS_Enter(void);
	void Bury_BS_Update(float deltaTime);
	void Bury_BS_End(void);

	// Bury_Loop
	void Bury_Loop_Init(void);
	void Bury_Loop_Enter(void);
	void Bury_Loop_Update(float deltaTime);
	void Bury_Loop_End(void);

	// Hit_H
	void Hit_H_Init(void);
	void Hit_H_Enter(void);
	void Hit_H_Update(float deltaTime);
	void Hit_H_End(void);

	// Hit_H_Early
	void Hit_H_Early_Init(void);
	void Hit_H_Early_Enter(void);
	void Hit_H_Early_Update(float deltaTime);
	void Hit_H_Early_End(void);

	// Hit_L
	void Hit_L_Init(void);
	void Hit_L_Enter(void);
	void Hit_L_Update(float deltaTime);
	void Hit_L_End(void);

	// Hit_L_Early
	void Hit_L_Early_Init(void);
	void Hit_L_Early_Enter(void);
	void Hit_L_Early_Update(float deltaTime);
	void Hit_L_Early_End(void);

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

	// StandBy
	void StandBy_Init(void);
	void StandBy_Enter(void);
	void StandBy_Update(float deltaTime);
	void StandBy_End(void);

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

	// Walk_Forward
	void Walk_Forward_Init(void);
	void Walk_Forward_Enter(void);
	void Walk_Forward_Update(float deltaTime);
	void Walk_Forward_End(void);

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
};
