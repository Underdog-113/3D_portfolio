#include "stdafx.h"
#include "FSM_TheresaC.h"

#include "SoundManager.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "Theresa.h"
#include "State.h"
#include "FSMDefine_Theresa.h"
#include "AttackBall.h"

#include "AttackTrail_Client.h"
#include "StageControlTower.h"

CFSM_TheresaC::CFSM_TheresaC()
{
}

SP(Engine::CComponent) CFSM_TheresaC::MakeClone(Engine::CObject * pObject)
{
	SP(CFSM_TheresaC) spClone(new CFSM_TheresaC);

	__super::InitClone(spClone, pObject);

	for (auto pState : m_stateList)
	{
		spClone->m_stateList.emplace(pState.first, pState.second->MakeClone(spClone.get()));
	}

	return spClone;
}

void CFSM_TheresaC::Awake(void)
{
	__super::Awake();
}

void CFSM_TheresaC::Start(SP(CComponent) spThis)
{
	m_pTheresa = static_cast<CTheresa*>(m_pOwner);

	__super::Start(spThis);

	RegisterAllState();

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pTheresa->GetComponent<Engine::CMeshC>()->GetMeshData());
	m_pStageControlTower = CStageControlTower::GetInstance();

	SetStartState(Name_IDLE);
	m_curState->DoEnter();
}

