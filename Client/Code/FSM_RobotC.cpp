#include "stdafx.h"
#include "..\Header\FSM_RobotC.h"
#include "State.h"
#include "DynamicMeshData.h"

FSM_RobotC::FSM_RobotC()
{
}

SP(Engine::CComponent) FSM_RobotC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_RobotC>(pObject);

	return spClone;
}

void FSM_RobotC::Awake(void)
{
	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"FSM_RobotC Init_FSM_Setting Failed");
		ABORT;
	}

	__super::Awake();
}

void FSM_RobotC::Start(SP(CComponent) spThis)
{
	SetStartState(L"StandBy");
	__super::Start(spThis);
}

void FSM_RobotC::ATTACK_1_Left_Init(void)
{
}

void FSM_RobotC::ATTACK_1_Left_Enter(void)
{
}

void FSM_RobotC::ATTACK_1_Left_Update(float deltaTime)
{
}

void FSM_RobotC::ATTACK_1_Left_End(void)
{
}

void FSM_RobotC::ATTACK_1_Right_Init(void)
{
}

void FSM_RobotC::ATTACK_1_Right_Enter(void)
{
}

void FSM_RobotC::ATTACK_1_Right_Update(float deltaTime)
{
}

void FSM_RobotC::ATTACK_1_Right_End(void)
{
}

void FSM_RobotC::ATTACK_2_Init(void)
{
}

void FSM_RobotC::ATTACK_2_Enter(void)
{
}

void FSM_RobotC::ATTACK_2_Update(float deltaTime)
{
}

void FSM_RobotC::ATTACK_2_End(void)
{
}

void FSM_RobotC::RUN_ATTACK_BS_Init(void)
{
}

void FSM_RobotC::RUN_ATTACK_BS_Enter(void)
{
}

void FSM_RobotC::RUN_ATTACK_BS_Update(float deltaTime)
{
}

void FSM_RobotC::RUN_ATTACK_BS_End(void)
{
}

void FSM_RobotC::ATTACK_RUN_LOOP_Init(void)
{
}

void FSM_RobotC::ATTACK_RUN_LOOP_Enter(void)
{
}

void FSM_RobotC::ATTACK_RUN_LOOP_Update(float deltaTime)
{
}

void FSM_RobotC::ATTACK_RUN_LOOP_End(void)
{
}

void FSM_RobotC::DIE_Init(void)
{
}

void FSM_RobotC::DIE_Enter(void)
{
}

void FSM_RobotC::DIE_Update(float deltaTime)
{
}

void FSM_RobotC::DIE_End(void)
{
}

void FSM_RobotC::DIE_BACK_Init(void)
{
}

void FSM_RobotC::DIE_BACK_Enter(void)
{
}

void FSM_RobotC::DIE_BACK_Update(float deltaTime)
{
}

void FSM_RobotC::DIE_BACK_End(void)
{
}

void FSM_RobotC::FASTRUN_LOOP_Init(void)
{
}

void FSM_RobotC::FASTRUN_LOOP_Enter(void)
{
}

void FSM_RobotC::FASTRUN_LOOP_Update(float deltaTime)
{
}

void FSM_RobotC::FASTRUN_LOOP_End(void)
{
}

void FSM_RobotC::FREE_FALL_Init(void)
{
}

void FSM_RobotC::FREE_FALL_Enter(void)
{
}

void FSM_RobotC::FREE_FALL_Update(float deltaTime)
{
}

void FSM_RobotC::FREE_FALL_End(void)
{
}

void FSM_RobotC::FREE_FALL_Low_Init(void)
{
}

void FSM_RobotC::FREE_FALL_Low_Enter(void)
{
}

void FSM_RobotC::FREE_FALL_Low_Update(float deltaTime)
{
}

void FSM_RobotC::FREE_FALL_Low_End(void)
{
}

void FSM_RobotC::Hit_Back_Init(void)
{
}

void FSM_RobotC::Hit_Back_Enter(void)
{
}

void FSM_RobotC::Hit_Back_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_Back_End(void)
{
}

void FSM_RobotC::Hit_H_Init(void)
{
}

void FSM_RobotC::Hit_H_Enter(void)
{
}

void FSM_RobotC::Hit_H_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_H_End(void)
{
}

void FSM_RobotC::Hit_L_1_Init(void)
{
}

void FSM_RobotC::Hit_L_1_Enter(void)
{
}

void FSM_RobotC::Hit_L_1_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_L_1_End(void)
{
}

void FSM_RobotC::Hit_L_1_Light_Init(void)
{
}

