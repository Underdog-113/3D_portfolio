#include "stdafx.h"
#include "..\Header\FSM_LancerC.h"


FSM_LancerC::FSM_LancerC()
{
}

SP(Engine::CComponent) FSM_LancerC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_LancerC>(pObject);

	return spClone;
}

void FSM_LancerC::Awake(void)
{
	Engine::CState* pState;

	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"FSM_LancerC Init_FSM_Setting Failed");
		ABORT;
	}

	__super::Awake();
}

void FSM_LancerC::Start(SP(CComponent) spThis)
{
	SetStartState(L"APPEAR");
	__super::Start(spThis);
}

void FSM_LancerC::APPEAR_Init(void)
{
}

void FSM_LancerC::APPEAR_Enter(void)
{
}

void FSM_LancerC::APPEAR_Update(float deltaTime)
{
}

void FSM_LancerC::APPEAR_End(void)
{
}

void FSM_LancerC::ATTACK_1_Init(void)
{
}

void FSM_LancerC::ATTACK_1_Enter(void)
{
}

void FSM_LancerC::ATTACK_1_Update(float deltaTime)
{
}

void FSM_LancerC::ATTACK_1_End(void)
{
}

void FSM_LancerC::ATTACK_2_Init(void)
{
}

void FSM_LancerC::ATTACK_2_Enter(void)
{
}

void FSM_LancerC::ATTACK_2_Update(float deltaTime)
{
}

void FSM_LancerC::ATTACK_2_End(void)
{
}

void FSM_LancerC::ATTACK_3_Init(void)
{
}

void FSM_LancerC::ATTACK_3_Enter(void)
{
}

void FSM_LancerC::ATTACK_3_Update(float deltaTime)
{
}

void FSM_LancerC::ATTACK_3_End(void)
{
}

void FSM_LancerC::BOM_READY_Init(void)
{
}

void FSM_LancerC::BOM_READY_Enter(void)
{
}

void FSM_LancerC::BOM_READY_Update(float deltaTime)
{
}

void FSM_LancerC::BOM_READY_End(void)
{
}

void FSM_LancerC::DIE_Init(void)
{
}

void FSM_LancerC::DIE_Enter(void)
{
}

void FSM_LancerC::DIE_Update(float deltaTime)
{
}

void FSM_LancerC::DIE_End(void)
{
}

void FSM_LancerC::DIE_BACK_Init(void)
{
}

void FSM_LancerC::DIE_BACK_Enter(void)
{
}

void FSM_LancerC::DIE_BACK_Update(float deltaTime)
{
}

void FSM_LancerC::DIE_BACK_End(void)
{
}

void FSM_LancerC::DIE_FLY_Init(void)
{
}

void FSM_LancerC::DIE_FLY_Enter(void)
{
}

void FSM_LancerC::DIE_FLY_Update(float deltaTime)
{
}

void FSM_LancerC::DIE_FLY_End(void)
{
}

void FSM_LancerC::FREE_FALL_Init(void)
{
}

void FSM_LancerC::FREE_FALL_Enter(void)
{
}

void FSM_LancerC::FREE_FALL_Update(float deltaTime)
{
}

void FSM_LancerC::FREE_FALL_End(void)
{
}

void FSM_LancerC::FREE_FALL_LOW_Init(void)
{
}

void FSM_LancerC::FREE_FALL_LOW_Enter(void)
{
}

void FSM_LancerC::FREE_FALL_LOW_Update(float deltaTime)
{
}

void FSM_LancerC::FREE_FALL_LOW_End(void)
{
}

void FSM_LancerC::HIDE_Init(void)
{
}

void FSM_LancerC::HIDE_Enter(void)
{
}

void FSM_LancerC::HIDE_Update(float deltaTime)
{
}

void FSM_LancerC::HIDE_End(void)
{
}

void FSM_LancerC::HIT_BACK_Init(void)
{
}

void FSM_LancerC::HIT_BACK_Enter(void)
{
}

void FSM_LancerC::HIT_BACK_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_BACK_End(void)
{
}

void FSM_LancerC::HIT_H_Init(void)
{
}

void FSM_LancerC::HIT_H_Enter(void)
{
}

void FSM_LancerC::HIT_H_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_H_End(void)
{
}

void FSM_LancerC::HIT_EARLY_Init(void)
{
}

void FSM_LancerC::HIT_EARLY_Enter(void)
{
}

void FSM_LancerC::HIT_EARLY_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_EARLY_End(void)
{
}

void FSM_LancerC::HIT_L_Init(void)
{
}

void FSM_LancerC::HIT_L_Enter(void)
{
}

void FSM_LancerC::HIT_L_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_L_End(void)
{
}

