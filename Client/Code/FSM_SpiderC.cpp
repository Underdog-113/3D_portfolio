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
	if (FAILED(Init_FSM_Setting()))
	{
		MSG_BOX(__FILE__, L"FSM_SpiderC Init_FSM_Setting Failed");
		ABORT;
	}

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
}

void FSM_SpiderC::ATTACK_1_Update(float deltaTime)
{

}

void FSM_SpiderC::ATTACK_1_End(void)
{

}

void FSM_SpiderC::ATTACK_2_Init(void)
{

}

void FSM_SpiderC::ATTACK_2_Enter(void)
{

}

void FSM_SpiderC::ATTACK_2_Update(float deltaTime)
{

}

void FSM_SpiderC::ATTACK_2_End(void)
{

}

void FSM_SpiderC::ATTACK_2_BS_Init(void)
{

}

void FSM_SpiderC::ATTACK_2_BS_Enter(void)
{

}

void FSM_SpiderC::ATTACK_2_BS_Update(float deltaTime)
{

}

void FSM_SpiderC::ATTACK_2_BS_End(void)
{

}

void FSM_SpiderC::ATTACK_2_Run_Init(void)
{

}

void FSM_SpiderC::ATTACK_2_Run_Enter(void)
{

}

void FSM_SpiderC::ATTACK_2_Run_Update(float deltaTime)
{

}

void FSM_SpiderC::ATTACK_2_Run_End(void)
{

}

void FSM_SpiderC::ATTACK_3_Init(void)
{

}

void FSM_SpiderC::ATTACK_3_Enter(void)
{

}

void FSM_SpiderC::ATTACK_3_Update(float deltaTime)
{

}

void FSM_SpiderC::ATTACK_3_End(void)
{

}

void FSM_SpiderC::ATTACK_3_AS_Init(void)
{

}

void FSM_SpiderC::ATTACK_3_AS_Enter(void)
{

}

void FSM_SpiderC::ATTACK_3_AS_Update(float deltaTime)
{

}

void FSM_SpiderC::ATTACK_3_AS_End(void)
{

}

void FSM_SpiderC::ATTACK_3_BS_Init(void)
{

}

void FSM_SpiderC::ATTACK_3_BS_Enter(void)
{
}

void FSM_SpiderC::ATTACK_3_BS_Update(float deltaTime)
{
}

void FSM_SpiderC::ATTACK_3_BS_End(void)
{
}

void FSM_SpiderC::ATTACK_DIE_Init(void)
{
}

void FSM_SpiderC::ATTACK_DIE_Enter(void)
{
}

void FSM_SpiderC::ATTACK_DIE_Update(float deltaTime)
{
}

void FSM_SpiderC::ATTACK_DIE_End(void)
{
}

void FSM_SpiderC::BORN_Init(void)
{
}

void FSM_SpiderC::BORN_Enter(void)
{
}

void FSM_SpiderC::BORN_Update(float deltaTime)
{
}

void FSM_SpiderC::BORN_End(void)
{
}

void FSM_SpiderC::Bury_AS_Init(void)
{
}

void FSM_SpiderC::Bury_AS_Enter(void)
{
}

void FSM_SpiderC::Bury_AS_Update(float deltaTime)
{
}

void FSM_SpiderC::Bury_AS_End(void)
{
}

void FSM_SpiderC::Bury_BS_Init(void)
{
}

void FSM_SpiderC::Bury_BS_Enter(void)
{
}

void FSM_SpiderC::Bury_BS_Update(float deltaTime)
{
}

void FSM_SpiderC::Bury_BS_End(void)
{
}

void FSM_SpiderC::Bury_Loop_Init(void)
{
}

void FSM_SpiderC::Bury_Loop_Enter(void)
{
}

void FSM_SpiderC::Bury_Loop_Update(float deltaTime)
{
}

void FSM_SpiderC::Bury_Loop_End(void)
{
}

void FSM_SpiderC::Attack_Die_Init(void)
{
}

void FSM_SpiderC::Attack_Die_Enter(void)
{
}

void FSM_SpiderC::Attack_Die_Update(float deltaTime)
{
}

void FSM_SpiderC::Attack_Die_End(void)
{
}

void FSM_SpiderC::Hit_H_Init(void)
{
}

void FSM_SpiderC::Hit_H_Enter(void)
{
}

void FSM_SpiderC::Hit_H_Update(float deltaTime)
{
}

void FSM_SpiderC::Hit_H_End(void)
{
}

