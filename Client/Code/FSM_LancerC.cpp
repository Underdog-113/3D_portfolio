#include "stdafx.h"
#include "..\Header\FSM_LancerC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Lancer.h"

CFSM_LancerC::CFSM_LancerC()
{
}

SP(Engine::CComponent) CFSM_LancerC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_LancerC>(pObject);

	return spClone;
}

void CFSM_LancerC::Awake(void)
{
	__super::Awake();
}

void CFSM_LancerC::Start(SP(CComponent) spThis)
{
	RegisterAllStage();

	__super::Start(spThis);

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	SetStartState(Name_APPEAR);
	m_curState->DoEnter();
}

void CFSM_LancerC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_LancerC, pState, APPEAR)
		AddState(pState, L"APPEAR");

	CreateState(CFSM_LancerC, pState, ATTACK_1)
		AddState(pState, L"ATTACK_1");

	CreateState(CFSM_LancerC, pState, ATTACK_2)
		AddState(pState, L"ATTACK_2");

	CreateState(CFSM_LancerC, pState, ATTACK_3)
		AddState(pState, L"ATTACK_3");

	CreateState(CFSM_LancerC, pState, DIE)
		AddState(pState, L"DIE");

	CreateState(CFSM_LancerC, pState, DIE_BACK)
		AddState(pState, L"DIE_BACK");

	CreateState(CFSM_LancerC, pState, DIE_FLY)
		AddState(pState, L"DIE_FLY");

	CreateState(CFSM_LancerC, pState, FREE_FALL)
		AddState(pState, L"FREE_FALL");

	CreateState(CFSM_LancerC, pState, FREE_FALL_LOW)
		AddState(pState, L"FREE_FALL_LOW");

	CreateState(CFSM_LancerC, pState, HIDE)
		AddState(pState, L"HIDE");

	CreateState(CFSM_LancerC, pState, HIT_BACK)
		AddState(pState, L"HIT_BACK");

	CreateState(CFSM_LancerC, pState, HIT_H)
		AddState(pState, L"HIT_H");

	CreateState(CFSM_LancerC, pState, HIT_EARLY)
		AddState(pState, L"HIT_EARLY");

	CreateState(CFSM_LancerC, pState, HIT_L)
		AddState(pState, L"HIT_L");

	CreateState(CFSM_LancerC, pState, HIT_L_EARLY)
		AddState(pState, L"HIT_L_EARLY");

	CreateState(CFSM_LancerC, pState, HIT_LEFT)
		AddState(pState, L"HIT_LEFT");

	CreateState(CFSM_LancerC, pState, HIT_RIGHT)
		AddState(pState, L"HIT_RIGHT");

	CreateState(CFSM_LancerC, pState, HIT_SHAKE)
		AddState(pState, L"HIT_SHAKE");

	CreateState(CFSM_LancerC, pState, JUMP_BACK)
		AddState(pState, L"JUMP_BACK");

	CreateState(CFSM_LancerC, pState, KNOCK_DOWN)
		AddState(pState, L"KNOCK_DOWN");

	CreateState(CFSM_LancerC, pState, RUN)
		AddState(pState, L"RUN");

	CreateState(CFSM_LancerC, pState, STAND)
		AddState(pState, L"STAND");

	CreateState(CFSM_LancerC, pState, STAND_UP)
		AddState(pState, L"STAND_UP");

	CreateState(CFSM_LancerC, pState, STUN)
		AddState(pState, L"STUN");

	CreateState(CFSM_LancerC, pState, THROW_0)
		AddState(pState, L"THROW_0");

	CreateState(CFSM_LancerC, pState, THROW_1)
		AddState(pState, L"THROW_1");

	CreateState(CFSM_LancerC, pState, THROW_2)
		AddState(pState, L"THROW_2");

	CreateState(CFSM_LancerC, pState, THROW_BLOW)
		AddState(pState, L"THROW_BLOW");

	CreateState(CFSM_LancerC, pState, THROW_LOW)
		AddState(pState, L"THROW_LOW");

	CreateState(CFSM_LancerC, pState, WALK_BACKWARD)
		AddState(pState, L"WALK_BACKWARD");

	CreateState(CFSM_LancerC, pState, WALK_FORWARD)
		AddState(pState, L"WALK_FORWARD");

	CreateState(CFSM_LancerC, pState, WALK_LEFT)
		AddState(pState, L"WALK_LEFT");

	CreateState(CFSM_LancerC, pState, WALK_RIGHT)
		AddState(pState, L"WALK_RIGHT");
}

void CFSM_LancerC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_LancerC::APPEAR_Init(void)
{
}

void CFSM_LancerC::APPEAR_Enter(void)
{
	m_pDM->ChangeAniSet(Index_APPEAR);
}

void CFSM_LancerC::APPEAR_Update(float deltaTime)
{
}

void CFSM_LancerC::APPEAR_End(void)
{
}

void CFSM_LancerC::ATTACK_1_Init(void)
{
}

