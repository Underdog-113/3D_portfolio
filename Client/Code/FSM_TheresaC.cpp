#include "stdafx.h"
#include "FSM_TheresaC.h"

#include "SoundManager.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "Theresa.h"
#include "State.h"
#include "FSMDefine_Theresa.h"
#include "AttackBall.h"
#include "AttackBox.h"

#include "AttackTrail_Client.h"
#include "StageControlTower.h"
#include "EffectMaker_Theresa.h"

CFSM_TheresaC::CFSM_TheresaC()
{
}

CFSM_TheresaC::~CFSM_TheresaC()
{
	OnDestroy();
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
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pTheresa->GetComponent<Engine::CMeshC>()->GetMeshData());
	m_pEffectMaker = new CEffectMaker_Theresa(m_pTheresa);

	__super::Start(spThis);

	RegisterAllState();

	m_pStageControlTower = CStageControlTower::GetInstance();

	SetStartState(Name_Appear);
	m_curState->DoEnter();
}

void CFSM_TheresaC::OnDestroy()
{
	__super::OnDestroy();
	delete m_pEffectMaker;
}

void CFSM_TheresaC::FixRootMotionOffset(_uint index)
{
	m_pTheresa->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_TheresaC::ResetCheckMembers()
{
	m_checkEffect = false;
	m_checkEffectSecond = false;
}

void CFSM_TheresaC::OnSwordCollider()
{
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_LeftHand(), 1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pTheresa->GetLeftHandWorldMatrix(), 0.1f, _float3(0.f, 0.5f, 0.f));
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_RightHand(), 1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pTheresa->GetRightHandWorldMatrix(), 0.1f, _float3(0.f, 0.5f, 0.f));
}

void CFSM_TheresaC::OffSwordCollider()
{
	m_pTheresa->GetAttackBall_LeftHand()->SetIsEnabled(false);
	m_pTheresa->GetAttackBall_RightHand()->SetIsEnabled(false);
}

void CFSM_TheresaC::OnAxeCollider()
{
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_Axe(), 1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 0.2f, _float3(2.f, 0.f, 0.f));
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_AxeStick(), 1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 0.2f, _float3(1.f, 0.f, 0.f));
}

void CFSM_TheresaC::OffAxeCollider()
{
	m_pTheresa->GetAttackBall_Axe()->SetIsEnabled(false);
	m_pTheresa->GetAttackBall_AxeStick()->SetIsEnabled(false);
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
		ChangeState(Name_StandBy);
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
			ChangeState(Name_RunStopLeft);
			return true;
		}
		else if (timeline > 0.55)
		{
			ChangeState(Name_RunStopRight);
			return true;
		}
		else if (timeline > 0.30)
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

bool CFSM_TheresaC::CheckAction_StandBy()
{
	if (!Engine::IMKEY_PRESS(StageKey_Move_Forward) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Left) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Back) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		ChangeState(Name_StandBy);
		return true;
	}

	return false;
}

bool CFSM_TheresaC::CheckAction_RunBS_To_Run()
{
	if (m_pDM->GetAniTimeline() > Cool_End - 0.15f)
	{
		ChangeState(Name_Run);
		return true;
	}
	return false;
}

bool CFSM_TheresaC::CheckAction_Ultra()
{
	if (Engine::IMKEY_DOWN(StageKey_Ult))
	{
		auto pStat = m_pTheresa->GetStat();
		if (pStat->GetCurSp() < pStat->GetUltraCost())
			return false;

		ChangeState(Name_Ultra);
		return true;
	}
	return false;
}

bool CFSM_TheresaC::CheckAction_ChargeAttack()
{
	if (Engine::IMKEY_DOWN(StageKey_Attack))
	{
		if (m_pDM->GetAniTimeline() > Cool_ChargeAttack)
		{
			switch (m_chargeAttackIndex)
			{
			case 1:
				ChangeState(Name_Charge1);
				CStageControlTower::GetInstance()->FindTarget();
				m_chargeAttackIndex = 2;
				return true;
			case 2:
				ChangeState(Name_Charge2);
				CStageControlTower::GetInstance()->FindTarget();
				m_chargeAttackIndex = 1;
				return true;
			}
		}
	}
	return false;
}

bool CFSM_TheresaC::CheckAction_ChargeAttack_End()
{
	if (m_pDM->GetAniTimeline() > Cool_End)
	{
		ChangeState(Name_StandBy);
		return true;
	}
	return false;
}

