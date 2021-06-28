#include "stdafx.h"
#include "..\Header\FSM_RobotC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Robot.h"

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
	__super::Awake();
}

void FSM_RobotC::Start(SP(CComponent) spThis)
{
	RegisterAllStage();

	__super::Start(spThis);
	
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	SetStartState(Name_StandBy);
	m_curState->DoEnter();
}

void FSM_RobotC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(FSM_RobotC, pState, ATTACK_1_Left)
		AddState(pState, Name_Attack_1_Left);

	CreateState(FSM_RobotC, pState, ATTACK_1_Right)
		AddState(pState, Name_Attack_1_Right);

	CreateState(FSM_RobotC, pState, ATTACK_2)
		AddState(pState, Name_Attack_2);

	CreateState(FSM_RobotC, pState, RUN_ATTACK_BS)
		AddState(pState, Name_Run_Attack_BS);

	CreateState(FSM_RobotC, pState, ATTACK_RUN_LOOP)
		AddState(pState, Name_Attack_Run_Loop);

	CreateState(FSM_RobotC, pState, DIE)
		AddState(pState, Name_Die);

	CreateState(FSM_RobotC, pState, DIE_BACK)
		AddState(pState, Name_Die_Back);

	CreateState(FSM_RobotC, pState, FASTRUN_LOOP)
		AddState(pState, Name_FastRun_Loop);

	CreateState(FSM_RobotC, pState, FREE_FALL)
		AddState(pState, Name_Freefall);

	CreateState(FSM_RobotC, pState, FREE_FALL_Low)
		AddState(pState, Name_Freefall_Low);

	CreateState(FSM_RobotC, pState, Hit_Back)
		AddState(pState, Name_Hit_Back);

	CreateState(FSM_RobotC, pState, Hit_H)
		AddState(pState, Name_Hit_H);

	CreateState(FSM_RobotC, pState, Hit_L_1)
		AddState(pState, Name_Hit_L_1);

	CreateState(FSM_RobotC, pState, Hit_L_1_Light)
		AddState(pState, Name_Hit_L_1_Light);

	CreateState(FSM_RobotC, pState, Hit_L_2)
		AddState(pState, Name_Hit_L_2);

	CreateState(FSM_RobotC, pState, Hit_L_1_Light)
		AddState(pState, Name_Hit_L_2_Light);

	CreateState(FSM_RobotC, pState, Hit_Shake)
		AddState(pState, Name_Hit_Shake);

	CreateState(FSM_RobotC, pState, Hit_Throw)
		AddState(pState, Name_Hit_Throw);

	CreateState(FSM_RobotC, pState, Hit_Throw_Low)
		AddState(pState, Name_Hit_Throw_Low);

	CreateState(FSM_RobotC, pState, KnockDown)
		AddState(pState, Name_KnockDown);

	CreateState(FSM_RobotC, pState, Run_AS)
		AddState(pState, Name_Run_AS);

	CreateState(FSM_RobotC, pState, Run_Attack)
		AddState(pState, Name_Run_Attack);

	CreateState(FSM_RobotC, pState, Run_Attack_Quick)
		AddState(pState, Name_Run_Attack_Quick);

	CreateState(FSM_RobotC, pState, StandBy)
		AddState(pState, Name_StandBy);

	CreateState(FSM_RobotC, pState, StandUp)
		AddState(pState, Name_StandUp);

	CreateState(FSM_RobotC, pState, Throw_01)
		AddState(pState, Name_Throw_01);

	CreateState(FSM_RobotC, pState, Throw_02)
		AddState(pState, Name_Throw_02);

	CreateState(FSM_RobotC, pState, Throw_Blow)
		AddState(pState, Name_Throw_Blow);

	CreateState(FSM_RobotC, pState, Walk_Backward)
		AddState(pState, Name_Walk_Backward);

	CreateState(FSM_RobotC, pState, Walk_Forward)
		AddState(pState, Name_Walk_Forward);
}

void FSM_RobotC::FixRootMotionOffset(_uint index)
{
}

void FSM_RobotC::ATTACK_1_Left_Init(void)
{
}

void FSM_RobotC::ATTACK_1_Left_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1_Left);
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
	m_pDM->ChangeAniSet(Index_Attack_1_Right);
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
	m_pDM->ChangeAniSet(Index_Attack_2);
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
	m_pDM->ChangeAniSet(Index_Run_Attack_BS);
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
	m_pDM->ChangeAniSet(Index_Attack_Run_Loop);
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
	m_pDM->ChangeAniSet(Index_Die);
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
	m_pDM->ChangeAniSet(Index_Die_Back);
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
	m_pDM->ChangeAniSet(Index_FastRun_Loop);
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
	m_pDM->ChangeAniSet(Index_Freefall);
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
	m_pDM->ChangeAniSet(Index_Freefall_Low);
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
	m_pDM->ChangeAniSet(Index_Hit_Back);
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
	m_pDM->ChangeAniSet(Index_Hit_H);
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
	m_pDM->ChangeAniSet(Index_Hit_L_1);
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
	m_pDM->ChangeAniSet(Index_Hit_L_1_Light);
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
	m_pDM->ChangeAniSet(Index_Hit_L_2);
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
	m_pDM->ChangeAniSet(Index_Hit_L_2_Light);
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
	m_pDM->ChangeAniSet(Index_Hit_Shake);
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
	m_pDM->ChangeAniSet(Index_Hit_Throw);
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
	m_pDM->ChangeAniSet(Index_Hit_Throw_Low);
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
	m_pDM->ChangeAniSet(Index_KnockDown);
}

void FSM_RobotC::KnockDown_Update(float deltaTime)
{
}

void FSM_RobotC::KnockDown_End(void)
{
}

void FSM_RobotC::Run_AS_Init(void)
{
}

void FSM_RobotC::Run_AS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run_AS);
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
	m_pDM->ChangeAniSet(Index_Run_Attack);
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
	m_pDM->ChangeAniSet(Index_Run_Attack_Quick);
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
	m_pDM->ChangeAniSet(Index_StandUp);
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
	m_pDM->ChangeAniSet(Index_Throw_02);
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
	m_pDM->ChangeAniSet(Index_Throw_Blow);
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
	m_pDM->ChangeAniSet(Index_Walk_Backward);
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
	m_pDM->ChangeAniSet(Index_Walk_Forward);
}

void FSM_RobotC::Walk_Forward_Update(float deltaTime)
{
}

void FSM_RobotC::Walk_Forward_End(void)
{
}