void FSM_LancerC::HIT_L_EARLY_Init(void)
{
}

void FSM_LancerC::HIT_L_EARLY_Enter(void)
{
}

void FSM_LancerC::HIT_L_EARLY_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_L_EARLY_End(void)
{
}

void FSM_LancerC::HIT_LEFT_Init(void)
{
}

void FSM_LancerC::HIT_LEFT_Enter(void)
{
}

void FSM_LancerC::HIT_LEFT_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_LEFT_End(void)
{
}

void FSM_LancerC::HIT_RIGHT_Init(void)
{
}

void FSM_LancerC::HIT_RIGHT_Enter(void)
{
}

void FSM_LancerC::HIT_RIGHT_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_RIGHT_End(void)
{
}

void FSM_LancerC::HIT_SHAKE_Init(void)
{
}

void FSM_LancerC::HIT_SHAKE_Enter(void)
{
}

void FSM_LancerC::HIT_SHAKE_Update(float deltaTime)
{
}

void FSM_LancerC::HIT_SHAKE_End(void)
{
}

void FSM_LancerC::JUMP_BACK_Init(void)
{
}

void FSM_LancerC::JUMP_BACK_Enter(void)
{
}

void FSM_LancerC::JUMP_BACK_Update(float deltaTime)
{
}

void FSM_LancerC::JUMP_BACK_End(void)
{
}

void FSM_LancerC::KNOCK_DOWN_Init(void)
{
}

void FSM_LancerC::KNOCK_DOWN_Enter(void)
{
}

void FSM_LancerC::KNOCK_DOWN_Update(float deltaTime)
{
}

void FSM_LancerC::KNOCK_DOWN_End(void)
{
}

void FSM_LancerC::RUN_Init(void)
{
}

void FSM_LancerC::RUN_Enter(void)
{
}

void FSM_LancerC::RUN_Update(float deltaTime)
{
}

void FSM_LancerC::RUN_End(void)
{
}

void FSM_LancerC::STAND_Init(void)
{
}

void FSM_LancerC::STAND_Enter(void)
{
}

void FSM_LancerC::STAND_Update(float deltaTime)
{
}

void FSM_LancerC::STAND_End(void)
{
}

void FSM_LancerC::STAND_UP_Init(void)
{
}

void FSM_LancerC::STAND_UP_Enter(void)
{
}

void FSM_LancerC::STAND_UP_Update(float deltaTime)
{
}

void FSM_LancerC::STAND_UP_End(void)
{
}

void FSM_LancerC::STUN_Init(void)
{
}

void FSM_LancerC::STUN_Enter(void)
{
}

void FSM_LancerC::STUN_Update(float deltaTime)
{
}

void FSM_LancerC::STUN_End(void)
{
}

void FSM_LancerC::THROW_0_Init(void)
{
}

void FSM_LancerC::THROW_0_Enter(void)
{
}

void FSM_LancerC::THROW_0_Update(float deltaTime)
{
}

void FSM_LancerC::THROW_0_End(void)
{
}

void FSM_LancerC::THROW_1_Init(void)
{
}

void FSM_LancerC::THROW_1_Enter(void)
{
}

void FSM_LancerC::THROW_1_Update(float deltaTime)
{
}

void FSM_LancerC::THROW_1_End(void)
{
}

void FSM_LancerC::THROW_2_Init(void)
{
}

void FSM_LancerC::THROW_2_Enter(void)
{
}

void FSM_LancerC::THROW_2_Update(float deltaTime)
{
}

void FSM_LancerC::THROW_2_End(void)
{
}

void FSM_LancerC::THROW_BLOW_Init(void)
{
}

void FSM_LancerC::THROW_BLOW_Enter(void)
{
}

void FSM_LancerC::THROW_BLOW_Update(float deltaTime)
{
}

void FSM_LancerC::THROW_BLOW_End(void)
{
}

void FSM_LancerC::THROW_LOW_Init(void)
{
}

void FSM_LancerC::THROW_LOW_Enter(void)
{
}

void FSM_LancerC::THROW_LOW_Update(float deltaTime)
{
}

void FSM_LancerC::THROW_LOW_End(void)
{
}

void FSM_LancerC::WALK_BACKWARD_Init(void)
{
}

void FSM_LancerC::WALK_BACKWARD_Enter(void)
{
}

void FSM_LancerC::WALK_BACKWARD_Update(float deltaTime)
{
}

void FSM_LancerC::WALK_BACKWARD_End(void)
{
}

void FSM_LancerC::WALK_FORWARD_Init(void)
{
}

void FSM_LancerC::WALK_FORWARD_Enter(void)
{
}

