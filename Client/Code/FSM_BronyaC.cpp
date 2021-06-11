#include "stdafx.h"
#include "..\Header\FSM_BronyaC.h"

FSM_BronyaC::FSM_BronyaC()
{
}

SP(Engine::CComponent) FSM_BronyaC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_BronyaC>(pObject);

	return spClone;
}


void FSM_BronyaC::Awake(void)
{
	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"FSM_BronyaC Init_FSM_Setting Failed");
		ABORT;
	}

	__super::Awake();
}

void FSM_BronyaC::Start(SP(CComponent) spThis)
{
	SetStartState(L"IDLE");
	__super::Start(spThis);
}

void FSM_BronyaC::IDLE_Init(void)
{
}

void FSM_BronyaC::IDLE_Enter(void)
{
}

void FSM_BronyaC::IDLE_Update(float deltaTime)
{
}

void FSM_BronyaC::IDLE_End(void)
{
}

void FSM_BronyaC::Run_Init(void)
{
}

void FSM_BronyaC::Run_Enter(void)
{
}

void FSM_BronyaC::Run_Update(float deltaTime)
{
}

void FSM_BronyaC::Run_End(void)
{
}

void FSM_BronyaC::DashBack_Init(void)
{
}

void FSM_BronyaC::DashBack_Enter(void)
{
}

void FSM_BronyaC::DashBack_Update(float deltaTime)
{
}

void FSM_BronyaC::DashBack_End(void)
{
}

void FSM_BronyaC::Arsenal_Charge_Init(void)
{
}

void FSM_BronyaC::Arsenal_Charge_Enter(void)
{
}

void FSM_BronyaC::Arsenal_Charge_Update(float deltaTime)
{
}

void FSM_BronyaC::Arsenal_Charge_End(void)
{
}

void FSM_BronyaC::Arsenal_Loop_Init(void)
{
}

void FSM_BronyaC::Arsenal_Loop_Enter(void)
{
}

void FSM_BronyaC::Arsenal_Loop_Update(float deltaTime)
{
}

void FSM_BronyaC::Arsenal_Loop_End(void)
{
}

void FSM_BronyaC::Arsenal_End_Init(void)
{
}

void FSM_BronyaC::Arsenal_End_Enter(void)
{
}

void FSM_BronyaC::Arsenal_End_Update(float deltaTime)
{
}

void FSM_BronyaC::Arsenal_End_End(void)
{
}

void FSM_BronyaC::Escape_Out_Init(void)
{
}

void FSM_BronyaC::Escape_Out_Enter(void)
{
}

void FSM_BronyaC::Escape_Out_Update(float deltaTime)
{
}

void FSM_BronyaC::Escape_Out_End(void)
{
}

void FSM_BronyaC::Escape_In_Init(void)
{
}

void FSM_BronyaC::Escape_In_Enter(void)
{
}

void FSM_BronyaC::Escape_In_Update(float deltaTime)
{
}

void FSM_BronyaC::Escape_In_End(void)
{
}

void FSM_BronyaC::Evade_Left_Init(void)
{
}

void FSM_BronyaC::Evade_Left_Enter(void)
{
}

void FSM_BronyaC::Evade_Left_Update(float deltaTime)
{
}

void FSM_BronyaC::Evade_Left_End(void)
{
}

void FSM_BronyaC::Evade_Right_Init(void)
{
}

void FSM_BronyaC::Evade_Right_Enter(void)
{
}

void FSM_BronyaC::Evade_Right_Update(float deltaTime)
{
}

void FSM_BronyaC::Evade_Right_End(void)
{
}

void FSM_BronyaC::Attack_1_Init(void)
{
}

void FSM_BronyaC::Attack_1_Enter(void)
{
}

void FSM_BronyaC::Attack_1_Update(float deltaTime)
{
}

void FSM_BronyaC::Attack_1_End(void)
{
}

void FSM_BronyaC::Shoot_1_Init(void)
{
}

void FSM_BronyaC::Shoot_1_Enter(void)
{
}

void FSM_BronyaC::Shoot_1_Update(float deltaTime)
{
}

void FSM_BronyaC::Shoot_1_End(void)
{
}

void FSM_BronyaC::Shoot_2_Init(void)
{
}

void FSM_BronyaC::Shoot_2_Enter(void)
{
}

void FSM_BronyaC::Shoot_2_Update(float deltaTime)
{
}

void FSM_BronyaC::Shoot_2_End(void)
{
}

void FSM_BronyaC::Shoot_3_Init(void)
{
}

void FSM_BronyaC::Shoot_3_Enter(void)
{
}

