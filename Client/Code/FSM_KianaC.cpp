#include "stdafx.h"
#include "..\Header\FSM_KianaC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Kiana.h"

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
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);

	SetStartState(L"StandBy");
	__super::Start(spThis);
}

void CFSM_KianaC::Appear_Init(void)
{
}

void CFSM_KianaC::Appear_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Appear);
}

void CFSM_KianaC::Appear_Update(float deltaTime)
{
}

void CFSM_KianaC::Appear_End(void)
{
}

void CFSM_KianaC::Attack_1_Init(void)
{
}

void CFSM_KianaC::Attack_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1);
}

void CFSM_KianaC::Attack_1_Update(float deltaTime)
{
	if (m_pDM->GetAniTimeline() > m_attackDelay)
	{
		if (Engine::IMKEY_DOWN(KEY_J))
		{
			ChangeState(Name_Attack_2);
			return;
		}
	}

	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		ChangeState(Name_StandBy);
		return;
	}
}

void CFSM_KianaC::Attack_1_End(void)
{

}

void CFSM_KianaC::Attack_2_Init(void)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(Index_Attack_2);
}

void CFSM_KianaC::Attack_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2);
}

void CFSM_KianaC::Attack_2_Update(float deltaTime)
{
	// Branch Attack
	if (m_pDM->GetAniTimeline() > m_branchAttackDelay)
	{
		if (Engine::IMKEY_DOWN(KEY_J))
		{
			ChangeState(Name_Attack_3_Branch);
			return;
		}
	}

	// Normal Attack
	if (m_pDM->GetAniTimeline() > m_attackDelay)
	{
		if (Engine::IMKEY_DOWN(KEY_J))
		{
			ChangeState(Name_Attack_3);
			return;
		}
	}
	
	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		ChangeState(Name_StandBy);
		return;
	}
}

void CFSM_KianaC::Attack_2_End(void)
{

}

void CFSM_KianaC::Attack_3_Init(void)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(Index_Attack_3);
}

void CFSM_KianaC::Attack_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3);
}

void CFSM_KianaC::Attack_3_Update(float deltaTime)
{
	// Branch Attack
	if (m_pDM->GetAniTimeline() > m_branchAttackDelay)
	{
		if (Engine::IMKEY_DOWN(KEY_J))
		{
			ChangeState(Name_Attack_3_Branch);
			return;
		}
	}

	if (m_pDM->GetAniTimeline() > m_attackDelay)
	{
		if (Engine::IMKEY_DOWN(KEY_J))
		{
			ChangeState(Name_Attack_4);
			return;
		}
	}

	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		ChangeState(Name_StandBy);
		return;
	}
}

void CFSM_KianaC::Attack_3_End(void)
{
}

void CFSM_KianaC::Attack_3_Branch_Init(void)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(Index_Attack_3_Branch);
}

void CFSM_KianaC::Attack_3_Branch_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3_Branch);
}

void CFSM_KianaC::Attack_3_Branch_Update(float deltaTime)
{
	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		ChangeState(Name_Attack_4_Branch);
		return;
	}
}

void CFSM_KianaC::Attack_3_Branch_End(void)
{
}

void CFSM_KianaC::Attack_4_Init(void)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(Index_Attack_4);
}

void CFSM_KianaC::Attack_4_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_4);
}

void CFSM_KianaC::Attack_4_Update(float deltaTime)
{
	if (m_pDM->GetAniTimeline() > m_attackDelay)
	{
		if (Engine::IMKEY_DOWN(KEY_J))
		{
			ChangeState(Name_Attack_5);
			return;
		}
	}

	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		ChangeState(Name_StandBy);
		return;
	}
}

void CFSM_KianaC::Attack_4_End(void)
{
}

void CFSM_KianaC::Attack_4_Branch_Init(void)
{
}

void CFSM_KianaC::Attack_4_Branch_Enter(void)
{
}

void CFSM_KianaC::Attack_4_Branch_Update(float deltaTime)
{
}

void CFSM_KianaC::Attack_4_Branch_End(void)
{
}

void CFSM_KianaC::Attack_5_Init(void)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(Index_Attack_5);
}

void CFSM_KianaC::Attack_5_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_5);
}

void CFSM_KianaC::Attack_5_Update(float deltaTime)
{
	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		ChangeState(Name_StandBy);
		return;
	}
}

