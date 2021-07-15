#include "stdafx.h"
#include "..\Header\FSM_SickleC.h"
#include "State.h"
#include "DynamicMeshData.h"

#include "AniCtrl.h"
#include "FSMDefine_Sickle.h"
#include "Monster.h"

CFSM_SickleC::CFSM_SickleC()
{
}

SP(Engine::CComponent) CFSM_SickleC::MakeClone(Engine::CObject * pObject)
{
	SP(CStateMachineC) spClone = MakeStateMachineClone<CFSM_SickleC>(pObject);

	return spClone;
}

void CFSM_SickleC::Awake()
{
	__super::Awake();
}

void CFSM_SickleC::Start(SP(CComponent) spThis)
{
	RegisterAllStage();

	

	__super::Start(spThis);

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pOwner->GetComponent<Engine::CMeshC>()->GetMeshData());

	SetStartState(Name_Sickle_Born);
	m_curState->DoEnter();
}

void CFSM_SickleC::RegisterAllStage()
{
	Engine::CState* pState;

	CreateState(CFSM_SickleC, pState, StandBy)
		AddState(pState, Name_Sickle_StandBy);

	CreateState(CFSM_SickleC, pState, Walk_Forward)
		AddState(pState, Name_Sickle_Walk_Forward);

	CreateState(CFSM_SickleC, pState, Walk_Back)
		AddState(pState, Name_Sickle_Walk_Back);

	CreateState(CFSM_SickleC, pState, Walk_Left)
		AddState(pState, Name_Sickle_Walk_Left);

	CreateState(CFSM_SickleC, pState, Walk_Right)
		AddState(pState, Name_Sickle_Walk_Right);

	CreateState(CFSM_SickleC, pState, Attack_1)
		AddState(pState, Name_Sickle_Attack_1);

	CreateState(CFSM_SickleC, pState, Attack_2)
		AddState(pState, Name_Sickle_Attack_2);

	CreateState(CFSM_SickleC, pState, Attack_2_1)
		AddState(pState, Name_Sickle_Attack_2_1);

	CreateState(CFSM_SickleC, pState, Attack_2_Loop)
		AddState(pState, Name_Sickle_Attack_2_Loop);

	CreateState(CFSM_SickleC, pState, Attack_3)
		AddState(pState, Name_Sickle_Attack_3);

	CreateState(CFSM_SickleC, pState, Attack_4_Start)
		AddState(pState, Name_Sickle_Attack_4_Start);

	CreateState(CFSM_SickleC, pState, Attack_4_Loop)
		AddState(pState, Name_Sickle_Attack_4_Loop);

	CreateState(CFSM_SickleC, pState, Attack_4_End)
		AddState(pState, Name_Sickle_Attack_4_End);

	CreateState(CFSM_SickleC, pState, Attack_Unique01)
		AddState(pState, Name_Sickle_Attack_Unique01);

	CreateState(CFSM_SickleC, pState, Born)
		AddState(pState, Name_Sickle_Born);

	CreateState(CFSM_SickleC, pState, Die)
		AddState(pState, Name_Sickle_Die);

	CreateState(CFSM_SickleC, pState, Die_Back)
		AddState(pState, Name_Sickle_Die_Back);

	CreateState(CFSM_SickleC, pState, Die_Fly)
		AddState(pState, Name_Sickle_Die_Fly);

	CreateState(CFSM_SickleC, pState, KnockDown)
		AddState(pState, Name_Sickle_KnockDown);

	CreateState(CFSM_SickleC, pState, Stun)
		AddState(pState, Name_Sickle_Stun);

	CreateState(CFSM_SickleC, pState, StandUp)
		AddState(pState, Name_Sickle_StandUp);

	CreateState(CFSM_SickleC, pState, Throw_01)
		AddState(pState, Name_Sickle_Throw_01);

	CreateState(CFSM_SickleC, pState, Throw_02)
		AddState(pState, Name_Sickle_Throw_02);

	CreateState(CFSM_SickleC, pState, Hit_Throw)
		AddState(pState, Name_Sickle_Hit_Throw);

	CreateState(CFSM_SickleC, pState, Hit_Throw_Low)
		AddState(pState, Name_Sickle_Hit_Throw_Low);

	CreateState(CFSM_SickleC, pState, Throw_Blow)
		AddState(pState, Name_Sickle_Throw_Blow);

	CreateState(CFSM_SickleC, pState, Hit_Front)
		AddState(pState, Name_Sickle_Hit_Front);

	CreateState(CFSM_SickleC, pState, Hit_Front_L)
		AddState(pState, Name_Sickle_Hit_Front_L);

	CreateState(CFSM_SickleC, pState, Hit_Back)
		AddState(pState, Name_Sickle_Hit_Back);

	CreateState(CFSM_SickleC, pState, Hit_H)
		AddState(pState, Name_Sickle_Hit_H);

	CreateState(CFSM_SickleC, pState, Hit_L)
		AddState(pState, Name_Sickle_Hit_L);

	CreateState(CFSM_SickleC, pState, Hit_Shake)
		AddState(pState, Name_Sickle_Hit_Shake);

	CreateState(CFSM_SickleC, pState, Hit_Shake_1)
		AddState(pState, Name_Sickle_Hit_Shake_1);

	CreateState(CFSM_SickleC, pState, Defend)
		AddState(pState, Name_Sickle_Defend);
}

