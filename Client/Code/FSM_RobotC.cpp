#include "stdafx.h"
#include "..\Header\FSM_RobotC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Robot.h"

CFSM_RobotC::CFSM_RobotC()
{
}

SP(Engine::CComponent) CFSM_RobotC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_RobotC>(pObject);

	return spClone;
}

void CFSM_RobotC::Awake(void)
{
	__super::Awake();
}

void CFSM_RobotC::Start(SP(CComponent) spThis)
{
	RegisterAllStage();

	__super::Start(spThis);
	
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	SetStartState(Name_StandBy);
	m_curState->DoEnter();
}

void CFSM_RobotC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_RobotC, pState, ATTACK_1_Left)
		AddState(pState, Name_Attack_1_Left);

	CreateState(CFSM_RobotC, pState, ATTACK_1_Right)
		AddState(pState, Name_Attack_1_Right);

	CreateState(CFSM_RobotC, pState, ATTACK_2)
		AddState(pState, Name_Attack_2);

	CreateState(CFSM_RobotC, pState, RUN_ATTACK_BS)
		AddState(pState, Name_Run_Attack_BS);

	CreateState(CFSM_RobotC, pState, ATTACK_RUN_LOOP)
		AddState(pState, Name_Attack_Run_Loop);

	CreateState(CFSM_RobotC, pState, DIE)
		AddState(pState, Name_Die);

	CreateState(CFSM_RobotC, pState, DIE_BACK)
		AddState(pState, Name_Die_Back);

	CreateState(CFSM_RobotC, pState, FASTRUN_LOOP)
		AddState(pState, Name_FastRun_Loop);

	CreateState(CFSM_RobotC, pState, FREE_FALL)
		AddState(pState, Name_Freefall);

	CreateState(CFSM_RobotC, pState, FREE_FALL_Low)
		AddState(pState, Name_Freefall_Low);

	CreateState(CFSM_RobotC, pState, Hit_Back)
		AddState(pState, Name_Hit_Back);

	CreateState(CFSM_RobotC, pState, Hit_H)
		AddState(pState, Name_Hit_H);

	CreateState(CFSM_RobotC, pState, Hit_L_1)
		AddState(pState, Name_Hit_L_1);

	CreateState(CFSM_RobotC, pState, Hit_L_1_Light)
		AddState(pState, Name_Hit_L_1_Light);

	CreateState(CFSM_RobotC, pState, Hit_L_2)
		AddState(pState, Name_Hit_L_2);

	CreateState(CFSM_RobotC, pState, Hit_L_1_Light)
		AddState(pState, Name_Hit_L_2_Light);

	CreateState(CFSM_RobotC, pState, Hit_Shake)
		AddState(pState, Name_Hit_Shake);

	CreateState(CFSM_RobotC, pState, Hit_Throw)
		AddState(pState, Name_Hit_Throw);

	CreateState(CFSM_RobotC, pState, Hit_Throw_Low)
		AddState(pState, Name_Hit_Throw_Low);

	CreateState(CFSM_RobotC, pState, KnockDown)
		AddState(pState, Name_KnockDown);

	CreateState(CFSM_RobotC, pState, Run_AS)
		AddState(pState, Name_Run_AS);

	CreateState(CFSM_RobotC, pState, Run_Attack)
		AddState(pState, Name_Run_Attack);

	CreateState(CFSM_RobotC, pState, Run_Attack_Quick)
		AddState(pState, Name_Run_Attack_Quick);

	CreateState(CFSM_RobotC, pState, StandBy)
		AddState(pState, Name_StandBy);

	CreateState(CFSM_RobotC, pState, StandUp)
		AddState(pState, Name_StandUp);

	CreateState(CFSM_RobotC, pState, Throw_01)
		AddState(pState, Name_Throw_01);

	CreateState(CFSM_RobotC, pState, Throw_02)
		AddState(pState, Name_Throw_02);

	CreateState(CFSM_RobotC, pState, Throw_Blow)
		AddState(pState, Name_Throw_Blow);

	CreateState(CFSM_RobotC, pState, Walk_Backward)
		AddState(pState, Name_Walk_Backward);

	CreateState(CFSM_RobotC, pState, Walk_Forward)
		AddState(pState, Name_Walk_Forward);
}

void CFSM_RobotC::FixRootMotionOffset(_uint index)
{
}