void CFSM_KianaC::Attack_5_End(void)
{
}

void CFSM_KianaC::Attack_QTE_Init(void)
{
}

void CFSM_KianaC::Attack_QTE_Enter(void)
{
}

void CFSM_KianaC::Attack_QTE_Update(float deltaTime)
{
}

void CFSM_KianaC::Attack_QTE_End(void)
{
}

void CFSM_KianaC::Die_Init(void)
{
}

void CFSM_KianaC::Die_Enter(void)
{
}

void CFSM_KianaC::Die_Update(float deltaTime)
{
}

void CFSM_KianaC::Die_End(void)
{
}

void CFSM_KianaC::EvadeBackward_Init(void)
{
}

void CFSM_KianaC::EvadeBackward_Enter(void)
{
}

void CFSM_KianaC::EvadeBackward_Update(float deltaTime)
{
}

void CFSM_KianaC::EvadeBackward_End(void)
{
}

void CFSM_KianaC::EvadeForward_Init(void)
{
}

void CFSM_KianaC::EvadeForward_Enter(void)
{
}

void CFSM_KianaC::EvadeForward_Update(float deltaTime)
{
}

void CFSM_KianaC::EvadeForward_End(void)
{
}

void CFSM_KianaC::Hit_H_Init(void)
{
}

void CFSM_KianaC::Hit_H_Enter(void)
{
}

void CFSM_KianaC::Hit_H_Update(float deltaTime)
{
}

void CFSM_KianaC::Hit_H_End(void)
{
}

void CFSM_KianaC::Hit_L_Init(void)
{
}

void CFSM_KianaC::Hit_L_Enter(void)
{
}

void CFSM_KianaC::Hit_L_Update(float deltaTime)
{
}

void CFSM_KianaC::Hit_L_End(void)
{
}

void CFSM_KianaC::Idle_01_Init(void)
{
}

void CFSM_KianaC::Idle_01_Enter(void)
{
}

void CFSM_KianaC::Idle_01_Update(float deltaTime)
{
}

void CFSM_KianaC::Idle_01_End(void)
{
}

void CFSM_KianaC::Idle_1to2_Init(void)
{
}

void CFSM_KianaC::Idle_1to2_Enter(void)
{
}

void CFSM_KianaC::Idle_1to2_Update(float deltaTime)
{
}

void CFSM_KianaC::Idle_1to2_End(void)
{
}

void CFSM_KianaC::Idle_02_Init(void)
{
}

void CFSM_KianaC::Idle_02_Enter(void)
{
}

void CFSM_KianaC::Idle_02_Update(float deltaTime)
{
}

void CFSM_KianaC::Idle_02_End(void)
{
}

void CFSM_KianaC::Idle_2to3_Init(void)
{
}

void CFSM_KianaC::Idle_2to3_Enter(void)
{
}

void CFSM_KianaC::Idle_2to3_Update(float deltaTime)
{
}

void CFSM_KianaC::Idle_2to3_End(void)
{
}

void CFSM_KianaC::Idle_03_Init(void)
{
}

void CFSM_KianaC::Idle_03_Enter(void)
{
}

void CFSM_KianaC::Idle_03_Update(float deltaTime)
{
}

void CFSM_KianaC::Idle_03_End(void)
{
}

void CFSM_KianaC::Idle_3to4_Init(void)
{
}

void CFSM_KianaC::Idle_3to4_Enter(void)
{
}

void CFSM_KianaC::Idle_3to4_Update(float deltaTime)
{
}

void CFSM_KianaC::Idle_3to4_End(void)
{
}

void CFSM_KianaC::Idle_4to5_Init(void)
{
}

void CFSM_KianaC::Idle_4to5_Enter(void)
{
}

void CFSM_KianaC::Idle_4to5_Update(float deltaTime)
{
}

void CFSM_KianaC::Idle_4to5_End(void)
{
}

void CFSM_KianaC::Run_Init(void)
{
}

void CFSM_KianaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(40);
}

void CFSM_KianaC::Run_Update(float deltaTime)
{
	if (Engine::IMKEY_UP(KEY_W))
	{
		ChangeState(Name_StandBy);
		return;
	}

	if (Engine::IMKEY_DOWN(KEY_J))
	{
		ChangeState(Name_Attack_1);
		return;
	}
}

void CFSM_KianaC::Run_End(void)
{
}

