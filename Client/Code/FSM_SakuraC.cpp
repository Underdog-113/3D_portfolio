#include "stdafx.h"
#include "FSM_SakuraC.h"

#include "SoundManager.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "Sakura.h"
#include "State.h"
#include "FSMDefine_Sakura.h"
#include "AttackBall.h"

#include "AttackTrail_Client.h"
#include "StageControlTower.h"

CFSM_SakuraC::CFSM_SakuraC()
{
}

SP(Engine::CComponent) CFSM_SakuraC::MakeClone(Engine::CObject * pObject)
{
	SP(CFSM_SakuraC) spClone(new CFSM_SakuraC);

	__super::InitClone(spClone, pObject);

	for (auto pState : m_stateList)
	{
		spClone->m_stateList.emplace(pState.first, pState.second->MakeClone(spClone.get()));
	}

	return spClone;
}

void CFSM_SakuraC::Awake(void)
{
	__super::Awake();
}

void CFSM_SakuraC::Start(SP(CComponent) spThis)
{
	m_pSakura = static_cast<CSakura*>(m_pOwner);
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pSakura->GetComponent<Engine::CMeshC>()->GetMeshData());

	__super::Start(spThis);

	RegisterAllState();

	m_pStageControlTower = CStageControlTower::GetInstance();

	SetStartState(Name_Appear);
	m_curState->DoEnter();
}

void CFSM_SakuraC::FixRootMotionOffset(_uint index)
{
	m_pSakura->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_SakuraC::ResetCheckMembers()
{
	m_checkEffect = false;
	m_checkAttack = false;
}

bool CFSM_SakuraC::CheckAction_Attack(const std::wstring & switchStateName, float coolTime)
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

bool CFSM_SakuraC::CheckAction_Charge(float coolTime)
{
	m_chargeEnterTimer += GET_DT;
	if (Engine::IMKEY_PRESS(StageKey_Attack))
	{
		if (m_chargeEnterTimer > 0.5f)
		{
			m_chargeEnterTimer = 0.f;
			ChangeState(Name_Charge1);
			CStageControlTower::GetInstance()->FindTarget(HitInfo::CrowdControl::CC_Sakura);
			return true;
		}
	}
	else
	{
		m_chargeEnterTimer = 0.f;
	}
	return false;
}

bool CFSM_SakuraC::CheckAction_Evade_OnAction(float coolTime)
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

bool CFSM_SakuraC::CheckAction_EvadeForward(float coolTime)
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

bool CFSM_SakuraC::CheckAction_EvadeBackward(float coolTime)
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

bool CFSM_SakuraC::CheckAction_StandBy_Timeout(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		ChangeState(Name_StandBy);
		return true;
	}

	return false;
}

bool CFSM_SakuraC::CheckAction_CombatToStandBy(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		ChangeState(Name_CombatToStandBy);
		return true;
	}

	return false;
}

bool CFSM_SakuraC::CheckAction_Combat_Timeout(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		ChangeState(Name_Combat);
		return true;
	}

	return false;
}

bool CFSM_SakuraC::CheckAction_Run_OnCombat(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		if (Engine::IMKEY_PRESS(StageKey_Move_Forward) ||
			Engine::IMKEY_PRESS(StageKey_Move_Left) ||
			Engine::IMKEY_PRESS(StageKey_Move_Back) ||
			Engine::IMKEY_PRESS(StageKey_Move_Right))
		{
			ChangeState(Name_RunBS);
			return true;
		}
	}

	return false;
}

bool CFSM_SakuraC::CheckAction_Run_OnAction(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		if (Engine::IMKEY_PRESS(StageKey_Move_Forward) ||
			Engine::IMKEY_PRESS(StageKey_Move_Left) ||
			Engine::IMKEY_PRESS(StageKey_Move_Back) ||
			Engine::IMKEY_PRESS(StageKey_Move_Right))
		{
			ChangeState(Name_Run_StartFromZero);
			return true;
		}
	}

	return false;
}

bool CFSM_SakuraC::CheckAction_Run_End()
{
	if (!Engine::IMKEY_PRESS(StageKey_Move_Forward) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Left) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Back) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		double timeline = m_pDM->GetAniTimeline();
		if (timeline > 0.8)
		{
			ChangeState(Name_RunStopRight);
			return true;
		}
		else if (timeline > 0.55)
		{
			ChangeState(Name_RunStopLeft);
			return true;
		}
		else if (timeline > 0.05)
		{
			ChangeState(Name_RunStopRight);
			return true;
		}
		else
		{
			ChangeState(Name_RunStopLeft);
			return true;
		}
	}

	return false;
}