void FSM_RobotC::Hit_L_1_Light_Enter(void)
{
}

void FSM_RobotC::Hit_L_1_Light_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_L_1_Light_End(void)
{
}

void FSM_RobotC::Hit_L_2_Init(void)
{
}

void FSM_RobotC::Hit_L_2_Enter(void)
{
}

void FSM_RobotC::Hit_L_2_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_L_2_End(void)
{
}

void FSM_RobotC::Hit_L_2_Light_Init(void)
{
}

void FSM_RobotC::Hit_L_2_Light_Enter(void)
{
}

void FSM_RobotC::Hit_L_2_Light_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_L_2_Light_End(void)
{
}

void FSM_RobotC::Hit_Shake_Init(void)
{
}

void FSM_RobotC::Hit_Shake_Enter(void)
{
}

void FSM_RobotC::Hit_Shake_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_Shake_End(void)
{
}

void FSM_RobotC::Hit_Throw_Init(void)
{
}

void FSM_RobotC::Hit_Throw_Enter(void)
{
}

void FSM_RobotC::Hit_Throw_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_Throw_End(void)
{
}

void FSM_RobotC::Hit_Throw_Low_Init(void)
{
}

void FSM_RobotC::Hit_Throw_Low_Enter(void)
{
}

void FSM_RobotC::Hit_Throw_Low_Update(float deltaTime)
{
}

void FSM_RobotC::Hit_Throw_Low_End(void)
{
}

void FSM_RobotC::KnockDown_Init(void)
{
}

void FSM_RobotC::KnockDown_Enter(void)
{
}

void FSM_RobotC::KnockDown_Update(float deltaTime)
{
}

void FSM_RobotC::KnockDown_End(void)
{
}

void FSM_RobotC::Attack_1_Left_Init(void)
{
}

void FSM_RobotC::Attack_1_Left_Enter(void)
{
}

void FSM_RobotC::Attack_1_Left_Update(float deltaTime)
{
}

void FSM_RobotC::Attack_1_Left_End(void)
{
}

void FSM_RobotC::Attack_1_Right_Init(void)
{
}

void FSM_RobotC::Attack_1_Right_Enter(void)
{
}

void FSM_RobotC::Attack_1_Right_Update(float deltaTime)
{
}

void FSM_RobotC::Attack_1_Right_End(void)
{
}

void FSM_RobotC::Run_AS_Init(void)
{
}

void FSM_RobotC::Run_AS_Enter(void)
{
}

void FSM_RobotC::Run_AS_Update(float deltaTime)
{
}

void FSM_RobotC::Run_AS_End(void)
{
}

void FSM_RobotC::Run_Attack_Init(void)
{
}

void FSM_RobotC::Run_Attack_Enter(void)
{
}

void FSM_RobotC::Run_Attack_Update(float deltaTime)
{
}

void FSM_RobotC::Run_Attack_End(void)
{
}

void FSM_RobotC::Run_Attack_Quick_Init(void)
{
}

void FSM_RobotC::Run_Attack_Quick_Enter(void)
{
}

void FSM_RobotC::Run_Attack_Quick_Update(float deltaTime)
{
}

void FSM_RobotC::Run_Attack_Quick_End(void)
{
}

void FSM_RobotC::StandBy_Init(void)
{
}

void FSM_RobotC::StandBy_Enter(void)
{
}

void FSM_RobotC::StandBy_Update(float deltaTime)
{
}

void FSM_RobotC::StandBy_End(void)
{
}

void FSM_RobotC::StandUp_Init(void)
{
}

void FSM_RobotC::StandUp_Enter(void)
{
}

void FSM_RobotC::StandUp_Update(float deltaTime)
{
}

void FSM_RobotC::StandUp_End(void)
{
}

void FSM_RobotC::Throw_01_Init(void)
{
}

void FSM_RobotC::Throw_01_Enter(void)
{
}

void FSM_RobotC::Throw_01_Update(float deltaTime)
{
}

void FSM_RobotC::Throw_01_End(void)
{
}

void FSM_RobotC::Throw_02_Init(void)
{
}

void FSM_RobotC::Throw_02_Enter(void)
{
}

void FSM_RobotC::Throw_02_Update(float deltaTime)
{
}

void FSM_RobotC::Throw_02_End(void)
{
}

void FSM_RobotC::Throw_Blow_Init(void)
{
}

void FSM_RobotC::Throw_Blow_Enter(void)
{
}

void FSM_RobotC::Throw_Blow_Update(float deltaTime)
{
}