bool CFSM_TheresaC::CheckAction_ChargeMode()
{
	m_chargeEnterTimer += GET_DT;
	if (Engine::IMKEY_PRESS(StageKey_Attack))
	{
		if (m_chargeEnterTimer > 0.5f)
		{
			ChangeState(Name_Charge0);
			return true;
		}
	}
	else
	{
		m_chargeEnterTimer = 0.f;
	}
	return false;
}

void CFSM_TheresaC::PlayActionSound(const std::wstring & soundName, Engine::EChannelID channel)
{
	TCHAR* name = (TCHAR*)soundName.c_str();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)channel);
	Engine::CSoundManager::GetInstance()->StartSound(name, (_uint)channel);
}

void CFSM_TheresaC::PlaySound_Voice(const std::wstring & soundName)
{
	TCHAR* name = (TCHAR*)soundName.c_str();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::PLAYER);
	Engine::CSoundManager::GetInstance()->StartSound(name, (_uint)Engine::EChannelID::PLAYER);
}

void CFSM_TheresaC::PlaySound_Effect(const std::wstring & soundName)
{
	TCHAR* name = (TCHAR*)soundName.c_str();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::PLAYEREFFECT);
	Engine::CSoundManager::GetInstance()->StartSound(name, (_uint)Engine::EChannelID::PLAYEREFFECT);
}

void CFSM_TheresaC::PlaySound_Charge_RandomVoice()
{
	_uint idx = rand() % 3;
	if (m_prevChargeVoiceSoundIndex == idx)
		idx = (m_prevChargeVoiceSoundIndex + 1) % 3;

	switch (idx)
	{
	case 0:
		PlaySound_Voice(Sound_Charge_Voice0);
		break;
	case 1:
		PlaySound_Voice(Sound_Charge_Voice1);
		break;
	case 2:
		PlaySound_Voice(Sound_Charge_Voice2);
		break;
	}

	m_prevChargeVoiceSoundIndex = idx;
}

void CFSM_TheresaC::PlaySound_Attack_RandomRun()
{
	_uint idx = rand() % 5;
	if (m_prevRunSoundIndex == idx)
		idx = (m_prevRunSoundIndex + 1) % 5;

	switch (idx)
	{
	case 0:
		PlaySound_Effect(Sound_RUN_0);
		break;
	case 1:
		PlaySound_Effect(Sound_RUN_1);
		break;
	case 2:
		PlaySound_Effect(Sound_RUN_2);
		break;
	case 3:
		PlaySound_Effect(Sound_RUN_3);
		break;
	case 4:
		PlaySound_Effect(Sound_RUN_4);
		break;
	default:
		break;
	}

	m_prevRunSoundIndex = idx;
}

void CFSM_TheresaC::StandBy_Init(void)
{
	m_pDM->SetLoopAnim(Index_StandBy);
}

void CFSM_TheresaC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
	m_pTheresa->Off_Sword();

	m_pTheresa->Off_Axe();

	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::StandBy_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;

	if (CheckAction_Run())
		return;

	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;

	if (CheckAction_Ultra())
		return;
}

void CFSM_TheresaC::StandBy_End(void)
{
}

void CFSM_TheresaC::Idle_Init(void)
{
}

void CFSM_TheresaC::Idle_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
}

void CFSM_TheresaC::Idle_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;

	if (CheckAction_Run())
		return;

	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;

	if (CheckAction_Ultra())
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Idle_End(void)
{
}

void CFSM_TheresaC::Appear_Init(void)
{
}

void CFSM_TheresaC::Appear_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle);
	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();
}

void CFSM_TheresaC::Appear_Update(float deltaTime)
{
// 	if (m_pDM->GetAniCtrl()->IsItEnd())
// 	{
// 		switch (m_appearOption)
// 		{
// 		case CFSM_TheresaC::None:
// 			ChangeState(Name_StandBy);
// 			break;
// 		case CFSM_TheresaC::QTE:
// 			//ChangeState(Name_QTE_FY);
// 			break;
// 		default:
// 			break;
// 		}
// 		return;
// 	}


	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Appear_End(void)
{
	m_appearOption = None;
}

void CFSM_TheresaC::Run_Init(void)
{
	m_pDM->SetLoopAnim(Index_Run);
}

void CFSM_TheresaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);

	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();
	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::Run_Update(float deltaTime)
{
	m_runSoundTimer += GET_DT;
	if (m_runSoundTimer > 0.3f)
	{
		m_runSoundTimer = 0.f;
		PlaySound_Attack_RandomRun();
	}


	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_Run_End())
		return;
	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_TheresaC::Run_End(void)
{
	m_runSoundTimer = 0.f;
}

