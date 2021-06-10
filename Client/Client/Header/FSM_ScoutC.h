#pragma once
#include "StateMachine.h"

class FSM_ScoutC final : public Engine::CStateMachineC
{
public:
	FSM_ScoutC();
	~FSM_ScoutC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake(void) override;
	void Start(SP(CComponent) spThis) override;

public:
	// <Animation List>

	// APPEAR
	void APPEAR_Init(void);
	void APPEAR_Enter(void);
	void APPEAR_Update(float deltaTime);
	void APPEAR_End(void);

	// IDLE
	void IDLE_Init(void);
	void IDLE_Enter(void);
	void IDLE_Update(float deltaTime);
	void IDLE_End(void);

	// RUN_L
	void RUN_L_Init(void);
	void RUN_L_Enter(void);
	void RUN_L_Update(float deltaTime);
	void RUN_L_End(void);

	// RUN_R
	void RUN_R_Init(void);
	void RUN_R_Enter(void);
	void RUN_R_Update(float deltaTime);
	void RUN_R_End(void);

	// RUN_F
	void RUN_F_Init(void);
	void RUN_F_Enter(void);
	void RUN_F_Update(float deltaTime);
	void RUN_F_End(void);

	// RUN_B
	void RUN_B_Init(void);
	void RUN_B_Enter(void);
	void RUN_B_Update(float deltaTime);
	void RUN_B_End(void);

	// SHOOT_1
	void SHOOT_1_Init(void);
	void SHOOT_1_Enter(void);
	void SHOOT_1_Update(float deltaTime);
	void SHOOT_1_End(void);

	// SHOOT_2
	void SHOOT_2_Init(void);
	void SHOOT_2_Enter(void);
	void SHOOT_2_Update(float deltaTime);
	void SHOOT_2_End(void);

	// SHOOT_3
	void SHOOT_3_Init(void);
	void SHOOT_3_Enter(void);
	void SHOOT_3_Update(float deltaTime);
	void SHOOT_3_End(void);

	// SHOOT_FIREFALL
	void SHOOT_FIREFALL_Init(void);
	void SHOOT_FIREFALL_Enter(void);
	void SHOOT_FIREFALL_Update(float deltaTime);
	void SHOOT_FIREFALL_End(void);

	// LASER_BS
	void LASER_BS_Init(void);
	void LASER_BS_Enter(void);
	void LASER_BS_Update(float deltaTime);
	void LASER_BS_End(void);

	// LASER_LOOP
	void LASER_LOOP_Init(void);
	void LASER_LOOP_Enter(void);
	void LASER_LOOP_Update(float deltaTime);
	void LASER_LOOP_End(void);

	// LASER_AS
	void LASER_AS_Init(void);
	void LASER_AS_Enter(void);
	void LASER_AS_Update(float deltaTime);
	void LASER_AS_End(void);

	// HIT_L
	void HIT_L_Init(void);
	void HIT_L_Enter(void);
	void HIT_L_Update(float deltaTime);
	void HIT_L_End(void);

	// HIT_H
	void HIT_H_Init(void);
	void HIT_H_Enter(void);
	void HIT_H_Update(float deltaTime);
	void HIT_H_End(void);

	// HIT_FRONT
	void HIT_FRONT_Init(void);
	void HIT_FRONT_Enter(void);
	void HIT_FRONT_Update(float deltaTime);
	void HIT_FRONT_End(void);

	// HIT_BACK
	void HIT_BACK_Init(void);
	void HIT_BACK_Enter(void);
	void HIT_BACK_Update(float deltaTime);
	void HIT_BACK_End(void);

	// THROW_0
	void THROW_0_Init(void);
	void THROW_0_Enter(void);
	void THROW_0_Update(float deltaTime);
	void THROW_0_End(void);
	
	// THROW_1
	void THROW_1_Init(void);
	void THROW_1_Enter(void);
	void THROW_1_Update(float deltaTime);
	void THROW_1_End(void);

	// THROW_2
	void THROW_2_Init(void);
	void THROW_2_Enter(void);
	void THROW_2_Update(float deltaTime);
	void THROW_2_End(void);

	// THROW_BLOW
	void THROW_BLOW_Init(void);
	void THROW_BLOW_Enter(void);
	void THROW_BLOW_Update(float deltaTime);
	void THROW_BLOW_End(void);

	// THROW_LOW
	void THROW_LOW_Init(void);
	void THROW_LOW_Enter(void);
	void THROW_LOW_Update(float deltaTime);
	void THROW_LOW_End(void);

	// KNOCK_DOWN
	void KNOCK_DOWN_Init(void);
	void KNOCK_DOWN_Enter(void);
	void KNOCK_DOWN_Update(float deltaTime);
	void KNOCK_DOWN_End(void);

	// STAND_UP
	void STAND_UP_Init(void);
	void STAND_UP_Enter(void);
	void STAND_UP_Update(float deltaTime);
	void STAND_UP_End(void);

	// STUN
	void STUN_Init(void);
	void STUN_Enter(void);
	void STUN_Update(float deltaTime);
	void STUN_End(void);

	// DIE
	void DIE_Init(void);
	void DIE_Enter(void);
	void DIE_Update(float deltaTime);
	void DIE_End(void);

	// DIE_FLY
	void DIE_FLY_Init(void);
	void DIE_FLY_Enter(void);
	void DIE_FLY_Update(float deltaTime);
	void DIE_FLY_End(void);

private:
	HRESULT Init_FSM_Setting();
};