bool CFSM_SakuraC::CheckAction_Idle()
{
	m_idleTimer += GET_PLAYER_DT;

	if (m_idleTimer > 5.f)
	{
		ChangeState(Name_Idle);
		return true;
	}

	return false;
}

bool CFSM_SakuraC::CheckAction_RunBS_To_Run()
{
	if (m_pDM->GetAniTimeline() > Cool_End - 0.25f)
	{
		ChangeState(Name_Run);
		return true;
	}
	return false;
}

bool CFSM_SakuraC::CheckAction_WeaponSkill(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		if (Engine::IMKEY_DOWN(StageKey_WeaponSkill))
		{
			if (m_pStageControlTower->ActSkill())
			{
				ChangeState(Name_WeaponSkill);
				CStageControlTower::GetInstance()->FindTarget();
				return true;
			}
		}
	}
	return false;
}

bool CFSM_SakuraC::CheckAction_Ultra(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		if (Engine::IMKEY_DOWN(StageKey_Ult))
		{
			if (m_pStageControlTower->ActUltra())
			{
				ChangeState(Name_Ultra);
				return true;
			}
		}
	}
	return false;
}


void CFSM_SakuraC::Appear_Init(void)
{
}

void CFSM_SakuraC::Appear_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Appear);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_SakuraC::Appear_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_SakuraC::Appear_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::StandBy_Init(void)
{
	m_pDM->SetLoopAnim(Index_StandBy);
}

void CFSM_SakuraC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
	m_idleTimer = 0.f;
}

void CFSM_SakuraC::StandBy_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;
	if (CheckAction_Run_OnAction(0.f))
		return;
	if (CheckAction_Attack(Name_Attack1_StandBy, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_Idle())
		return;
}

void CFSM_SakuraC::StandBy_End(void)
{
}

void CFSM_SakuraC::Attack1_StandBy_Init(void)
{
}

void CFSM_SakuraC::Attack1_StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack1_StandBy);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	ResetCheckMembers();
	m_chargeEnterTimer = 0.f;
}

void CFSM_SakuraC::Attack1_StandBy_Update(float deltaTime)
{
	m_chargeEnterTimer += GET_PLAYER_DT;

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Atk01)
	{
		//PlaySound_Attack_RandomVoice();
		//m_pKiana->ActiveAttackBall(1.1f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);

		//PlaySound_Effect(Sound_Attack_1_Effect);
		//m_pEffectMaker->CreateEffect_Attack1();

		m_checkEffect = true;
	}

	//if (m_pDM->GetAniTimeline() > Delay_Effect_Atk01 + 0.1f)
	//	m_pKiana->UnActiveAttackBall();

	

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack2, 0.3f))
		return;
	if (CheckAction_Charge())
		return;
	if (CheckAction_Ultra(Delay_Effect_Atk01 + 0.1f))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Atk01 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack + 0.2f))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Attack1_StandBy_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	//m_pKiana->UnActiveAttackBall();
}

void CFSM_SakuraC::Attack1_Combat_Init(void)
{
}

void CFSM_SakuraC::Attack1_Combat_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack1_Combat);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	ResetCheckMembers();
	m_chargeEnterTimer = 0.f;
}

void CFSM_SakuraC::Attack1_Combat_Update(float deltaTime)
{
	m_chargeEnterTimer += GET_PLAYER_DT;

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Atk01)
	{
		//PlaySound_Attack_RandomVoice();
		//m_pKiana->ActiveAttackBall(1.1f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);

		//PlaySound_Effect(Sound_Attack_1_Effect);
		//m_pEffectMaker->CreateEffect_Attack1();

		m_checkEffect = true;
	}

	//if (m_pDM->GetAniTimeline() > Delay_Effect_Atk01 + 0.1f)
	//	m_pKiana->UnActiveAttackBall();

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack2, 0.3f))
		return;
	if (CheckAction_Charge())
		return;
	if (CheckAction_Ultra(Delay_Effect_Atk01 + 0.1f))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Atk01 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack + 0.2f))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Attack1_Combat_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	//m_pKiana->UnActiveAttackBall();
}