void CFSM_TheresaC::RunBS_Init(void)
{
}

void CFSM_TheresaC::RunBS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunBS);	
	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::RunBS_Update(float deltaTime)
{
	m_runSoundTimer += GET_DT;
	if (m_runSoundTimer > 0.3f)
	{
		m_runSoundTimer = 0.f;
		PlaySound_Attack_RandomRun();
	}

	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_RunBS_To_Run())
		return;
	if (CheckAction_Run_End())
		return;
	if (CheckAction_StandBy())
		return;
	if (CheckAction_Attack(Name_Attack1, 0.f))
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
	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();

	PlaySound_Effect(Sound_Evade);

	m_isEvade = true;
	m_pTheresa->OffHitbox();
}

void CFSM_TheresaC::EvadeBackward_Update(float deltaTime)
{
	if (m_isEvade && m_pDM->GetAniTimeline() > 0.3)
	{
		m_pTheresa->OnHitbox();
		m_isEvade = false;
	}

	if (!m_isSecondEvade && CheckAction_Evade_OnAction(Cool_Evade + 0.1f))
	{
		m_isSecondEvade = true;
		return;
	}
	if (CheckAction_Attack(Name_Attack1, 0.4f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Run_OnAction(0.5f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_StandBy_Timeout())
	{
		m_isSecondEvade = false;
		return;
	}
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

	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();
	
	PlaySound_Effect(Sound_Evade);

	m_isEvade = true;
	m_pTheresa->OffHitbox();
}

void CFSM_TheresaC::EvadeForward_Update(float deltaTime)
{
	if (m_isEvade&& m_pDM->GetAniTimeline() > 0.3)
	{
		m_pTheresa->OnHitbox();
		m_isEvade = false;
	}

	if (!m_isSecondEvade && CheckAction_Evade_OnAction(Cool_Evade + 0.1f))
	{
		m_isSecondEvade = true;
		return;
	}
	if (CheckAction_Attack(Name_Attack1, 0.4f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Run_OnAction(0.5f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_StandBy_Timeout())
	{
		m_isSecondEvade = false;
		return;
	}
}

void CFSM_TheresaC::EvadeForward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_TheresaC::Attack1_Init(void)
{
}

void CFSM_TheresaC::Attack1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack1);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	ResetCheckMembers();

	m_chargeEnterTimer = 0.f;

	m_pTheresa->On_Sword();
	OnSwordCollider();
}

void CFSM_TheresaC::Attack1_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Attack1_1)
	{
		m_pEffectMaker->CreateEffect_Attack1_1();
		PlaySound_Effect(Sound_Attack1_Effect);
		PlaySound_Voice(Sound_Attack1_Voice);

		m_checkEffect = true;
	}
	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Attack1_2)
	{
		m_pEffectMaker->CreateEffect_Attack1_2();

		m_checkEffectSecond = true;
	}

	if (CheckAction_ChargeMode())
		return;

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack2, 0.25f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack1_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	OffSwordCollider();
}

void CFSM_TheresaC::Attack2_Init(void)
{
	FixRootMotionOffset(Index_Attack2);
}

void CFSM_TheresaC::Attack2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack2);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
	m_chargeEnterTimer = 0.f;

	OnSwordCollider();

	m_pEffectMaker->CreateEffect_Attack2_1();
}

void CFSM_TheresaC::Attack2_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Attack2_1)
	{
		m_pEffectMaker->CreateEffect_Attack2_1();
		PlaySound_Effect(Sound_Attack2_Effect);
		PlaySound_Voice(Sound_Attack2_Voice);

		m_checkEffect = true;
	}
	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Attack2_2)
	{
		m_pEffectMaker->CreateEffect_Attack2_2();

		m_checkEffectSecond = true;
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_ChargeMode())
		return;
	if (CheckAction_Attack(Name_Attack3))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack2_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	OffSwordCollider();
}

void CFSM_TheresaC::Attack3_Init(void)
{
	FixRootMotionOffset(Index_Attack3);
}

void CFSM_TheresaC::Attack3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack3);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();

	m_chargeEnterTimer = 0.f;

	OnSwordCollider();
}