void CFSM_TheresaC::FixRootMotionOffset(_uint index)
{
	m_pTheresa->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_TheresaC::ResetCheckMembers()
{
	//m_checkEffect = false;
	//m_checkEffectSecond = false;
}

bool CFSM_TheresaC::CheckAction_Attack(const std::wstring & switchStateName, float coolTime)
{
	if (Engine::IMKEY_DOWN(StageKey_Attack))
	{
		if (m_pDM->GetAniTimeline() > coolTime)
		{
			ChangeState(switchStateName);
			CStageControlTower::GetInstance()->FindTarget();
			return true;
		}
	}
	return false;
}

bool CFSM_TheresaC::CheckAction_Evade_OnAction(float coolTime)
{
	if (Engine::IMKEY_PRESS(StageKey_Move_Forward) ||
		Engine::IMKEY_PRESS(StageKey_Move_Left) ||
		Engine::IMKEY_PRESS(StageKey_Move_Back) ||
		Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		return CheckAction_EvadeForward(coolTime);
	}
	else
		return CheckAction_EvadeBackward(coolTime);
}

bool CFSM_TheresaC::CheckAction_EvadeForward(float coolTime)
{
	if (Engine::IMKEY_DOWN(StageKey_Evade))
	{
		if (m_pDM->GetAniTimeline() > coolTime)
		{
			ChangeState(Name_EvadeForward);
			return true;
		}
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_EvadeBackward(float coolTime)
{
	if (Engine::IMKEY_DOWN(StageKey_Evade))
	{
		if (m_pDM->GetAniTimeline() > coolTime)
		{
			ChangeState(Name_EvadeBackward);
			return true;
		}
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_StandBy_Timeout(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		ChangeState(Name_IDLE);
		return true;
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_Run()
{
	if (Engine::IMKEY_PRESS(StageKey_Move_Forward) ||
		Engine::IMKEY_PRESS(StageKey_Move_Left) ||
		Engine::IMKEY_PRESS(StageKey_Move_Back) ||
		Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		ChangeState(Name_RunBS);
		return true;
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_Run_OnAction(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		if (Engine::IMKEY_PRESS(StageKey_Move_Forward) ||
			Engine::IMKEY_PRESS(StageKey_Move_Left) ||
			Engine::IMKEY_PRESS(StageKey_Move_Back) ||
			Engine::IMKEY_PRESS(StageKey_Move_Right))
		{
			ChangeState(Name_Run);
			return true;
		}
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_Run_End()
{
	if (!Engine::IMKEY_PRESS(StageKey_Move_Forward) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Left) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Back) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		double timeline = m_pDM->GetAniTimeline();
		if (timeline > 0.8)
		{
			ChangeState(Name_RUNSTOPLEFT);
			return true;
		}
		else if (timeline > 0.55)
		{
			ChangeState(Name_RUNSTOPRIGHT);
			return true;
		}
		else if (timeline > 0.30)
		{
			ChangeState(Name_RUNSTOPLEFT);
			return true;
		}

		else if (timeline > 0.05)
		{
			ChangeState(Name_RUNSTOPRIGHT);
			return true;
		}
		else
		{
			ChangeState(Name_RUNSTOPLEFT);
			return true;
		}
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_Idle()
{
	if (!Engine::IMKEY_PRESS(StageKey_Move_Forward) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Left) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Back) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		ChangeState(Name_IDLE);
		return true;
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_RunBS_To_Run()
{
	if (m_pDM->GetAniTimeline() > Cool_End - 0.25f)
	{
		ChangeState(Name_Run);
		return true;
	}
	return false;
}

void CFSM_TheresaC::IDLE_Init(void)
{
}

void CFSM_TheresaC::IDLE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_IDLE);
}

void CFSM_TheresaC::IDLE_Update(float deltaTime)
{
	if (CheckAction_Run())
		return;

	if (CheckAction_Attack(Name_ATTACK1, 0.f))
		return;

	if (CheckAction_EvadeBackward(0.f))
		return;

	//if (CheckAction_Ultra())
	//	return;

	if (Engine::IMKEY_DOWN(StageKey_QTE))
	{
		ChangeState(Name_APPEAR);
		m_appearOption = QTE;
		return;
	}


	if (Engine::IMKEY_DOWN(StageKey_Test_Hit_L))
	{
		ChangeState(Name_HIT_L);
		return;
	}

	if (Engine::IMKEY_DOWN(StageKey_Test_Hit_H))
	{
		ChangeState(Name_HIT_H);
		return;
	}
}

void CFSM_TheresaC::IDLE_End(void)
{
}

void CFSM_TheresaC::APPEAR_Init(void)
{
}

void CFSM_TheresaC::APPEAR_Enter(void)
{
	m_pDM->ChangeAniSet(Index_APPEAR);
}

void CFSM_TheresaC::APPEAR_Update(float deltaTime)
{
	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		switch (m_appearOption)
		{
		case CFSM_TheresaC::None:
			ChangeState(Name_IDLE);
			break;
		case CFSM_TheresaC::QTE:
			ChangeState(Name_QTE_FY);
			break;
		default:
			break;
		}
		return;
	}
}

void CFSM_TheresaC::APPEAR_End(void)
{
	m_appearOption = None;
}

void CFSM_TheresaC::RUN_Init(void)
{
}

void CFSM_TheresaC::RUN_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUN);
}

void CFSM_TheresaC::RUN_Update(float deltaTime)
{
	//m_runSoundTimer += GET_DT;
	//if (m_runSoundTimer > 0.3f)
	//{
	//	m_runSoundTimer = 0.f;
	//	PlaySound_Attack_RandomRun();
	//}


	if (CheckAction_Run_End())
		return;
	if (CheckAction_Attack(Name_ATTACK1, 0.f))
		return;
	if (CheckAction_EvadeForward())
		return;
	//if (CheckAction_Ultra())
	//	return;
}

void CFSM_TheresaC::RUN_End(void)
{
	//m_runSoundTimer = 0.f;
}

void CFSM_TheresaC::RunBS_Init(void)
{
}

void CFSM_TheresaC::RunBS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunBS);
}

void CFSM_TheresaC::RunBS_Update(float deltaTime)
{
	//m_runSoundTimer += GET_DT;
	//if (m_runSoundTimer > 0.3f)
	//{
	//	m_runSoundTimer = 0.f;
	//	PlaySound_Attack_RandomRun();
	//}

	if (CheckAction_RunBS_To_Run())
		return;

	if (CheckAction_Run_End())
		return;

	if (CheckAction_Idle())
		return;
	if (CheckAction_Attack(Name_ATTACK1, 0.f))
		return;
	if (CheckAction_EvadeForward())
		return;
}

void CFSM_TheresaC::RunBS_End(void)
{
}

void CFSM_TheresaC::EvadeBackward_Init(void)
{
}

void CFSM_TheresaC::EvadeBackward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_EvadeBackward);
	m_pStageControlTower->ActorControl_SetInputLock(true);

}

void CFSM_TheresaC::EvadeBackward_Update(float deltaTime)
{
	if (CheckAction_Run_OnAction(0.5f))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::EvadeBackward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_TheresaC::EvadeForward_Init(void)
{
}

void CFSM_TheresaC::EvadeForward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_EvadeForward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_TheresaC::EvadeForward_Update(float deltaTime)
{
	if (CheckAction_Run_OnAction(0.5f))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::EvadeForward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_TheresaC::ATTACK1_Init(void)
{
}

void CFSM_TheresaC::ATTACK1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_ATTACK1);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	ResetCheckMembers();
	//m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
}

