#include "stdafx.h"
#include "..\Header\FSM_NinzaC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Ninza.h"

CFSM_NinzaC::CFSM_NinzaC()
{
}

SP(Engine::CComponent) CFSM_NinzaC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_NinzaC>(pObject);

	return spClone;
}

void CFSM_NinzaC::Awake()
{
	__super::Awake();
}

void CFSM_NinzaC::Start(SP(CComponent) spThis)
{
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	RegisterAllStage();

	__super::Start(spThis);


	SetStartState(Name_born);
	m_curState->DoEnter();
}

void CFSM_NinzaC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_NinzaC, pState, Attack_1_as)
		AddState(pState, Name_attack_1_as);

	CreateState(CFSM_NinzaC, pState, Attack_1_atk)
		AddState(pState, Name_attack_1_atk);

	CreateState(CFSM_NinzaC, pState, Attack_1_bs)
		AddState(pState, Name_attack_1_bs);

	CreateState(CFSM_NinzaC, pState, Attack_2_atk_1)
		AddState(pState, Name_attack_2_atk_1);

	CreateState(CFSM_NinzaC, pState, Attack_2_atk_2)
		AddState(pState, Name_attack_2_atk_2);

	CreateState(CFSM_NinzaC, pState, Attack_2_atk_3)
		AddState(pState, Name_attack_2_atk_3);

	CreateState(CFSM_NinzaC, pState, Attack_2_atk_as_long)
		AddState(pState, Name_attack_2_atk_as_long);

	CreateState(CFSM_NinzaC, pState, Attack_2_bs)
		AddState(pState, Name_attack_2_bs);

	CreateState(CFSM_NinzaC, pState, Born)
		AddState(pState, Name_born);

	CreateState(CFSM_NinzaC, pState, Defend)
		AddState(pState, Name_defend);

	CreateState(CFSM_NinzaC, pState, DefendAttack)
		AddState(pState, Name_defendattack);

	CreateState(CFSM_NinzaC, pState, Die)
		AddState(pState, Name_die);

	CreateState(CFSM_NinzaC, pState, Die_back)
		AddState(pState, Name_die_back);

	CreateState(CFSM_NinzaC, pState, Die_fly)
		AddState(pState, Name_die_fly);

	CreateState(CFSM_NinzaC, pState, Hit_back)
		AddState(pState, Name_hit_back);

	CreateState(CFSM_NinzaC, pState, Hit_front)
		AddState(pState, Name_hit_front);

	CreateState(CFSM_NinzaC, pState, Hit_front_L)
		AddState(pState, Name_hit_front_l);

	CreateState(CFSM_NinzaC, pState, Hit_H)
		AddState(pState, Name_hit_h);

	CreateState(CFSM_NinzaC, pState, Hit_Left)
		AddState(pState, Name_hit_left);

	CreateState(CFSM_NinzaC, pState, Hit_Right)
		AddState(pState, Name_hit_right);

	CreateState(CFSM_NinzaC, pState, Hit_Shake)
		AddState(pState, Name_hit_shake);

	CreateState(CFSM_NinzaC, pState, Hit_Throw)
		AddState(pState, Name_hit_throw);

	CreateState(CFSM_NinzaC, pState, Hit_Throw_Low)
		AddState(pState, Name_hit_throw_low);

	CreateState(CFSM_NinzaC, pState, KnockDown)
		AddState(pState, Name_knockdown);

	CreateState(CFSM_NinzaC, pState, Run)
		AddState(pState, Name_run);

	CreateState(CFSM_NinzaC, pState, StandBy)
		AddState(pState, Name_standby);

	CreateState(CFSM_NinzaC, pState, StandUp)
		AddState(pState, Name_standup);

	CreateState(CFSM_NinzaC, pState, Stay)
		AddState(pState, Name_stay);

	CreateState(CFSM_NinzaC, pState, Stun)
		AddState(pState, Name_stun);

	CreateState(CFSM_NinzaC, pState, Teleport)
		AddState(pState, Name_teleport);

	CreateState(CFSM_NinzaC, pState, Throw_01)
		AddState(pState, Name_throw_01);

	CreateState(CFSM_NinzaC, pState, Throw_02)
		AddState(pState, Name_throw_02);

	CreateState(CFSM_NinzaC, pState, Throw_Blow)
		AddState(pState, Name_throw_blow);

	CreateState(CFSM_NinzaC, pState, Walk_B)
		AddState(pState, Name_walk_b);

	CreateState(CFSM_NinzaC, pState, Walk_F)
		AddState(pState, Name_walk_f);

	CreateState(CFSM_NinzaC, pState, Walk_L)
		AddState(pState, Name_walk_l);

	CreateState(CFSM_NinzaC, pState, Walk_R)
		AddState(pState, Name_walk_r);
}

