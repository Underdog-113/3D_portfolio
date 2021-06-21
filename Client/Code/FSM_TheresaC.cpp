#include "stdafx.h"
#include "FSM_TheresaC.h"

#include "State.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "FSMDefine_Theresa.h"
#include "StageControlTower.h"
#include "Theresa.h"

CFSM_TheresaC::CFSM_TheresaC()
{
}

SP(Engine::CComponent) CFSM_TheresaC::MakeClone(Engine::CObject * pObject)
{
	SP(CFSM_TheresaC) spClone(new CFSM_TheresaC);

	__super::InitClone(spClone, pObject);

	for (auto pState : m_stateList)
	{
		spClone->m_stateList.emplace(pState.first, pState.second->MakeClone(spClone.get()));
	}

	return spClone;
}

void CFSM_TheresaC::Awake(void)
{
	__super::Awake();
}

void CFSM_TheresaC::Start(SP(CComponent) spThis)
{
	m_pTheresa = static_cast<CTheresa*>(m_pOwner);
	
	__super::Start(spThis);

	RegisterAllState();

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pTheresa->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	m_pStageControlTower = CStageControlTower::GetInstance();

	SetStartState(Name_APPEAR);
	m_curState->DoEnter();
}

void CFSM_TheresaC::RegisterAllState()
{
	Engine::CState* pState;

	CreateState(CFSM_TheresaC, pState, IDLE)
		AddState(pState, Name_IDLE);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

}

void CFSM_TheresaC::FixRootMotionOffset(_uint index)
{
}

void CFSM_TheresaC::IDLE_Init(void)
{
}

void CFSM_TheresaC::IDLE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_IDLE);
}

void CFSM_TheresaC::IDLE_Update(float deltaTime)
{
}

void CFSM_TheresaC::IDLE_End(void)
{
}

void CFSM_TheresaC::VICTORY_Init(void)
{
}

void CFSM_TheresaC::VICTORY_Enter(void)
{
	m_pDM->ChangeAniSet(Index_VICTORY);
}

void CFSM_TheresaC::VICTORY_Update(float deltaTime)
{
}

void CFSM_TheresaC::VICTORY_End(void)
{
}

void CFSM_TheresaC::Die_Init(void)
{
}

void CFSM_TheresaC::Die_Enter(void)
{
}

void CFSM_TheresaC::Die_Update(float deltaTime)
{
}

void CFSM_TheresaC::Die_End(void)
{
}

void CFSM_TheresaC::STUN_Init(void)
{
}

void CFSM_TheresaC::STUN_Enter(void)
{
}

void CFSM_TheresaC::STUN_Update(float deltaTime)
{
}

void CFSM_TheresaC::STUN_End(void)
{
}

void CFSM_TheresaC::QTE_FY_Init(void)
{
}

void CFSM_TheresaC::QTE_FY_Enter(void)
{
}

void CFSM_TheresaC::QTE_FY_Update(float deltaTime)
{
}

void CFSM_TheresaC::QTE_FY_End(void)
{
}

void CFSM_TheresaC::JUMP_2_Init(void)
{
}

void CFSM_TheresaC::JUMP_2_Enter(void)
{
}

void CFSM_TheresaC::JUMP_2_Update(float deltaTime)
{
}

void CFSM_TheresaC::JUMP_2_End(void)
{
}

void CFSM_TheresaC::JUMP_1_Init(void)
{
}

void CFSM_TheresaC::JUMP_1_Enter(void)
{
}

void CFSM_TheresaC::JUMP_1_Update(float deltaTime)
{
}

void CFSM_TheresaC::JUMP_1_End(void)
{
}

void CFSM_TheresaC::JUMP_0_Init(void)
{
}

void CFSM_TheresaC::JUMP_0_Enter(void)
{
}

void CFSM_TheresaC::JUMP_0_Update(float deltaTime)
{
}

void CFSM_TheresaC::JUMP_0_End(void)
{
}

void CFSM_TheresaC::SWITCHOUT_Init(void)
{
}

void CFSM_TheresaC::SWITCHOUT_Enter(void)
{
}