void CFSM_TheresaC::ATTACK1_Update(float deltaTime)
{
	//if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk01)
	//{
	//	CreateEffect_Attack1();
	//	PlaySound_Attack_RandomVoice();

	//	if (m_pKiana->GetUltraMode())
	//		PlaySound_Effect(Sound_Ult_Att_0);
	//	else
	//		PlaySound_Effect(Sound_Attack_1_Effect);

	//	m_checkEffect = true;
	//}

	if (CheckAction_Attack(Name_ATTACK2, 0.3f))
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::ATTACK1_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);

	//m_pKiana->UnActiveAttackBall();
}

void CFSM_TheresaC::ATTACK2_Init(void)
{
	FixRootMotionOffset(Index_ATTACK2);
}

void CFSM_TheresaC::ATTACK2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_ATTACK2);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
	//m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetLeftHandWorldMatrix(), 0.3f);
}

void CFSM_TheresaC::ATTACK2_Update(float deltaTime)
{
	//if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk02)
	//{
	//	CreateEffect_Attack2();
	//	m_checkEffect = true;

	//	PlaySound_Attack_RandomVoice();

	//	if (m_pKiana->GetUltraMode())
	//		PlaySound_Effect(Sound_Ult_Att_1);
	//	else
	//		PlaySound_Effect(Sound_Attack_2_Effect);
	//}

	if (CheckAction_Attack(Name_ATTACK3))
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::ATTACK2_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);

	//m_pKiana->UnActiveAttackBall();
}

void CFSM_TheresaC::ATTACK3_Init(void)
{
	FixRootMotionOffset(Index_ATTACK3);
}

void CFSM_TheresaC::ATTACK3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_ATTACK3);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
	//m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightHandWorldMatrix(), 0.3f);

}

void CFSM_TheresaC::ATTACK3_Update(float deltaTime)
{
	// 	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk03)
	// 	{
	// 		CreateEffect_Attack3();
	// 		m_checkEffect = true;
	// 
	// 		PlaySound_Attack_RandomVoice();
	// 
	// 		if (m_pKiana->GetUltraMode())
	// 			PlaySound_Effect(Sound_Ult_Att_1);
	// 		else
	// 			PlaySound_Effect(Sound_Attack_3_Effect);
	// 	}

	if (CheckAction_Attack(Name_ATTACK4))
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::ATTACK3_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);

	//m_pKiana->UnActiveAttackBall();
}

void CFSM_TheresaC::ATTACK4_Init(void)
{
	FixRootMotionOffset(Index_ATTACK4);
}

void CFSM_TheresaC::ATTACK4_Enter(void)
{
	m_pDM->ChangeAniSet(Index_ATTACK4);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
	//m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
}

void CFSM_TheresaC::ATTACK4_Update(float deltaTime)
{
	//if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > 0.15f)
	//{
	//	CreateEffect_Attack4();
	//	m_checkEffectSecond = true;
	//}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::ATTACK4_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);

	//m_pKiana->UnActiveAttackBall();
}

void CFSM_TheresaC::CHARGE0_Init(void)
{
}

void CFSM_TheresaC::CHARGE0_Enter(void)
{
}

void CFSM_TheresaC::CHARGE0_Update(float deltaTime)
{
}

void CFSM_TheresaC::CHARGE0_End(void)
{
}

void CFSM_TheresaC::CHARGE1_Init(void)
{
}

void CFSM_TheresaC::CHARGE1_Enter(void)
{
}

void CFSM_TheresaC::CHARGE1_Update(float deltaTime)
{
}

void CFSM_TheresaC::CHARGE1_End(void)
{
}

void CFSM_TheresaC::CHARGE2_Init(void)
{
}

void CFSM_TheresaC::CHARGE2_Enter(void)
{
}

void CFSM_TheresaC::CHARGE2_Update(float deltaTime)
{
}

void CFSM_TheresaC::CHARGE2_End(void)
{
}

void CFSM_TheresaC::VICTORY_Init(void)
{
}

void CFSM_TheresaC::VICTORY_Enter(void)
{
}

void CFSM_TheresaC::VICTORY_Update(float deltaTime)
{
}

void CFSM_TheresaC::VICTORY_End(void)
{
}