void CFSM_SakuraC::Attack2_Init(void)
{
	FixRootMotionOffset(Index_Attack2);
}

void CFSM_SakuraC::Attack2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack2);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();

}

void CFSM_SakuraC::Attack2_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Atk02)
	{
		m_checkEffect = true;

		//PlaySound_Attack_RandomVoice();
		//m_pKiana->ActiveAttackBall(1.2f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetLeftHandWorldMatrix(), 0.3f);

		//PlaySound_Effect(Sound_Attack_2_Effect);
		//m_pEffectMaker->CreateEffect_Attack2();
	}

// 	if (m_pDM->GetAniTimeline() > Delay_Effect_Atk02 + 0.1f)
// 		m_pKiana->UnActiveAttackBall();

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack3))
		return;
	if (CheckAction_Ultra(Delay_Effect_Atk02 + 0.1f))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Atk02 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Attack2_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	//m_pKiana->UnActiveAttackBall();
}

void CFSM_SakuraC::Attack3_Init(void)
{
	FixRootMotionOffset(Index_Attack3);
}

void CFSM_SakuraC::Attack3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack3);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
}

void CFSM_SakuraC::Attack3_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Atk03)
	{
		m_checkEffect = true;
// 
// 		PlaySound_Attack_RandomVoice();
// 		m_pKiana->ActiveAttackBall(1.3f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightHandWorldMatrix(), 0.3f);

// 		PlaySound_Effect(Sound_Attack_3_Effect);
// 		m_pEffectMaker->CreateEffect_Attack3();
	}

// 	if (m_pDM->GetAniTimeline() > Delay_Effect_Atk03 + 0.1f)
// 		m_pKiana->UnActiveAttackBall();
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack4))
		return;
	if (CheckAction_Ultra(Delay_Effect_Atk03 + 0.1f))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Atk03 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Attack3_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

// 	m_pKiana->UnActiveAttackBall();
}

void CFSM_SakuraC::Attack4_Init(void)
{
	FixRootMotionOffset(Index_Attack4);
}

void CFSM_SakuraC::Attack4_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack4);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
}

void CFSM_SakuraC::Attack4_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Atk04)
	{
		m_checkEffect = true;

// 		PlaySound_Attack_RandomVoice();
// 		PlaySound_Effect(Sound_Attack_4_Effect);
// 		m_pEffectMaker->CreateEffect_Attack4(-0.05f);
	}

// 	if (!m_checkEffectSecond && !m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Atk04 + 0.05f)
// 	{
// 		m_pKiana->ActiveAttackBall(0.9f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetLeftToeWorldMatrix(), 0.3f);
// 		m_checkAttack = true;
// 	}
// 
// 	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Atk04 + 0.1f)
// 	{
// 		m_pKiana->UnActiveAttackBall();
// 
// 		if (!m_pKiana->GetUltraMode())
// 			m_pEffectMaker->CreateEffect_Attack4(0.f);
// 		m_checkEffectSecond = true;
// 		m_checkAttack = false;
// 	}
// 
// 	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Atk04 + 0.15f)
// 	{
// 		m_pKiana->ActiveAttackBall(1.4f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
// 		m_checkAttack = true;
// 	}
// 
// 	if (m_pDM->GetAniTimeline() > Delay_Effect_Atk04 + 0.2f)
// 		m_pKiana->UnActiveAttackBall();

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack5))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Atk04 + 0.2f))
		return;
	if (CheckAction_Ultra(Delay_Effect_Atk04 + 0.2f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Attack4_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

/*	m_pKiana->UnActiveAttackBall();*/
}

void CFSM_SakuraC::Attack5_Init(void)
{
	FixRootMotionOffset(Index_Attack5);
}

void CFSM_SakuraC::Attack5_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack5);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
}

void CFSM_SakuraC::Attack5_Update(float deltaTime)
{

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Atk05)
	{
/*		m_pEffectMaker->CreateEffect_Attack5();*/
		m_checkEffect = true;
// 
// 		PlaySound_Attack_RandomVoice();
// 		m_pKiana->ActiveAttackBall(1.5f, HitInfo::Str_High, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
// 
// 		m_pEffectMaker->CreateEffect_Attack5();
// 		PlaySound_Effect(Sound_Attack_5_Effect);
	}