void CFSM_TheresaC::Attack3_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Attack3_1)
	{
		m_pEffectMaker->CreateEffect_Attack3_1();
		PlaySound_Effect(Sound_Attack3_Effect);
		PlaySound_Voice(Sound_Attack3_Voice);

		m_checkEffect = true;
	}
	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Attack3_2)
	{
		m_pEffectMaker->CreateEffect_Attack3_2();

		m_checkEffectSecond = true;
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_ChargeMode())
		return;
	if (CheckAction_Attack(Name_Attack4))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack3_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	OffSwordCollider();
}

void CFSM_TheresaC::Attack4_Init(void)
{
	FixRootMotionOffset(Index_Attack4);
}

void CFSM_TheresaC::Attack4_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack4);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();

	m_chargeEnterTimer = 0.f;

	OnSwordCollider();
}

void CFSM_TheresaC::Attack4_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Attack4_1)
	{
		m_pEffectMaker->CreateEffect_Attack4_1();
		PlaySound_Effect(Sound_Attack4_Effect);
		PlaySound_Voice(Sound_Attack4_Voice);

		m_checkEffect = true;
	}
	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Attack4_2)
	{
		m_pEffectMaker->CreateEffect_Attack4_2();

		m_checkEffectSecond = true;
	}

	if (CheckAction_ChargeMode())
		return;

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack4_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	OffSwordCollider();
}

void CFSM_TheresaC::Charge0_Init(void)
{
	FixRootMotionOffset(Index_Charge0);
}

void CFSM_TheresaC::Charge0_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Charge0);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();

	m_pTheresa->Off_Sword();
	m_pTheresa->On_Axe();
	m_chargeEnterTimer = 0.f;

	OnAxeCollider();

	PlaySound_Effect(Sound_Charge0_Effect);
}

void CFSM_TheresaC::Charge0_Update(float deltaTime)
{
	if (m_pDM->GetAniTimeline() > 0.8f)
	{
		ChangeState(Name_Charge1);
		return;
	}

	if (CheckAction_Evade_OnAction())
		return;
}

void CFSM_TheresaC::Charge0_End(void)
{
	m_pTheresa->Off_Axe();
	OffAxeCollider();
}

void CFSM_TheresaC::Charge1_Init(void)
{
	FixRootMotionOffset(Index_Charge1);
}

void CFSM_TheresaC::Charge1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Charge1);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_chargeAttackIndex = 2;

	m_pTheresa->On_Axe();
	OnAxeCollider();

	PlaySound_Effect(Sound_Charge1_Effect);
	PlaySound_Charge_RandomVoice();
}

void CFSM_TheresaC::Charge1_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_ChargeAttack())
		return;
	if (CheckAction_ChargeAttack_End())
		return;
}

void CFSM_TheresaC::Charge1_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_pTheresa->Off_Axe();
	OffAxeCollider();
}

void CFSM_TheresaC::Charge2_Init(void)
{
	FixRootMotionOffset(Index_Charge2);
}

void CFSM_TheresaC::Charge2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Charge2);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_chargeAttackIndex = 1;

	m_pTheresa->On_Axe();
	OnAxeCollider();

	PlaySound_Effect(Sound_Charge2_Effect);
	PlaySound_Charge_RandomVoice();
}

void CFSM_TheresaC::Charge2_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_ChargeAttack())
		return;
	if (CheckAction_ChargeAttack_End())
		return;
}

void CFSM_TheresaC::Charge2_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_pTheresa->Off_Axe();
	OffAxeCollider();
}

void CFSM_TheresaC::Victory_Init(void)
{
}

void CFSM_TheresaC::Victory_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Victory);
}

void CFSM_TheresaC::Victory_Update(float deltaTime)
{
	if (m_pDM->IsAnimationEnd())
	{
		ChangeState(Name_Victory_Idle);
		return;
	}
}

void CFSM_TheresaC::Victory_End(void)
{
}

void CFSM_TheresaC::Victory_Idle_Init(void)
{
	m_pDM->SetLoopAnim(Index_Victory_Idle);
}

void CFSM_TheresaC::Victory_Idle_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Victory_Idle);
}

void CFSM_TheresaC::Victory_Idle_Update(float deltaTime)
{
}

void CFSM_TheresaC::Victory_Idle_End(void)
{
}

void CFSM_TheresaC::Die_Init(void)
{
}

