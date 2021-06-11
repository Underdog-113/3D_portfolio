#include "stdafx.h"
#include "..\Header\FSM_ScoutC.h"
#include "State.h"
#include "DynamicMeshData.h"


FSM_ScoutC::FSM_ScoutC()
{
}

SP(Engine::CComponent) FSM_ScoutC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_ScoutC>(pObject);

	return spClone;
}

void FSM_ScoutC::Awake(void)
{
	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"FSM_ScoutC Init_FSM_Setting Failed");
		ABORT;
	}


	__super::Awake();
}

void FSM_ScoutC::Start(SP(CComponent) spThis)
{
	SetStartState(L"APPEAR");
	__super::Start(spThis);
}

void FSM_ScoutC::APPEAR_Init(void)
{
}

void FSM_ScoutC::APPEAR_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(0);
}

void FSM_ScoutC::APPEAR_Update(float deltaTime)
{
}

void FSM_ScoutC::APPEAR_End(void)
{
}

void FSM_ScoutC::IDLE_Init(void)
{
}

void FSM_ScoutC::IDLE_Enter(void)
{
}

void FSM_ScoutC::IDLE_Update(float deltaTime)
{
}

void FSM_ScoutC::IDLE_End(void)
{
}

void FSM_ScoutC::RUN_L_Init(void)
{
}

void FSM_ScoutC::RUN_L_Enter(void)
{
}

void FSM_ScoutC::RUN_L_Update(float deltaTime)
{
}

void FSM_ScoutC::RUN_L_End(void)
{
}

void FSM_ScoutC::RUN_R_Init(void)
{
}

void FSM_ScoutC::RUN_R_Enter(void)
{
}

void FSM_ScoutC::RUN_R_Update(float deltaTime)
{
}

void FSM_ScoutC::RUN_R_End(void)
{
}

void FSM_ScoutC::RUN_F_Init(void)
{
}

void FSM_ScoutC::RUN_F_Enter(void)
{
}

void FSM_ScoutC::RUN_F_Update(float deltaTime)
{
}

void FSM_ScoutC::RUN_F_End(void)
{
}

void FSM_ScoutC::RUN_B_Init(void)
{
}

void FSM_ScoutC::RUN_B_Enter(void)
{
}

void FSM_ScoutC::RUN_B_Update(float deltaTime)
{
}

void FSM_ScoutC::RUN_B_End(void)
{
}

void FSM_ScoutC::SHOOT_1_Init(void)
{
}

void FSM_ScoutC::SHOOT_1_Enter(void)
{
}

void FSM_ScoutC::SHOOT_1_Update(float deltaTime)
{
}

void FSM_ScoutC::SHOOT_1_End(void)
{
}

void FSM_ScoutC::SHOOT_2_Init(void)
{
}

void FSM_ScoutC::SHOOT_2_Enter(void)
{
}

void FSM_ScoutC::SHOOT_2_Update(float deltaTime)
{
}

void FSM_ScoutC::SHOOT_2_End(void)
{
}

void FSM_ScoutC::SHOOT_3_Init(void)
{
}

void FSM_ScoutC::SHOOT_3_Enter(void)
{
}

void FSM_ScoutC::SHOOT_3_Update(float deltaTime)
{
}

void FSM_ScoutC::SHOOT_3_End(void)
{
}

void FSM_ScoutC::SHOOT_FIREFALL_Init(void)
{
}

void FSM_ScoutC::SHOOT_FIREFALL_Enter(void)
{
}

void FSM_ScoutC::SHOOT_FIREFALL_Update(float deltaTime)
{
}

void FSM_ScoutC::SHOOT_FIREFALL_End(void)
{
}

void FSM_ScoutC::LASER_BS_Init(void)
{
}

void FSM_ScoutC::LASER_BS_Enter(void)
{
}

void FSM_ScoutC::LASER_BS_Update(float deltaTime)
{
}

