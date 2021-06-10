#include "stdafx.h"
#include "..\Header\FSM_NinzaC.h"


FSM_NinzaC::FSM_NinzaC()
{
}

SP(Engine::CComponent) FSM_NinzaC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_NinzaC>(pObject);

	return spClone;
}

void FSM_NinzaC::Awake()
{
	if (FAILED(Init_FSM_Setting()))
	{		
		MSG_BOX(__FILE__, L"FSM_NinzaC Init_FSM_Setting Failed");
		ABORT;
	}

	__super::Awake();
}

void FSM_NinzaC::Start(SP(CComponent) spThis)
{
	SetStartState(L"StandBy");
	__super::Start(spThis);
}

void FSM_NinzaC::StandBy_Init(void)
{
}

void FSM_NinzaC::StandBy_Enter(void)
{
}

void FSM_NinzaC::StandBy_Update(float deltaTime)
{
}

void FSM_NinzaC::StandBy_End(void)
{
}

void FSM_NinzaC::Attack_1_as_Init(void)
{
}

void FSM_NinzaC::Attack_1_as_Enter(void)
{
}

void FSM_NinzaC::Attack_1_as_Update(float deltaTime)
{
}

void FSM_NinzaC::Attack_1_as_End(void)
{
}

void FSM_NinzaC::Attack_1_atk_Init(void)
{
}

void FSM_NinzaC::Attack_1_atk_Enter(void)
{
}

void FSM_NinzaC::Attack_1_atk_Update(float deltaTime)
{
}

void FSM_NinzaC::Attack_1_atk_End(void)
{
}

void FSM_NinzaC::Attack_1_bs_Init(void)
{
}

void FSM_NinzaC::Attack_1_bs_Enter(void)
{
}

void FSM_NinzaC::Attack_1_bs_Update(float deltaTime)
{
}

void FSM_NinzaC::Attack_1_bs_End(void)
{
}

void FSM_NinzaC::Attack_2_atk_1_Init(void)
{
}

void FSM_NinzaC::Attack_2_atk_1_Enter(void)
{
}

void FSM_NinzaC::Attack_2_atk_1_Update(float deltaTime)
{
}

void FSM_NinzaC::Attack_2_atk_1_End(void)
{
}

void FSM_NinzaC::Attack_2_atk_2_Init(void)
{
}

void FSM_NinzaC::Attack_2_atk_2_Enter(void)
{
}

void FSM_NinzaC::Attack_2_atk_2_Update(float deltaTime)
{
}

void FSM_NinzaC::Attack_2_atk_2_End(void)
{
}

void FSM_NinzaC::Attack_2_atk_3_Init(void)
{
}

void FSM_NinzaC::Attack_2_atk_3_Enter(void)
{
}

void FSM_NinzaC::Attack_2_atk_3_Update(float deltaTime)
{
}

void FSM_NinzaC::Attack_2_atk_3_End(void)
{
}

void FSM_NinzaC::Attack_2_atk_as_long_Init(void)
{
}

void FSM_NinzaC::Attack_2_atk_as_long_Enter(void)
{
}

void FSM_NinzaC::Attack_2_atk_as_long_Update(float deltaTime)
{
}

void FSM_NinzaC::Attack_2_atk_as_long_End(void)
{
}

void FSM_NinzaC::Born_Init(void)
{
}

void FSM_NinzaC::Born_Enter(void)
{
}

void FSM_NinzaC::Born_Update(float deltaTime)
{
}

void FSM_NinzaC::Born_End(void)
{
}

void FSM_NinzaC::Defend_Init(void)
{
}

void FSM_NinzaC::Defend_Enter(void)
{
}

void FSM_NinzaC::Defend_Update(float deltaTime)
{
}

void FSM_NinzaC::Defend_End(void)
{
}

void FSM_NinzaC::DefendAttack_Init(void)
{
}

void FSM_NinzaC::DefendAttack_Enter(void)
{
}

void FSM_NinzaC::DefendAttack_Update(float deltaTime)
{
}

void FSM_NinzaC::DefendAttack_End(void)
{
}

void FSM_NinzaC::Die_Init(void)
{
}

void FSM_NinzaC::Die_Enter(void)
{
}

void FSM_NinzaC::Die_Update(float deltaTime)
{
}

void FSM_NinzaC::Die_End(void)
{
}

void FSM_NinzaC::Die_back_Init(void)
{
}

void FSM_NinzaC::Die_back_Enter(void)
{
}

void FSM_NinzaC::Die_back_Update(float deltaTime)
{
}

void FSM_NinzaC::Die_back_End(void)
{
}

void FSM_NinzaC::Die_fly_Init(void)
{
}

void FSM_NinzaC::Die_fly_Enter(void)
{
}

void FSM_NinzaC::Die_fly_Update(float deltaTime)
{
}

void FSM_NinzaC::Die_fly_End(void)
{
}

