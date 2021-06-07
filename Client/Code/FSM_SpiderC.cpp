#include "stdafx.h"
#include "..\Header\FSM_SpiderC.h"
#include "State.h"
#include "DynamicMeshData.h"

FSM_SpiderC::FSM_SpiderC()
{
}

SP(Engine::CComponent) FSM_SpiderC::MakeClone(Engine::CObject * pObject)
{	
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_SpiderC>(pObject);

	return spClone;
}

void FSM_SpiderC::Awake(void)
{
	Engine::CState* pState;

	CreateState(FSM_SpiderC, pState, ATTACK_1)
	AddState(pState, L"ATTACK_1");
	CreateState(FSM_SpiderC, pState, ATTACK_2)
	AddState(pState, L"ATTACK_2");
	CreateState(FSM_SpiderC, pState, RUN)
	AddState(pState, L"RUN");

	CreateState(FSM_SpiderC, pState, StandBy)
		AddState(pState, L"StandBy");

	__super::Awake();
}

void FSM_SpiderC::Start(SP(CComponent) spThis)
{
	SetStartState(L"StandBy");
	__super::Start(spThis);
}

void FSM_SpiderC::ATTACK_1_Init(void)
{
}

void FSM_SpiderC::ATTACK_1_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(1);
}

void FSM_SpiderC::ATTACK_1_Update(float deltaTime)
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

void FSM_SpiderC::ATTACK_1_End(void)
{
}

void FSM_SpiderC::ATTACK_2_Init(void)
{
}

void FSM_SpiderC::ATTACK_2_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(2);
}

void FSM_SpiderC::ATTACK_2_Update(float deltaTime)
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

void FSM_SpiderC::ATTACK_2_End(void)
{
}

void FSM_SpiderC::RUN_Init(void)
{
}

void FSM_SpiderC::RUN_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(40);
}

void FSM_SpiderC::RUN_Update(float deltaTime)
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

void FSM_SpiderC::RUN_End(void)
{
}

void FSM_SpiderC::StandBy_Init(void)
{
}

void FSM_SpiderC::StandBy_Enter(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet(47);
}

void FSM_SpiderC::StandBy_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		ChangeState(L"RUN");
		return;
	}
}

void FSM_SpiderC::StandBy_End(void)
{
}