void CFSM_NinzaC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_NinzaC::StandBy_Init(void)
{
	m_pDM->SetLoopAnim(Index_standby);
}

void CFSM_NinzaC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_standby);
}

void CFSM_NinzaC::StandBy_Update(float deltaTime)
{
}

void CFSM_NinzaC::StandBy_End(void)
{
}

void CFSM_NinzaC::Attack_1_as_Init(void)
{
}

void CFSM_NinzaC::Attack_1_as_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_1_as);
}

void CFSM_NinzaC::Attack_1_as_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_1_as_End(void)
{
}

void CFSM_NinzaC::Attack_1_atk_Init(void)
{
}

void CFSM_NinzaC::Attack_1_atk_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_1_atk);
}

void CFSM_NinzaC::Attack_1_atk_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_1_atk_End(void)
{
}

void CFSM_NinzaC::Attack_1_bs_Init(void)
{
}

void CFSM_NinzaC::Attack_1_bs_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_1_bs);
}

void CFSM_NinzaC::Attack_1_bs_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_1_bs_End(void)
{
}

void CFSM_NinzaC::Attack_2_atk_1_Init(void)
{
}

void CFSM_NinzaC::Attack_2_atk_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_2_atk_1);
}

void CFSM_NinzaC::Attack_2_atk_1_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_2_atk_1_End(void)
{
}

void CFSM_NinzaC::Attack_2_atk_2_Init(void)
{
}

void CFSM_NinzaC::Attack_2_atk_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_2_atk_2);
}

void CFSM_NinzaC::Attack_2_atk_2_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_2_atk_2_End(void)
{
}

void CFSM_NinzaC::Attack_2_atk_3_Init(void)
{
}

void CFSM_NinzaC::Attack_2_atk_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_2_atk_3);
}

void CFSM_NinzaC::Attack_2_atk_3_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_2_atk_3_End(void)
{
}

void CFSM_NinzaC::Attack_2_atk_as_long_Init(void)
{
}

void CFSM_NinzaC::Attack_2_atk_as_long_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_2_atk_as_long);
}

void CFSM_NinzaC::Attack_2_atk_as_long_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_2_atk_as_long_End(void)
{
}

void CFSM_NinzaC::Attack_2_bs_Init(void)
{
}

void CFSM_NinzaC::Attack_2_bs_Enter(void)
{
	m_pDM->ChangeAniSet(Index_attack_2_bs);
}

void CFSM_NinzaC::Attack_2_bs_Update(float deltaTime)
{
}

void CFSM_NinzaC::Attack_2_bs_End(void)
{
}

void CFSM_NinzaC::Born_Init(void)
{
}

void CFSM_NinzaC::Born_Enter(void)
{
	m_pDM->ChangeAniSet(Index_born);
}

void CFSM_NinzaC::Born_Update(float deltaTime)
{
}

void CFSM_NinzaC::Born_End(void)
{
}

void CFSM_NinzaC::Defend_Init(void)
{
}

void CFSM_NinzaC::Defend_Enter(void)
{
	m_pDM->ChangeAniSet(Index_defend);
}

void CFSM_NinzaC::Defend_Update(float deltaTime)
{
}

