#include "stdafx.h"
#include "..\Header\FSM_GaneshaC.h"


FSM_GaneshaC::FSM_GaneshaC()
{
}

SP(Engine::CComponent) FSM_GaneshaC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<FSM_GaneshaC>(pObject);

	return spClone;
}

void FSM_GaneshaC::Awake(void)
{
	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"FSM_GaneshaC Init_FSM_Setting Failed");
		ABORT;
	}

	__super::Awake();
}

void FSM_GaneshaC::Start(SP(CComponent) spThis)
{
	SetStartState(L"StandBy");
	__super::Start(spThis);
}

void FSM_GaneshaC::ActivateRampage_Init(void)
{
}

void FSM_GaneshaC::ActivateRampage_Enter(void)
{
}

void FSM_GaneshaC::ActivateRampage_Update(float deltaTime)
{
}

void FSM_GaneshaC::ActivateRampage_End(void)
{
}

void FSM_GaneshaC::Attack01_Init(void)
{
}

void FSM_GaneshaC::Attack01_Enter(void)
{
}

void FSM_GaneshaC::Attack01_Update(float deltaTime)
{
}

void FSM_GaneshaC::Attack01_End(void)
{
}

void FSM_GaneshaC::Born_Init(void)
{
}

void FSM_GaneshaC::Born_Enter(void)
{
}

void FSM_GaneshaC::Born_Update(float deltaTime)
{
}

void FSM_GaneshaC::Born_End(void)
{
}

void FSM_GaneshaC::Burst01_Init(void)
{
}

void FSM_GaneshaC::Burst01_Enter(void)
{
}

void FSM_GaneshaC::Burst01_Update(float deltaTime)
{
}

void FSM_GaneshaC::Burst01_End(void)
{
}

void FSM_GaneshaC::Burst02_Init(void)
{
}

void FSM_GaneshaC::Burst02_Enter(void)
{
}

void FSM_GaneshaC::Burst02_Update(float deltaTime)
{
}

void FSM_GaneshaC::Burst02_End(void)
{
}

void FSM_GaneshaC::Die_Init(void)
{
}

void FSM_GaneshaC::Die_Enter(void)
{
}

void FSM_GaneshaC::Die_Update(float deltaTime)
{
}

void FSM_GaneshaC::Die_End(void)
{
}

void FSM_GaneshaC::Jump_Back_Init(void)
{
}

void FSM_GaneshaC::Jump_Back_Enter(void)
{
}

void FSM_GaneshaC::Jump_Back_Update(float deltaTime)
{
}

void FSM_GaneshaC::Jump_Back_End(void)
{
}

void FSM_GaneshaC::Jump_Turn_Init(void)
{
}

void FSM_GaneshaC::Jump_Turn_Enter(void)
{
}

void FSM_GaneshaC::Jump_Turn_Update(float deltaTime)
{
}

void FSM_GaneshaC::Jump_Turn_End(void)
{
}

void FSM_GaneshaC::Roll01_Init(void)
{
}

void FSM_GaneshaC::Roll01_Enter(void)
{
}

void FSM_GaneshaC::Roll01_Update(float deltaTime)
{
}

void FSM_GaneshaC::Roll01_End(void)
{
}

void FSM_GaneshaC::Roll02_Init(void)
{
}

void FSM_GaneshaC::Roll02_Enter(void)
{
}

void FSM_GaneshaC::Roll02_Update(float deltaTime)
{
}

void FSM_GaneshaC::Roll02_End(void)
{
}

void FSM_GaneshaC::Run_Init(void)
{
}

void FSM_GaneshaC::Run_Enter(void)
{
}

void FSM_GaneshaC::Run_Update(float deltaTime)
{
}

void FSM_GaneshaC::Run_End(void)
{
}

void FSM_GaneshaC::Stamp_Init(void)
{
}

void FSM_GaneshaC::Stamp_Enter(void)
{
}

void FSM_GaneshaC::Stamp_Update(float deltaTime)
{
}