void FSM_LancerC::WALK_FORWARD_Update(float deltaTime)
{
}

void FSM_LancerC::WALK_FORWARD_End(void)
{
}

void FSM_LancerC::WALK_LEFT_Init(void)
{
}

void FSM_LancerC::WALK_LEFT_Enter(void)
{
}

void FSM_LancerC::WALK_LEFT_Update(float deltaTime)
{
}

void FSM_LancerC::WALK_LEFT_End(void)
{
}

void FSM_LancerC::WALK_RIGHT_Init(void)
{
}

void FSM_LancerC::WALK_RIGHT_Enter(void)
{
}

void FSM_LancerC::WALK_RIGHT_Update(float deltaTime)
{
}

void FSM_LancerC::WALK_RIGHT_End(void)
{
}

HRESULT FSM_LancerC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_LancerC, pState, APPEAR)
		AddState(pState, L"APPEAR");

	CreateState(FSM_LancerC, pState, ATTACK_1)
		AddState(pState, L"ATTACK_1");

	CreateState(FSM_LancerC, pState, ATTACK_2)
		AddState(pState, L"ATTACK_2");

	CreateState(FSM_LancerC, pState, ATTACK_3)
		AddState(pState, L"ATTACK_3");

	CreateState(FSM_LancerC, pState, DIE)
		AddState(pState, L"DIE");

	CreateState(FSM_LancerC, pState, DIE_BACK)
		AddState(pState, L"DIE_BACK");

	CreateState(FSM_LancerC, pState, DIE_FLY)
		AddState(pState, L"DIE_FLY");

	CreateState(FSM_LancerC, pState, FREE_FALL)
		AddState(pState, L"FREE_FALL");

	CreateState(FSM_LancerC, pState, FREE_FALL_LOW)
		AddState(pState, L"FREE_FALL_LOW");

	CreateState(FSM_LancerC, pState, HIDE)
		AddState(pState, L"HIDE");

	CreateState(FSM_LancerC, pState, HIT_BACK)
		AddState(pState, L"HIT_BACK");

	CreateState(FSM_LancerC, pState, HIT_H)
		AddState(pState, L"HIT_H");

	CreateState(FSM_LancerC, pState, HIT_EARLY)
		AddState(pState, L"HIT_EARLY");

	CreateState(FSM_LancerC, pState, HIT_L)
		AddState(pState, L"HIT_L");

	CreateState(FSM_LancerC, pState, HIT_L_EARLY)
		AddState(pState, L"HIT_L_EARLY");

	CreateState(FSM_LancerC, pState, HIT_LEFT)
		AddState(pState, L"HIT_LEFT");

	CreateState(FSM_LancerC, pState, HIT_RIGHT)
		AddState(pState, L"HIT_RIGHT");

	CreateState(FSM_LancerC, pState, HIT_SHAKE)
		AddState(pState, L"HIT_SHAKE");

	CreateState(FSM_LancerC, pState, JUMP_BACK)
		AddState(pState, L"JUMP_BACK");

	CreateState(FSM_LancerC, pState, KNOCK_DOWN)
		AddState(pState, L"KNOCK_DOWN");

	CreateState(FSM_LancerC, pState, RUN)
		AddState(pState, L"RUN");

	CreateState(FSM_LancerC, pState, STAND)
		AddState(pState, L"STAND");

	CreateState(FSM_LancerC, pState, STAND_UP)
		AddState(pState, L"STAND_UP");

	CreateState(FSM_LancerC, pState, STUN)
		AddState(pState, L"STUN");

	CreateState(FSM_LancerC, pState, THROW_0)
		AddState(pState, L"THROW_0");

	CreateState(FSM_LancerC, pState, THROW_1)
		AddState(pState, L"THROW_1");

	CreateState(FSM_LancerC, pState, THROW_2)
		AddState(pState, L"THROW_2");

	CreateState(FSM_LancerC, pState, THROW_BLOW)
		AddState(pState, L"THROW_BLOW");

	CreateState(FSM_LancerC, pState, THROW_LOW)
		AddState(pState, L"THROW_LOW");

	CreateState(FSM_LancerC, pState, WALK_BACKWARD)
		AddState(pState, L"WALK_BACKWARD");

	CreateState(FSM_LancerC, pState, WALK_FORWARD)
		AddState(pState, L"WALK_FORWARD");

	CreateState(FSM_LancerC, pState, WALK_LEFT)
		AddState(pState, L"WALK_LEFT");

	CreateState(FSM_LancerC, pState, WALK_RIGHT)
		AddState(pState, L"WALK_RIGHT");

	if (nullptr == pState)
	{
		return E_FAIL;
	}

	return S_OK;
}
