#include "stdafx.h"
#include "..\Header\FSM_SpiderC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Spider.h"

CFSM_SpiderC::CFSM_SpiderC()
{
}

SP(Engine::CComponent) CFSM_SpiderC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_SpiderC>(pObject);

	return spClone;
}

void CFSM_SpiderC::Awake(void)
{
	__super::Awake();
}

void CFSM_SpiderC::Start(SP(CComponent) spThis)
{
	RegisterAllState();

	__super::Start(spThis);

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);

	SetStartState(Name_StandBy);
	m_curState->DoEnter();
}

void CFSM_SpiderC::RegisterAllState()
{
	Engine::CState* pState;

	CreateState(CFSM_SpiderC, pState, ATTACK_1)
		AddState(pState, Name_Attack_1);

	CreateState(CFSM_SpiderC, pState, ATTACK_2)
		AddState(pState, Name_Attack_2);

	CreateState(CFSM_SpiderC, pState, ATTACK_2_BS)
		AddState(pState, Name_Attack_2_BS);

	CreateState(CFSM_SpiderC, pState, ATTACK_2_Run)
		AddState(pState, Name_Attack_2_Run);

	CreateState(CFSM_SpiderC, pState, ATTACK_3)
		AddState(pState, Name_Attack_3);

	CreateState(CFSM_SpiderC, pState, ATTACK_3_AS)
		AddState(pState, Name_Attack_3_AS);

	CreateState(CFSM_SpiderC, pState, ATTACK_3_BS)
		AddState(pState, Name_Attack_3_BS);

	CreateState(CFSM_SpiderC, pState, ATTACK_DIE)
		AddState(pState, Name_Attack_Die);

	CreateState(CFSM_SpiderC, pState, BORN)
		AddState(pState, Name_Born);

	CreateState(CFSM_SpiderC, pState, Bury_AS)
		AddState(pState, Name_Bury_AS);

	CreateState(CFSM_SpiderC, pState, Bury_BS)
		AddState(pState, Name_Bury_BS);

	CreateState(CFSM_SpiderC, pState, Bury_Loop)
		AddState(pState, Name_Bury_Loop);

	CreateState(CFSM_SpiderC, pState, Hit_H)
		AddState(pState, Name_Hit_H);

	CreateState(CFSM_SpiderC, pState, Hit_H_Early)
		AddState(pState, Name_Hit_H_Early);

	CreateState(CFSM_SpiderC, pState, Hit_L)
		AddState(pState, Name_Hit_L);

	CreateState(CFSM_SpiderC, pState, Hit_L_Early)
		AddState(pState, Name_Hit_L_Early);

	CreateState(CFSM_SpiderC, pState, Hit_Throw)
		AddState(pState, Name_Hit_Throw);

	CreateState(CFSM_SpiderC, pState, Hit_Throw_Low)
		AddState(pState, Name_Hit_Throw_Low);

	CreateState(CFSM_SpiderC, pState, KnockDown)
		AddState(pState, Name_KnockDown);

	CreateState(CFSM_SpiderC, pState, StandBy)
		AddState(pState, Name_StandBy);

	CreateState(CFSM_SpiderC, pState, Throw_01)
		AddState(pState, Name_Throw_01);

	CreateState(CFSM_SpiderC, pState, Throw_02)
		AddState(pState, Name_Throw_02);

	CreateState(CFSM_SpiderC, pState, Throw_Blow)
		AddState(pState, Name_Throw_Blow);

	CreateState(CFSM_SpiderC, pState, Walk_Forward)
		AddState(pState, Name_Walk_Forward);

	CreateState(CFSM_SpiderC, pState, Walk_Left)
		AddState(pState, Name_Walk_Left);

	CreateState(CFSM_SpiderC, pState, Walk_Right)
		AddState(pState, Name_Walk_Right);
}

void CFSM_SpiderC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_SpiderC::ATTACK_1_Init(void)
{
}