void CFSM_NinzaC::Defend_End(void)
{
}

void CFSM_NinzaC::DefendAttack_Init(void)
{
}

void CFSM_NinzaC::DefendAttack_Enter(void)
{
	m_pDM->ChangeAniSet(Index_defendattack);
}

void CFSM_NinzaC::DefendAttack_Update(float deltaTime)
{
}

void CFSM_NinzaC::DefendAttack_End(void)
{
}

void CFSM_NinzaC::Die_Init(void)
{
}

void CFSM_NinzaC::Die_Enter(void)
{
	m_pDM->ChangeAniSet(Index_die);
}

void CFSM_NinzaC::Die_Update(float deltaTime)
{
}

void CFSM_NinzaC::Die_End(void)
{
}

void CFSM_NinzaC::Die_back_Init(void)
{
}

void CFSM_NinzaC::Die_back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_die_back);
}

void CFSM_NinzaC::Die_back_Update(float deltaTime)
{
}

void CFSM_NinzaC::Die_back_End(void)
{
}

void CFSM_NinzaC::Die_fly_Init(void)
{
}

void CFSM_NinzaC::Die_fly_Enter(void)
{
	m_pDM->ChangeAniSet(Index_die_fly);
}

void CFSM_NinzaC::Die_fly_Update(float deltaTime)
{
}

void CFSM_NinzaC::Die_fly_End(void)
{
}

void CFSM_NinzaC::Hit_back_Init(void)
{
}

void CFSM_NinzaC::Hit_back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_back);
}

void CFSM_NinzaC::Hit_back_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_back_End(void)
{
}

void CFSM_NinzaC::Hit_front_Init(void)
{
}

void CFSM_NinzaC::Hit_front_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_front);
}

void CFSM_NinzaC::Hit_front_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_front_End(void)
{
}

void CFSM_NinzaC::Hit_front_L_Init(void)
{
}

void CFSM_NinzaC::Hit_front_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_front_l);
}

void CFSM_NinzaC::Hit_front_L_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_front_L_End(void)
{
}

void CFSM_NinzaC::Hit_H_Init(void)
{
}

void CFSM_NinzaC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_h);
}

void CFSM_NinzaC::Hit_H_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_H_End(void)
{
}

void CFSM_NinzaC::Hit_Left_Init(void)
{
}

void CFSM_NinzaC::Hit_Left_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_left);
}

void CFSM_NinzaC::Hit_Left_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_Left_End(void)
{
}

void CFSM_NinzaC::Hit_Right_Init(void)
{
}

void CFSM_NinzaC::Hit_Right_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_right);
}

void CFSM_NinzaC::Hit_Right_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_Right_End(void)
{
}

void CFSM_NinzaC::Hit_Shake_Init(void)
{
}

void CFSM_NinzaC::Hit_Shake_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_shake);
}

void CFSM_NinzaC::Hit_Shake_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_Shake_End(void)
{
}

void CFSM_NinzaC::Hit_Throw_Init(void)
{
}

void CFSM_NinzaC::Hit_Throw_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_throw);
}

void CFSM_NinzaC::Hit_Throw_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_Throw_End(void)
{
}

void CFSM_NinzaC::Hit_Throw_Low_Init(void)
{
}

void CFSM_NinzaC::Hit_Throw_Low_Enter(void)
{
	m_pDM->ChangeAniSet(Index_hit_throw_low);
}

void CFSM_NinzaC::Hit_Throw_Low_Update(float deltaTime)
{
}

void CFSM_NinzaC::Hit_Throw_Low_End(void)
{
}

void CFSM_NinzaC::KnockDown_Init(void)
{
}

void CFSM_NinzaC::KnockDown_Enter(void)
{
	m_pDM->ChangeAniSet(Index_knockdown);
}

void CFSM_NinzaC::KnockDown_Update(float deltaTime)
{
}

void CFSM_NinzaC::KnockDown_End(void)
{
}