void CFSM_KianaC::StandBy_Init(void)
{
}

void CFSM_KianaC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(47);
}

void CFSM_KianaC::StandBy_Update(float deltaTime)
{
	if (Engine::IMKEY_DOWN(KEY_W))
	{
		ChangeState(Name_Run);
		return;
	}


	if (Engine::IMKEY_DOWN(KEY_J))
	{
		ChangeState(Name_Attack_1);
		return;
	}
}

void CFSM_KianaC::StandBy_End(void)
{
}

void CFSM_KianaC::Stun_Init(void)
{
}

void CFSM_KianaC::Stun_Enter(void)
{
}

void CFSM_KianaC::Stun_Update(float deltaTime)
{
}

void CFSM_KianaC::Stun_End(void)
{
}

void CFSM_KianaC::SwitchIn_Init(void)
{
}

void CFSM_KianaC::SwitchIn_Enter(void)
{
}

void CFSM_KianaC::SwitchIn_Update(float deltaTime)
{
}

void CFSM_KianaC::SwitchIn_End(void)
{
}

void CFSM_KianaC::SwitchOut_Init(void)
{
}

void CFSM_KianaC::SwitchOut_Enter(void)
{
}

void CFSM_KianaC::SwitchOut_Update(float deltaTime)
{
}

void CFSM_KianaC::SwitchOut_End(void)
{
}

HRESULT CFSM_KianaC::Init_FSM_Setting()
{
	Engine::CState* pState;

	CreateState(CFSM_KianaC, pState, Attack_1)
		AddState(pState, L"Attack_1");

	CreateState(CFSM_KianaC, pState, Attack_2)
		AddState(pState, L"Attack_2");
	
	CreateState(CFSM_KianaC, pState, Attack_3)
		AddState(pState, L"Attack_3");

	CreateState(CFSM_KianaC, pState, Attack_3_Branch)
		AddState(pState, L"Attack_3_Branch");

	CreateState(CFSM_KianaC, pState, Attack_4)
		AddState(pState, L"Attack_4");

	CreateState(CFSM_KianaC, pState, Attack_4_Branch)
		AddState(pState, L"Attack_4_Branch");

	CreateState(CFSM_KianaC, pState, Attack_5)
		AddState(pState, L"Attack_5");

	CreateState(CFSM_KianaC, pState, Attack_QTE)
		AddState(pState, L"Attack_QTE");

	CreateState(CFSM_KianaC, pState, Die)
		AddState(pState, L"Die");

	CreateState(CFSM_KianaC, pState, EvadeBackward)
		AddState(pState, L"EvadeBackward");
	
	CreateState(CFSM_KianaC, pState, EvadeForward)
		AddState(pState, L"EvadeForward");

	CreateState(CFSM_KianaC, pState, Hit_H)
		AddState(pState, L"Hit_H");

	CreateState(CFSM_KianaC, pState, Hit_L)
		AddState(pState, L"Hit_L");

	CreateState(CFSM_KianaC, pState, Idle_01)
		AddState(pState, L"Idle_01");

	CreateState(CFSM_KianaC, pState, Idle_1to2)
		AddState(pState, L"Idle_1to2");

	CreateState(CFSM_KianaC, pState, Idle_02)
		AddState(pState, L"Idle_02");

	CreateState(CFSM_KianaC, pState, Idle_2to3)
		AddState(pState, L"Idle_2to3");

	CreateState(CFSM_KianaC, pState, Idle_03)
		AddState(pState, L"Idle_03");

	CreateState(CFSM_KianaC, pState, Idle_3to4)
		AddState(pState, L"Idle_3to4");

	CreateState(CFSM_KianaC, pState, Idle_4to5)
		AddState(pState, L"Idle_4to5");

	CreateState(CFSM_KianaC, pState, Run)
		AddState(pState, L"Run");
	
	CreateState(CFSM_KianaC, pState, StandBy)
		AddState(pState, L"StandBy");
	

	if (pState == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}
//
//void CFSM_KianaC::Attack_2_Init(void)
//{
//}
//
//void CFSM_KianaC::Attack_2_Enter(void)
//{
//	Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//	pDM->ChangeAniSet(2);
//}
//
//void CFSM_KianaC::Attack_2_Update(float deltaTime)
//{

//}
//
//void CFSM_KianaC::Attack_2_End(void)
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