void CFSM_LancerC::ATTACK_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_ATTACK1);
}

void CFSM_LancerC::ATTACK_1_Update(float deltaTime)
{
}

void CFSM_LancerC::ATTACK_1_End(void)
{
}

void CFSM_LancerC::ATTACK_2_Init(void)
{
}

void CFSM_LancerC::ATTACK_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_ATTACK_2);
}

void CFSM_LancerC::ATTACK_2_Update(float deltaTime)
{
}

void CFSM_LancerC::ATTACK_2_End(void)
{
}

void CFSM_LancerC::ATTACK_3_Init(void)
{
}

void CFSM_LancerC::ATTACK_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_ATTACK3);
}

void CFSM_LancerC::ATTACK_3_Update(float deltaTime)
{
}

void CFSM_LancerC::ATTACK_3_End(void)
{
}

void CFSM_LancerC::BOM_READY_Init(void)
{
}

void CFSM_LancerC::BOM_READY_Enter(void)
{
	m_pDM->ChangeAniSet(Index_BOM_READY);
}

void CFSM_LancerC::BOM_READY_Update(float deltaTime)
{
}

void CFSM_LancerC::BOM_READY_End(void)
{
}

void CFSM_LancerC::DIE_Init(void)
{
}

void CFSM_LancerC::DIE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_DIE);
}

void CFSM_LancerC::DIE_Update(float deltaTime)
{
}

void CFSM_LancerC::DIE_End(void)
{
}

void CFSM_LancerC::DIE_BACK_Init(void)
{
}

void CFSM_LancerC::DIE_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_DIE_BACK);
}

void CFSM_LancerC::DIE_BACK_Update(float deltaTime)
{
}

void CFSM_LancerC::DIE_BACK_End(void)
{
}

void CFSM_LancerC::DIE_FLY_Init(void)
{
}

void CFSM_LancerC::DIE_FLY_Enter(void)
{
	m_pDM->ChangeAniSet(Index_DIE_FLY);
}

void CFSM_LancerC::DIE_FLY_Update(float deltaTime)
{
}

void CFSM_LancerC::DIE_FLY_End(void)
{
}

void CFSM_LancerC::FREE_FALL_Init(void)
{
}

void CFSM_LancerC::FREE_FALL_Enter(void)
{
	m_pDM->ChangeAniSet(Index_FREE_FALL);
}

void CFSM_LancerC::FREE_FALL_Update(float deltaTime)
{
}

void CFSM_LancerC::FREE_FALL_End(void)
{
}

void CFSM_LancerC::FREE_FALL_LOW_Init(void)
{
}

void CFSM_LancerC::FREE_FALL_LOW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_FREE_FALL_LOW);
}

void CFSM_LancerC::FREE_FALL_LOW_Update(float deltaTime)
{
}

void CFSM_LancerC::FREE_FALL_LOW_End(void)
{
}

void CFSM_LancerC::HIDE_Init(void)
{
}

void CFSM_LancerC::HIDE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIDE);
}

void CFSM_LancerC::HIDE_Update(float deltaTime)
{
}

void CFSM_LancerC::HIDE_End(void)
{
}

void CFSM_LancerC::HIT_BACK_Init(void)
{
}

void CFSM_LancerC::HIT_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_BACK);
}

void CFSM_LancerC::HIT_BACK_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_BACK_End(void)
{
}

void CFSM_LancerC::HIT_H_Init(void)
{
}

void CFSM_LancerC::HIT_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_H);
}

void CFSM_LancerC::HIT_H_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_H_End(void)
{
}

void CFSM_LancerC::HIT_EARLY_Init(void)
{
}

void CFSM_LancerC::HIT_EARLY_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_EARLY);
}

void CFSM_LancerC::HIT_EARLY_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_EARLY_End(void)
{
}

void CFSM_LancerC::HIT_L_Init(void)
{
}

void CFSM_LancerC::HIT_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_L);
}

void CFSM_LancerC::HIT_L_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_L_End(void)
{
}

void CFSM_LancerC::HIT_L_EARLY_Init(void)
{
}

void CFSM_LancerC::HIT_L_EARLY_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_L_EARLY);
}

void CFSM_LancerC::HIT_L_EARLY_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_L_EARLY_End(void)
{
}

void CFSM_LancerC::HIT_LEFT_Init(void)
{
}

void CFSM_LancerC::HIT_LEFT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_LEFT);
}

void CFSM_LancerC::HIT_LEFT_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_LEFT_End(void)
{
}

void CFSM_LancerC::HIT_RIGHT_Init(void)
{
}

void CFSM_LancerC::HIT_RIGHT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_RIGHT);
}

void CFSM_LancerC::HIT_RIGHT_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_RIGHT_End(void)
{
}

void CFSM_LancerC::HIT_SHAKE_Init(void)
{
}

void CFSM_LancerC::HIT_SHAKE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_SHAKE);
}

void CFSM_LancerC::HIT_SHAKE_Update(float deltaTime)
{
}