void FSM_NinzaC::Hit_back_Init(void)
{
}

void FSM_NinzaC::Hit_back_Enter(void)
{
}

void FSM_NinzaC::Hit_back_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_back_End(void)
{
}

void FSM_NinzaC::Hit_front_Init(void)
{
}

void FSM_NinzaC::Hit_front_Enter(void)
{
}

void FSM_NinzaC::Hit_front_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_front_End(void)
{
}

void FSM_NinzaC::Hit_front_L_Init(void)
{
}

void FSM_NinzaC::Hit_front_L_Enter(void)
{
}

void FSM_NinzaC::Hit_front_L_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_front_L_End(void)
{
}

void FSM_NinzaC::Hit_H_Init(void)
{
}

void FSM_NinzaC::Hit_H_Enter(void)
{
}

void FSM_NinzaC::Hit_H_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_H_End(void)
{
}

void FSM_NinzaC::Hit_Left_Init(void)
{
}

void FSM_NinzaC::Hit_Left_Enter(void)
{
}

void FSM_NinzaC::Hit_Left_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_Left_End(void)
{
}

void FSM_NinzaC::Hit_Right_Init(void)
{
}

void FSM_NinzaC::Hit_Right_Enter(void)
{
}

void FSM_NinzaC::Hit_Right_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_Right_End(void)
{
}

void FSM_NinzaC::Hit_Shake_Init(void)
{
}

void FSM_NinzaC::Hit_Shake_Enter(void)
{
}

void FSM_NinzaC::Hit_Shake_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_Shake_End(void)
{
}

void FSM_NinzaC::Hit_Throw_Init(void)
{
}

void FSM_NinzaC::Hit_Throw_Enter(void)
{
}

void FSM_NinzaC::Hit_Throw_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_Throw_End(void)
{
}

void FSM_NinzaC::Hit_Throw_L_Init(void)
{
}

void FSM_NinzaC::Hit_Throw_L_Enter(void)
{
}

void FSM_NinzaC::Hit_Throw_L_Update(float deltaTime)
{
}

void FSM_NinzaC::Hit_Throw_L_End(void)
{
}

void FSM_NinzaC::KnockDown_Init(void)
{
}

void FSM_NinzaC::KnockDown_Enter(void)
{
}

void FSM_NinzaC::KnockDown_Update(float deltaTime)
{
}

void FSM_NinzaC::KnockDown_End(void)
{
}

void FSM_NinzaC::Run_Init(void)
{
}

void FSM_NinzaC::Run_Enter(void)
{
}

void FSM_NinzaC::Run_Update(float deltaTime)
{
}

void FSM_NinzaC::Run_End(void)
{
}

void FSM_NinzaC::StandUp_Init(void)
{
}

void FSM_NinzaC::StandUp_Enter(void)
{
}

void FSM_NinzaC::StandUp_Update(float deltaTime)
{
}

void FSM_NinzaC::StandUp_End(void)
{
}

void FSM_NinzaC::Stay_Init(void)
{
}

void FSM_NinzaC::Stay_Enter(void)
{
}

void FSM_NinzaC::Stay_Update(float deltaTime)
{
}

void FSM_NinzaC::Stay_End(void)
{
}

void FSM_NinzaC::Stun_Init(void)
{
}

void FSM_NinzaC::Stun_Enter(void)
{
}

void FSM_NinzaC::Stun_Update(float deltaTime)
{
}

void FSM_NinzaC::Stun_End(void)
{
}

void FSM_NinzaC::Teleport_Init(void)
{
}

void FSM_NinzaC::Teleport_Enter(void)
{
}

void FSM_NinzaC::Teleport_Update(float deltaTime)
{
}

void FSM_NinzaC::Teleport_End(void)
{
}

void FSM_NinzaC::Throw_01_Init(void)
{
}

void FSM_NinzaC::Throw_01_Enter(void)
{
}

void FSM_NinzaC::Throw_01_Update(float deltaTime)
{
}

void FSM_NinzaC::Throw_01_End(void)
{
}

void FSM_NinzaC::Throw_02_Init(void)
{
}

void FSM_NinzaC::Throw_02_Enter(void)
{
}

void FSM_NinzaC::Throw_02_Update(float deltaTime)
{
}

void FSM_NinzaC::Throw_02_End(void)
{
}

void FSM_NinzaC::Throw_Blow_Init(void)
{
}

void FSM_NinzaC::Throw_Blow_Enter(void)
{
}

void FSM_NinzaC::Throw_Blow_Update(float deltaTime)
{
}

void FSM_NinzaC::Throw_Blow_End(void)
{
}

void FSM_NinzaC::Walk_B_Init(void)
{
}

void FSM_NinzaC::Walk_B_Enter(void)
{
}

void FSM_NinzaC::Walk_B_Update(float deltaTime)
{
}

