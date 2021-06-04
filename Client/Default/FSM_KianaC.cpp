#include "stdafx.h"
#include "FSM_KianaC.h"

#include "State.h"
#include "DynamicMeshData.h"


CFSM_KianaC::CFSM_KianaC()
{
}


CFSM_KianaC::~CFSM_KianaC()
{
}

void CFSM_KianaC::Awake(void)
{
	Engine::CState* pState;

	//pState = new Engine::CState;
	//pState->SetInitailize(std::bind(&CFSM_KianaC::Anim1_Init,this));
	//pState->SetEnter(std::bind(&CFSM_KianaC::Anim1_Enter, this));
	//pState->SetUpdate(std::bind(&CFSM_KianaC::Anim1_Update, this, GET_DT));
	//pState->SetExit(std::bind(&CFSM_KianaC::Anim1_End, this));
	CreateState(CFSM_KianaC, pState, Anim1)
	AddState(pState, L"Anim1");
	
	CreateState(CFSM_KianaC, pState, Anim2)
	AddState(pState, L"Anim2");

	__super::Awake();
}

void CFSM_KianaC::Start(SP(CComponent) spThis)
{
	SetStartState(L"Anim1");
	__super::Start(spThis);
}

#pragma region anim1

void CFSM_KianaC::Anim1_Init(void)
{
}

void CFSM_KianaC::Anim1_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(1);
}

void CFSM_KianaC::Anim1_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		ChangeState(L"Anim2");
		return;
	}
}

void CFSM_KianaC::Anim1_End(void)
{
}

#pragma endregion

#pragma region anim2

void CFSM_KianaC::Anim2_Init(void)
{
}

void CFSM_KianaC::Anim2_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(2);
}

void CFSM_KianaC::Anim2_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		ChangeState(L"Anim1");
		return;
	}
}

void CFSM_KianaC::Anim2_End(void)
{
}

#pragma endregion

void CFSM_KianaC::Anim3_Init(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(3);
}

void CFSM_KianaC::Anim3_Start(void)
{
}

void CFSM_KianaC::Anim3_Update(float deltaTime)
{
}

void CFSM_KianaC::Anim3_End(void)
{
}
