#include "stdafx.h"
#include "..\Header\FSM_SpiderC.h"
#include "State.h"
#include "DynamicMeshData.h"

FSM_SpiderC::FSM_SpiderC()
{
}

SP(Engine::CComponent) FSM_SpiderC::MakeClone(Engine::CObject * pObject)
{
	SP(FSM_SpiderC) spClone(new FSM_SpiderC);

	__super::InitClone(spClone, pObject);

	for (auto pState : m_stateList)
	{
		spClone->m_stateList.emplace(pState);
	}

	return spClone;
}
void FSM_SpiderC::Awake(void)
{
	Engine::CState* pState;

	CreateState(FSM_SpiderC, pState, ATTACK_1)
	AddState(pState, L"ATTACK_1");

	__super::Awake();
}

void FSM_SpiderC::Start(SP(CComponent) spThis)
{
	SetStartState(L"ATTACK_1");
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
}

void FSM_SpiderC::ATTACK_1_End(void)
{
}