void FSM_BronyaC::Shoot_3_Update(float deltaTime)
{
}

void FSM_BronyaC::Shoot_3_End(void)
{
}

void FSM_BronyaC::Shock_1_Init(void)
{
}

void FSM_BronyaC::Shock_1_Enter(void)
{
}

void FSM_BronyaC::Shock_1_Update(float deltaTime)
{
}

void FSM_BronyaC::Shock_1_End(void)
{
}

void FSM_BronyaC::Shock_2_Init(void)
{
}

void FSM_BronyaC::Shock_2_Enter(void)
{
}

void FSM_BronyaC::Shock_2_Update(float deltaTime)
{
}

void FSM_BronyaC::Shock_2_End(void)
{
}

void FSM_BronyaC::Shock_2_Boom_Init(void)
{
}

void FSM_BronyaC::Shock_2_Boom_Enter(void)
{
}

void FSM_BronyaC::Shock_2_Boom_Update(float deltaTime)
{
}

void FSM_BronyaC::Shock_2_Boom_End(void)
{
}

void FSM_BronyaC::Shock_2_Miss_Init(void)
{
}

void FSM_BronyaC::Shock_2_Miss_Enter(void)
{
}

void FSM_BronyaC::Shock_2_Miss_Update(float deltaTime)
{
}

void FSM_BronyaC::Shock_2_Miss_End(void)
{
}

void FSM_BronyaC::Stealth_BACK_Init(void)
{
}

void FSM_BronyaC::Stealth_BACK_Enter(void)
{
}

void FSM_BronyaC::Stealth_BACK_Update(float deltaTime)
{
}

void FSM_BronyaC::Stealth_BACK_End(void)
{
}

void FSM_BronyaC::Snealth_Init(void)
{
}

void FSM_BronyaC::Snealth_Enter(void)
{
}

void FSM_BronyaC::Snealth_Update(float deltaTime)
{
}

void FSM_BronyaC::Snealth_End(void)
{
}

void FSM_BronyaC::Summon_Init(void)
{
}

void FSM_BronyaC::Summon_Enter(void)
{
}

void FSM_BronyaC::Summon_Update(float deltaTime)
{
}

void FSM_BronyaC::Summon_End(void)
{
}

void FSM_BronyaC::Throw_1_Init(void)
{
}

void FSM_BronyaC::Throw_1_Enter(void)
{
}

void FSM_BronyaC::Throw_1_Update(float deltaTime)
{
}

void FSM_BronyaC::Throw_1_End(void)
{
}

void FSM_BronyaC::Throw_2_Init(void)
{
}

void FSM_BronyaC::Throw_2_Enter(void)
{
}

void FSM_BronyaC::Throw_2_Update(float deltaTime)
{
}

void FSM_BronyaC::Throw_2_End(void)
{
}

void FSM_BronyaC::Throw_3_Init(void)
{
}

void FSM_BronyaC::Throw_3_Enter(void)
{
}

void FSM_BronyaC::Throw_3_Update(float deltaTime)
{
}

void FSM_BronyaC::Throw_3_End(void)
{
}

void FSM_BronyaC::Skill_Ultra_Init(void)
{
}

void FSM_BronyaC::Skill_Ultra_Enter(void)
{
}

void FSM_BronyaC::Skill_Ultra_Update(float deltaTime)
{
}

void FSM_BronyaC::Skill_Ultra_End(void)
{
}

void FSM_BronyaC::Weak_Init(void)
{
}

void FSM_BronyaC::Weak_Enter(void)
{
}

void FSM_BronyaC::Weak_Update(float deltaTime)
{
}

void FSM_BronyaC::Weak_End(void)
{
}

void FSM_BronyaC::Weak_Hit_L_Init(void)
{
}

void FSM_BronyaC::Weak_Hit_L_Enter(void)
{
}

void FSM_BronyaC::Weak_Hit_L_Update(float deltaTime)
{
}

void FSM_BronyaC::Weak_Hit_L_End(void)
{
}

void FSM_BronyaC::Weak_Hit_H_Init(void)
{
}

void FSM_BronyaC::Weak_Hit_H_Enter(void)
{
}

void FSM_BronyaC::Weak_Hit_H_Update(float deltaTime)
{
}

void FSM_BronyaC::Weak_Hit_H_End(void)
{
}

void FSM_BronyaC::Weak_Start_L_Init(void)
{
}

void FSM_BronyaC::Weak_Start_L_Enter(void)
{
}

void FSM_BronyaC::Weak_Start_L_Update(float deltaTime)
{
}

void FSM_BronyaC::Weak_Start_L_End(void)
{
}