void FSM_RobotC::Throw_Blow_End(void)
{
}

void FSM_RobotC::Walk_Backward_Init(void)
{
}

void FSM_RobotC::Walk_Backward_Enter(void)
{
}

void FSM_RobotC::Walk_Backward_Update(float deltaTime)
{
}

void FSM_RobotC::Walk_Backward_End(void)
{
}

void FSM_RobotC::Walk_Forward_Init(void)
{
}

void FSM_RobotC::Walk_Forward_Enter(void)
{
}

void FSM_RobotC::Walk_Forward_Update(float deltaTime)
{
}

void FSM_RobotC::Walk_Forward_End(void)
{
}

HRESULT FSM_RobotC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_RobotC, pState, ATTACK_1_Left)
		AddState(pState, L"ATTACK_1_Left");

	CreateState(FSM_RobotC, pState, ATTACK_1_Right)
		AddState(pState, L"ATTACK_1_Right");

	CreateState(FSM_RobotC, pState, ATTACK_2)
		AddState(pState, L"ATTACK_2");

	CreateState(FSM_RobotC, pState, RUN_ATTACK_BS)
		AddState(pState, L"RUN_ATTACK_BS");

	CreateState(FSM_RobotC, pState, ATTACK_RUN_LOOP)
		AddState(pState, L"ATTACK_RUN_LOOP");

	CreateState(FSM_RobotC, pState, DIE)
		AddState(pState, L"DIE");

	CreateState(FSM_RobotC, pState, DIE_BACK)
		AddState(pState, L"DIE_BACK");

	CreateState(FSM_RobotC, pState, FASTRUN_LOOP)
		AddState(pState, L"FASTRUN_LOOP");

	CreateState(FSM_RobotC, pState, FREE_FALL)
		AddState(pState, L"FREE_FALL");

	CreateState(FSM_RobotC, pState, FREE_FALL_Low)
		AddState(pState, L"FREE_FALL_Low");

	CreateState(FSM_RobotC, pState, Hit_Back)
		AddState(pState, L"Hit_Back");

	CreateState(FSM_RobotC, pState, Hit_H)
		AddState(pState, L"Hit_H");

	CreateState(FSM_RobotC, pState, Hit_L_1)
		AddState(pState, L"Hit_L_1");

	CreateState(FSM_RobotC, pState, Hit_L_1_Light)
		AddState(pState, L"Hit_L_1_Light");

	CreateState(FSM_RobotC, pState, Hit_L_2)
		AddState(pState, L"Hit_L_2");

	CreateState(FSM_RobotC, pState, Hit_L_1_Light)
		AddState(pState, L"Hit_L_1_Light");

	CreateState(FSM_RobotC, pState, Hit_Shake)
		AddState(pState, L"Hit_Shake");

	CreateState(FSM_RobotC, pState, Hit_Throw)
		AddState(pState, L"Hit_Throw");

	CreateState(FSM_RobotC, pState, Hit_Throw_Low)
		AddState(pState, L"Hit_Throw_Low");

	CreateState(FSM_RobotC, pState, KnockDown)
		AddState(pState, L"KnockDown");

	CreateState(FSM_RobotC, pState, Attack_1_Left)
		AddState(pState, L"Attack_1_Left");

	CreateState(FSM_RobotC, pState, Attack_1_Right)
		AddState(pState, L"Attack_1_Right");

	CreateState(FSM_RobotC, pState, Run_AS)
		AddState(pState, L"Run_AS");

	CreateState(FSM_RobotC, pState, Run_Attack)
		AddState(pState, L"Run_Attack");

	CreateState(FSM_RobotC, pState, Run_Attack_Quick)
		AddState(pState, L"Run_Attack_Quick");

	CreateState(FSM_RobotC, pState, StandBy)
		AddState(pState, L"StandBy");

	CreateState(FSM_RobotC, pState, StandUp)
		AddState(pState, L"StandUp");

	CreateState(FSM_RobotC, pState, Throw_01)
		AddState(pState, L"Throw_01");

	CreateState(FSM_RobotC, pState, Throw_02)
		AddState(pState, L"Throw_02");

	CreateState(FSM_RobotC, pState, Throw_Blow)
		AddState(pState, L"Throw_Blow");

	CreateState(FSM_RobotC, pState, Walk_Backward)
		AddState(pState, L"Walk_Backward");

	CreateState(FSM_RobotC, pState, Walk_Forward)
		AddState(pState, L"Walk_Forward");

	if (pState == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