void CFSM_SickleC::FixRootMotionOffset(_uint index)
{
	m_pOwner->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_SickleC::StandBy_Init(void)
{
}

void CFSM_SickleC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_StandBy);
}

void CFSM_SickleC::StandBy_Update(float deltaTime)
{
	
}

void CFSM_SickleC::StandBy_End(void)
{
}

void CFSM_SickleC::Walk_Forward_Init(void)
{
}

void CFSM_SickleC::Walk_Forward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Walk_Forward);
}

void CFSM_SickleC::Walk_Forward_Update(float deltaTime)
{
}

void CFSM_SickleC::Walk_Forward_End(void)
{
}

void CFSM_SickleC::Walk_Back_Init(void)
{
}

void CFSM_SickleC::Walk_Back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Walk_Back);
}

void CFSM_SickleC::Walk_Back_Update(float deltaTime)
{
}

void CFSM_SickleC::Walk_Back_End(void)
{
}

void CFSM_SickleC::Walk_Left_Init(void)
{
}

void CFSM_SickleC::Walk_Left_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Walk_Left);
}

void CFSM_SickleC::Walk_Left_Update(float deltaTime)
{
}

void CFSM_SickleC::Walk_Left_End(void)
{
}

void CFSM_SickleC::Walk_Right_Init(void)
{
}

void CFSM_SickleC::Walk_Right_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Walk_Right);
}

void CFSM_SickleC::Walk_Right_Update(float deltaTime)
{
}

void CFSM_SickleC::Walk_Right_End(void)
{
}

void CFSM_SickleC::Attack_1_Init(void)
{
}

void CFSM_SickleC::Attack_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_1);
}

void CFSM_SickleC::Attack_1_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_1_End(void)
{
}

void CFSM_SickleC::Attack_2_Init(void)
{
}

void CFSM_SickleC::Attack_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_2);
}

void CFSM_SickleC::Attack_2_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_2_End(void)
{
}

void CFSM_SickleC::Attack_2_1_Init(void)
{
}

void CFSM_SickleC::Attack_2_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_2_1);
}

void CFSM_SickleC::Attack_2_1_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_2_1_End(void)
{
}

void CFSM_SickleC::Attack_2_Loop_Init(void)
{
}

void CFSM_SickleC::Attack_2_Loop_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_2_Loop);
}

void CFSM_SickleC::Attack_2_Loop_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_2_Loop_End(void)
{
}

void CFSM_SickleC::Attack_3_Init(void)
{
}

void CFSM_SickleC::Attack_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_3);
}

void CFSM_SickleC::Attack_3_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_3_End(void)
{
}

void CFSM_SickleC::Attack_4_Start_Init(void)
{
}

void CFSM_SickleC::Attack_4_Start_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_4_Start);
}

void CFSM_SickleC::Attack_4_Start_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_4_Start_End(void)
{
}

void CFSM_SickleC::Attack_4_Loop_Init(void)
{
}

void CFSM_SickleC::Attack_4_Loop_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_4_Loop);
}

void CFSM_SickleC::Attack_4_Loop_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_4_Loop_End(void)
{
}

void CFSM_SickleC::Attack_4_End_Init(void)
{
}

void CFSM_SickleC::Attack_4_End_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_4_End);
}

void CFSM_SickleC::Attack_4_End_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_4_End_End(void)
{
}

void CFSM_SickleC::Attack_Unique01_Init(void)
{
}

void CFSM_SickleC::Attack_Unique01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Attack_Unique01);
}

void CFSM_SickleC::Attack_Unique01_Update(float deltaTime)
{
}

void CFSM_SickleC::Attack_Unique01_End(void)
{
}

void CFSM_SickleC::Born_Init(void)
{
}

void CFSM_SickleC::Born_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Born);
}

void CFSM_SickleC::Born_Update(float deltaTime)
{
}

void CFSM_SickleC::Born_End(void)
{
}

void CFSM_SickleC::Die_Init(void)
{
}

void CFSM_SickleC::Die_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Die);
}

void CFSM_SickleC::Die_Update(float deltaTime)
{
}

void CFSM_SickleC::Die_End(void)
{
}

void CFSM_SickleC::Die_Back_Init(void)
{
}

void CFSM_SickleC::Die_Back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Die_Back);
}