// 	if (m_pDM->GetAniTimeline() > Delay_Effect_Atk05 + 0.1f)
// 	{
// 		m_pKiana->UnActiveAttackBall();
// 	}
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_Attack(Name_Attack1_Combat, 0.5f))
		return;

	if (CheckAction_Combat_Timeout())
		return;

}

void CFSM_SakuraC::Attack5_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

//	m_pKiana->UnActiveAttackBall();
}

void CFSM_SakuraC::Charge1_Init(void)
{
}

void CFSM_SakuraC::Charge1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Charge1);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
}

void CFSM_SakuraC::Charge1_Update(float deltaTime)
{

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Charge1)
	{
		/*		m_pEffectMaker->CreateEffect_Attack5();*/
		m_checkEffect = true;
		// 
		// 		PlaySound_Attack_RandomVoice();
		// 		m_pKiana->ActiveAttackBall(1.5f, HitInfo::Str_High, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
		// 
		// 		m_pEffectMaker->CreateEffect_Attack5();
		// 		PlaySound_Effect(Sound_Attack_5_Effect);
	}

	// 	if (m_pDM->GetAniTimeline() > Delay_Effect_Atk05 + 0.1f)
	// 	{
	// 		m_pKiana->UnActiveAttackBall();
	// 	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack1_Combat))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Charge1))
		return;
	if (CheckAction_Ultra(Delay_Effect_Charge1))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack + 0.15f))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Charge1_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::Charge1_AS_Init(void)
{
}

void CFSM_SakuraC::Charge1_AS_Enter(void)
{
}

void CFSM_SakuraC::Charge1_AS_Update(float deltaTime)
{
}

void CFSM_SakuraC::Charge1_AS_End(void)
{
}

void CFSM_SakuraC::Charge1_Quick_Init(void)
{
}

void CFSM_SakuraC::Charge1_Quick_Enter(void)
{
}

void CFSM_SakuraC::Charge1_Quick_Update(float deltaTime)
{
}

void CFSM_SakuraC::Charge1_Quick_End(void)
{
}

void CFSM_SakuraC::Combat_Init(void)
{
}

void CFSM_SakuraC::Combat_Enter(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pDM->ChangeAniSet(Index_Combat);

	ResetCheckMembers();
	m_combatTimer = 0.f;
}

void CFSM_SakuraC::Combat_Update(float deltaTime)
{
	m_combatTimer += GET_PLAYER_DT;
	if (m_combatTimer > 3.f)
	{
		ChangeState(Name_CombatToStandBy);
		return;
	}

	if (CheckAction_EvadeBackward(0.f))
		return;
	if (CheckAction_Run_OnCombat(0.f))
		return;
	if (CheckAction_Attack(Name_Attack1_Combat, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
}

void CFSM_SakuraC::Combat_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::CombatToStandBy_Init(void)
{
}

void CFSM_SakuraC::CombatToStandBy_Enter(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pDM->ChangeAniSet(Index_CombatToStandBy);

	ResetCheckMembers();
}

void CFSM_SakuraC::CombatToStandBy_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;
	if (CheckAction_Attack(Name_Attack1_Combat))
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_Run_OnAction())
		return;
	if (CheckAction_StandBy_Timeout(0.9f))
		return;
}

void CFSM_SakuraC::CombatToStandBy_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::Die_Init(void)
{
}

void CFSM_SakuraC::Die_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die);
}

void CFSM_SakuraC::Die_Update(float deltaTime)
{
}

void CFSM_SakuraC::Die_End(void)
{
}

void CFSM_SakuraC::Run_Init(void)
{
	m_pDM->SetLoopAnim(Index_Run);
}

void CFSM_SakuraC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);
}

void CFSM_SakuraC::Run_Update(float deltaTime)
{
	m_runSoundTimer += GET_PLAYER_DT;
	if (m_runSoundTimer > 0.3f)
	{
		m_runSoundTimer = 0.f;
		//PlaySound_Attack_RandomRun();
	}

	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_Run_End())
		return;
	if (CheckAction_Attack(Name_Attack1_StandBy, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
}

void CFSM_SakuraC::Run_End(void)
{
	m_runSoundTimer = 0.f;
}

void CFSM_SakuraC::Run_StartFromZero_Init(void)
{
	m_pDM->SetLoopAnim(Index_Run_StartFromZero);
}

void CFSM_SakuraC::Run_StartFromZero_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run_StartFromZero);
}