void CFSM_RobotC::ATTACK_1_Left_Init(void)
{
}

void CFSM_RobotC::ATTACK_1_Left_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1_Left);
}

void CFSM_RobotC::ATTACK_1_Left_Update(float deltaTime)
{
}

void CFSM_RobotC::ATTACK_1_Left_End(void)
{
}

void CFSM_RobotC::ATTACK_1_Right_Init(void)
{
}

void CFSM_RobotC::ATTACK_1_Right_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1_Right);
}

void CFSM_RobotC::ATTACK_1_Right_Update(float deltaTime)
{
}

void CFSM_RobotC::ATTACK_1_Right_End(void)
{
}

void CFSM_RobotC::ATTACK_2_Init(void)
{
}

void CFSM_RobotC::ATTACK_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2);
}

void CFSM_RobotC::ATTACK_2_Update(float deltaTime)
{
}

void CFSM_RobotC::ATTACK_2_End(void)
{
}

void CFSM_RobotC::RUN_ATTACK_BS_Init(void)
{
}

void CFSM_RobotC::RUN_ATTACK_BS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run_Attack_BS);
}

void CFSM_RobotC::RUN_ATTACK_BS_Update(float deltaTime)
{
}

void CFSM_RobotC::RUN_ATTACK_BS_End(void)
{
}

void CFSM_RobotC::ATTACK_RUN_LOOP_Init(void)
{
}

void CFSM_RobotC::ATTACK_RUN_LOOP_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_Run_Loop);
}

void CFSM_RobotC::ATTACK_RUN_LOOP_Update(float deltaTime)
{
}

void CFSM_RobotC::ATTACK_RUN_LOOP_End(void)
{
}

void CFSM_RobotC::DIE_Init(void)
{
}

void CFSM_RobotC::DIE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die);
}

void CFSM_RobotC::DIE_Update(float deltaTime)
{
}

void CFSM_RobotC::DIE_End(void)
{
}

void CFSM_RobotC::DIE_BACK_Init(void)
{
}

void CFSM_RobotC::DIE_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die_Back);
}

void CFSM_RobotC::DIE_BACK_Update(float deltaTime)
{
}

void CFSM_RobotC::DIE_BACK_End(void)
{
}

void CFSM_RobotC::FASTRUN_LOOP_Init(void)
{
}

void CFSM_RobotC::FASTRUN_LOOP_Enter(void)
{
	m_pDM->ChangeAniSet(Index_FastRun_Loop);
}

void CFSM_RobotC::FASTRUN_LOOP_Update(float deltaTime)
{
}

void CFSM_RobotC::FASTRUN_LOOP_End(void)
{
}

void CFSM_RobotC::FREE_FALL_Init(void)
{
}

void CFSM_RobotC::FREE_FALL_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Freefall);
}

void CFSM_RobotC::FREE_FALL_Update(float deltaTime)
{
}

void CFSM_RobotC::FREE_FALL_End(void)
{
}

void CFSM_RobotC::FREE_FALL_Low_Init(void)
{
}

void CFSM_RobotC::FREE_FALL_Low_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Freefall_Low);
}

void CFSM_RobotC::FREE_FALL_Low_Update(float deltaTime)
{
}

void CFSM_RobotC::FREE_FALL_Low_End(void)
{
}

void CFSM_RobotC::Hit_Back_Init(void)
{
}

void CFSM_RobotC::Hit_Back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Back);
}

void CFSM_RobotC::Hit_Back_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_Back_End(void)
{
}

void CFSM_RobotC::Hit_H_Init(void)
{
}

void CFSM_RobotC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H);
}

void CFSM_RobotC::Hit_H_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_H_End(void)
{
}

void CFSM_RobotC::Hit_L_1_Init(void)
{
}

void CFSM_RobotC::Hit_L_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L_1);
}

void CFSM_RobotC::Hit_L_1_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_L_1_End(void)
{
}

void CFSM_RobotC::Hit_L_1_Light_Init(void)
{
}

void CFSM_RobotC::Hit_L_1_Light_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L_1_Light);
}

void CFSM_RobotC::Hit_L_1_Light_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_L_1_Light_End(void)
{
}

void CFSM_RobotC::Hit_L_2_Init(void)
{
}

void CFSM_RobotC::Hit_L_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L_2);
}