void FSM_ScoutC::LASER_BS_End(void)
{
}

void FSM_ScoutC::LASER_LOOP_Init(void)
{
}

void FSM_ScoutC::LASER_LOOP_Enter(void)
{
}

void FSM_ScoutC::LASER_LOOP_Update(float deltaTime)
{
}

void FSM_ScoutC::LASER_LOOP_End(void)
{
}

void FSM_ScoutC::LASER_AS_Init(void)
{
}

void FSM_ScoutC::LASER_AS_Enter(void)
{
}

void FSM_ScoutC::LASER_AS_Update(float deltaTime)
{
}

void FSM_ScoutC::LASER_AS_End(void)
{
}

void FSM_ScoutC::HIT_L_Init(void)
{
}

void FSM_ScoutC::HIT_L_Enter(void)
{
}

void FSM_ScoutC::HIT_L_Update(float deltaTime)
{
}

void FSM_ScoutC::HIT_L_End(void)
{
}

void FSM_ScoutC::HIT_H_Init(void)
{
}

void FSM_ScoutC::HIT_H_Enter(void)
{
}

void FSM_ScoutC::HIT_H_Update(float deltaTime)
{
}

void FSM_ScoutC::HIT_H_End(void)
{
}

void FSM_ScoutC::HIT_FRONT_Init(void)
{
}

void FSM_ScoutC::HIT_FRONT_Enter(void)
{
}

void FSM_ScoutC::HIT_FRONT_Update(float deltaTime)
{
}

void FSM_ScoutC::HIT_FRONT_End(void)
{
}

void FSM_ScoutC::HIT_BACK_Init(void)
{
}

void FSM_ScoutC::HIT_BACK_Enter(void)
{
}

void FSM_ScoutC::HIT_BACK_Update(float deltaTime)
{
}

void FSM_ScoutC::HIT_BACK_End(void)
{
}

void FSM_ScoutC::THROW_0_Init(void)
{
}

void FSM_ScoutC::THROW_0_Enter(void)
{
}

void FSM_ScoutC::THROW_0_Update(float deltaTime)
{
}

void FSM_ScoutC::THROW_0_End(void)
{
}

void FSM_ScoutC::THROW_1_Init(void)
{
}

void FSM_ScoutC::THROW_1_Enter(void)
{
}

void FSM_ScoutC::THROW_1_Update(float deltaTime)
{
}

void FSM_ScoutC::THROW_1_End(void)
{
}

void FSM_ScoutC::THROW_2_Init(void)
{
}

void FSM_ScoutC::THROW_2_Enter(void)
{
}

void FSM_ScoutC::THROW_2_Update(float deltaTime)
{
}

void FSM_ScoutC::THROW_2_End(void)
{
}

void FSM_ScoutC::THROW_BLOW_Init(void)
{
}

void FSM_ScoutC::THROW_BLOW_Enter(void)
{
}

void FSM_ScoutC::THROW_BLOW_Update(float deltaTime)
{
}

void FSM_ScoutC::THROW_BLOW_End(void)
{
}

void FSM_ScoutC::THROW_LOW_Init(void)
{
}

void FSM_ScoutC::THROW_LOW_Enter(void)
{
}

void FSM_ScoutC::THROW_LOW_Update(float deltaTime)
{
}

void FSM_ScoutC::THROW_LOW_End(void)
{
}

void FSM_ScoutC::KNOCK_DOWN_Init(void)
{
}

void FSM_ScoutC::KNOCK_DOWN_Enter(void)
{
}

void FSM_ScoutC::KNOCK_DOWN_Update(float deltaTime)
{
}

void FSM_ScoutC::KNOCK_DOWN_End(void)
{
}

void FSM_ScoutC::STAND_UP_Init(void)
{
}

void FSM_ScoutC::STAND_UP_Enter(void)
{
}

void FSM_ScoutC::STAND_UP_Update(float deltaTime)
{
}

