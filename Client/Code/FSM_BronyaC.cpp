#include "stdafx.h"
#include "..\Header\FSM_BronyaC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Bronya.h"

#include "StageCameraMan.h"
#include "CameraShake.h"

CFSM_BronyaC::CFSM_BronyaC()
{
}

SP(Engine::CComponent) CFSM_BronyaC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_BronyaC>(pObject);

	return spClone;
}


void CFSM_BronyaC::Awake(void)
{
	__super::Awake();
}

void CFSM_BronyaC::Start(SP(CComponent) spThis)
{
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	RegisterAllStage();

	__super::Start(spThis);


	SetStartState(Name_IDLE);
	m_curState->DoEnter();
}

void CFSM_BronyaC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_BronyaC, pState, IDLE)
		AddState(pState, L"IDLE");

	CreateState(CFSM_BronyaC, pState, Run)
		AddState(pState, L"Run");

	CreateState(CFSM_BronyaC, pState, DashBack)
		AddState(pState, L"DashBack");

	CreateState(CFSM_BronyaC, pState, Arsenal_Charge)
		AddState(pState, L"Arsenal_Charge");

	CreateState(CFSM_BronyaC, pState, Arsenal_Loop)
		AddState(pState, L"Arsenal_Loop");

	CreateState(CFSM_BronyaC, pState, Arsenal_End)
		AddState(pState, L"Arsenal_End");

	CreateState(CFSM_BronyaC, pState, Escape_Out)
		AddState(pState, L"Escape_Out");

	CreateState(CFSM_BronyaC, pState, Escape_In)
		AddState(pState, L"Escape_In");

	CreateState(CFSM_BronyaC, pState, Evade_Left)
		AddState(pState, L"Evade_Left");

	CreateState(CFSM_BronyaC, pState, Evade_Right)
		AddState(pState, L"Evade_Right");

	CreateState(CFSM_BronyaC, pState, Attack_1)
		AddState(pState, L"Attack_1");

	CreateState(CFSM_BronyaC, pState, Shoot_1)
		AddState(pState, L"Shoot_1");

	CreateState(CFSM_BronyaC, pState, Shoot_2)
		AddState(pState, L"Shoot_2");

	CreateState(CFSM_BronyaC, pState, Shoot_3)
		AddState(pState, L"Shoot_3");

	CreateState(CFSM_BronyaC, pState, Shock_1)
		AddState(pState, L"Shock_1");

	CreateState(CFSM_BronyaC, pState, Shock_2)
		AddState(pState, L"Shock_2");

	CreateState(CFSM_BronyaC, pState, Shock_2_Boom)
		AddState(pState, L"Shock_2_Boom");

	CreateState(CFSM_BronyaC, pState, Shock_2_Miss)
		AddState(pState, L"Shock_2_Miss");

	CreateState(CFSM_BronyaC, pState, Stealth_BACK)
		AddState(pState, L"Stealth_BACK");

	CreateState(CFSM_BronyaC, pState, Snealth)
		AddState(pState, L"Snealth");

	CreateState(CFSM_BronyaC, pState, Summon)
		AddState(pState, L"Summon");

	CreateState(CFSM_BronyaC, pState, Throw_1)
		AddState(pState, L"Throw_1");

	CreateState(CFSM_BronyaC, pState, Throw_2)
		AddState(pState, L"Throw_2");

	CreateState(CFSM_BronyaC, pState, Throw_3)
		AddState(pState, L"Throw_3");

	CreateState(CFSM_BronyaC, pState, Skill_Ultra)
		AddState(pState, L"Skill_Ultra");

	CreateState(CFSM_BronyaC, pState, Weak)
		AddState(pState, L"Weak");

	CreateState(CFSM_BronyaC, pState, Weak_Hit_L)
		AddState(pState, L"Weak_Hit_L");

	CreateState(CFSM_BronyaC, pState, Weak_Hit_H)
		AddState(pState, L"Weak_Hit_H");

	CreateState(CFSM_BronyaC, pState, Weak_Start_L)
		AddState(pState, L"Weak_Start_L");

	CreateState(CFSM_BronyaC, pState, Weak_Start_H)
		AddState(pState, L"Weak_Start_H");

	CreateState(CFSM_BronyaC, pState, Hit_H)
		AddState(pState, L"Hit_H");

	CreateState(CFSM_BronyaC, pState, Die)
		AddState(pState, L"Die");
}

void CFSM_BronyaC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_BronyaC::IDLE_Init(void)
{
}

void CFSM_BronyaC::IDLE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_IDLE);
}

void CFSM_BronyaC::IDLE_Update(float deltaTime)
{
}

void CFSM_BronyaC::IDLE_End(void)
{
}

void CFSM_BronyaC::Run_Init(void)
{
}

void CFSM_BronyaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);
}

void CFSM_BronyaC::Run_Update(float deltaTime)
{
}

void CFSM_BronyaC::Run_End(void)
{
}

