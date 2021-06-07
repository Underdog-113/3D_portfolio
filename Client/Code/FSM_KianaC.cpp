#include "stdafx.h"
#include "..\Header\FSM_KianaC.h"
#include "State.h"
#include "DynamicMeshData.h"

CFSM_KianaC::CFSM_KianaC()
{
}

SP(Engine::CComponent) CFSM_KianaC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_KianaC>(pObject);

	return spClone;
}

void CFSM_KianaC::Awake(void)
{
	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"CFSM_KianaC Init_FSM_Setting Failed");
		ABORT;
	}

	__super::Awake();
}

void CFSM_KianaC::Start(SP(CComponent) spThis)
{
	SetStartState(L"StandBy");
	__super::Start(spThis);
}

void CFSM_KianaC::ATTACK_1_Init(void)
{
}

void CFSM_KianaC::ATTACK_1_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(1);
}

void CFSM_KianaC::ATTACK_1_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		ChangeState(L"RUN");
		return;
	}

	if (Engine::IMKEY_DOWN(KEY_Z))
	{
		ChangeState(L"ATTACK_2");
		return;
	}

}

void CFSM_KianaC::ATTACK_1_End(void)
{

}

void CFSM_KianaC::ATTACK_2_Init(void)
{

}

void CFSM_KianaC::ATTACK_2_Enter(void)
{
		Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
		pDM->ChangeAniSet(2);
}

void CFSM_KianaC::ATTACK_2_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		ChangeState(L"RUN");
		return;
	}

	if (Engine::IMKEY_DOWN(KEY_Z))
	{
		ChangeState(L"ATTACK_1");
		return;
	}
}

void CFSM_KianaC::ATTACK_2_End(void)
{

}

void CFSM_KianaC::RUN_Init(void)
{
}

void CFSM_KianaC::RUN_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(40);
}

void CFSM_KianaC::RUN_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		ChangeState(L"StandBy");
		return;
	}
	if (Engine::IMKEY_DOWN(KEY_Z))
	{
		ChangeState(L"ATTACK_1");
		return;
	}
}

void CFSM_KianaC::RUN_End(void)
{
}

void CFSM_KianaC::StandBy_Init(void)
{
}

void CFSM_KianaC::StandBy_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(47);
}

void CFSM_KianaC::StandBy_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		ChangeState(L"RUN");
		return;
	}
}

void CFSM_KianaC::StandBy_End(void)
{
}

HRESULT CFSM_KianaC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(CFSM_KianaC, pState, ATTACK_1)
		AddState(pState, L"ATTACK_1");

	CreateState(CFSM_KianaC, pState, ATTACK_2)
		AddState(pState, L"ATTACK_2");

	CreateState(CFSM_KianaC, pState, ATTACK_2)
		AddState(pState, L"RUN");
	
	CreateState(CFSM_KianaC, pState, StandBy)
		AddState(pState, L"StandBy");
	

	if (pState == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}
//
//void CFSM_KianaC::ATTACK_2_Init(void)
//{
//}
//
//void CFSM_KianaC::ATTACK_2_Enter(void)
//{
//	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//	pDM->ChangeAniSet(2);
//}
//
//void CFSM_KianaC::ATTACK_2_Update(float deltaTime)
//{

//}
//
//void CFSM_KianaC::ATTACK_2_End(void)
//{
//}
//
//void CFSM_KianaC::RUN_Init(void)
//{
//}
//
//void CFSM_KianaC::RUN_Enter(void)
//{
//	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//	pDM->ChangeAniSet(40);
//}
//
//void CFSM_KianaC::RUN_Update(float deltaTime)
//{

//
//}
//
//void CFSM_KianaC::RUN_End(void)
//{
//}
//
//void CFSM_KianaC::StandBy_Init(void)
//{
//}
//
//void CFSM_KianaC::StandBy_Enter(void)
//{
//	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//	pDM->ChangeAniSet(47);
//}
//
//void CFSM_KianaC::StandBy_Update(float deltaTime)
//{
//	if (Engine::IMKEY_DOWN(KEY_TAB))
//	{
//		ChangeState(L"RUN");
//		return;
//	}
//}
//
//void CFSM_KianaC::StandBy_End(void)
//{
//}
