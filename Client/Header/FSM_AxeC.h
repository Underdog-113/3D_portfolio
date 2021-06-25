#pragma once
#include "StateMachineC.h"

class CStageControlTower;
class CFSM_AxeC final : public Engine::CStateMachineC
{
public:
	CFSM_AxeC();
	~CFSM_AxeC() = default;

public:
	SP(Engine::CComponent) MakeClone(Engine::CObject* pObject) override;
	void Awake() override;
	void Start(SP(CComponent)spThis) override;

private:
	void RegisterAllStage();
	void FixRootMotionOffset(_uint index);

private:
	_float m_accTime = 0.f;
	GETTOR_SETTOR(Engine::CDynamicMeshData*, m_pDM, nullptr, DM);
	CStageControlTower* m_pStageControlTower = nullptr;

	GETTOR_SETTOR(_bool, m_pattern1, false, Pattern1);

public:
	// <Animation List>

	// IDLE
	void IDLE_Init(void);
	void IDLE_Enter(void);
	void IDLE_Update(float deltaTime);
	void IDLE_End(void);

	// WALK_RIGHT
	void WALK_RIGHT_Init(void);
	void WALK_RIGHT_Enter(void);
	void WALK_RIGHT_Update(float deltaTime);
	void WALK_RIGHT_End(void);

	// WALK_LEFT
	void WALK_LEFT_Init(void);
	void WALK_LEFT_Enter(void);
	void WALK_LEFT_Update(float deltaTime);
	void WALK_LEFT_End(void);

	// WALK_BACK
	void WALK_BACK_Init(void);
	void WALK_BACK_Enter(void);
	void WALK_BACK_Update(float deltaTime);
	void WALK_BACK_End(void);

	// RUN
	void RUN_Init(void);
	void RUN_Enter(void);
	void RUN_Update(float deltaTime);
	void RUN_End(void);

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

	// ATTACK_2_1
	void ATTACK_2_1_Init(void);
	void ATTACK_2_1_Enter(void);
	void ATTACK_2_1_Update(float deltaTime);
	void ATTACK_2_1_End(void);

	// ATTACK_3
	void ATTACK_3_Init(void);
	void ATTACK_3_Enter(void);
	void ATTACK_3_Update(float deltaTime);
	void ATTACK_3_End(void);

	// ATTACK_3_1
	void ATTACK_3_1_Init(void);
	void ATTACK_3_1_Enter(void);
	void ATTACK_3_1_Update(float deltaTime);
	void ATTACK_3_1_End(void);

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

	// HIT_BACK
	void HIT_BACK_Init(void);
	void HIT_BACK_Enter(void);
	void HIT_BACK_Update(float deltaTime);
	void HIT_BACK_End(void);

	// HIT_THROW
	void HIT_THROW_Init(void);
	void HIT_THROW_Enter(void);
	void HIT_THROW_Update(float deltaTime);
	void HIT_THROW_End(void);

	// HIT_THROW_LOW
	void HIT_THROW_LOW_Init(void);
	void HIT_THROW_LOW_Enter(void);
	void HIT_THROW_LOW_Update(float deltaTime);
	void HIT_THROW_LOW_End(void);

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

	// DIE_FLY
	void DIE_FLY_Init(void);
	void DIE_FLY_Enter(void);
	void DIE_FLY_Update(float deltaTime);
	void DIE_FLY_End(void);
};

