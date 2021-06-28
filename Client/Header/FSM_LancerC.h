#pragma once
#include "StateMachineC.h"

class CStageControlTower;
class CFSM_LancerC final : public Engine::CStateMachineC
{
public:
	CFSM_LancerC();
	~CFSM_LancerC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

private:
	void RegisterAllStage();
	void FixRootMotionOffset(_uint index);

private:
	GETTOR_SETTOR(Engine::CDynamicMeshData*, m_pDM, nullptr, DM);

public:
	// <Animation List>

	//APPEAR
	void APPEAR_Init(void);
	void APPEAR_Enter(void);
	void APPEAR_Update(float deltaTime);
	void APPEAR_End(void);

	//ATTACK_1
	void ATTACK_1_Init(void);
	void ATTACK_1_Enter(void);
	void ATTACK_1_Update(float deltaTime);
	void ATTACK_1_End(void);

	//ATTACK_2
	void ATTACK_2_Init(void);
	void ATTACK_2_Enter(void);
	void ATTACK_2_Update(float deltaTime);
	void ATTACK_2_End(void);

	//ATTACK_3
	void ATTACK_3_Init(void);
	void ATTACK_3_Enter(void);
	void ATTACK_3_Update(float deltaTime);
	void ATTACK_3_End(void);

	//BOM_READY
	void BOM_READY_Init(void);
	void BOM_READY_Enter(void);
	void BOM_READY_Update(float deltaTime);
	void BOM_READY_End(void);

	//DIE
	void DIE_Init(void);
	void DIE_Enter(void);
	void DIE_Update(float deltaTime);
	void DIE_End(void);

	//DIE_BACK
	void DIE_BACK_Init(void);
	void DIE_BACK_Enter(void);
	void DIE_BACK_Update(float deltaTime);
	void DIE_BACK_End(void);

	//DIE_FLY
	void DIE_FLY_Init(void);
	void DIE_FLY_Enter(void);
	void DIE_FLY_Update(float deltaTime);
	void DIE_FLY_End(void);

	//FREE_FALL
	void FREE_FALL_Init(void);
	void FREE_FALL_Enter(void);
	void FREE_FALL_Update(float deltaTime);
	void FREE_FALL_End(void);

	//FREE_FALL_LOW
	void FREE_FALL_LOW_Init(void);
	void FREE_FALL_LOW_Enter(void);
	void FREE_FALL_LOW_Update(float deltaTime);
	void FREE_FALL_LOW_End(void);

	//HIDE
	void HIDE_Init(void);
	void HIDE_Enter(void);
	void HIDE_Update(float deltaTime);
	void HIDE_End(void);

	//HIT_BACK
	void HIT_BACK_Init(void);
	void HIT_BACK_Enter(void);
	void HIT_BACK_Update(float deltaTime);
	void HIT_BACK_End(void);

	//HIT_H
	void HIT_H_Init(void);
	void HIT_H_Enter(void);
	void HIT_H_Update(float deltaTime);
	void HIT_H_End(void);

	//HIT_EARLY
	void HIT_EARLY_Init(void);
	void HIT_EARLY_Enter(void);
	void HIT_EARLY_Update(float deltaTime);
	void HIT_EARLY_End(void);

	//HIT_L
	void HIT_L_Init(void);
	void HIT_L_Enter(void);
	void HIT_L_Update(float deltaTime);
	void HIT_L_End(void);

	//HIT_L_EARLY
	void HIT_L_EARLY_Init(void);
	void HIT_L_EARLY_Enter(void);
	void HIT_L_EARLY_Update(float deltaTime);
	void HIT_L_EARLY_End(void);

	//HIT_LEFT
	void HIT_LEFT_Init(void);
	void HIT_LEFT_Enter(void);
	void HIT_LEFT_Update(float deltaTime);
	void HIT_LEFT_End(void);

	//HIT_RIGHT
	void HIT_RIGHT_Init(void);
	void HIT_RIGHT_Enter(void);
	void HIT_RIGHT_Update(float deltaTime);
	void HIT_RIGHT_End(void);

	//HIT_SHAKE
	void HIT_SHAKE_Init(void);
	void HIT_SHAKE_Enter(void);
	void HIT_SHAKE_Update(float deltaTime);
	void HIT_SHAKE_End(void);

	//JUMP_BACK
	void JUMP_BACK_Init(void);
	void JUMP_BACK_Enter(void);
	void JUMP_BACK_Update(float deltaTime);
	void JUMP_BACK_End(void);

	//KNOCK_DOWN
	void KNOCK_DOWN_Init(void);
	void KNOCK_DOWN_Enter(void);
	void KNOCK_DOWN_Update(float deltaTime);
	void KNOCK_DOWN_End(void);

	//RUN
	void RUN_Init(void);
	void RUN_Enter(void);
	void RUN_Update(float deltaTime);
	void RUN_End(void);

	//STAND
	void STAND_Init(void);
	void STAND_Enter(void);
	void STAND_Update(float deltaTime);
	void STAND_End(void);

	//STAND_UP
	void STAND_UP_Init(void);
	void STAND_UP_Enter(void);
	void STAND_UP_Update(float deltaTime);
	void STAND_UP_End(void);

	//STUN
	void STUN_Init(void);
	void STUN_Enter(void);
	void STUN_Update(float deltaTime);
	void STUN_End(void);

	//THROW_0
	void THROW_0_Init(void);
	void THROW_0_Enter(void);
	void THROW_0_Update(float deltaTime);
	void THROW_0_End(void);

	//THROW_1
	void THROW_1_Init(void);
	void THROW_1_Enter(void);
	void THROW_1_Update(float deltaTime);
	void THROW_1_End(void);

	//THROW_2
	void THROW_2_Init(void);
	void THROW_2_Enter(void);
	void THROW_2_Update(float deltaTime);
	void THROW_2_End(void);

	//THROW_BLOW
	void THROW_BLOW_Init(void);
	void THROW_BLOW_Enter(void);
	void THROW_BLOW_Update(float deltaTime);
	void THROW_BLOW_End(void);

	//THROW_LOW
	void THROW_LOW_Init(void);
	void THROW_LOW_Enter(void);
	void THROW_LOW_Update(float deltaTime);
	void THROW_LOW_End(void);

	//WALK_BACKWARD
	void WALK_BACKWARD_Init(void);
	void WALK_BACKWARD_Enter(void);
	void WALK_BACKWARD_Update(float deltaTime);
	void WALK_BACKWARD_End(void);

	//WALK_FORWARD
	void WALK_FORWARD_Init(void);
	void WALK_FORWARD_Enter(void);
	void WALK_FORWARD_Update(float deltaTime);
	void WALK_FORWARD_End(void);

	//WALK_LEFT
	void WALK_LEFT_Init(void);
	void WALK_LEFT_Enter(void);
	void WALK_LEFT_Update(float deltaTime);
	void WALK_LEFT_End(void);

	//WALK_RIGHT
	void WALK_RIGHT_Init(void);
	void WALK_RIGHT_Enter(void);
	void WALK_RIGHT_Update(float deltaTime);
	void WALK_RIGHT_End(void);
};