void FSM_GaneshaC::Stamp_End(void)
{
}

void FSM_GaneshaC::StandBy_Init(void)
{
}

void FSM_GaneshaC::StandBy_Enter(void)
{
}

void FSM_GaneshaC::StandBy_Update(float deltaTime)
{
}

void FSM_GaneshaC::StandBy_End(void)
{
}

void FSM_GaneshaC::Weak_Init(void)
{
}

void FSM_GaneshaC::Weak_Enter(void)
{
}

void FSM_GaneshaC::Weak_Update(float deltaTime)
{
}

void FSM_GaneshaC::Weak_End(void)
{
}

void FSM_GaneshaC::Weak_End_Init(void)
{
}

void FSM_GaneshaC::Weak_End_Enter(void)
{
}

void FSM_GaneshaC::Weak_End_Update(float deltaTime)
{
}

void FSM_GaneshaC::Weak_End_End(void)
{
}

void FSM_GaneshaC::Weak_Hit_Init(void)
{
}

void FSM_GaneshaC::Weak_Hit_Enter(void)
{
}

void FSM_GaneshaC::Weak_Hit_Update(float deltaTime)
{
}

void FSM_GaneshaC::Weak_Hit_End(void)
{
}

void FSM_GaneshaC::Weak_Loop_Init(void)
{
}

void FSM_GaneshaC::Weak_Loop_Enter(void)
{
}

void FSM_GaneshaC::Weak_Loop_Update(float deltaTime)
{
}

void FSM_GaneshaC::Weak_Loop_End(void)
{
}

void FSM_GaneshaC::Weak_Start_Init(void)
{
}

void FSM_GaneshaC::Weak_Start_Enter(void)
{
}

void FSM_GaneshaC::Weak_Start_Update(float deltaTime)
{
}

void FSM_GaneshaC::Weak_Start_End(void)
{
}

HRESULT FSM_GaneshaC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_GaneshaC, pState, ActivateRampage)
		AddState(pState, L"ActivateRampage");

	CreateState(FSM_GaneshaC, pState, Attack01)
		AddState(pState, L"Attack01");

	CreateState(FSM_GaneshaC, pState, Born)
		AddState(pState, L"Born");

	CreateState(FSM_GaneshaC, pState, Burst01)
		AddState(pState, L"Burst01");

	CreateState(FSM_GaneshaC, pState, Burst02)
		AddState(pState, L"Burst02");

	CreateState(FSM_GaneshaC, pState, Die)
		AddState(pState, L"Die");

	CreateState(FSM_GaneshaC, pState, Jump_Back)
		AddState(pState, L"Jump_Back");

	CreateState(FSM_GaneshaC, pState, Jump_Turn)
		AddState(pState, L"Jump_Turn");

	CreateState(FSM_GaneshaC, pState, Roll01)
		AddState(pState, L"Roll01");

	CreateState(FSM_GaneshaC, pState, Roll02)
		AddState(pState, L"Roll02");

	CreateState(FSM_GaneshaC, pState, Run)
		AddState(pState, L"Run");

	CreateState(FSM_GaneshaC, pState, Stamp)
		AddState(pState, L"Stamp");

	CreateState(FSM_GaneshaC, pState, StandBy)
		AddState(pState, L"StandBy");

	CreateState(FSM_GaneshaC, pState, Weak)
		AddState(pState, L"Weak");

	CreateState(FSM_GaneshaC, pState, Weak_End)
		AddState(pState, L"Weak_End");

	CreateState(FSM_GaneshaC, pState, Weak_Hit)
		AddState(pState, L"Weak_Hit");

	CreateState(FSM_GaneshaC, pState, Weak_Loop)
		AddState(pState, L"Weak_Loop");

	CreateState(FSM_GaneshaC, pState, Weak_Start)
		AddState(pState, L"Weak_Start");

	if (pState == nullptr)
		return E_FAIL;

	return S_OK;
}