void CFSM_TheresaC::Die_Init(void)
{
}

void CFSM_TheresaC::Die_Enter(void)
{
}

void CFSM_TheresaC::Die_Update(float deltaTime)
{
}

void CFSM_TheresaC::Die_End(void)
{
}

void CFSM_TheresaC::STUN_Init(void)
{
}

void CFSM_TheresaC::STUN_Enter(void)
{
}

void CFSM_TheresaC::STUN_Update(float deltaTime)
{
}

void CFSM_TheresaC::STUN_End(void)
{
}

void CFSM_TheresaC::QTE_FY_Init(void)
{
}

void CFSM_TheresaC::QTE_FY_Enter(void)
{
}

void CFSM_TheresaC::QTE_FY_Update(float deltaTime)
{
}

void CFSM_TheresaC::QTE_FY_End(void)
{
}

void CFSM_TheresaC::JUMP_2_Init(void)
{
}

void CFSM_TheresaC::JUMP_2_Enter(void)
{
}

void CFSM_TheresaC::JUMP_2_Update(float deltaTime)
{
}

void CFSM_TheresaC::JUMP_2_End(void)
{
}

void CFSM_TheresaC::JUMP_1_Init(void)
{
}

void CFSM_TheresaC::JUMP_1_Enter(void)
{
}

void CFSM_TheresaC::JUMP_1_Update(float deltaTime)
{
}

void CFSM_TheresaC::JUMP_1_End(void)
{
}

void CFSM_TheresaC::JUMP_0_Init(void)
{
}

void CFSM_TheresaC::JUMP_0_Enter(void)
{
}

void CFSM_TheresaC::JUMP_0_Update(float deltaTime)
{
}

void CFSM_TheresaC::JUMP_0_End(void)
{
}

void CFSM_TheresaC::SWITCHOUT_Init(void)
{
}

void CFSM_TheresaC::SWITCHOUT_Enter(void)
{
}

void CFSM_TheresaC::SWITCHOUT_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHOUT_End(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_Init(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_Enter(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHINATTACK_YD_End(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_Init(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_Enter(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHINATTACK_TP_End(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_Init(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_Enter(void)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHINATTACK_FY_End(void)
{
}

void CFSM_TheresaC::SWITCHIN_Init(void)
{
}

void CFSM_TheresaC::SWITCHIN_Enter(void)
{
}

void CFSM_TheresaC::SWITCHIN_Update(float deltaTime)
{
}

void CFSM_TheresaC::SWITCHIN_End(void)
{
}

void CFSM_TheresaC::Ult_Init(void)
{
}

void CFSM_TheresaC::Ult_Enter(void)
{
}

void CFSM_TheresaC::Ult_Update(float deltaTime)
{
}

void CFSM_TheresaC::Ult_End(void)
{
}

void CFSM_TheresaC::CROSSSKILL_Init(void)
{
}

void CFSM_TheresaC::CROSSSKILL_Enter(void)
{
}

void CFSM_TheresaC::CROSSSKILL_Update(float deltaTime)
{
}

void CFSM_TheresaC::CROSSSKILL_End(void)
{
}

void CFSM_TheresaC::RUNSTOPRIGHT_Init(void)
{
}

void CFSM_TheresaC::RUNSTOPRIGHT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUNSTOPRIGHT);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_TheresaC::RUNSTOPRIGHT_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_ATTACK2, 0.f))
		return;
	if (CheckAction_EvadeForward())
		return;
	// 	if (CheckAction_Ultra())
	// 		return;
}

void CFSM_TheresaC::RUNSTOPRIGHT_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_TheresaC::RUNSTOPLEFT_Init(void)
{
}

void CFSM_TheresaC::RUNSTOPLEFT_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RUNSTOPLEFT);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_TheresaC::RUNSTOPLEFT_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_ATTACK1, 0.f))
		return;
	if (CheckAction_EvadeForward())
		return;
	//if (CheckAction_Ultra())
	//	return;
}

void CFSM_TheresaC::RUNSTOPLEFT_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_TheresaC::FASTRUN_Init(void)
{
}

void CFSM_TheresaC::FASTRUN_Enter(void)
{
}

void CFSM_TheresaC::FASTRUN_Update(float deltaTime)
{
}

void CFSM_TheresaC::FASTRUN_End(void)
{
}

void CFSM_TheresaC::HIT_H_Init(void)
{
}