void CFSM_SakuraC::Run_StartFromZero_Update(float deltaTime)
{
	m_runSoundTimer += GET_PLAYER_DT;
	if (m_runSoundTimer > 0.3f)
	{
		m_runSoundTimer = 0.f;
		//PlaySound_Attack_RandomRun();
	}

	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_Run_End())
		return;
	if (CheckAction_Attack(Name_Attack1_StandBy, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
}

void CFSM_SakuraC::Run_StartFromZero_End(void)
{
	m_runSoundTimer = 0.f;
}

void CFSM_SakuraC::RunBS_Init(void)
{
}

void CFSM_SakuraC::RunBS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunBS);
}

void CFSM_SakuraC::RunBS_Update(float deltaTime)
{
	//m_runSoundTimer += GET_DT;
	//if (m_runSoundTimer > 0.3f)
	//{
	//	m_runSoundTimer = 0.f;
	//	PlaySound_Attack_RandomRun();
	//}


	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_RunBS_To_Run())
		return;
 	if (CheckAction_Attack(Name_Attack1_Combat, 0.f))
 		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_Run_End())
		return;
}

void CFSM_SakuraC::RunBS_End(void)
{
}

void CFSM_SakuraC::RunStopLeft_Init(void)
{
}

void CFSM_SakuraC::RunStopLeft_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopLeft);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_SakuraC::RunStopLeft_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(0.f))
		return;
	if (CheckAction_Run_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack1_StandBy, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_SakuraC::RunStopLeft_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::RunStopRight_Init(void)
{
}

void CFSM_SakuraC::RunStopRight_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopRight);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_SakuraC::RunStopRight_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(0.f))
		return;
	if (CheckAction_Run_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack1_StandBy, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_SakuraC::RunStopRight_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::StandBy_Back_Init(void)
{
	m_pDM->SetLoopAnim(Index_StandBy_Back);
}

void CFSM_SakuraC::StandBy_Back_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy_Back);
}

void CFSM_SakuraC::StandBy_Back_Update(float deltaTime)
{
}

void CFSM_SakuraC::StandBy_Back_End(void)
{
}

void CFSM_SakuraC::Stun_Init(void)
{
}

void CFSM_SakuraC::Stun_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Stun);
}

void CFSM_SakuraC::Stun_Update(float deltaTime)
{
}

void CFSM_SakuraC::Stun_End(void)
{
}

void CFSM_SakuraC::EvadeForward_Init(void)
{
}

void CFSM_SakuraC::EvadeForward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_EvadeForward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	//PlaySound_Attack_RandomEvade();

	m_isEvade = true;
	m_pSakura->SetIsEvade(true);
}

void CFSM_SakuraC::EvadeForward_Update(float deltaTime)
{
	if (m_isEvade&& m_pDM->GetAniTimeline() > 0.3)
	{
		m_isEvade = false;
		m_pSakura->SetIsEvade(false);
	}

	if (!m_isSecondEvade && CheckAction_Evade_OnAction(Cool_Evade + 0.1f))
	{
		m_isSecondEvade = true;
		return;
	}
	if (CheckAction_Attack(Name_Attack1_Combat, 0.5f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Run_OnCombat(0.5f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Combat_Timeout())
	{
		m_isSecondEvade = false;
		return;
	}
}

void CFSM_SakuraC::EvadeForward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_isEvade = false;
	m_pSakura->SetIsEvade(false);
}

void CFSM_SakuraC::EvadeBackward_Init(void)
{
}

void CFSM_SakuraC::EvadeBackward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_EvadeBackward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	//PlaySound_Attack_RandomEvade();

	m_isEvade = true;
	m_pSakura->SetIsEvade(true);
}

void CFSM_SakuraC::EvadeBackward_Update(float deltaTime)
{
	if (m_isEvade && m_pDM->GetAniTimeline() > 0.3)
	{
		m_isEvade = false;
		m_pSakura->SetIsEvade(false);
	}

	if (!m_isSecondEvade && CheckAction_Evade_OnAction(Cool_Evade + 0.1f))
	{
		m_isSecondEvade = true;
		return;
	}
	if (CheckAction_Attack(Name_Attack1_Combat, 0.6f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Run_OnCombat(0.6f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Combat_Timeout())
	{
		m_isSecondEvade = false;
		return;
	}
}


void CFSM_SakuraC::EvadeBackward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_isEvade = false;
	m_pSakura->SetIsEvade(false);
}

void CFSM_SakuraC::Failure_Init(void)
{
}

void CFSM_SakuraC::Failure_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Failure);
}

