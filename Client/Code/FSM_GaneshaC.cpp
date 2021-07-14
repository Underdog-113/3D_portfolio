#include "stdafx.h"
#include "..\Header\FSM_GaneshaC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Ganesha.h"

CFSM_GaneshaC::CFSM_GaneshaC()
{
}

SP(Engine::CComponent) CFSM_GaneshaC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_GaneshaC>(pObject);

	return spClone;
}

void CFSM_GaneshaC::Awake(void)
{
	__super::Awake();
}

void CFSM_GaneshaC::Start(SP(CComponent) spThis)
{
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	RegisterAllStage();

	__super::Start(spThis);


	SetStartState(Name_Ganesha_StandBy);
	m_curState->DoEnter();
}

void CFSM_GaneshaC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_GaneshaC, pState, ActivateRampage)
		AddState(pState, L"ActivateRampage");

	CreateState(CFSM_GaneshaC, pState, Attack01)
		AddState(pState, L"Attack01");

	CreateState(CFSM_GaneshaC, pState, Born)
		AddState(pState, L"Born");

	CreateState(CFSM_GaneshaC, pState, Burst01)
		AddState(pState, L"Burst01");

	CreateState(CFSM_GaneshaC, pState, Burst02)
		AddState(pState, L"Burst02");

	CreateState(CFSM_GaneshaC, pState, Die)
		AddState(pState, L"Die");

	CreateState(CFSM_GaneshaC, pState, Jump_Back)
		AddState(pState, L"Jump_Back");

	CreateState(CFSM_GaneshaC, pState, Jump_Turn)
		AddState(pState, L"Jump_Turn");

	CreateState(CFSM_GaneshaC, pState, Roll01)
		AddState(pState, L"Roll01");

	CreateState(CFSM_GaneshaC, pState, Roll02)
		AddState(pState, L"Roll02");

	CreateState(CFSM_GaneshaC, pState, Run)
		AddState(pState, L"Run");

	CreateState(CFSM_GaneshaC, pState, Stamp)
		AddState(pState, L"Stamp");

	CreateState(CFSM_GaneshaC, pState, StandBy)
		AddState(pState, L"StandBy");

	CreateState(CFSM_GaneshaC, pState, Weak)
		AddState(pState, L"Weak");

	CreateState(CFSM_GaneshaC, pState, Weak_End)
		AddState(pState, L"Weak_End");

	CreateState(CFSM_GaneshaC, pState, Weak_Hit)
		AddState(pState, L"Weak_Hit");

	CreateState(CFSM_GaneshaC, pState, Weak_Loop)
		AddState(pState, L"Weak_Loop");

	CreateState(CFSM_GaneshaC, pState, Weak_Start)
		AddState(pState, L"Weak_Start");
}

void CFSM_GaneshaC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_GaneshaC::ActivateRampage_Init(void)
{
}

void CFSM_GaneshaC::ActivateRampage_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_ActivateRampage);
}

void CFSM_GaneshaC::ActivateRampage_Update(float deltaTime)
{
}

void CFSM_GaneshaC::ActivateRampage_End(void)
{
}

void CFSM_GaneshaC::Attack01_Init(void)
{
}

void CFSM_GaneshaC::Attack01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Attack01);
}

void CFSM_GaneshaC::Attack01_Update(float deltaTime)
{
	
}

void CFSM_GaneshaC::Attack01_End(void)
{
}

void CFSM_GaneshaC::Born_Init(void)
{
}

void CFSM_GaneshaC::Born_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Born);
}

void CFSM_GaneshaC::Born_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Born_End(void)
{
}

void CFSM_GaneshaC::Burst01_Init(void)
{
}

void CFSM_GaneshaC::Burst01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Burst01);
}

void CFSM_GaneshaC::Burst01_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Burst01_End(void)
{
}

void CFSM_GaneshaC::Burst02_Init(void)
{
}

void CFSM_GaneshaC::Burst02_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Burst02);
}

void CFSM_GaneshaC::Burst02_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Burst02_End(void)
{
}

void CFSM_GaneshaC::Die_Init(void)
{
}

void CFSM_GaneshaC::Die_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Die);
}

void CFSM_GaneshaC::Die_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Die_End(void)
{
}

void CFSM_GaneshaC::Jump_Back_Init(void)
{
	FixRootMotionOffset(Index_Ganesha_Jump_Back);
}

void CFSM_GaneshaC::Jump_Back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Jump_Back);
}

void CFSM_GaneshaC::Jump_Back_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Jump_Back_End(void)
{
}

void CFSM_GaneshaC::Jump_Turn_Init(void)
{
}

void CFSM_GaneshaC::Jump_Turn_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Jump_Turn);
}

void CFSM_GaneshaC::Jump_Turn_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Jump_Turn_End(void)
{
}

void CFSM_GaneshaC::Roll01_Init(void)
{
}

void CFSM_GaneshaC::Roll01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Roll01);
}

void CFSM_GaneshaC::Roll01_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Roll01_End(void)
{
}

void CFSM_GaneshaC::Roll02_Init(void)
{
}

void CFSM_GaneshaC::Roll02_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Roll02);
}

void CFSM_GaneshaC::Roll02_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Roll02_End(void)
{
}

void CFSM_GaneshaC::Run_Init(void)
{
	m_pDM->SetLoopAnim(Index_Ganesha_Run);
}

void CFSM_GaneshaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Run);
}

void CFSM_GaneshaC::Run_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Run_End(void)
{
}

void CFSM_GaneshaC::Stamp_Init(void)
{
}

void CFSM_GaneshaC::Stamp_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Stamp);
}

void CFSM_GaneshaC::Stamp_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Stamp_End(void)
{
}

void CFSM_GaneshaC::StandBy_Init(void)
{
	m_pDM->SetLoopAnim(Index_Ganesha_StandBy);
}

void CFSM_GaneshaC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_StandBy);
}

void CFSM_GaneshaC::StandBy_Update(float deltaTime)
{
}

void CFSM_GaneshaC::StandBy_End(void)
{
}

void CFSM_GaneshaC::Weak_Init(void)
{
}

void CFSM_GaneshaC::Weak_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Weak);
}

void CFSM_GaneshaC::Weak_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Weak_End(void)
{
}

void CFSM_GaneshaC::Weak_End_Init(void)
{
}

void CFSM_GaneshaC::Weak_End_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Weak_End);
}

void CFSM_GaneshaC::Weak_End_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Weak_End_End(void)
{
}

void CFSM_GaneshaC::Weak_Hit_Init(void)
{
}

void CFSM_GaneshaC::Weak_Hit_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Weak_Hit);
}

void CFSM_GaneshaC::Weak_Hit_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Weak_Hit_End(void)
{
}

void CFSM_GaneshaC::Weak_Loop_Init(void)
{
}

void CFSM_GaneshaC::Weak_Loop_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Weak_Loop);
}

void CFSM_GaneshaC::Weak_Loop_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Weak_Loop_End(void)
{
}

void CFSM_GaneshaC::Weak_Start_Init(void)
{
}

void CFSM_GaneshaC::Weak_Start_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ganesha_Weak_Start);
}

void CFSM_GaneshaC::Weak_Start_Update(float deltaTime)
{
}

void CFSM_GaneshaC::Weak_Start_End(void)
{
}