void CFSM_LancerC::HIT_SHAKE_End(void)
{
}

void CFSM_LancerC::JUMP_BACK_Init(void)
{
}

void CFSM_LancerC::JUMP_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_JUMP_BACK);
}

void CFSM_LancerC::JUMP_BACK_Update(float deltaTime)
{
}

void CFSM_LancerC::JUMP_BACK_End(void)
{
}

void CFSM_LancerC::KNOCK_DOWN_Init(void)
{
}

void CFSM_LancerC::KNOCK_DOWN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_KNOCK_DOWN);
}

void CFSM_LancerC::KNOCK_DOWN_Update(float deltaTime)
{
}

void CFSM_LancerC::KNOCK_DOWN_End(void)
{
}

void CFSM_LancerC::RUN_Init(void)
{
}

void CFSM_LancerC::RUN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUN);
}

void CFSM_LancerC::RUN_Update(float deltaTime)
{
}

void CFSM_LancerC::RUN_End(void)
{
}

void CFSM_LancerC::STAND_Init(void)
{
}

void CFSM_LancerC::STAND_Enter(void)
{
	m_pDM->ChangeAniSet(Index_STAND);
}

void CFSM_LancerC::STAND_Update(float deltaTime)
{
}

void CFSM_LancerC::STAND_End(void)
{
}

void CFSM_LancerC::STAND_UP_Init(void)
{
}

void CFSM_LancerC::STAND_UP_Enter(void)
{
	m_pDM->ChangeAniSet(Index_STAND_UP);
}

void CFSM_LancerC::STAND_UP_Update(float deltaTime)
{
}

void CFSM_LancerC::STAND_UP_End(void)
{
}

void CFSM_LancerC::STUN_Init(void)
{
}

void CFSM_LancerC::STUN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_STUN);
}

void CFSM_LancerC::STUN_Update(float deltaTime)
{
}

void CFSM_LancerC::STUN_End(void)
{
}

void CFSM_LancerC::THROW_0_Init(void)
{
}

void CFSM_LancerC::THROW_0_Enter(void)
{
	m_pDM->ChangeAniSet(Index_THROW_0);
}

void CFSM_LancerC::THROW_0_Update(float deltaTime)
{
}

void CFSM_LancerC::THROW_0_End(void)
{
}

void CFSM_LancerC::THROW_1_Init(void)
{
}

void CFSM_LancerC::THROW_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_THROW_1);
}

void CFSM_LancerC::THROW_1_Update(float deltaTime)
{
}

void CFSM_LancerC::THROW_1_End(void)
{
}

void CFSM_LancerC::THROW_2_Init(void)
{
}

void CFSM_LancerC::THROW_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_THROW_2);
}

void CFSM_LancerC::THROW_2_Update(float deltaTime)
{
}

void CFSM_LancerC::THROW_2_End(void)
{
}

void CFSM_LancerC::THROW_BLOW_Init(void)
{
}

void CFSM_LancerC::THROW_BLOW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_THROW_BLOW);
}

void CFSM_LancerC::THROW_BLOW_Update(float deltaTime)
{
}

void CFSM_LancerC::THROW_BLOW_End(void)
{
}

void CFSM_LancerC::THROW_LOW_Init(void)
{
}

void CFSM_LancerC::THROW_LOW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_THROW_LOW);
}

void CFSM_LancerC::THROW_LOW_Update(float deltaTime)
{
}

void CFSM_LancerC::THROW_LOW_End(void)
{
}

void CFSM_LancerC::WALK_BACKWARD_Init(void)
{
}

void CFSM_LancerC::WALK_BACKWARD_Enter(void)
{
	m_pDM->ChangeAniSet(Index_WALK_BACKWARD);
}

void CFSM_LancerC::WALK_BACKWARD_Update(float deltaTime)
{
}

void CFSM_LancerC::WALK_BACKWARD_End(void)
{
}

void CFSM_LancerC::WALK_FORWARD_Init(void)
{
}

void CFSM_LancerC::WALK_FORWARD_Enter(void)
{
	m_pDM->ChangeAniSet(Index_WALK_FORWARD);
}

void CFSM_LancerC::WALK_FORWARD_Update(float deltaTime)
{
}

void CFSM_LancerC::WALK_FORWARD_End(void)
{
}

void CFSM_LancerC::WALK_LEFT_Init(void)
{
}

void CFSM_LancerC::WALK_LEFT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_WALK_LEFT);
}

void CFSM_LancerC::WALK_LEFT_Update(float deltaTime)
{
}

void CFSM_LancerC::WALK_LEFT_End(void)
{
}

void CFSM_LancerC::WALK_RIGHT_Init(void)
{
}

void CFSM_LancerC::WALK_RIGHT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_WALK_RIGHT);
}

void CFSM_LancerC::WALK_RIGHT_Update(float deltaTime)
{
}

void CFSM_LancerC::WALK_RIGHT_End(void)
{
}