void FSM_BronyaC::Weak_Start_H_Init(void)
{
}

void FSM_BronyaC::Weak_Start_H_Enter(void)
{
}

void FSM_BronyaC::Weak_Start_H_Update(float deltaTime)
{
}

void FSM_BronyaC::Weak_Start_H_End(void)
{
}

void FSM_BronyaC::Hit_H_Init(void)
{
}

void FSM_BronyaC::Hit_H_Enter(void)
{
}

void FSM_BronyaC::Hit_H_Update(float deltaTime)
{
}

void FSM_BronyaC::Hit_H_End(void)
{
}

void FSM_BronyaC::Die_Init(void)
{
}

void FSM_BronyaC::Die_Enter(void)
{
}

void FSM_BronyaC::Die_Update(float deltaTime)
{
}

void FSM_BronyaC::Die_End(void)
{
}

HRESULT FSM_BronyaC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_BronyaC, pState, IDLE)
		AddState(pState, L"IDLE");

	CreateState(FSM_BronyaC, pState, Run)
		AddState(pState, L"Run");

	CreateState(FSM_BronyaC, pState, DashBack)
		AddState(pState, L"DashBack");

	CreateState(FSM_BronyaC, pState, Arsenal_Charge)
		AddState(pState, L"Arsenal_Charge");

	CreateState(FSM_BronyaC, pState, Arsenal_Loop)
		AddState(pState, L"Arsenal_Loop");

	CreateState(FSM_BronyaC, pState, Arsenal_End)
		AddState(pState, L"Arsenal_End");

	CreateState(FSM_BronyaC, pState, Escape_Out)
		AddState(pState, L"Escape_Out");

	CreateState(FSM_BronyaC, pState, Escape_In)
		AddState(pState, L"Escape_In");

	CreateState(FSM_BronyaC, pState, Evade_Left)
		AddState(pState, L"Evade_Left");

	CreateState(FSM_BronyaC, pState, Evade_Right)
		AddState(pState, L"Evade_Right");

	CreateState(FSM_BronyaC, pState, Attack_1)
		AddState(pState, L"Attack_1");

	CreateState(FSM_BronyaC, pState, Shoot_1)
		AddState(pState, L"Shoot_1");

	CreateState(FSM_BronyaC, pState, Shoot_2)
		AddState(pState, L"Shoot_2");

	CreateState(FSM_BronyaC, pState, Shoot_3)
		AddState(pState, L"Shoot_3");

	CreateState(FSM_BronyaC, pState, Shock_1)
		AddState(pState, L"Shock_1");

	CreateState(FSM_BronyaC, pState, Shock_2)
		AddState(pState, L"Shock_2");

	CreateState(FSM_BronyaC, pState, Shock_2_Boom)
		AddState(pState, L"Shock_2_Boom");

	CreateState(FSM_BronyaC, pState, Shock_2_Miss)
		AddState(pState, L"Shock_2_Miss");

	CreateState(FSM_BronyaC, pState, Stealth_BACK)
		AddState(pState, L"Stealth_BACK");

	CreateState(FSM_BronyaC, pState, Snealth)
		AddState(pState, L"Snealth");

	CreateState(FSM_BronyaC, pState, Summon)
		AddState(pState, L"Summon");

	CreateState(FSM_BronyaC, pState, Throw_1)
		AddState(pState, L"Throw_1");

	CreateState(FSM_BronyaC, pState, Throw_2)
		AddState(pState, L"Throw_2");

	CreateState(FSM_BronyaC, pState, Throw_3)
		AddState(pState, L"Throw_3");

	CreateState(FSM_BronyaC, pState, Skill_Ultra)
		AddState(pState, L"Skill_Ultra");

	CreateState(FSM_BronyaC, pState, Weak)
		AddState(pState, L"Weak");

	CreateState(FSM_BronyaC, pState, Weak_Hit_L)
		AddState(pState, L"Weak_Hit_L");

	CreateState(FSM_BronyaC, pState, Weak_Hit_H)
		AddState(pState, L"Weak_Hit_H");

	CreateState(FSM_BronyaC, pState, Weak_Start_L)
		AddState(pState, L"Weak_Start_L");

	CreateState(FSM_BronyaC, pState, Weak_Start_H)
		AddState(pState, L"Weak_Start_H");

	CreateState(FSM_BronyaC, pState, Hit_H)
		AddState(pState, L"Hit_H");

	CreateState(FSM_BronyaC, pState, Die)
		AddState(pState, L"Die");

	if (pState == nullptr)
		return E_FAIL;

	return S_OK;
}
