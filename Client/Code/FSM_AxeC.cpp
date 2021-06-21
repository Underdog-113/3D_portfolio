#include "stdafx.h"
#include "..\Header\FSM_AxeC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Axe.h"
#include "StageControlTower.h"

CFSM_AxeC::CFSM_AxeC()
{
}

SP(Engine::CComponent) CFSM_AxeC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_AxeC>(pObject);

	return spClone;
}

void CFSM_AxeC::Awake()
{
	__super::Awake();
}

void CFSM_AxeC::Start(SP(CComponent) spThis)
{
	RegisterAllStage();

	__super::Start(spThis);

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());
	m_pStageControlTower = CStageControlTower::GetInstance();

	SetStartState(Name_IDLE);
	m_curState->DoEnter();
}

void CFSM_AxeC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_AxeC, pState, IDLE)
		AddState(pState, L"IDLE");

	CreateState(CFSM_AxeC, pState, WALK_RIGHT)
		AddState(pState, L"WALK_RIGHT");

	CreateState(CFSM_AxeC, pState, WALK_LEFT)
		AddState(pState, L"WALK_LEFT");

	CreateState(CFSM_AxeC, pState, WALK_BACK)
		AddState(pState, L"WALK_BACK");

	CreateState(CFSM_AxeC, pState, RUN)
		AddState(pState, L"RUN");

	CreateState(CFSM_AxeC, pState, ATTACK_1)
		AddState(pState, L"ATTACK_1");

	CreateState(CFSM_AxeC, pState, ATTACK_2)
		AddState(pState, L"ATTACK_2");

	CreateState(CFSM_AxeC, pState, ATTACK_2_1)
		AddState(pState, L"ATTACK_2_1");

	CreateState(CFSM_AxeC, pState, ATTACK_3)
		AddState(pState, L"ATTACK_3");

	CreateState(CFSM_AxeC, pState, ATTACK_3_1)
		AddState(pState, L"ATTACK_3_1");

	CreateState(CFSM_AxeC, pState, THROW_1)
		AddState(pState, L"THROW_1");

	CreateState(CFSM_AxeC, pState, THROW_2)
		AddState(pState, L"THROW_2");

	CreateState(CFSM_AxeC, pState, THROW_BLOW)
		AddState(pState, L"THROW_BLOW");

	CreateState(CFSM_AxeC, pState, KNOCK_DOWN)
		AddState(pState, L"KNOCK_DOWN");

	CreateState(CFSM_AxeC, pState, STAND_UP)
		AddState(pState, L"STAND_UP");

	CreateState(CFSM_AxeC, pState, STUN)
		AddState(pState, L"STUN");

	CreateState(CFSM_AxeC, pState, HIT_BACK)
		AddState(pState, L"HIT_BACK");

	CreateState(CFSM_AxeC, pState, HIT_THROW)
		AddState(pState, L"HIT_THROW");

	CreateState(CFSM_AxeC, pState, HIT_THROW_LOW)
		AddState(pState, L"HIT_THROW_LOW");

	CreateState(CFSM_AxeC, pState, DIE)
		AddState(pState, L"DIE");

	CreateState(CFSM_AxeC, pState, DIE_BACK)
		AddState(pState, L"DIE_BACK");

	CreateState(CFSM_AxeC, pState, DIE_FLY)
		AddState(pState, L"DIE_FLY");
}

void CFSM_AxeC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_AxeC::IDLE_Init(void)
{
}

void CFSM_AxeC::IDLE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_IDLE);
}

void CFSM_AxeC::IDLE_Update(float deltaTime)
{
	
}

void CFSM_AxeC::IDLE_End(void)
{
}

void CFSM_AxeC::WALK_RIGHT_Init(void)
{
}

void CFSM_AxeC::WALK_RIGHT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Right);
}

void CFSM_AxeC::WALK_RIGHT_Update(float deltaTime)
{
}

void CFSM_AxeC::WALK_RIGHT_End(void)
{
}

void CFSM_AxeC::WALK_LEFT_Init(void)
{
}

void CFSM_AxeC::WALK_LEFT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Left);
}

void CFSM_AxeC::WALK_LEFT_Update(float deltaTime)
{
}

void CFSM_AxeC::WALK_LEFT_End(void)
{
}

void CFSM_AxeC::WALK_BACK_Init(void)
{
}

void CFSM_AxeC::WALK_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Back);
}

void CFSM_AxeC::WALK_BACK_Update(float deltaTime)
{
}

void CFSM_AxeC::WALK_BACK_End(void)
{
}

void CFSM_AxeC::RUN_Init(void)
{
}

void CFSM_AxeC::RUN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);
	m_pDM->GetAniCtrl()->SetSpeed(0.5f);
}

void CFSM_AxeC::RUN_Update(float deltaTime)
{
	
}

void CFSM_AxeC::RUN_End(void)
{
}

void CFSM_AxeC::ATTACK_1_Init(void)
{
}