void CFSM_SickleC::Die_Back_Update(float deltaTime)
{
}

void CFSM_SickleC::Die_Back_End(void)
{
}

void CFSM_SickleC::Die_Fly_Init(void)
{
}

void CFSM_SickleC::Die_Fly_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Die_Fly);
}

void CFSM_SickleC::Die_Fly_Update(float deltaTime)
{
}

void CFSM_SickleC::Die_Fly_End(void)
{
}

void CFSM_SickleC::KnockDown_Init(void)
{
}

void CFSM_SickleC::KnockDown_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_KnockDown);
}

void CFSM_SickleC::KnockDown_Update(float deltaTime)
{
}

void CFSM_SickleC::KnockDown_End(void)
{
}

void CFSM_SickleC::Stun_Init(void)
{
}

void CFSM_SickleC::Stun_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Stun);
	static_cast<CMonster*>(m_pOwner)->GetStat()->SetOnPatternShield(true);
}

void CFSM_SickleC::Stun_Update(float deltaTime)
{
}

void CFSM_SickleC::Stun_End(void)
{
	static_cast<CMonster*>(m_pOwner)->GetStat()->SetOnPatternShield(false);
}

void CFSM_SickleC::StandUp_Init(void)
{
}

void CFSM_SickleC::StandUp_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_StandUp);
}

void CFSM_SickleC::StandUp_Update(float deltaTime)
{
}

void CFSM_SickleC::StandUp_End(void)
{
}

void CFSM_SickleC::Throw_01_Init(void)
{
}

void CFSM_SickleC::Throw_01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Throw_01);
}

void CFSM_SickleC::Throw_01_Update(float deltaTime)
{
}

void CFSM_SickleC::Throw_01_End(void)
{
}

void CFSM_SickleC::Throw_02_Init(void)
{
}

void CFSM_SickleC::Throw_02_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Throw_02);
}

void CFSM_SickleC::Throw_02_Update(float deltaTime)
{
}

void CFSM_SickleC::Throw_02_End(void)
{
}

void CFSM_SickleC::Hit_Throw_Init(void)
{
}

void CFSM_SickleC::Hit_Throw_Enter(void)
{
	m_pDM->RepeatAniSet(Index_Sickle_Hit_Throw);
}

void CFSM_SickleC::Hit_Throw_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_Throw_End(void)
{
}

void CFSM_SickleC::Hit_Throw_Low_Init(void)
{
}

void CFSM_SickleC::Hit_Throw_Low_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_Throw_Low);
}

void CFSM_SickleC::Hit_Throw_Low_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_Throw_Low_End(void)
{
}

void CFSM_SickleC::Throw_Blow_Init(void)
{
}

void CFSM_SickleC::Throw_Blow_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Throw_Blow);
}

void CFSM_SickleC::Throw_Blow_Update(float deltaTime)
{
}

void CFSM_SickleC::Throw_Blow_End(void)
{
}

void CFSM_SickleC::Hit_Front_Init(void)
{
}

void CFSM_SickleC::Hit_Front_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_Front);
}

void CFSM_SickleC::Hit_Front_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_Front_End(void)
{
}

void CFSM_SickleC::Hit_Front_L_Init(void)
{
}

void CFSM_SickleC::Hit_Front_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_Front_L);
}

void CFSM_SickleC::Hit_Front_L_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_Front_L_End(void)
{
}

void CFSM_SickleC::Hit_Back_Init(void)
{
}

void CFSM_SickleC::Hit_Back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_Back);
}

void CFSM_SickleC::Hit_Back_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_Back_End(void)
{
}

void CFSM_SickleC::Hit_H_Init(void)
{
}

void CFSM_SickleC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_H);
}

void CFSM_SickleC::Hit_H_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_H_End(void)
{
}

void CFSM_SickleC::Hit_L_Init(void)
{
}

void CFSM_SickleC::Hit_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_L);
}

void CFSM_SickleC::Hit_L_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_L_End(void)
{
}

void CFSM_SickleC::Hit_Shake_Init(void)
{
}

void CFSM_SickleC::Hit_Shake_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_Shake);
}

void CFSM_SickleC::Hit_Shake_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_Shake_End(void)
{
}

void CFSM_SickleC::Hit_Shake_1_Init(void)
{
}

void CFSM_SickleC::Hit_Shake_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Hit_Shake_1);
}

void CFSM_SickleC::Hit_Shake_1_Update(float deltaTime)
{
}

void CFSM_SickleC::Hit_Shake_1_End(void)
{
}

void CFSM_SickleC::Defend_Init(void)
{
}

void CFSM_SickleC::Defend_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Sickle_Defend);
}

void CFSM_SickleC::Defend_Update(float deltaTime)
{
}

void CFSM_SickleC::Defend_End(void)
{
}
