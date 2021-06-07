#include "stdafx.h"
#include "..\Header\FSM_AxeC.h"


FSM_AxeC::FSM_AxeC()
{
}

SP(Engine::CComponent) FSM_AxeC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_AxeC>(pObject);

	return spClone;
}

void FSM_AxeC::Awake()
{

	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"FSM_AxeC Init_FSM_Setting Failed");
		ABORT;
	}

	__super::Awake();
}

void FSM_AxeC::Start(SP(CComponent) spThis)
{
	SetStartState(L"IDLE");
	__super::Start(spThis);
}

void FSM_AxeC::IDLE_Init(void)
{
}

void FSM_AxeC::IDLE_Enter(void)
{
}

void FSM_AxeC::IDLE_Update(float deltaTime)
{
}

void FSM_AxeC::IDLE_End(void)
{
}

void FSM_AxeC::WALK_RIGHT_Init(void)
{
}

void FSM_AxeC::WALK_RIGHT_Enter(void)
{
}

void FSM_AxeC::WALK_RIGHT_Update(float deltaTime)
{
}

void FSM_AxeC::WALK_RIGHT_End(void)
{
}

void FSM_AxeC::WALK_LEFT_Init(void)
{
}

void FSM_AxeC::WALK_LEFT_Enter(void)
{
}

void FSM_AxeC::WALK_LEFT_Update(float deltaTime)
{
}

void FSM_AxeC::WALK_LEFT_End(void)
{
}

void FSM_AxeC::WALK_BACK_Init(void)
{
}

void FSM_AxeC::WALK_BACK_Enter(void)
{
}

void FSM_AxeC::WALK_BACK_Update(float deltaTime)
{
}

void FSM_AxeC::WALK_BACK_End(void)
{
}

void FSM_AxeC::RUN_Init(void)
{
}

void FSM_AxeC::RUN_Enter(void)
{
}

void FSM_AxeC::RUN_Update(float deltaTime)
{
}

void FSM_AxeC::RUN_End(void)
{
}

void FSM_AxeC::ATTACK_1_Init(void)
{
}

void FSM_AxeC::ATTACK_1_Enter(void)
{
}

void FSM_AxeC::ATTACK_1_Update(float deltaTime)
{
}

void FSM_AxeC::ATTACK_1_End(void)
{
}

void FSM_AxeC::ATTACK_2_Init(void)
{
}

void FSM_AxeC::ATTACK_2_Enter(void)
{
}

void FSM_AxeC::ATTACK_2_Update(float deltaTime)
{
}

void FSM_AxeC::ATTACK_2_End(void)
{
}

void FSM_AxeC::ATTACK_2_1_Init(void)
{
}

void FSM_AxeC::ATTACK_2_1_Enter(void)
{
}

void FSM_AxeC::ATTACK_2_1_Update(float deltaTime)
{
}

void FSM_AxeC::ATTACK_2_1_End(void)
{
}

void FSM_AxeC::ATTACK_3_Init(void)
{
}

void FSM_AxeC::ATTACK_3_Enter(void)
{
}

void FSM_AxeC::ATTACK_3_Update(float deltaTime)
{
}

void FSM_AxeC::ATTACK_3_End(void)
{
}

void FSM_AxeC::ATTACK_3_1_Init(void)
{
}

void FSM_AxeC::ATTACK_3_1_Enter(void)
{
}

void FSM_AxeC::ATTACK_3_1_Update(float deltaTime)
{
}

void FSM_AxeC::ATTACK_3_1_End(void)
{
}

void FSM_AxeC::THROW_1_Init(void)
{
}

void FSM_AxeC::THROW_1_Enter(void)
{
}

void FSM_AxeC::THROW_1_Update(float deltaTime)
{
}

void FSM_AxeC::THROW_1_End(void)
{
}

void FSM_AxeC::THROW_2_Init(void)
{
}

void FSM_AxeC::THROW_2_Enter(void)
{
}

void FSM_AxeC::THROW_2_Update(float deltaTime)
{
}

void FSM_AxeC::THROW_2_End(void)
{
}

void FSM_AxeC::THROW_BLOW_Init(void)
{
}

void FSM_AxeC::THROW_BLOW_Enter(void)
{
}

void FSM_AxeC::THROW_BLOW_Update(float deltaTime)
{
}

void FSM_AxeC::THROW_BLOW_End(void)
{
}

void FSM_AxeC::KNOCK_DOWN_Init(void)
{
}

void FSM_AxeC::KNOCK_DOWN_Enter(void)
{
}

void FSM_AxeC::KNOCK_DOWN_Update(float deltaTime)
{
}

void FSM_AxeC::KNOCK_DOWN_End(void)
{
}

void FSM_AxeC::STAND_UP_Init(void)
{
}