void CFSM_RobotC::Hit_L_2_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_L_2_End(void)
{
}

void CFSM_RobotC::Hit_L_2_Light_Init(void)
{
}

void CFSM_RobotC::Hit_L_2_Light_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L_2_Light);
}

void CFSM_RobotC::Hit_L_2_Light_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_L_2_Light_End(void)
{
}

void CFSM_RobotC::Hit_Shake_Init(void)
{
}

void CFSM_RobotC::Hit_Shake_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Shake);
}

void CFSM_RobotC::Hit_Shake_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_Shake_End(void)
{
}

void CFSM_RobotC::Hit_Throw_Init(void)
{
}

void CFSM_RobotC::Hit_Throw_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Throw);
}

void CFSM_RobotC::Hit_Throw_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_Throw_End(void)
{
}

void CFSM_RobotC::Hit_Throw_Low_Init(void)
{
}

void CFSM_RobotC::Hit_Throw_Low_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Throw_Low);
}

void CFSM_RobotC::Hit_Throw_Low_Update(float deltaTime)
{
}

void CFSM_RobotC::Hit_Throw_Low_End(void)
{
}

void CFSM_RobotC::KnockDown_Init(void)
{
}

void CFSM_RobotC::KnockDown_Enter(void)
{
	m_pDM->ChangeAniSet(Index_KnockDown);
}

void CFSM_RobotC::KnockDown_Update(float deltaTime)
{
}

void CFSM_RobotC::KnockDown_End(void)
{
}

void CFSM_RobotC::Run_AS_Init(void)
{
}

void CFSM_RobotC::Run_AS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run_AS);
}

void CFSM_RobotC::Run_AS_Update(float deltaTime)
{
}

void CFSM_RobotC::Run_AS_End(void)
{
}

void CFSM_RobotC::Run_Attack_Init(void)
{
}

void CFSM_RobotC::Run_Attack_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run_Attack);
}

void CFSM_RobotC::Run_Attack_Update(float deltaTime)
{
}

void CFSM_RobotC::Run_Attack_End(void)
{
}

void CFSM_RobotC::Run_Attack_Quick_Init(void)
{
}

void CFSM_RobotC::Run_Attack_Quick_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run_Attack_Quick);
}

void CFSM_RobotC::Run_Attack_Quick_Update(float deltaTime)
{
}

void CFSM_RobotC::Run_Attack_Quick_End(void)
{
}

void CFSM_RobotC::StandBy_Init(void)
{
}

void CFSM_RobotC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
}

void CFSM_RobotC::StandBy_Update(float deltaTime)
{
}

void CFSM_RobotC::StandBy_End(void)
{
}

void CFSM_RobotC::StandUp_Init(void)
{
}

void CFSM_RobotC::StandUp_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandUp);
}

void CFSM_RobotC::StandUp_Update(float deltaTime)
{
}

void CFSM_RobotC::StandUp_End(void)
{
}

void CFSM_RobotC::Throw_01_Init(void)
{
}

void CFSM_RobotC::Throw_01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_01);
}

void CFSM_RobotC::Throw_01_Update(float deltaTime)
{
}

void CFSM_RobotC::Throw_01_End(void)
{
}

void CFSM_RobotC::Throw_02_Init(void)
{
}

void CFSM_RobotC::Throw_02_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_02);
}

void CFSM_RobotC::Throw_02_Update(float deltaTime)
{
}

void CFSM_RobotC::Throw_02_End(void)
{
}

void CFSM_RobotC::Throw_Blow_Init(void)
{
}

void CFSM_RobotC::Throw_Blow_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_Blow);
}

void CFSM_RobotC::Throw_Blow_Update(float deltaTime)
{
}

void CFSM_RobotC::Throw_Blow_End(void)
{
}

void CFSM_RobotC::Walk_Backward_Init(void)
{
}

void CFSM_RobotC::Walk_Backward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Backward);
}

void CFSM_RobotC::Walk_Backward_Update(float deltaTime)
{
}

void CFSM_RobotC::Walk_Backward_End(void)
{
}

void CFSM_RobotC::Walk_Forward_Init(void)
{
}

void CFSM_RobotC::Walk_Forward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Forward);
}

void CFSM_RobotC::Walk_Forward_Update(float deltaTime)
{
}

void CFSM_RobotC::Walk_Forward_End(void)
{
}
