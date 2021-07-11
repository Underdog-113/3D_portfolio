#include "stdafx.h"
#include "..\Header\FSM_ScoutC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Scout.h"
#include "Monster.h"

CFSM_ScoutC::CFSM_ScoutC()
{
}

SP(Engine::CComponent) CFSM_ScoutC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_ScoutC>(pObject);

	return spClone;
}

void CFSM_ScoutC::Awake(void)
{
	__super::Awake();
}

void CFSM_ScoutC::Start(SP(CComponent) spThis)
{
	RegisterAllStage();

	__super::Start(spThis);

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	SetStartState(Name_APPEAR);
	m_curState->DoEnter();
}

void CFSM_ScoutC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_ScoutC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_ScoutC, pState, IDLE)
		AddState(pState, Name_IDLE);

	CreateState(CFSM_ScoutC, pState, RUN_L)
		AddState(pState, Name_RUN_L);

	CreateState(CFSM_ScoutC, pState, RUN_R)
		AddState(pState, Name_RUN_R);

	CreateState(CFSM_ScoutC, pState, RUN_F)
		AddState(pState, Name_RUN_F);

	CreateState(CFSM_ScoutC, pState, RUN_B)
		AddState(pState, Name_RUN_B);

	CreateState(CFSM_ScoutC, pState, SHOOT_1)
		AddState(pState, Name_SHOOT_1);

	CreateState(CFSM_ScoutC, pState, SHOOT_2)
		AddState(pState, Name_SHOOT_2);

	CreateState(CFSM_ScoutC, pState, SHOOT_3)
		AddState(pState, Name_SHOOT_3);

	CreateState(CFSM_ScoutC, pState, SHOOT_FIREFALL)
		AddState(pState, Name_SHOOT_FIREFALL);

	CreateState(CFSM_ScoutC, pState, LASER_BS)
		AddState(pState, Name_LASER_BS);

	CreateState(CFSM_ScoutC, pState, LASER_LOOP)
		AddState(pState, Name_LASER_LOOP);

	CreateState(CFSM_ScoutC, pState, LASER_AS)
		AddState(pState, Name_Laser_AS);

	CreateState(CFSM_ScoutC, pState, HIT_L)
		AddState(pState, Name_HIT_L);

	CreateState(CFSM_ScoutC, pState, HIT_H)
		AddState(pState, Name_HIT_H);

	CreateState(CFSM_ScoutC, pState, HIT_FRONT)
		AddState(pState, Name_HIT_FRONT);

	CreateState(CFSM_ScoutC, pState, HIT_BACK)
		AddState(pState, Name_HIT_BACK);

	CreateState(CFSM_ScoutC, pState, THROW_0)
		AddState(pState, Name_Throw_0);

	CreateState(CFSM_ScoutC, pState, THROW_1)
		AddState(pState, Name_Throw_1);

	CreateState(CFSM_ScoutC, pState, THROW_2)
		AddState(pState, Name_Throw_2);

	CreateState(CFSM_ScoutC, pState, THROW_BLOW)
		AddState(pState, Name_Throw_Blow);

	CreateState(CFSM_ScoutC, pState, THROW_LOW)
		AddState(pState, Name_Throw_Low);

	CreateState(CFSM_ScoutC, pState, KNOCK_DOWN)
		AddState(pState, Name_KnockDown);

	CreateState(CFSM_ScoutC, pState, STAND_UP)
		AddState(pState, Name_StandUp);

	CreateState(CFSM_ScoutC, pState, STUN)
		AddState(pState, Name_Stun);

	CreateState(CFSM_ScoutC, pState, DIE)
		AddState(pState, Name_DIE);

	CreateState(CFSM_ScoutC, pState, DIE_FLY)
		AddState(pState, Name_DIE_FLY);
}

void CFSM_ScoutC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_ScoutC::APPEAR_Init(void)
{
}

void CFSM_ScoutC::APPEAR_Enter(void)
{
	m_pDM->ChangeAniSet(Index_APPEAR);
}

void CFSM_ScoutC::APPEAR_Update(float deltaTime)
{
}

void CFSM_ScoutC::APPEAR_End(void)
{
}