void CFSM_NinzaC::Run_Init(void)
{
}

void CFSM_NinzaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_run);
}

void CFSM_NinzaC::Run_Update(float deltaTime)
{
}

void CFSM_NinzaC::Run_End(void)
{
}

void CFSM_NinzaC::StandUp_Init(void)
{
}

void CFSM_NinzaC::StandUp_Enter(void)
{
	m_pDM->ChangeAniSet(Index_standup);
}

void CFSM_NinzaC::StandUp_Update(float deltaTime)
{
}

void CFSM_NinzaC::StandUp_End(void)
{
}

void CFSM_NinzaC::Stay_Init(void)
{
}

void CFSM_NinzaC::Stay_Enter(void)
{
	m_pDM->ChangeAniSet(Index_stay);
}

void CFSM_NinzaC::Stay_Update(float deltaTime)
{
}

void CFSM_NinzaC::Stay_End(void)
{
}

void CFSM_NinzaC::Stun_Init(void)
{
}

void CFSM_NinzaC::Stun_Enter(void)
{
	m_pDM->ChangeAniSet(Index_stun);
}

void CFSM_NinzaC::Stun_Update(float deltaTime)
{
}

void CFSM_NinzaC::Stun_End(void)
{
}

void CFSM_NinzaC::Teleport_Init(void)
{
}

void CFSM_NinzaC::Teleport_Enter(void)
{
	m_pDM->ChangeAniSet(Index_teleport);
}

void CFSM_NinzaC::Teleport_Update(float deltaTime)
{
}

void CFSM_NinzaC::Teleport_End(void)
{
}

void CFSM_NinzaC::Throw_01_Init(void)
{
}

void CFSM_NinzaC::Throw_01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_throw_01);
}

void CFSM_NinzaC::Throw_01_Update(float deltaTime)
{
}

void CFSM_NinzaC::Throw_01_End(void)
{
}

void CFSM_NinzaC::Throw_02_Init(void)
{
}

void CFSM_NinzaC::Throw_02_Enter(void)
{
	m_pDM->ChangeAniSet(Index_throw_02);
}

void CFSM_NinzaC::Throw_02_Update(float deltaTime)
{
}

void CFSM_NinzaC::Throw_02_End(void)
{
}

void CFSM_NinzaC::Throw_Blow_Init(void)
{
}

void CFSM_NinzaC::Throw_Blow_Enter(void)
{
	m_pDM->ChangeAniSet(Index_throw_blow);
}

void CFSM_NinzaC::Throw_Blow_Update(float deltaTime)
{
}

void CFSM_NinzaC::Throw_Blow_End(void)
{
}

void CFSM_NinzaC::Walk_B_Init(void)
{
}

void CFSM_NinzaC::Walk_B_Enter(void)
{
	m_pDM->ChangeAniSet(Index_walk_b);
}

void CFSM_NinzaC::Walk_B_Update(float deltaTime)
{
}

void CFSM_NinzaC::Walk_B_End(void)
{
}

void CFSM_NinzaC::Walk_F_Init(void)
{
}

void CFSM_NinzaC::Walk_F_Enter(void)
{
	m_pDM->ChangeAniSet(Index_walk_f);
}

void CFSM_NinzaC::Walk_F_Update(float deltaTime)
{
}

void CFSM_NinzaC::Walk_F_End(void)
{
}

void CFSM_NinzaC::Walk_L_Init(void)
{
}

void CFSM_NinzaC::Walk_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_walk_l);
}

void CFSM_NinzaC::Walk_L_Update(float deltaTime)
{
}

void CFSM_NinzaC::Walk_L_End(void)
{
}

void CFSM_NinzaC::Walk_R_Init(void)
{
}

void CFSM_NinzaC::Walk_R_Enter(void)
{
	m_pDM->ChangeAniSet(Index_walk_r);
}

void CFSM_NinzaC::Walk_R_Update(float deltaTime)
{
}

void CFSM_NinzaC::Walk_R_End(void)
{
}