void FSM_SpiderC::Hit_H_Early_Init(void)
{
}

void FSM_SpiderC::Hit_H_Early_Enter(void)
{
}

void FSM_SpiderC::Hit_H_Early_Update(float deltaTime)
{
}

void FSM_SpiderC::Hit_H_Early_End(void)
{
}

void FSM_SpiderC::Hit_L_Init(void)
{
}

void FSM_SpiderC::Hit_L_Enter(void)
{
}

void FSM_SpiderC::Hit_L_Update(float deltaTime)
{
}

void FSM_SpiderC::Hit_L_End(void)
{
}

void FSM_SpiderC::Hit_L_Early_Init(void)
{
}

void FSM_SpiderC::Hit_L_Early_Enter(void)
{
}

void FSM_SpiderC::Hit_L_Early_Update(float deltaTime)
{
}

void FSM_SpiderC::Hit_L_Early_End(void)
{
}

void FSM_SpiderC::Hit_Throw_Init(void)
{
}

void FSM_SpiderC::Hit_Throw_Enter(void)
{
}

void FSM_SpiderC::Hit_Throw_Update(float deltaTime)
{
}

void FSM_SpiderC::Hit_Throw_End(void)
{
}

void FSM_SpiderC::Hit_Throw_Low_Init(void)
{
}

void FSM_SpiderC::Hit_Throw_Low_Enter(void)
{
}

void FSM_SpiderC::Hit_Throw_Low_Update(float deltaTime)
{
}

void FSM_SpiderC::Hit_Throw_Low_End(void)
{
}

void FSM_SpiderC::KnockDown_Init(void)
{
}

void FSM_SpiderC::KnockDown_Enter(void)
{
}

void FSM_SpiderC::KnockDown_Update(float deltaTime)
{
}

void FSM_SpiderC::KnockDown_End(void)
{
}

void FSM_SpiderC::StandBy_Init(void)
{
	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	pDM->ChangeAniSet("StandBy");
}

void FSM_SpiderC::StandBy_Enter(void)
{

}

void FSM_SpiderC::StandBy_Update(float deltaTime)
{
}

void FSM_SpiderC::StandBy_End(void)
{
}

void FSM_SpiderC::Throw_01_Init(void)
{
}

void FSM_SpiderC::Throw_01_Enter(void)
{
}

void FSM_SpiderC::Throw_01_Update(float deltaTime)
{
}

void FSM_SpiderC::Throw_01_End(void)
{
}

void FSM_SpiderC::Throw_02_Init(void)
{
}

void FSM_SpiderC::Throw_02_Enter(void)
{
}

void FSM_SpiderC::Throw_02_Update(float deltaTime)
{
}

void FSM_SpiderC::Throw_02_End(void)
{
}

void FSM_SpiderC::Throw_Blow_Init(void)
{
}

void FSM_SpiderC::Throw_Blow_Enter(void)
{
}

void FSM_SpiderC::Throw_Blow_Update(float deltaTime)
{
}

void FSM_SpiderC::Throw_Blow_End(void)
{
}

void FSM_SpiderC::Walk_Forward_Init(void)
{
}

void FSM_SpiderC::Walk_Forward_Enter(void)
{
}

void FSM_SpiderC::Walk_Forward_Update(float deltaTime)
{
}

void FSM_SpiderC::Walk_Forward_End(void)
{
}

void FSM_SpiderC::Walk_Left_Init(void)
{
}

void FSM_SpiderC::Walk_Left_Enter(void)
{
}

void FSM_SpiderC::Walk_Left_Update(float deltaTime)
{
}

void FSM_SpiderC::Walk_Left_End(void)
{
}

void FSM_SpiderC::Walk_Right_Init(void)
{
}

void FSM_SpiderC::Walk_Right_Enter(void)
{
}

void FSM_SpiderC::Walk_Right_Update(float deltaTime)
{
}

void FSM_SpiderC::Walk_Right_End(void)
{
}