void CFSM_TheresaC::HIT_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_H);

	//PlaySound_Attack_RandomHit();
}

void CFSM_TheresaC::HIT_H_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::HIT_H_End(void)
{
}

void CFSM_TheresaC::HIT_L_Init(void)
{
}

void CFSM_TheresaC::HIT_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_HIT_L);

	//PlaySound_Attack_RandomHit();
}

void CFSM_TheresaC::HIT_L_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::HIT_L_End(void)
{
}

void CFSM_TheresaC::RegisterAllState()
{
	Engine::CState* pState;

	CreateState(CFSM_TheresaC, pState, IDLE)
		AddState(pState, Name_IDLE);

	CreateState(CFSM_TheresaC, pState, RunBS)
		AddState(pState, Name_RunBS);

	CreateState(CFSM_TheresaC, pState, EvadeBackward)
		AddState(pState, Name_EvadeBackward);

	CreateState(CFSM_TheresaC, pState, EvadeForward)
		AddState(pState, Name_EvadeForward);

	CreateState(CFSM_TheresaC, pState, APPEAR)
		AddState(pState, Name_APPEAR);

	CreateState(CFSM_TheresaC, pState, RUN)
		AddState(pState, Name_Run);

	CreateState(CFSM_TheresaC, pState, FASTRUN)
		AddState(pState, Name_FASTRUN);

	CreateState(CFSM_TheresaC, pState, RUNSTOPLEFT)
		AddState(pState, Name_RUNSTOPLEFT);

	CreateState(CFSM_TheresaC, pState, RUNSTOPRIGHT)
		AddState(pState, Name_RUNSTOPRIGHT);

	CreateState(CFSM_TheresaC, pState, ATTACK1)
		AddState(pState, Name_ATTACK1);

	CreateState(CFSM_TheresaC, pState, ATTACK2)
		AddState(pState, Name_ATTACK2);

	CreateState(CFSM_TheresaC, pState, ATTACK3)
		AddState(pState, Name_ATTACK3);

	CreateState(CFSM_TheresaC, pState, ATTACK4)
		AddState(pState, Name_ATTACK4);

	CreateState(CFSM_TheresaC, pState, CHARGE0)
		AddState(pState, Name_CHARGE0);

	CreateState(CFSM_TheresaC, pState, CHARGE1)
		AddState(pState, Name_CHARGE1);

	CreateState(CFSM_TheresaC, pState, CHARGE2)
		AddState(pState, Name_CHARGE2);

	CreateState(CFSM_TheresaC, pState, CROSSSKILL)
		AddState(pState, Name_CROSSSKILL);

	CreateState(CFSM_TheresaC, pState, Ult)
		AddState(pState, Name_Ult);

	CreateState(CFSM_TheresaC, pState, SWITCHIN)
		AddState(pState, Name_SWITCHIN);

	CreateState(CFSM_TheresaC, pState, SWITCHOUT)
		AddState(pState, Name_SWITCHOUT);

	CreateState(CFSM_TheresaC, pState, SWITCHINATTACK_FY)
		AddState(pState, Name_SWITCHINATTACK_FY);

	CreateState(CFSM_TheresaC, pState, SWITCHINATTACK_TP)
		AddState(pState, Name_SWITCHINATTACK_TP);

	CreateState(CFSM_TheresaC, pState, SWITCHINATTACK_YD)
		AddState(pState, Name_SWITCHINATTACK_YD);

	CreateState(CFSM_TheresaC, pState, JUMP_0)
		AddState(pState, Name_JUMP_0);

	CreateState(CFSM_TheresaC, pState, JUMP_1)
		AddState(pState, Name_JUMP_1);

	CreateState(CFSM_TheresaC, pState, JUMP_2)
		AddState(pState, Name_JUMP_2);

	CreateState(CFSM_TheresaC, pState, QTE_FY)
		AddState(pState, Name_QTE_FY);

	CreateState(CFSM_TheresaC, pState, HIT_L)
		AddState(pState, Name_HIT_L);

	CreateState(CFSM_TheresaC, pState, HIT_H)
		AddState(pState, Name_HIT_H);

	CreateState(CFSM_TheresaC, pState, STUN)
		AddState(pState, Name_STUN);

	CreateState(CFSM_TheresaC, pState, Die)
		AddState(pState, Name_Die);

	CreateState(CFSM_TheresaC, pState, VICTORY)
		AddState(pState, Name_VICTORY);
}