void CFSM_ScoutC::IDLE_Init(void)
{
}

void CFSM_ScoutC::IDLE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_IDLE);
}

void CFSM_ScoutC::IDLE_Update(float deltaTime)
{
}

void CFSM_ScoutC::IDLE_End(void)
{
}

void CFSM_ScoutC::RUN_L_Init(void)
{
}

void CFSM_ScoutC::RUN_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUN_L);
}

void CFSM_ScoutC::RUN_L_Update(float deltaTime)
{
}

void CFSM_ScoutC::RUN_L_End(void)
{
}

void CFSM_ScoutC::RUN_R_Init(void)
{
}

void CFSM_ScoutC::RUN_R_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUN_R);
}

void CFSM_ScoutC::RUN_R_Update(float deltaTime)
{
}

void CFSM_ScoutC::RUN_R_End(void)
{
}

void CFSM_ScoutC::RUN_F_Init(void)
{
}

void CFSM_ScoutC::RUN_F_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUN_F);
}

void CFSM_ScoutC::RUN_F_Update(float deltaTime)
{
}

void CFSM_ScoutC::RUN_F_End(void)
{
}

void CFSM_ScoutC::RUN_B_Init(void)
{
}

void CFSM_ScoutC::RUN_B_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUN_B);
}

void CFSM_ScoutC::RUN_B_Update(float deltaTime)
{
}

void CFSM_ScoutC::RUN_B_End(void)
{
}

void CFSM_ScoutC::SHOOT_1_Init(void)
{
}

void CFSM_ScoutC::SHOOT_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SHOOT_1);
}

void CFSM_ScoutC::SHOOT_1_Update(float deltaTime)
{
}

void CFSM_ScoutC::SHOOT_1_End(void)
{
}

void CFSM_ScoutC::SHOOT_2_Init(void)
{
}

void CFSM_ScoutC::SHOOT_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SHOOT_2);
	static_cast<CMonster*>(m_pOwner)->GetStat()->SetOnPatternShield(true);
}

void CFSM_ScoutC::SHOOT_2_Update(float deltaTime)
{
}

void CFSM_ScoutC::SHOOT_2_End(void)
{
	static_cast<CMonster*>(m_pOwner)->GetStat()->SetOnPatternShield(false);
}

void CFSM_ScoutC::SHOOT_3_Init(void)
{
}

void CFSM_ScoutC::SHOOT_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SHOOT_3);
	static_cast<CMonster*>(m_pOwner)->GetStat()->SetOnPatternShield(true);
}

void CFSM_ScoutC::SHOOT_3_Update(float deltaTime)
{
}

void CFSM_ScoutC::SHOOT_3_End(void)
{
	static_cast<CMonster*>(m_pOwner)->GetStat()->SetOnPatternShield(false);
}

void CFSM_ScoutC::SHOOT_FIREFALL_Init(void)
{
}

void CFSM_ScoutC::SHOOT_FIREFALL_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SHOOT_FIREFALL);
}

void CFSM_ScoutC::SHOOT_FIREFALL_Update(float deltaTime)
{
}

void CFSM_ScoutC::SHOOT_FIREFALL_End(void)
{
}

void CFSM_ScoutC::LASER_BS_Init(void)
{
}

void CFSM_ScoutC::LASER_BS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_LASER_BS);
}

void CFSM_ScoutC::LASER_BS_Update(float deltaTime)
{
}

void CFSM_ScoutC::LASER_BS_End(void)
{
}

void CFSM_ScoutC::LASER_LOOP_Init(void)
{
}

void CFSM_ScoutC::LASER_LOOP_Enter(void)
{
	m_pDM->ChangeAniSet(Index_LASER_LOOP);
}

void CFSM_ScoutC::LASER_LOOP_Update(float deltaTime)
{
}

void CFSM_ScoutC::LASER_LOOP_End(void)
{
}

void CFSM_ScoutC::LASER_AS_Init(void)
{
}

void CFSM_ScoutC::LASER_AS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Laser_AS);
}

void CFSM_ScoutC::LASER_AS_Update(float deltaTime)
{
}

void CFSM_ScoutC::LASER_AS_End(void)
{
}