void CFSM_SakuraC::Failure_Update(float deltaTime)
{
	if (m_pDM->IsAnimationEnd())
	{
		ChangeState(Name_Failure_Idle);
		return;
	}
}

void CFSM_SakuraC::Failure_End(void)
{
}

void CFSM_SakuraC::Failure_Idle_Init(void)
{
	m_pDM->SetLoopAnim(Index_Failure_Idle);
}

void CFSM_SakuraC::Failure_Idle_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Failure_Idle);
}

void CFSM_SakuraC::Failure_Idle_Update(float deltaTime)
{
}

void CFSM_SakuraC::Failure_Idle_End(void)
{
}

void CFSM_SakuraC::Hit_H_Init(void)
{
}

void CFSM_SakuraC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	//PlaySound_Attack_RandomHit();
}

void CFSM_SakuraC::Hit_H_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Hit_H_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::Hit_L_Init(void)
{
}

void CFSM_SakuraC::Hit_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_SakuraC::Hit_L_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty - 0.2f))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::Hit_L_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::Idle_Init(void)
{
	FixRootMotionOffset(Index_Idle);
}

void CFSM_SakuraC::Idle_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle);
}

void CFSM_SakuraC::Idle_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;
	if (CheckAction_Run_OnAction(0.f))
		return;
	if (CheckAction_Attack(Name_Attack1_StandBy, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_StandBy_Timeout(0.8f))
		return;
}

void CFSM_SakuraC::Idle_End(void)
{
}

void CFSM_SakuraC::SwitchIn_Init(void)
{
}

void CFSM_SakuraC::SwitchIn_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SwitchIn);
}

void CFSM_SakuraC::SwitchIn_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_SakuraC::SwitchIn_End(void)
{
	CStageControlTower::GetInstance()->EndSwitching();
}

void CFSM_SakuraC::SwitchOut_Init(void)
{
}

void CFSM_SakuraC::SwitchOut_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SwitchOut);
}

void CFSM_SakuraC::SwitchOut_Update(float deltaTime)
{
	if (m_pDM->GetAniTimeline() > 0.75)
	{
		m_pSakura->SetIsEnabled(false);
		return;
	}
}

void CFSM_SakuraC::SwitchOut_End(void)
{
}

void CFSM_SakuraC::TurnAround_Init(void)
{
}

void CFSM_SakuraC::TurnAround_Enter(void)
{
}

void CFSM_SakuraC::TurnAround_Update(float deltaTime)
{
}

void CFSM_SakuraC::TurnAround_End(void)
{
}

void CFSM_SakuraC::Ultra_Init(void)
{
}

void CFSM_SakuraC::Ultra_Enter(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pDM->ChangeAniSet(Index_Ultra);

	//PlaySound_Voice(Sound_Ult_Start_Voice);
	//PlaySound_Effect(Sound_Ult_Start);
	//m_pEffectMaker->CreateEffect_Ultra();
}

void CFSM_SakuraC::Ultra_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout(0.9f))
		return;
}

void CFSM_SakuraC::Ultra_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::Victory_Init(void)
{
}

void CFSM_SakuraC::Victory_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Victory);
}

void CFSM_SakuraC::Victory_Update(float deltaTime)
{
	if (m_pDM->IsAnimationEnd())
	{
		ChangeState(Name_Victory_Idle);
		return;
	}
}

void CFSM_SakuraC::Victory_End(void)
{
}

void CFSM_SakuraC::Victory_Idle_Init(void)
{
	m_pDM->SetLoopAnim(Index_Victory_Idle);
}

void CFSM_SakuraC::Victory_Idle_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Victory_Idle);
}

void CFSM_SakuraC::Victory_Idle_Update(float deltaTime)
{
}

void CFSM_SakuraC::Victory_Idle_End(void)
{
}

void CFSM_SakuraC::WeaponSkill_Init(void)
{
}

void CFSM_SakuraC::WeaponSkill_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ultra);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->LookTarget();
	ResetCheckMembers();
}

void CFSM_SakuraC::WeaponSkill_Update(float deltaTime)
{
	if (!m_checkAttack && m_pDM->GetAniTimeline() > 0.3f)
	{
		//PlaySound_Effect(Sound_Attack_2_Effect);

		m_checkAttack = true;
	}


	if (CheckAction_Evade_OnAction(0.4f))
		return;
	if (CheckAction_Run_OnCombat(0.4f))
		return;
	if (CheckAction_Attack(Name_Attack1_Combat, 0.4f))
		return;
	if (CheckAction_Combat_Timeout())
		return;
}

