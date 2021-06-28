#include "stdafx.h"
#include "..\Header\FSM_NinzaC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Ninza.h"

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
	__super::Awake();
}

void FSM_NinzaC::Start(SP(CComponent) spThis)
{
	RegisterAllStage();

	__super::Start(spThis);

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	SetStartState(Name_standby);
	m_curState->DoEnter();
}

void FSM_NinzaC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(FSM_NinzaC, pState, StandBy)
		AddState(pState, L"standby");

	CreateState(FSM_NinzaC, pState, Attack_1_as)
		AddState(pState, L"attack_1_as");

	CreateState(FSM_NinzaC, pState, Attack_1_atk)
		AddState(pState, L"attack_1_atk");

	CreateState(FSM_NinzaC, pState, Attack_1_bs)
		AddState(pState, L"attack_1_bs");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_1)
		AddState(pState, L"attack_2_atk_1");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_2)
		AddState(pState, L"attack_2_atk_2");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_3)
		AddState(pState, L"attack_2_atk_3");

	CreateState(FSM_NinzaC, pState, Attack_2_atk_as_long)
		AddState(pState, L"attack_2_atk_as_long");

	CreateState(FSM_NinzaC, pState, Born)
		AddState(pState, L"born");

	CreateState(FSM_NinzaC, pState, Defend)
		AddState(pState, L"defend");

	CreateState(FSM_NinzaC, pState, DefendAttack)
		AddState(pState, L"defendattack");

	CreateState(FSM_NinzaC, pState, Die)
		AddState(pState, L"die");

	CreateState(FSM_NinzaC, pState, Die_back)
		AddState(pState, L"die_back");

	CreateState(FSM_NinzaC, pState, Die_fly)
		AddState(pState, L"die_fly");

	CreateState(FSM_NinzaC, pState, Hit_back)
		AddState(pState, L"hit_back");

	CreateState(FSM_NinzaC, pState, Hit_front)
		AddState(pState, L"hit_front");

	CreateState(FSM_NinzaC, pState, Hit_front_L)
		AddState(pState, L"hit_front_l");

	CreateState(FSM_NinzaC, pState, Hit_H)
		AddState(pState, L"hit_h");

	CreateState(FSM_NinzaC, pState, Hit_Left)
		AddState(pState, L"hit_left");

	CreateState(FSM_NinzaC, pState, Hit_Right)
		AddState(pState, L"hit_right");

	CreateState(FSM_NinzaC, pState, Hit_Shake)
		AddState(pState, L"hit_shake");

	CreateState(FSM_NinzaC, pState, Hit_Right)
		AddState(pState, L"hit_right");

	CreateState(FSM_NinzaC, pState, Hit_Throw)
		AddState(pState, L"hit_throw");

	CreateState(FSM_NinzaC, pState, Hit_Throw_L)
		AddState(pState, L"hit_throw_l");

	CreateState(FSM_NinzaC, pState, KnockDown)
		AddState(pState, L"knockdown");

	CreateState(FSM_NinzaC, pState, Run)
		AddState(pState, L"run");

	CreateState(FSM_NinzaC, pState, StandUp)
		AddState(pState, L"standup");

	CreateState(FSM_NinzaC, pState, Stay)
		AddState(pState, L"stay");

	CreateState(FSM_NinzaC, pState, Stun)
		AddState(pState, L"stun");

	CreateState(FSM_NinzaC, pState, Teleport)
		AddState(pState, L"teleport");

	CreateState(FSM_NinzaC, pState, Throw_01)
		AddState(pState, L"throw_01");

	CreateState(FSM_NinzaC, pState, Throw_02)
		AddState(pState, L"throw_02");

	CreateState(FSM_NinzaC, pState, Throw_Blow)
		AddState(pState, L"throw_blow");

	CreateState(FSM_NinzaC, pState, Walk_B)
		AddState(pState, L"walk_b");

	CreateState(FSM_NinzaC, pState, Walk_F)
		AddState(pState, L"walk_f");

	CreateState(FSM_NinzaC, pState, Walk_L)
		AddState(pState, L"walk_l");

	CreateState(FSM_NinzaC, pState, Walk_R)
		AddState(pState, L"walk_r");
}

void FSM_NinzaC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void FSM_NinzaC::StandBy_Init(void)
{
}

void FSM_NinzaC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_standby);
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
	m_pDM->ChangeAniSet(Index_attack_1_as);
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
	m_pDM->ChangeAniSet(Index_attack_1_atk);
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
	m_pDM->ChangeAniSet(Index_attack_1_bs);
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
	m_pDM->ChangeAniSet(Index_attack_2_atk_1);
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
	m_pDM->ChangeAniSet(Index_attack_2_atk_2);
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
	m_pDM->ChangeAniSet(Index_attack_2_atk_3);
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
	m_pDM->ChangeAniSet(Index_attack_2_atk_as_long);
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
	m_pDM->ChangeAniSet(Index_born);
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
	m_pDM->ChangeAniSet(Index_defend);
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
	m_pDM->ChangeAniSet(Index_defendattack);
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
	m_pDM->ChangeAniSet(Index_die);
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
	m_pDM->ChangeAniSet(Index_die_back);
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
	m_pDM->ChangeAniSet(Index_die_fly);
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
	m_pDM->ChangeAniSet(Index_hit_back);
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
	m_pDM->ChangeAniSet(Index_hit_front);
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
	m_pDM->ChangeAniSet(Index_hit_front_l);
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
	m_pDM->ChangeAniSet(Index_hit_h);
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
	m_pDM->ChangeAniSet(Index_hit_left);
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
	m_pDM->ChangeAniSet(Index_hit_right);
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
	m_pDM->ChangeAniSet(Index_hit_shake);
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
	m_pDM->ChangeAniSet(Index_hit_throw);
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
	m_pDM->ChangeAniSet(Index_hit_throw);
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
	m_pDM->ChangeAniSet(Index_knockdown);
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
	m_pDM->ChangeAniSet(Index_run);
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
	m_pDM->ChangeAniSet(Index_standup);
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
	m_pDM->ChangeAniSet(Index_stay);
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
	m_pDM->ChangeAniSet(Index_stun);
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
	m_pDM->ChangeAniSet(Index_teleport);
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
	m_pDM->ChangeAniSet(Index_throw_01);
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
	m_pDM->ChangeAniSet(Index_throw_02);
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
	m_pDM->ChangeAniSet(Index_throw_blow);
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
	m_pDM->ChangeAniSet(Index_walk_b);
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
	m_pDM->ChangeAniSet(Index_walk_f);
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
	m_pDM->ChangeAniSet(Index_walk_l);
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
	m_pDM->ChangeAniSet(Index_walk_r);
}

void FSM_NinzaC::Walk_R_Update(float deltaTime)
{
}

void FSM_NinzaC::Walk_R_End(void)
{
}