void CFSM_TheresaC::Die_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die);
	m_pDM->GetAniCtrl()->SetReplay(false);
}

void CFSM_TheresaC::Die_Update(float deltaTime)
{
	if (m_pDM->IsAnimationEnd())
	{
		//m_pTheresa->
	}
}

void CFSM_TheresaC::Die_End(void)
{
}

void CFSM_TheresaC::Stun_Init(void)
{
	m_pDM->SetLoopAnim(Index_Stun);
}

void CFSM_TheresaC::Stun_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Stun);
	m_stunTimer = 0.f;
}

void CFSM_TheresaC::Stun_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Stun_End(void)
{
}

void CFSM_TheresaC::SwitchIn_Init(void)
{
}

void CFSM_TheresaC::SwitchIn_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SwitchIn);
}

void CFSM_TheresaC::SwitchIn_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::SwitchIn_End(void)
{
}

void CFSM_TheresaC::SwitchOut_Init(void)
{
}

void CFSM_TheresaC::SwitchOut_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SwitchOut);
}

void CFSM_TheresaC::SwitchOut_Update(float deltaTime)
{
	if (m_pDM->GetAniTimeline() > 0.6)
	{
		m_pTheresa->SetIsEnabled(false);
		return;
	}
}

void CFSM_TheresaC::SwitchOut_End(void)
{
}

void CFSM_TheresaC::Ultra_Init(void)
{

}

void CFSM_TheresaC::Ultra_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Ultra);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();

	m_pTheresa->Off_Sword();
	m_ultraAxeOnOff = false;
	m_ultraImpact = false;

	m_pEffectMaker->CreateEffect_Ultra_Charge();
	m_pDM->GetAniCtrl()->SetSpeed(0.8f);

	PlaySound_Voice(Sound_Ult_Voice);
	PlaySound_Effect(Sound_Ult);
}

void CFSM_TheresaC::Ultra_Update(float deltaTime)
{
	if (!m_ultraAxeOnOff && m_pDM->GetAniTimeline() > Delay_UltShowAxe)
	{
		m_pDM->GetAniCtrl()->SetSpeed(1.f);
		m_pTheresa->On_Axe();
		OnAxeCollider();
		m_ultraAxeOnOff = true;

		m_pEffectMaker->CreateEffect_Ultra_Trail();
		m_pEffectMaker->CreateEffect_Ultra_Smoke();
	}

	if (!m_ultraImpact && m_pDM->GetAniTimeline() > 0.605f)
	{
		OffAxeCollider();
		m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_AxeImpact(), 3.f, HitInfo::Str_High, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 1.f, _float3(2.f, 0.f, 0.f));
		m_pEffectMaker->CreateEffect_Ultra_Bomb();
		m_ultraImpact = true;
	}

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Ultra_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_ultraUsed = true;
	m_pTheresa->GetAttackBall_AxeImpact()->SetIsEnabled(false);
}

void CFSM_TheresaC::CastCross_Init(void)
{
}

void CFSM_TheresaC::CastCross_Enter(void)
{
	m_pDM->ChangeAniSet(Index_CastCross);
}

void CFSM_TheresaC::CastCross_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::CastCross_End(void)
{
}

void CFSM_TheresaC::RunStopRight_Init(void)
{
}

void CFSM_TheresaC::RunStopRight_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopRight);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::RunStopRight_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Evade_OnAction(0.1f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_TheresaC::RunStopRight_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_TheresaC::RunStopLeft_Init(void)
{
}

void CFSM_TheresaC::RunStopLeft_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopLeft);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::RunStopLeft_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Evade_OnAction(0.1f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_TheresaC::RunStopLeft_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}
// 
// void CFSM_TheresaC::FASTRun_Init(void)
// {
// }
// 
// void CFSM_TheresaC::FASTRun_Enter(void)
// {
// }
// 
// void CFSM_TheresaC::FASTRun_Update(float deltaTime)
// {
// }
// 
// void CFSM_TheresaC::FASTRun_End(void)
// {
// }

void CFSM_TheresaC::Hit_H_Init(void)
{
}

void CFSM_TheresaC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H);

	PlaySound_Effect(Sound_HIT_Effect);
	PlaySound_Effect(Sound_HIT_Voice);
}

void CFSM_TheresaC::Hit_H_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Hit_H_End(void)
{
}

void CFSM_TheresaC::Hit_L_Init(void)
{
}