void CFSM_SpiderC::ATTACK_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1);
}

void CFSM_SpiderC::ATTACK_1_Update(float deltaTime)
{

}

void CFSM_SpiderC::ATTACK_1_End(void)
{

}

void CFSM_SpiderC::ATTACK_2_Init(void)
{

}

void CFSM_SpiderC::ATTACK_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2);
}

void CFSM_SpiderC::ATTACK_2_Update(float deltaTime)
{

}

void CFSM_SpiderC::ATTACK_2_End(void)
{

}

void CFSM_SpiderC::ATTACK_2_BS_Init(void)
{

}

void CFSM_SpiderC::ATTACK_2_BS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2_BS);
}

void CFSM_SpiderC::ATTACK_2_BS_Update(float deltaTime)
{
}

void CFSM_SpiderC::ATTACK_2_BS_End(void)
{

}

void CFSM_SpiderC::ATTACK_2_Run_Init(void)
{

}

void CFSM_SpiderC::ATTACK_2_Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2_Run);
}

void CFSM_SpiderC::ATTACK_2_Run_Update(float deltaTime)
{

}

void CFSM_SpiderC::ATTACK_2_Run_End(void)
{

}

void CFSM_SpiderC::ATTACK_3_Init(void)
{

}

void CFSM_SpiderC::ATTACK_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3);
}

void CFSM_SpiderC::ATTACK_3_Update(float deltaTime)
{

}

void CFSM_SpiderC::ATTACK_3_End(void)
{

}

void CFSM_SpiderC::ATTACK_3_AS_Init(void)
{

}

void CFSM_SpiderC::ATTACK_3_AS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3_AS);
}

void CFSM_SpiderC::ATTACK_3_AS_Update(float deltaTime)
{

}

void CFSM_SpiderC::ATTACK_3_AS_End(void)
{

}

void CFSM_SpiderC::ATTACK_3_BS_Init(void)
{

}

void CFSM_SpiderC::ATTACK_3_BS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3_BS);
}

void CFSM_SpiderC::ATTACK_3_BS_Update(float deltaTime)
{
}

void CFSM_SpiderC::ATTACK_3_BS_End(void)
{
}

void CFSM_SpiderC::ATTACK_DIE_Init(void)
{
}

void CFSM_SpiderC::ATTACK_DIE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_Die);
}

void CFSM_SpiderC::ATTACK_DIE_Update(float deltaTime)
{
}

void CFSM_SpiderC::ATTACK_DIE_End(void)
{
}

void CFSM_SpiderC::BORN_Init(void)
{
}

void CFSM_SpiderC::BORN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Born);
}

void CFSM_SpiderC::BORN_Update(float deltaTime)
{
}

void CFSM_SpiderC::BORN_End(void)
{
}

void CFSM_SpiderC::Bury_AS_Init(void)
{
}

void CFSM_SpiderC::Bury_AS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Bury_AS);
}

void CFSM_SpiderC::Bury_AS_Update(float deltaTime)
{
}

void CFSM_SpiderC::Bury_AS_End(void)
{
}

void CFSM_SpiderC::Bury_BS_Init(void)
{
}

void CFSM_SpiderC::Bury_BS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Bury_BS);
}

void CFSM_SpiderC::Bury_BS_Update(float deltaTime)
{
}

void CFSM_SpiderC::Bury_BS_End(void)
{
}

void CFSM_SpiderC::Bury_Loop_Init(void)
{
}

void CFSM_SpiderC::Bury_Loop_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Bury_Loop);
}

void CFSM_SpiderC::Bury_Loop_Update(float deltaTime)
{
}

void CFSM_SpiderC::Bury_Loop_End(void)
{
}

void CFSM_SpiderC::Hit_H_Init(void)
{
}

void CFSM_SpiderC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H);
}

void CFSM_SpiderC::Hit_H_Update(float deltaTime)
{
}

void CFSM_SpiderC::Hit_H_End(void)
{
}