void CFSM_BronyaC::DashBack_Init(void)
{
}

void CFSM_BronyaC::DashBack_Enter(void)
{
	m_pDM->ChangeAniSet(Index_DashBack);
}

void CFSM_BronyaC::DashBack_Update(float deltaTime)
{
}

void CFSM_BronyaC::DashBack_End(void)
{
}

void CFSM_BronyaC::Arsenal_Charge_Init(void)
{
}

void CFSM_BronyaC::Arsenal_Charge_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Arsenal_Charge);
}

void CFSM_BronyaC::Arsenal_Charge_Update(float deltaTime)
{
}

void CFSM_BronyaC::Arsenal_Charge_End(void)
{
}

void CFSM_BronyaC::Arsenal_Loop_Init(void)
{
}

void CFSM_BronyaC::Arsenal_Loop_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Arsenal_Loop);
}

void CFSM_BronyaC::Arsenal_Loop_Update(float deltaTime)
{
}

void CFSM_BronyaC::Arsenal_Loop_End(void)
{
}

void CFSM_BronyaC::Arsenal_End_Init(void)
{
}

void CFSM_BronyaC::Arsenal_End_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Arsenal_End);
}

void CFSM_BronyaC::Arsenal_End_Update(float deltaTime)
{
}

void CFSM_BronyaC::Arsenal_End_End(void)
{
}

void CFSM_BronyaC::Escape_Out_Init(void)
{
}

void CFSM_BronyaC::Escape_Out_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Escape_Out);
}

void CFSM_BronyaC::Escape_Out_Update(float deltaTime)
{
}

void CFSM_BronyaC::Escape_Out_End(void)
{
}

void CFSM_BronyaC::Escape_In_Init(void)
{
}

void CFSM_BronyaC::Escape_In_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Escape_In);
}

void CFSM_BronyaC::Escape_In_Update(float deltaTime)
{
}

void CFSM_BronyaC::Escape_In_End(void)
{
}

void CFSM_BronyaC::Evade_Left_Init(void)
{
}

void CFSM_BronyaC::Evade_Left_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Evade_Left);
}

void CFSM_BronyaC::Evade_Left_Update(float deltaTime)
{
}

void CFSM_BronyaC::Evade_Left_End(void)
{
}

void CFSM_BronyaC::Evade_Right_Init(void)
{
}

void CFSM_BronyaC::Evade_Right_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Evade_Right);
}

void CFSM_BronyaC::Evade_Right_Update(float deltaTime)
{
}

void CFSM_BronyaC::Evade_Right_End(void)
{
}

void CFSM_BronyaC::Attack_1_Init(void)
{
}

void CFSM_BronyaC::Attack_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1);
}

void CFSM_BronyaC::Attack_1_Update(float deltaTime)
{
}

void CFSM_BronyaC::Attack_1_End(void)
{
}

void CFSM_BronyaC::Shoot_1_Init(void)
{
}

void CFSM_BronyaC::Shoot_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Shoot_1);
}

void CFSM_BronyaC::Shoot_1_Update(float deltaTime)
{
}

void CFSM_BronyaC::Shoot_1_End(void)
{
}

void CFSM_BronyaC::Shoot_2_Init(void)
{
}

void CFSM_BronyaC::Shoot_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Shoot_2);
}

void CFSM_BronyaC::Shoot_2_Update(float deltaTime)
{
}

void CFSM_BronyaC::Shoot_2_End(void)
{
}

void CFSM_BronyaC::Shoot_3_Init(void)
{
}

void CFSM_BronyaC::Shoot_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Shoot_3);
}

void CFSM_BronyaC::Shoot_3_Update(float deltaTime)
{
}

void CFSM_BronyaC::Shoot_3_End(void)
{
}

void CFSM_BronyaC::Shock_1_Init(void)
{
}

void CFSM_BronyaC::Shock_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Shock_1);
	m_shake = false;
}

void CFSM_BronyaC::Shock_1_Update(float deltaTime)
{
	if (!m_shake && m_pDM->GetAniTimeline() > 0.475 && m_pDM->GetAniTimeline() < 0.55)
	{
		CStageControlTower::GetInstance()->GetCameraMan()->GetCameraShake()->Preset_HighImpact();
		m_shake = true;
	}
}

void CFSM_BronyaC::Shock_1_End(void)
{
}

void CFSM_BronyaC::Shock_2_Init(void)
{
}

void CFSM_BronyaC::Shock_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Shock_2);
	m_shake = false;
}

void CFSM_BronyaC::Shock_2_Update(float deltaTime)
{
	if (!m_shake && m_pDM->GetAniTimeline() > 0.705 && m_pDM->GetAniTimeline() < 0.8)
	{
		CStageControlTower::GetInstance()->GetCameraMan()->GetCameraShake()->Preset_HighImpact();
		m_shake = true;
	}
}

void CFSM_BronyaC::Shock_2_End(void)
{
}