void CFSM_AxeC::ATTACK_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1);
}

void CFSM_AxeC::ATTACK_1_Update(float deltaTime)
{
	
}

void CFSM_AxeC::ATTACK_1_End(void)
{
}

void CFSM_AxeC::ATTACK_2_Init(void)
{
}

void CFSM_AxeC::ATTACK_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2);
}

void CFSM_AxeC::ATTACK_2_Update(float deltaTime)
{
}

void CFSM_AxeC::ATTACK_2_End(void)
{
}

void CFSM_AxeC::ATTACK_2_1_Init(void)
{
}

void CFSM_AxeC::ATTACK_2_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2_1);
}

void CFSM_AxeC::ATTACK_2_1_Update(float deltaTime)
{
}

void CFSM_AxeC::ATTACK_2_1_End(void)
{
}

void CFSM_AxeC::ATTACK_3_Init(void)
{
}

void CFSM_AxeC::ATTACK_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3);
}

void CFSM_AxeC::ATTACK_3_Update(float deltaTime)
{
}

void CFSM_AxeC::ATTACK_3_End(void)
{
}

void CFSM_AxeC::ATTACK_3_1_Init(void)
{
}

void CFSM_AxeC::ATTACK_3_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3_1);
}

void CFSM_AxeC::ATTACK_3_1_Update(float deltaTime)
{
}

void CFSM_AxeC::ATTACK_3_1_End(void)
{
}

void CFSM_AxeC::THROW_1_Init(void)
{
}

void CFSM_AxeC::THROW_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_1);
}

void CFSM_AxeC::THROW_1_Update(float deltaTime)
{
}

void CFSM_AxeC::THROW_1_End(void)
{
}

void CFSM_AxeC::THROW_2_Init(void)
{
}

void CFSM_AxeC::THROW_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_2);
}

void CFSM_AxeC::THROW_2_Update(float deltaTime)
{
}

void CFSM_AxeC::THROW_2_End(void)
{
}

void CFSM_AxeC::THROW_BLOW_Init(void)
{
}

void CFSM_AxeC::THROW_BLOW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_Blow);
}

void CFSM_AxeC::THROW_BLOW_Update(float deltaTime)
{
}

void CFSM_AxeC::THROW_BLOW_End(void)
{
}

void CFSM_AxeC::KNOCK_DOWN_Init(void)
{
}

void CFSM_AxeC::KNOCK_DOWN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Knock_Down);
}

void CFSM_AxeC::KNOCK_DOWN_Update(float deltaTime)
{
}

void CFSM_AxeC::KNOCK_DOWN_End(void)
{
}

void CFSM_AxeC::STAND_UP_Init(void)
{
}

void CFSM_AxeC::STAND_UP_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Stand_Up);
}

void CFSM_AxeC::STAND_UP_Update(float deltaTime)
{
}

void CFSM_AxeC::STAND_UP_End(void)
{
}

void CFSM_AxeC::STUN_Init(void)
{
}

void CFSM_AxeC::STUN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Stun);
}

void CFSM_AxeC::STUN_Update(float deltaTime)
{
}

void CFSM_AxeC::STUN_End(void)
{
}

void CFSM_AxeC::HIT_BACK_Init(void)
{
}

void CFSM_AxeC::HIT_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Back);
}

void CFSM_AxeC::HIT_BACK_Update(float deltaTime)
{
}

void CFSM_AxeC::HIT_BACK_End(void)
{
}

void CFSM_AxeC::HIT_THROW_Init(void)
{
}

void CFSM_AxeC::HIT_THROW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Throw);
}

void CFSM_AxeC::HIT_THROW_Update(float deltaTime)
{
}

void CFSM_AxeC::HIT_THROW_End(void)
{
}

void CFSM_AxeC::HIT_THROW_LOW_Init(void)
{
}

void CFSM_AxeC::HIT_THROW_LOW_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Throw);
}

void CFSM_AxeC::HIT_THROW_LOW_Update(float deltaTime)
{
}

void CFSM_AxeC::HIT_THROW_LOW_End(void)
{
}

void CFSM_AxeC::DIE_Init(void)
{
}

void CFSM_AxeC::DIE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die);
}

void CFSM_AxeC::DIE_Update(float deltaTime)
{
}

void CFSM_AxeC::DIE_End(void)
{
}

void CFSM_AxeC::DIE_BACK_Init(void)
{
}

void CFSM_AxeC::DIE_BACK_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die_Back);
}

void CFSM_AxeC::DIE_BACK_Update(float deltaTime)
{
}

void CFSM_AxeC::DIE_BACK_End(void)
{
}

void CFSM_AxeC::DIE_FLY_Init(void)
{
}

void CFSM_AxeC::DIE_FLY_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die_Fly);
}

void CFSM_AxeC::DIE_FLY_Update(float deltaTime)
{
}

void CFSM_AxeC::DIE_FLY_End(void)
{
}