void CFSM_TheresaC::SWITCHOUT_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHOUT_End(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_Init(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_Enter(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_End(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_Init(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_Enter(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_End(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_Init(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_Enter(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_End(void)
{
}

void CFSM_TheresaC::SWITCHIN_Init(void)
{
}

void CFSM_TheresaC::SWITCHIN_Enter(void)
{
}

void CFSM_TheresaC::SWITCHIN_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHIN_End(void)
{
}

void CFSM_TheresaC::Ult_Init(void)
{
}

void CFSM_TheresaC::Ult_Enter(void)
{
}

void CFSM_TheresaC::Ult_Update(float deltaTime)
{
}

void CFSM_TheresaC::Ult_End(void)
{
}

void CFSM_TheresaC::CROSSSKILL_Init(void)
{
}

void CFSM_TheresaC::CROSSSKILL_Enter(void)
{
}

void CFSM_TheresaC::CROSSSKILL_Update(float deltaTime)
{
}

void CFSM_TheresaC::CROSSSKILL_End(void)
{
}

void CFSM_TheresaC::CHARGE2_Init(void)
{
}

void CFSM_TheresaC::CHARGE2_Enter(void)
{
}

void CFSM_TheresaC::CHARGE2_Update(float deltaTime)
{
}

void CFSM_TheresaC::CHARGE2_End(void)
{
}

void CFSM_TheresaC::CHARGE1_Init(void)
{
}

void CFSM_TheresaC::CHARGE1_Enter(void)
{
}

void CFSM_TheresaC::CHARGE1_Update(float deltaTime)
{
}

void CFSM_TheresaC::CHARGE1_End(void)
{
}

void CFSM_TheresaC::CHARGE0_Init(void)
{
}

void CFSM_TheresaC::CHARGE0_Enter(void)
{
}

void CFSM_TheresaC::CHARGE0_Update(float deltaTime)
{
}

void CFSM_TheresaC::CHARGE0_End(void)
{
}

void CFSM_TheresaC::ATTACK4_Init(void)
{
}

void CFSM_TheresaC::ATTACK4_Enter(void)
{
}

void CFSM_TheresaC::ATTACK4_Update(float deltaTime)
{
}

void CFSM_TheresaC::ATTACK4_End(void)
{
}

void CFSM_TheresaC::ATTACK3_Init(void)
{
}

void CFSM_TheresaC::ATTACK3_Enter(void)
{
}

void CFSM_TheresaC::ATTACK3_Update(float deltaTime)
{
}

void CFSM_TheresaC::ATTACK3_End(void)
{
}

void CFSM_TheresaC::ATTACK2_Init(void)
{
}

void CFSM_TheresaC::ATTACK2_Enter(void)
{
}

void CFSM_TheresaC::ATTACK2_Update(float deltaTime)
{
}

void CFSM_TheresaC::ATTACK2_End(void)
{
}

void CFSM_TheresaC::ATTACK1_Init(void)
{
}

void CFSM_TheresaC::ATTACK1_Enter(void)
{
}

void CFSM_TheresaC::ATTACK1_Update(float deltaTime)
{
}

void CFSM_TheresaC::ATTACK1_End(void)
{
}

void CFSM_TheresaC::RUNSTOPRIGHT_Init(void)
{
}

void CFSM_TheresaC::RUNSTOPRIGHT_Enter(void)
{
}

void CFSM_TheresaC::RUNSTOPRIGHT_Update(float deltaTime)
{
}

void CFSM_TheresaC::RUNSTOPRIGHT_End(void)
{
}

void CFSM_TheresaC::RUNSTOPLEFT_Init(void)
{
}

void CFSM_TheresaC::RUNSTOPLEFT_Enter(void)
{
}

void CFSM_TheresaC::RUNSTOPLEFT_Update(float deltaTime)
{
}

void CFSM_TheresaC::RUNSTOPLEFT_End(void)
{
}

void CFSM_TheresaC::FASTRUN_Init(void)
{
}

void CFSM_TheresaC::FASTRUN_Enter(void)
{
}

void CFSM_TheresaC::FASTRUN_Update(float deltaTime)
{
}

void CFSM_TheresaC::FASTRUN_End(void)
{
}

void CFSM_TheresaC::RUN_Init(void)
{
}

void CFSM_TheresaC::RUN_Enter(void)
{
}

void CFSM_TheresaC::RUN_Update(float deltaTime)
{
}

void CFSM_TheresaC::RUN_End(void)
{
}

void CFSM_TheresaC::APPEAR_Init(void)
{
}

void CFSM_TheresaC::APPEAR_Enter(void)
{
}

void CFSM_TheresaC::APPEAR_Update(float deltaTime)
{
}

void CFSM_TheresaC::APPEAR_End(void)
{
}

void CFSM_TheresaC::HIT_H_Init(void)
{
}

void CFSM_TheresaC::HIT_H_Enter(void)
{
}

void CFSM_TheresaC::HIT_H_Update(float deltaTime)
{
}

void CFSM_TheresaC::HIT_H_End(void)
{
}

void CFSM_TheresaC::HIT_L_Init(void)
{
}

void CFSM_TheresaC::HIT_L_Enter(void)
{
}

void CFSM_TheresaC::HIT_L_Update(float deltaTime)
{
}

void CFSM_TheresaC::HIT_L_End(void)
{
}