void FSM_AxeC::STAND_UP_Enter(void)
{
}

void FSM_AxeC::STAND_UP_Update(float deltaTime)
{
}

void FSM_AxeC::STAND_UP_End(void)
{
}

void FSM_AxeC::STUN_Init(void)
{
}

void FSM_AxeC::STUN_Enter(void)
{
}

void FSM_AxeC::STUN_Update(float deltaTime)
{
}

void FSM_AxeC::STUN_End(void)
{
}

void FSM_AxeC::HIT_BACK_Init(void)
{
}

void FSM_AxeC::HIT_BACK_Enter(void)
{
}

void FSM_AxeC::HIT_BACK_Update(float deltaTime)
{
}

void FSM_AxeC::HIT_BACK_End(void)
{
}

void FSM_AxeC::HIT_THROW_Init(void)
{
}

void FSM_AxeC::HIT_THROW_Enter(void)
{
}

void FSM_AxeC::HIT_THROW_Update(float deltaTime)
{
}

void FSM_AxeC::HIT_THROW_End(void)
{
}

void FSM_AxeC::HIT_THROW_LOW_Init(void)
{
}

void FSM_AxeC::HIT_THROW_LOW_Enter(void)
{
}

void FSM_AxeC::HIT_THROW_LOW_Update(float deltaTime)
{
}

void FSM_AxeC::HIT_THROW_LOW_End(void)
{
}

void FSM_AxeC::DIE_Init(void)
{
}

void FSM_AxeC::DIE_Enter(void)
{
}

void FSM_AxeC::DIE_Update(float deltaTime)
{
}

void FSM_AxeC::DIE_End(void)
{
}

void FSM_AxeC::DIE_BACK_Init(void)
{
}

void FSM_AxeC::DIE_BACK_Enter(void)
{
}

void FSM_AxeC::DIE_BACK_Update(float deltaTime)
{
}

void FSM_AxeC::DIE_BACK_End(void)
{
}

void FSM_AxeC::DIE_FLY_Init(void)
{
}

void FSM_AxeC::DIE_FLY_Enter(void)
{
}

void FSM_AxeC::DIE_FLY_Update(float deltaTime)
{
}

void FSM_AxeC::DIE_FLY_End(void)
{
}

HRESULT FSM_AxeC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_AxeC, pState, IDLE)
		AddState(pState, L"IDLE");

	CreateState(FSM_AxeC, pState, WALK_RIGHT)
		AddState(pState, L"WALK_RIGHT");

	CreateState(FSM_AxeC, pState, WALK_LEFT)
		AddState(pState, L"WALK_LEFT");

	CreateState(FSM_AxeC, pState, WALK_BACK)
		AddState(pState, L"WALK_BACK");

	CreateState(FSM_AxeC, pState, RUN)
		AddState(pState, L"RUN");

	CreateState(FSM_AxeC, pState, ATTACK_1)
		AddState(pState, L"ATTACK_1");

	CreateState(FSM_AxeC, pState, ATTACK_2)
		AddState(pState, L"ATTACK_2");

	CreateState(FSM_AxeC, pState, ATTACK_2_1)
		AddState(pState, L"ATTACK_2_1");

	CreateState(FSM_AxeC, pState, ATTACK_3)
		AddState(pState, L"ATTACK_3");

	CreateState(FSM_AxeC, pState, ATTACK_3_1)
		AddState(pState, L"ATTACK_3_1");

	CreateState(FSM_AxeC, pState, THROW_1)
		AddState(pState, L"THROW_1");

	CreateState(FSM_AxeC, pState, THROW_2)
		AddState(pState, L"THROW_2");

	CreateState(FSM_AxeC, pState, THROW_BLOW)
		AddState(pState, L"THROW_BLOW");

	CreateState(FSM_AxeC, pState, KNOCK_DOWN)
		AddState(pState, L"KNOCK_DOWN");

	CreateState(FSM_AxeC, pState, STAND_UP)
		AddState(pState, L"STAND_UP");

	CreateState(FSM_AxeC, pState, STUN)
		AddState(pState, L"STUN");

	CreateState(FSM_AxeC, pState, HIT_BACK)
		AddState(pState, L"HIT_BACK");

	CreateState(FSM_AxeC, pState, HIT_THROW)
		AddState(pState, L"HIT_THROW");

	CreateState(FSM_AxeC, pState, HIT_THROW_LOW)
		AddState(pState, L"HIT_THROW_LOW");

	CreateState(FSM_AxeC, pState, DIE)
		AddState(pState, L"DIE");

	CreateState(FSM_AxeC, pState, DIE_BACK)
		AddState(pState, L"DIE_BACK");

	CreateState(FSM_AxeC, pState, DIE_FLY)
		AddState(pState, L"DIE_FLY");

	if (pState == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}