void CFSM_BronyaC::Shock_2_Boom_Init(void)
{
	m_pDM->ChangeAniSet(Index_Shock_2_Boom);
}

void CFSM_BronyaC::Shock_2_Boom_Enter(void)
{
}

void CFSM_BronyaC::Shock_2_Boom_Update(float deltaTime)
{
}

void CFSM_BronyaC::Shock_2_Boom_End(void)
{
}

void CFSM_BronyaC::Shock_2_Miss_Init(void)
{
}

void CFSM_BronyaC::Shock_2_Miss_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Shock_2_Miss);
}

void CFSM_BronyaC::Shock_2_Miss_Update(float deltaTime)
{
}

void CFSM_BronyaC::Shock_2_Miss_End(void)
{
}

void CFSM_BronyaC::Stealth_BACK_Init(void)
{
}

void CFSM_BronyaC::Stealth_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Stealth_Back);
}

void CFSM_BronyaC::Stealth_BACK_Update(float deltaTime)
{
}

void CFSM_BronyaC::Stealth_BACK_End(void)
{
}

void CFSM_BronyaC::Snealth_Init(void)
{
}

void CFSM_BronyaC::Snealth_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Snealth);
}

void CFSM_BronyaC::Snealth_Update(float deltaTime)
{
}

void CFSM_BronyaC::Snealth_End(void)
{
}

void CFSM_BronyaC::Summon_Init(void)
{
}

void CFSM_BronyaC::Summon_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Summon);
}

void CFSM_BronyaC::Summon_Update(float deltaTime)
{
}

void CFSM_BronyaC::Summon_End(void)
{
}

void CFSM_BronyaC::Throw_1_Init(void)
{
}

void CFSM_BronyaC::Throw_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_1);
}

void CFSM_BronyaC::Throw_1_Update(float deltaTime)
{
}

void CFSM_BronyaC::Throw_1_End(void)
{
}

void CFSM_BronyaC::Throw_2_Init(void)
{
}

void CFSM_BronyaC::Throw_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_2);
}

void CFSM_BronyaC::Throw_2_Update(float deltaTime)
{
}

void CFSM_BronyaC::Throw_2_End(void)
{
}

void CFSM_BronyaC::Throw_3_Init(void)
{
}

void CFSM_BronyaC::Throw_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_3);
}

void CFSM_BronyaC::Throw_3_Update(float deltaTime)
{
}

void CFSM_BronyaC::Throw_3_End(void)
{
}

void CFSM_BronyaC::Skill_Ultra_Init(void)
{
}

void CFSM_BronyaC::Skill_Ultra_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Skill_Ultra);
}

void CFSM_BronyaC::Skill_Ultra_Update(float deltaTime)
{
}

void CFSM_BronyaC::Skill_Ultra_End(void)
{
}

void CFSM_BronyaC::Weak_Init(void)
{
}

void CFSM_BronyaC::Weak_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Weak);
}

void CFSM_BronyaC::Weak_Update(float deltaTime)
{
}

void CFSM_BronyaC::Weak_End(void)
{
}

void CFSM_BronyaC::Weak_Hit_L_Init(void)
{
}

void CFSM_BronyaC::Weak_Hit_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Weak_Hit_L);
}

void CFSM_BronyaC::Weak_Hit_L_Update(float deltaTime)
{
}

void CFSM_BronyaC::Weak_Hit_L_End(void)
{
}

void CFSM_BronyaC::Weak_Hit_H_Init(void)
{
}

void CFSM_BronyaC::Weak_Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Weak_Hit_H);
}

void CFSM_BronyaC::Weak_Hit_H_Update(float deltaTime)
{
}

void CFSM_BronyaC::Weak_Hit_H_End(void)
{
}

void CFSM_BronyaC::Weak_Start_L_Init(void)
{
}

void CFSM_BronyaC::Weak_Start_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Weak_Start_L);
}

void CFSM_BronyaC::Weak_Start_L_Update(float deltaTime)
{
}

void CFSM_BronyaC::Weak_Start_L_End(void)
{
}

void CFSM_BronyaC::Weak_Start_H_Init(void)
{
}

void CFSM_BronyaC::Weak_Start_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Weak_Start_H);
}

void CFSM_BronyaC::Weak_Start_H_Update(float deltaTime)
{
}

void CFSM_BronyaC::Weak_Start_H_End(void)
{
}

void CFSM_BronyaC::Hit_H_Init(void)
{
}

void CFSM_BronyaC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H);
}

void CFSM_BronyaC::Hit_H_Update(float deltaTime)
{
}

void CFSM_BronyaC::Hit_H_End(void)
{
}

void CFSM_BronyaC::Die_Init(void)
{
}

void CFSM_BronyaC::Die_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die);
}

void CFSM_BronyaC::Die_Update(float deltaTime)
{
}

void CFSM_BronyaC::Die_End(void)
{
}