HRESULT FSM_SpiderC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(FSM_SpiderC, pState, ATTACK_1)
		AddState(pState, L"ATTACK_1");

	CreateState(FSM_SpiderC, pState, ATTACK_2)
		AddState(pState, L"ATTACK_2");

	CreateState(FSM_SpiderC, pState, ATTACK_2_BS)
		AddState(pState, L"ATTACK_2_BS");

	CreateState(FSM_SpiderC, pState, ATTACK_2_Run)
		AddState(pState, L"ATTACK_2_Run");

	CreateState(FSM_SpiderC, pState, ATTACK_3)
		AddState(pState, L"ATTACK_3");

	CreateState(FSM_SpiderC, pState, ATTACK_3_AS)
		AddState(pState, L"ATTACK_3_AS");

	CreateState(FSM_SpiderC, pState, ATTACK_3_BS)
		AddState(pState, L"ATTACK_3_BS");

	CreateState(FSM_SpiderC, pState, ATTACK_DIE)
		AddState(pState, L"ATTACK_DIE");

	CreateState(FSM_SpiderC, pState, BORN)
		AddState(pState, L"BORN");

	CreateState(FSM_SpiderC, pState, Bury_AS)
		AddState(pState, L"Bury_AS");

	CreateState(FSM_SpiderC, pState, Bury_BS)
		AddState(pState, L"Bury_BS");

	CreateState(FSM_SpiderC, pState, Bury_Loop)
		AddState(pState, L"Bury_Loop");

	CreateState(FSM_SpiderC, pState, Attack_Die)
		AddState(pState, L"Attack_Die");

	CreateState(FSM_SpiderC, pState, Hit_H)
		AddState(pState, L"Hit_H");

	CreateState(FSM_SpiderC, pState, Hit_H_Early)
		AddState(pState, L"Hit_H_Early");

	CreateState(FSM_SpiderC, pState, Hit_L)
		AddState(pState, L"Hit_L");

	CreateState(FSM_SpiderC, pState, Hit_L_Early)
		AddState(pState, L"Hit_L_Early");

	CreateState(FSM_SpiderC, pState, Hit_Throw)
		AddState(pState, L"Hit_Throw");

	CreateState(FSM_SpiderC, pState, Hit_Throw_Low)
		AddState(pState, L"Hit_Throw_Low");

	CreateState(FSM_SpiderC, pState, KnockDown)
		AddState(pState, L"KnockDown");

	CreateState(FSM_SpiderC, pState, StandBy)
		AddState(pState, L"StandBy");

	CreateState(FSM_SpiderC, pState, Throw_01)
		AddState(pState, L"Throw_01");

	CreateState(FSM_SpiderC, pState, Throw_02)
		AddState(pState, L"Throw_02");

	CreateState(FSM_SpiderC, pState, Throw_Blow)
		AddState(pState, L"Throw_Blow");

	CreateState(FSM_SpiderC, pState, Walk_Forward)
		AddState(pState, L"Walk_Forward");

	CreateState(FSM_SpiderC, pState, Walk_Left)
		AddState(pState, L"Walk_Left");

	CreateState(FSM_SpiderC, pState, Walk_Right)
		AddState(pState, L"Walk_Right");

	if (pState == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}
//
//void FSM_SpiderC::ATTACK_2_Init(void)
//{
//}
//
//void FSM_SpiderC::ATTACK_2_Enter(void)
//{
//	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//	pDM->ChangeAniSet(2);
//}
//
//void FSM_SpiderC::ATTACK_2_Update(float deltaTime)
//{
//	if (Engine::IMKEY_DOWN(KEY_TAB))
//	{
//		ChangeState(L"RUN");
//		return;
//	}
//
//	if (Engine::IMKEY_DOWN(KEY_Z))
//	{
//		ChangeState(L"ATTACK_1");
//		return;
//	}
//}
//
//void FSM_SpiderC::ATTACK_2_End(void)
//{
//}
//
//void FSM_SpiderC::RUN_Init(void)
//{
//}
//
//void FSM_SpiderC::RUN_Enter(void)
//{
//	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//	pDM->ChangeAniSet(40);
//}
//
//void FSM_SpiderC::RUN_Update(float deltaTime)
//{
//	if (Engine::IMKEY_DOWN(KEY_TAB))
//	{
//		ChangeState(L"StandBy");
//		return;
//	}
//	if (Engine::IMKEY_DOWN(KEY_Z))
//	{
//		ChangeState(L"ATTACK_1");
//		return;
//	}
//
//}
//
//void FSM_SpiderC::RUN_End(void)
//{
//}
//
//void FSM_SpiderC::StandBy_Init(void)
//{
//}
//
//void FSM_SpiderC::StandBy_Enter(void)
//{
//	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//	pDM->ChangeAniSet(47);
//}
//
//void FSM_SpiderC::StandBy_Update(float deltaTime)
//{
//	if (Engine::IMKEY_DOWN(KEY_TAB))
//	{
//		ChangeState(L"RUN");
//		return;
//	}
//}
//
//void FSM_SpiderC::StandBy_End(void)
//{
//}