void CFSM_SakuraC::WeaponSkill_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::RegisterAllState()
{
	Engine::CState* pState;

	CreateState(CFSM_SakuraC, pState, Appear)
		AddState(pState, Name_Appear);

	CreateState(CFSM_SakuraC, pState, StandBy)
		AddState(pState, Name_StandBy);

	CreateState(CFSM_SakuraC, pState, Attack1_StandBy)
		AddState(pState, Name_Attack1_StandBy);

	CreateState(CFSM_SakuraC, pState, Attack1_Combat)
		AddState(pState, Name_Attack1_Combat);

	CreateState(CFSM_SakuraC, pState, Attack2)
		AddState(pState, Name_Attack2);

	CreateState(CFSM_SakuraC, pState, Attack3)
		AddState(pState, Name_Attack3);

	CreateState(CFSM_SakuraC, pState, Attack4)
		AddState(pState, Name_Attack4);

	CreateState(CFSM_SakuraC, pState, Attack5)
		AddState(pState, Name_Attack5);

	CreateState(CFSM_SakuraC, pState, Charge1)
		AddState(pState, Name_Charge1);

	CreateState(CFSM_SakuraC, pState, Charge1_AS)
		AddState(pState, Name_Charge1_AS);

	CreateState(CFSM_SakuraC, pState, Charge1_Quick)
		AddState(pState, Name_Charge1_Quick);

	CreateState(CFSM_SakuraC, pState, Combat)
		AddState(pState, Name_Combat);

	CreateState(CFSM_SakuraC, pState, CombatToStandBy)
		AddState(pState, Name_CombatToStandBy);

	CreateState(CFSM_SakuraC, pState, Die)
		AddState(pState, Name_Die);

	CreateState(CFSM_SakuraC, pState, EvadeForward)
		AddState(pState, Name_EvadeForward);

	CreateState(CFSM_SakuraC, pState, EvadeBackward)
		AddState(pState, Name_EvadeBackward);

	CreateState(CFSM_SakuraC, pState, Failure)
		AddState(pState, Name_Failure);

	CreateState(CFSM_SakuraC, pState, Failure_Idle)
		AddState(pState, Name_Failure_Idle);

	CreateState(CFSM_SakuraC, pState, Hit_H)
		AddState(pState, Name_Hit_H);

	CreateState(CFSM_SakuraC, pState, Hit_L)
		AddState(pState, Name_Hit_L);

	CreateState(CFSM_SakuraC, pState, Idle)
		AddState(pState, Name_Idle);

	CreateState(CFSM_SakuraC, pState, Run)
		AddState(pState, Name_Run);

	CreateState(CFSM_SakuraC, pState, Run_StartFromZero)
		AddState(pState, Name_Run_StartFromZero);

	CreateState(CFSM_SakuraC, pState, RunBS)
		AddState(pState, Name_RunBS);

	CreateState(CFSM_SakuraC, pState, RunStopLeft)
		AddState(pState, Name_RunStopLeft);

	CreateState(CFSM_SakuraC, pState, RunStopRight)
		AddState(pState, Name_RunStopRight);

	CreateState(CFSM_SakuraC, pState, StandBy_Back)
		AddState(pState, Name_StandBy_Back);

	CreateState(CFSM_SakuraC, pState, Stun)
		AddState(pState, Name_Stun);
	
	CreateState(CFSM_SakuraC, pState, SwitchIn)
		AddState(pState, Name_SwitchIn);

	CreateState(CFSM_SakuraC, pState, SwitchOut)
		AddState(pState, Name_SwitchOut);

	CreateState(CFSM_SakuraC, pState, TurnAround)
		AddState(pState, Name_TurnAround);

	CreateState(CFSM_SakuraC, pState, Ultra)
		AddState(pState, Name_Ultra);

	CreateState(CFSM_SakuraC, pState, Victory)
		AddState(pState, Name_Victory);

	CreateState(CFSM_SakuraC, pState, Victory_Idle)
		AddState(pState, Name_Victory_Idle);

	CreateState(CFSM_SakuraC, pState, WeaponSkill)
		AddState(pState, Name_WeaponSkill);

}