void FSM_ScoutC::STAND_UP_End(void)
{
}

void FSM_ScoutC::STUN_Init(void)
{
}

void FSM_ScoutC::STUN_Enter(void)
{
}

void FSM_ScoutC::STUN_Update(float deltaTime)
{
}

void FSM_ScoutC::STUN_End(void)
{
}

void FSM_ScoutC::DIE_Init(void)
{
}

void FSM_ScoutC::DIE_Enter(void)
{
}

void FSM_ScoutC::DIE_Update(float deltaTime)
{
}

void FSM_ScoutC::DIE_End(void)
{
}

void FSM_ScoutC::DIE_FLY_Init(void)
{
}

void FSM_ScoutC::DIE_FLY_Enter(void)
{
}

void FSM_ScoutC::DIE_FLY_Update(float deltaTime)
{
}

void FSM_ScoutC::DIE_FLY_End(void)
{
}

HRESULT FSM_ScoutC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_ScoutC, pState, APPEAR)
		AddState(pState, L"APPEAR");

	CreateState(FSM_ScoutC, pState, IDLE)
		AddState(pState, L"IDLE");

	CreateState(FSM_ScoutC, pState, RUN_L)
		AddState(pState, L"RUN_L");

	CreateState(FSM_ScoutC, pState, RUN_R)
		AddState(pState, L"RUN_R");

	CreateState(FSM_ScoutC, pState, RUN_B)
		AddState(pState, L"RUN_B");

	CreateState(FSM_ScoutC, pState, SHOOT_1)
		AddState(pState, L"SHOOT_1");

	CreateState(FSM_ScoutC, pState, SHOOT_2)
		AddState(pState, L"SHOOT_2");

	CreateState(FSM_ScoutC, pState, SHOOT_3)
		AddState(pState, L"SHOOT_3");

	CreateState(FSM_ScoutC, pState, SHOOT_FIREFALL)
		AddState(pState, L"SHOOT_FIREFALL");

	CreateState(FSM_ScoutC, pState, LASER_BS)
		AddState(pState, L"LASER_BS");

	CreateState(FSM_ScoutC, pState, LASER_LOOP)
		AddState(pState, L"LASER_LOOP");

	CreateState(FSM_ScoutC, pState, LASER_AS)
		AddState(pState, L"LASER_AS");

	CreateState(FSM_ScoutC, pState, HIT_L)
		AddState(pState, L"HIT_L");

	CreateState(FSM_ScoutC, pState, HIT_H)
		AddState(pState, L"HIT_H");

	CreateState(FSM_ScoutC, pState, HIT_FRONT)
		AddState(pState, L"HIT_FRONT");

	CreateState(FSM_ScoutC, pState, HIT_BACK)
		AddState(pState, L"HIT_BACK");

	CreateState(FSM_ScoutC, pState, THROW_0)
		AddState(pState, L"THROW_0");

	CreateState(FSM_ScoutC, pState, THROW_1)
		AddState(pState, L"THROW_1");

	CreateState(FSM_ScoutC, pState, THROW_2)
		AddState(pState, L"THROW_2");

	CreateState(FSM_ScoutC, pState, THROW_BLOW)
		AddState(pState, L"THROW_BLOW");

	CreateState(FSM_ScoutC, pState, THROW_LOW)
		AddState(pState, L"THROW_LOW");

	CreateState(FSM_ScoutC, pState, KNOCK_DOWN)
		AddState(pState, L"KNOCK_DOWN");

	CreateState(FSM_ScoutC, pState, STAND_UP)
		AddState(pState, L"STAND_UP");

	CreateState(FSM_ScoutC, pState, STUN)
		AddState(pState, L"STUN");

	CreateState(FSM_ScoutC, pState, DIE)
		AddState(pState, L"DIE");

	CreateState(FSM_ScoutC, pState, DIE_FLY)
		AddState(pState, L"DIE_FLY");

	if (pState == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}