void FSM_NinzaC::Walk_B_End(void)
{
}

void FSM_NinzaC::Walk_F_Init(void)
{
}

void FSM_NinzaC::Walk_F_Enter(void)
{
}

void FSM_NinzaC::Walk_F_Update(float deltaTime)
{
}

void FSM_NinzaC::Walk_F_End(void)
{
}

void FSM_NinzaC::Walk_L_Init(void)
{
}

void FSM_NinzaC::Walk_L_Enter(void)
{
}

void FSM_NinzaC::Walk_L_Update(float deltaTime)
{
}

void FSM_NinzaC::Walk_L_End(void)
{
}

void FSM_NinzaC::Walk_R_Init(void)
{
}

void FSM_NinzaC::Walk_R_Enter(void)
{
}

void FSM_NinzaC::Walk_R_Update(float deltaTime)
{
}

void FSM_NinzaC::Walk_R_End(void)
{
}

HRESULT FSM_NinzaC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_NinzaC, pState, StandBy)
		AddState(pState, L"StandBy");

	CreateState(FSM_NinzaC, pState, Attack_1_as)
		AddState(pState, L"Attack_1_as");

	CreateState(FSM_NinzaC, pState, Attack_1_atk)
		AddState(pState, L"Attack_1_atk");

	CreateState(FSM_NinzaC, pState, Attack_1_bs)
		AddState(pState, L"Attack_1_bs");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_1)
		AddState(pState, L"Attack_2_atk_1");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_2)
		AddState(pState, L"Attack_2_atk_2");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_3)
		AddState(pState, L"Attack_2_atk_3");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_as_long)
		AddState(pState, L"Attack_2_atk_as_long");

	CreateState(FSM_NinzaC, pState, Born)
		AddState(pState, L"Born");

	CreateState(FSM_NinzaC, pState, Defend)
		AddState(pState, L"Defend");

	CreateState(FSM_NinzaC, pState, DefendAttack)
		AddState(pState, L"DefendAttack");

	CreateState(FSM_NinzaC, pState, Die)
		AddState(pState, L"Die");

	CreateState(FSM_NinzaC, pState, Die_back)
		AddState(pState, L"Die_back");

	CreateState(FSM_NinzaC, pState, Die_fly)
		AddState(pState, L"Die_fly");

	CreateState(FSM_NinzaC, pState, Hit_back)
		AddState(pState, L"Hit_back");

	CreateState(FSM_NinzaC, pState, Hit_front)
		AddState(pState, L"Hit_front");

	CreateState(FSM_NinzaC, pState, Hit_front_L)
		AddState(pState, L"Hit_front_L");

	CreateState(FSM_NinzaC, pState, Hit_H)
		AddState(pState, L"Hit_H");

	CreateState(FSM_NinzaC, pState, Hit_Left)
		AddState(pState, L"Hit_Left");

	CreateState(FSM_NinzaC, pState, Hit_Right)
		AddState(pState, L"Hit_Right");

	CreateState(FSM_NinzaC, pState, Hit_Shake)
		AddState(pState, L"Hit_Shake");

	CreateState(FSM_NinzaC, pState, Hit_Right)
		AddState(pState, L"Hit_Right");

	CreateState(FSM_NinzaC, pState, Hit_Throw)
		AddState(pState, L"Hit_Throw");

	CreateState(FSM_NinzaC, pState, Hit_Throw_L)
		AddState(pState, L"Hit_Throw_L");

	CreateState(FSM_NinzaC, pState, KnockDown)
		AddState(pState, L"KnockDown");

	CreateState(FSM_NinzaC, pState, Run)
		AddState(pState, L"Run");

	CreateState(FSM_NinzaC, pState, StandUp)
		AddState(pState, L"StandUp");

	CreateState(FSM_NinzaC, pState, Stay)
		AddState(pState, L"Stay");

	CreateState(FSM_NinzaC, pState, Stun)
		AddState(pState, L"Stun");

	CreateState(FSM_NinzaC, pState, Teleport)
		AddState(pState, L"Teleport");

	CreateState(FSM_NinzaC, pState, Throw_01)
		AddState(pState, L"Throw_01");

	CreateState(FSM_NinzaC, pState, Throw_02)
		AddState(pState, L"Throw_02");

	CreateState(FSM_NinzaC, pState, Throw_Blow)
		AddState(pState, L"Throw_Blow");

	CreateState(FSM_NinzaC, pState, Walk_B)
		AddState(pState, L"Walk_B");

	CreateState(FSM_NinzaC, pState, Walk_F)
		AddState(pState, L"Walk_F");

	CreateState(FSM_NinzaC, pState, Walk_L)
		AddState(pState, L"Walk_L");

	CreateState(FSM_NinzaC, pState, Walk_R)
		AddState(pState, L"Walk_R");

	if (pState != nullptr)
	{		
		return E_FAIL;
	}

	return S_OK;
}