void CFSM_SpiderC::Hit_H_Early_Init(void)
{
}

void CFSM_SpiderC::Hit_H_Early_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H_Early);
}

void CFSM_SpiderC::Hit_H_Early_Update(float deltaTime)
{
}

void CFSM_SpiderC::Hit_H_Early_End(void)
{
}

void CFSM_SpiderC::Hit_L_Init(void)
{
}

void CFSM_SpiderC::Hit_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L);
}

void CFSM_SpiderC::Hit_L_Update(float deltaTime)
{
}

void CFSM_SpiderC::Hit_L_End(void)
{
}

void CFSM_SpiderC::Hit_L_Early_Init(void)
{
}

void CFSM_SpiderC::Hit_L_Early_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L_Early);
}

void CFSM_SpiderC::Hit_L_Early_Update(float deltaTime)
{
}

void CFSM_SpiderC::Hit_L_Early_End(void)
{
}

void CFSM_SpiderC::Hit_Throw_Init(void)
{
}

void CFSM_SpiderC::Hit_Throw_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Throw);
}

void CFSM_SpiderC::Hit_Throw_Update(float deltaTime)
{
}

void CFSM_SpiderC::Hit_Throw_End(void)
{
}

void CFSM_SpiderC::Hit_Throw_Low_Init(void)
{
}

void CFSM_SpiderC::Hit_Throw_Low_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_Throw_Low);
}

void CFSM_SpiderC::Hit_Throw_Low_Update(float deltaTime)
{
}

void CFSM_SpiderC::Hit_Throw_Low_End(void)
{
}

void CFSM_SpiderC::KnockDown_Init(void)
{
}

void CFSM_SpiderC::KnockDown_Enter(void)
{
	m_pDM->ChangeAniSet(Index_KnockDown);
}

void CFSM_SpiderC::KnockDown_Update(float deltaTime)
{
}

void CFSM_SpiderC::KnockDown_End(void)
{
}

void CFSM_SpiderC::StandBy_Init(void)
{
}

void CFSM_SpiderC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
}

void CFSM_SpiderC::StandBy_Update(float deltaTime)
{
}

void CFSM_SpiderC::StandBy_End(void)
{
}

void CFSM_SpiderC::Throw_01_Init(void)
{
}

void CFSM_SpiderC::Throw_01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_01);
}

void CFSM_SpiderC::Throw_01_Update(float deltaTime)
{
}

void CFSM_SpiderC::Throw_01_End(void)
{
}

void CFSM_SpiderC::Throw_02_Init(void)
{
}

void CFSM_SpiderC::Throw_02_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_02);
}

void CFSM_SpiderC::Throw_02_Update(float deltaTime)
{
}

void CFSM_SpiderC::Throw_02_End(void)
{
}

void CFSM_SpiderC::Throw_Blow_Init(void)
{
}

void CFSM_SpiderC::Throw_Blow_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Throw_Blow);
}

void CFSM_SpiderC::Throw_Blow_Update(float deltaTime)
{
}

void CFSM_SpiderC::Throw_Blow_End(void)
{
}

void CFSM_SpiderC::Walk_Forward_Init(void)
{
}

void CFSM_SpiderC::Walk_Forward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Forward);
}

void CFSM_SpiderC::Walk_Forward_Update(float deltaTime)
{
}

void CFSM_SpiderC::Walk_Forward_End(void)
{
}

void CFSM_SpiderC::Walk_Left_Init(void)
{
}

void CFSM_SpiderC::Walk_Left_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Left);
}

void CFSM_SpiderC::Walk_Left_Update(float deltaTime)
{
}

void CFSM_SpiderC::Walk_Left_End(void)
{
}

void CFSM_SpiderC::Walk_Right_Init(void)
{
}

void CFSM_SpiderC::Walk_Right_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Walk_Right);
}

void CFSM_SpiderC::Walk_Right_Update(float deltaTime)
{
}

void CFSM_SpiderC::Walk_Right_End(void)
{
}