void CFSM_ScoutC::HIT_L_Init(void)
{
}

void CFSM_ScoutC::HIT_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_L);
}

void CFSM_ScoutC::HIT_L_Update(float deltaTime)
{
}

void CFSM_ScoutC::HIT_L_End(void)
{
}

void CFSM_ScoutC::HIT_H_Init(void)
{
}

void CFSM_ScoutC::HIT_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_H);
}

void CFSM_ScoutC::HIT_H_Update(float deltaTime)
{
}

void CFSM_ScoutC::HIT_H_End(void)
{
}

void CFSM_ScoutC::HIT_FRONT_Init(void)
{
}

void CFSM_ScoutC::HIT_FRONT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_FRONT);
}

void CFSM_ScoutC::HIT_FRONT_Update(float deltaTime)
{
}

void CFSM_ScoutC::HIT_FRONT_End(void)
{
}

void CFSM_ScoutC::HIT_BACK_Init(void)
{
}

void CFSM_ScoutC::HIT_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_BACK);
}

void CFSM_ScoutC::HIT_BACK_Update(float deltaTime)
{
}

void CFSM_ScoutC::HIT_BACK_End(void)
{
}

void CFSM_ScoutC::THROW_0_Init(void)
{
}

void CFSM_ScoutC::THROW_0_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_0);
}

void CFSM_ScoutC::THROW_0_Update(float deltaTime)
{
}

void CFSM_ScoutC::THROW_0_End(void)
{
}

void CFSM_ScoutC::THROW_1_Init(void)
{
}

void CFSM_ScoutC::THROW_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_1);
}

void CFSM_ScoutC::THROW_1_Update(float deltaTime)
{
}

void CFSM_ScoutC::THROW_1_End(void)
{
}

void CFSM_ScoutC::THROW_2_Init(void)
{
}

void CFSM_ScoutC::THROW_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_2);
}

void CFSM_ScoutC::THROW_2_Update(float deltaTime)
{
}

void CFSM_ScoutC::THROW_2_End(void)
{
}

void CFSM_ScoutC::THROW_BLOW_Init(void)
{
}

void CFSM_ScoutC::THROW_BLOW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_Blow);
}

void CFSM_ScoutC::THROW_BLOW_Update(float deltaTime)
{
}

void CFSM_ScoutC::THROW_BLOW_End(void)
{
}

void CFSM_ScoutC::THROW_LOW_Init(void)
{
}

void CFSM_ScoutC::THROW_LOW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_Low);
}

void CFSM_ScoutC::THROW_LOW_Update(float deltaTime)
{
}

void CFSM_ScoutC::THROW_LOW_End(void)
{
}

void CFSM_ScoutC::KNOCK_DOWN_Init(void)
{
}

void CFSM_ScoutC::KNOCK_DOWN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_KnockDown);
}

void CFSM_ScoutC::KNOCK_DOWN_Update(float deltaTime)
{
}

void CFSM_ScoutC::KNOCK_DOWN_End(void)
{
}

void CFSM_ScoutC::STAND_UP_Init(void)
{
}

void CFSM_ScoutC::STAND_UP_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandUp);
}

void CFSM_ScoutC::STAND_UP_Update(float deltaTime)
{
}

void CFSM_ScoutC::STAND_UP_End(void)
{
}

void CFSM_ScoutC::STUN_Init(void)
{
}

void CFSM_ScoutC::STUN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Stun);
}

void CFSM_ScoutC::STUN_Update(float deltaTime)
{
}

void CFSM_ScoutC::STUN_End(void)
{
}

void CFSM_ScoutC::DIE_Init(void)
{
}

void CFSM_ScoutC::DIE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_DIE);
}

void CFSM_ScoutC::DIE_Update(float deltaTime)
{
}

void CFSM_ScoutC::DIE_End(void)
{
}

void CFSM_ScoutC::DIE_FLY_Init(void)
{
}

void CFSM_ScoutC::DIE_FLY_Enter(void)
{
	m_pDM->ChangeAniSet(Index_DIE_FLY);
}

void CFSM_ScoutC::DIE_FLY_Update(float deltaTime)
{
}

void CFSM_ScoutC::DIE_FLY_End(void)
{
}