void CFSM_TheresaC::Hit_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L);

	PlaySound_Effect(Sound_HIT_Effect);
	PlaySound_Effect(Sound_HIT_Voice);
}

void CFSM_TheresaC::Hit_L_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty - 0.2f))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Hit_L_End(void)
{
}

void CFSM_TheresaC::RegisterAllState()
{
	Engine::CState* pState;

	CreateState(CFSM_TheresaC, pState, StandBy)
		AddState(pState, Name_StandBy);

	CreateState(CFSM_TheresaC, pState, Idle)
		AddState(pState, Name_Idle);

	CreateState(CFSM_TheresaC, pState, RunBS)
		AddState(pState, Name_RunBS);

	CreateState(CFSM_TheresaC, pState, EvadeBackward)
		AddState(pState, Name_EvadeBackward);

	CreateState(CFSM_TheresaC, pState, EvadeForward)
		AddState(pState, Name_EvadeForward);

	CreateState(CFSM_TheresaC, pState, Appear)
		AddState(pState, Name_Appear);

	CreateState(CFSM_TheresaC, pState, Run)
		AddState(pState, Name_Run);

// 	CreateState(CFSM_TheresaC, pState, FASTRun)
// 		AddState(pState, Name_FASTRun);

	CreateState(CFSM_TheresaC, pState, RunStopLeft)
		AddState(pState, Name_RunStopLeft);

	CreateState(CFSM_TheresaC, pState, RunStopRight)
		AddState(pState, Name_RunStopRight);

	CreateState(CFSM_TheresaC, pState, Attack1)
		AddState(pState, Name_Attack1);

	CreateState(CFSM_TheresaC, pState, Attack2)
		AddState(pState, Name_Attack2);

	CreateState(CFSM_TheresaC, pState, Attack3)
		AddState(pState, Name_Attack3);

	CreateState(CFSM_TheresaC, pState, Attack4)
		AddState(pState, Name_Attack4);

	CreateState(CFSM_TheresaC, pState, Charge0)
		AddState(pState, Name_Charge0);

	CreateState(CFSM_TheresaC, pState, Charge1)
		AddState(pState, Name_Charge1);

	CreateState(CFSM_TheresaC, pState, Charge2)
		AddState(pState, Name_Charge2);

	CreateState(CFSM_TheresaC, pState, CastCross)
		AddState(pState, Name_CastCross);

	CreateState(CFSM_TheresaC, pState, Ultra)
		AddState(pState, Name_Ultra);

	CreateState(CFSM_TheresaC, pState, SwitchIn)
		AddState(pState, Name_SwitchIn);

	CreateState(CFSM_TheresaC, pState, SwitchOut)
		AddState(pState, Name_SwitchOut);

// 	CreateState(CFSM_TheresaC, pState, SwitchInATTACK_FY)
// 		AddState(pState, Name_SwitchInATTACK_FY);
// 
// 	CreateState(CFSM_TheresaC, pState, SwitchInATTACK_TP)
// 		AddState(pState, Name_SwitchInATTACK_TP);
// 
// 	CreateState(CFSM_TheresaC, pState, SwitchInATTACK_YD)
// 		AddState(pState, Name_SwitchInATTACK_YD);
// 
// 	CreateState(CFSM_TheresaC, pState, JUMP_0)
// 		AddState(pState, Name_JUMP_0);
// 
// 	CreateState(CFSM_TheresaC, pState, JUMP_1)
// 		AddState(pState, Name_JUMP_1);
// 
// 	CreateState(CFSM_TheresaC, pState, JUMP_2)
// 		AddState(pState, Name_JUMP_2);
// 
// 	CreateState(CFSM_TheresaC, pState, QTE_FY)
// 		AddState(pState, Name_QTE_FY);

	CreateState(CFSM_TheresaC, pState, Hit_L)
		AddState(pState, Name_Hit_L);

	CreateState(CFSM_TheresaC, pState, Hit_H)
		AddState(pState, Name_Hit_H);

	CreateState(CFSM_TheresaC, pState, Stun)
		AddState(pState, Name_Stun);

	CreateState(CFSM_TheresaC, pState, Die)
		AddState(pState, Name_Die);

	CreateState(CFSM_TheresaC, pState, Victory)
		AddState(pState, Name_Victory);

	CreateState(CFSM_TheresaC, pState, Victory_Idle)
		AddState(pState, Name_Victory_Idle);
}
