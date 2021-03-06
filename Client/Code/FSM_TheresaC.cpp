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
#include "StageCameraMan.h"
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
	if (m_isUI)
		return;

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
	m_checkAttack = false;
	m_checkAttack2nd = false;
	m_checkAttack3th = false;
	m_checkAttack4th = false;
	m_checkEffect = false;
	m_checkEffectSecond = false;
	m_checkShake = false;
	m_checkShot = false;
}

void CFSM_TheresaC::OnSwordCollider()
{
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_LeftHand(), 0.6f, HitInfo::Str_Low, HitInfo::CC_None, m_pTheresa->GetLeftHandWorldMatrix(), 0.1f, _float3(0.f, 0.5f, 0.f));
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_RightHand(), 0.6f, HitInfo::Str_Low, HitInfo::CC_None, m_pTheresa->GetRightHandWorldMatrix(), 0.1f, _float3(0.f, 0.5f, 0.f));
}

void CFSM_TheresaC::OffSwordCollider()
{
	m_pTheresa->GetAttackBall_LeftHand()->SetIsEnabled(false);
	m_pTheresa->GetAttackBall_RightHand()->SetIsEnabled(false);
}

void CFSM_TheresaC::OnAxeCollider()
{
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_Axe(), 3.f, HitInfo::Str_High, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 0.4f, _float3(2.f, 0.f, 0.f));
	m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_AxeStick(), 1.6f, HitInfo::Str_High, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 0.2f, _float3(1.f, 0.f, 0.f));
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

bool CFSM_TheresaC::CheckAction_Ultra(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		if (Engine::IMKEY_DOWN(StageKey_Ult))
		{
			if (m_pStageControlTower->ActUltra())
			{
				ChangeState(Name_Ultra);
				CStageControlTower::GetInstance()->FindTarget();
				return true;
			}
		}
	}
	return false;
}

bool CFSM_TheresaC::CheckAction_WeaponSkill(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		if (Engine::IMKEY_DOWN(StageKey_WeaponSkill))
		{
			if (m_pStageControlTower->ActSkill())
			{
				ChangeState(Name_CastCross);
				return true;
			}
		}
	}
	return false;
}

bool CFSM_TheresaC::CheckAction_Idle()
{
	m_idleTimer += GET_PLAYER_DT;
	if (m_idleTimer > 3.f)
	{
		ChangeState(Name_Idle);
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
	m_chargeEnterTimer += GET_PLAYER_DT;
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

void CFSM_TheresaC::PlaySound_SelectChannel(const std::wstring & soundName, _uint channel)
{
	TCHAR* name = (TCHAR*)soundName.c_str();
	Engine::CSoundManager::GetInstance()->StopSound(channel);
	Engine::CSoundManager::GetInstance()->StartSound(name, channel);
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
	m_idleTimer = 0.f;
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

	if (CheckAction_WeaponSkill())
		return;

	if (CheckAction_Idle())
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
	m_pDM->ChangeAniSet(Index_Idle);
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
	if (CheckAction_WeaponSkill())
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
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(false);
	m_pDM->ChangeAniSet(Index_Appear);
	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();

	m_checkShake = false;

	PlaySound_Effect(L"Swap.wav");

	m_pEffectMaker->CreateEffect_Switching();
}

void CFSM_TheresaC::Appear_Update(float deltaTime)
{

	if (!m_checkShake && m_pDM->GetAniTimeline() > 0.128)
	{
		m_pStageControlTower->GetCameraMan()->GetCameraShake()->Preset_Land();
		m_checkShake = true;
	}

	if (CheckAction_StandBy_Timeout(0.9f))
		return;
}

void CFSM_TheresaC::Appear_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_appearOption = None;
}

void CFSM_TheresaC::Run_Init(void)
{
	m_pDM->SetLoopAnim(Index_Run);
}

void CFSM_TheresaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);
	m_pStageControlTower->SetVertCorrecting(true);

	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();
	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::Run_Update(float deltaTime)
{
	m_runSoundTimer += GET_PLAYER_DT;
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
	if (CheckAction_WeaponSkill())
		return;

	if (m_pDM->GetAniTimeline() > 0.8)
	{
		ChangeState(Name_FastRun);
		return;
	}
}

void CFSM_TheresaC::Run_End(void)
{
	m_runSoundTimer = 0.f;
	m_pStageControlTower->SetVertCorrecting(false);
}

void CFSM_TheresaC::FastRun_Init(void)
{
	m_pDM->SetLoopAnim(Index_FastRun);
}

void CFSM_TheresaC::FastRun_Enter(void)
{
	m_pDM->ChangeAniSet(Index_FastRun);
	m_pStageControlTower->SetVertCorrecting(true);

	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();
	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::FastRun_Update(float deltaTime)
{
	m_runSoundTimer += GET_PLAYER_DT;
	if (m_runSoundTimer > 0.23f)
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
	if (CheckAction_WeaponSkill())
		return;
}

void CFSM_TheresaC::FastRun_End(void)
{
	m_runSoundTimer = 0.f;
	m_pStageControlTower->SetVertCorrecting(false);
}

void CFSM_TheresaC::RunBS_Init(void)
{
}

void CFSM_TheresaC::RunBS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunBS);	
	m_chargeEnterTimer = 0.f;
	m_pStageControlTower->SetVertCorrecting(true);
}

void CFSM_TheresaC::RunBS_Update(float deltaTime)
{
	m_runSoundTimer += GET_PLAYER_DT;
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
	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
}

void CFSM_TheresaC::RunBS_End(void)
{
	m_pStageControlTower->SetVertCorrecting(false);
}

void CFSM_TheresaC::EvadeBackward_Init(void)
{
}

void CFSM_TheresaC::EvadeBackward_Enter(void)
{
	m_pDM->RepeatAniSet(Index_EvadeBackward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();

	PlaySound_Effect(Sound_Evade);

	m_isEvade = true;
	m_pTheresa->SetIsEvade(true);
}

void CFSM_TheresaC::EvadeBackward_Update(float deltaTime)
{
	if (m_isEvade && m_pDM->GetAniTimeline() > 0.3)
	{
		m_isEvade = false;
		m_pTheresa->OnHitbox();
		m_pTheresa->SetIsEvade(false);
		PlaySound_Effect(Sound_EvadeLand);
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

	m_isEvade = false;
	m_pTheresa->OnHitbox();
	m_pTheresa->SetIsEvade(false);
}

void CFSM_TheresaC::EvadeForward_Init(void)
{
}

void CFSM_TheresaC::EvadeForward_Enter(void)
{
	m_pDM->RepeatAniSet(Index_EvadeForward);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();
	
	PlaySound_Effect(Sound_Evade);

	m_isEvade = true;
	m_pTheresa->SetIsEvade(true);
}

void CFSM_TheresaC::EvadeForward_Update(float deltaTime)
{
	if (m_isEvade&& m_pDM->GetAniTimeline() > 0.3)
	{
		m_isEvade = false;
		m_pTheresa->OnHitbox();
		m_pTheresa->SetIsEvade(false);
		PlaySound_Effect(Sound_EvadeLand);
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

	m_isEvade = false;
	m_pTheresa->OnHitbox();
	m_pTheresa->SetIsEvade(false);
}

void CFSM_TheresaC::Attack1_Init(void)
{
}

void CFSM_TheresaC::Attack1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack1);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(true);

	ResetCheckMembers();

	m_chargeEnterTimer = 0.f;

	m_pTheresa->On_Sword();
}

void CFSM_TheresaC::Attack1_Update(float deltaTime)
{
	if (!m_checkEffect &&  m_pDM->GetAniTimeline() > 0.02f)
	{
		m_pEffectMaker->CreateEffect_Attack1_1();
		PlaySound_Effect(Sound_Attack1_Effect);
		m_checkEffect = true;
	}

	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Attack1_1)
	{
		PlaySound_Voice(Sound_Attack1_Voice);

		OnSwordCollider();
		m_checkAttack = true;
	}
	if (m_pDM->GetAniTimeline() > Delay_Effect_Attack1_1 + 0.1f)
		OffSwordCollider();

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
	if (CheckAction_Ultra(Delay_Effect_Attack1_1 + 0.1f))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Attack1_1 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack1_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);

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
	m_pStageControlTower->SetVertCorrecting(true);
	ResetCheckMembers();
	m_chargeEnterTimer = 0.f;
	
	m_pEffectMaker->CreateEffect_Attack2_1();
	OnSwordCollider();
}

void CFSM_TheresaC::Attack2_Update(float deltaTime)
{
	if (!m_checkEffect &&  m_pDM->GetAniTimeline() > 0.05f)
	{
		m_pEffectMaker->CreateEffect_Attack2_1();
		PlaySound_Effect(Sound_Attack2_Effect);
		m_checkEffect = true;
	}


	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Attack2_1)
	{
		PlaySound_Voice(Sound_Attack2_Voice);

		m_checkAttack = true;
	}
	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Attack2_2)
	{
		m_pEffectMaker->CreateEffect_Attack2_2();

		m_checkEffectSecond = true;
	}

	if (m_pDM->GetAniTimeline() > Delay_Effect_Attack2_2 + 0.07f)
		OffSwordCollider();

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_ChargeMode())
		return;
	if (CheckAction_Attack(Name_Attack3))
		return;
	if (CheckAction_Ultra(Delay_Effect_Attack2_2 + 0.1f))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Attack2_2 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack2_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);

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
	m_pStageControlTower->SetVertCorrecting(true);
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
	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Attack3_2 - 0.05f)
	{
		m_checkAttack = true;
		OffSwordCollider();
	}
	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Attack3_2)
	{
		m_pEffectMaker->CreateEffect_Attack3_2();

		OnSwordCollider();
		m_checkEffectSecond = true;
	}

	if (m_pDM->GetAniTimeline() > Delay_Effect_Attack3_2 + 0.1f)
		OffSwordCollider();
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_ChargeMode())
		return;
	if (CheckAction_Attack(Name_Attack4))
		return;
	if (CheckAction_Ultra(Delay_Effect_Attack3_2 + 0.1f))
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Attack3_2 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack3_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);

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
	m_pStageControlTower->SetVertCorrecting(true);
	ResetCheckMembers();

	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::Attack4_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Attack4_1)
	{
		m_pEffectMaker->CreateEffect_Attack4_1();
		PlaySound_Effect(Sound_Attack4_Effect);
		PlaySound_Voice(Sound_Attack4_Voice);

		OnSwordCollider();
		m_checkEffect = true;
	}
	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Attack4_2 - 0.05f) 
	{
		m_pEffectMaker->CreateEffect_Attack4_2();
		m_checkAttack = true;
		OffSwordCollider();
	}
	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > Delay_Effect_Attack4_2)
	{

		OnSwordCollider();
		m_checkEffectSecond = true;
	}

	if (m_pDM->GetAniTimeline() > Delay_Effect_Attack4_2 + 0.13f)
		OffSwordCollider();
	if (CheckAction_ChargeMode())
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_WeaponSkill(Delay_Effect_Attack4_2 + 0.1f))
		return;
	if (CheckAction_Ultra(Delay_Effect_Attack4_2 + 0.1f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::Attack4_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);

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
	m_pStageControlTower->SetVertCorrecting(true);
	ResetCheckMembers();

	m_pTheresa->Off_Sword();
	m_pTheresa->On_Axe();
	m_chargeEnterTimer = 0.f;
	
}

void CFSM_TheresaC::Charge0_Update(float deltaTime)
{
	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Charge0)
	{
		m_pEffectMaker->CreateEffect_Charge0();
		PlaySound_Effect(Sound_Charge0_Effect);

		m_checkAttack = true;
	}

	if (m_pDM->GetAniTimeline() > 0.8f)
	{
		ChangeState(Name_Charge1);
		return;
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_WeaponSkill(0.2f))
		return;
	if (CheckAction_Ultra(0.2f))
		return;
}

void CFSM_TheresaC::Charge0_End(void)
{
	m_pTheresa->Off_Axe();
	m_pStageControlTower->SetVertCorrecting(false);
}

void CFSM_TheresaC::Charge1_Init(void)
{
	FixRootMotionOffset(Index_Charge1);
}

void CFSM_TheresaC::Charge1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Charge1);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(true);
	m_chargeAttackIndex = 2;

	ResetCheckMembers();

	m_pTheresa->On_Axe();

	m_pTheresa->SetCCImmune(true);

	if (CBattleUiManager::GetInstance()->GetSpecialUIValue() > 1.f)
	{
		CBattleUiManager::GetInstance()->SpecialUIDwon();
	}
	else
	{
		m_pDM->GetAniCtrl()->SetSpeed(0.8f);
	}
}

void CFSM_TheresaC::Charge1_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Charge1)
	{
		m_pEffectMaker->CreateEffect_Charge1();
		PlaySound_Effect(Sound_Charge1_Effect);
		PlaySound_Charge_RandomVoice();

		m_checkEffect = true;
	}
	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Charge1)
	{
		OnAxeCollider();
		m_checkAttack = true;
	}

	if (!m_checkShot && !m_checkShake && m_pDM->GetAniTimeline() > 0.21f)
	{
		CStageControlTower::GetInstance()->SetCameraCustomShot(2.8f, 2.5f, D3DXToRadian(12.f));
		m_checkShot = true;
	}
	if (!m_checkShake && m_pDM->GetAniTimeline() > 0.26f)
	{
		CStageControlTower::GetInstance()->GetCameraMan()->ShakeCamera_Theresa_Charge1Impact(Engine::GET_MAIN_CAM->GetTransform()->GetPosition());
		m_checkShake = true;
		m_checkShot = false;
	}

	if (!m_checkShot && m_pDM->GetAniTimeline() > 0.35f)
	{
		CStageControlTower::GetInstance()->SetCameraCustomShot(3.f, 2.f, D3DXToRadian(10.f));
		m_checkShot = true;
	}

	if (m_pDM->GetAniTimeline() > 0.4f)
		OffAxeCollider();

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_WeaponSkill(0.5f))
		return;
	if (CheckAction_Ultra(0.5f))
		return;
	if (CheckAction_ChargeAttack())
		return;
	if (CheckAction_ChargeAttack_End())
		return;
}

void CFSM_TheresaC::Charge1_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);
	
	m_pTheresa->Off_Axe();
	OffAxeCollider();

	m_pTheresa->SetCCImmune(false);
	m_pDM->GetAniCtrl()->SetSpeed(1.f);
}

void CFSM_TheresaC::Charge2_Init(void)
{
	FixRootMotionOffset(Index_Charge2);
}

void CFSM_TheresaC::Charge2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Charge2);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(true);
	m_chargeAttackIndex = 1;

	ResetCheckMembers();

	m_pTheresa->On_Axe();
	m_pTheresa->SetCCImmune(true);

	if (CBattleUiManager::GetInstance()->GetSpecialUIValue() > 1.f)
	{
		CBattleUiManager::GetInstance()->SpecialUIDwon();
	}
	else
	{
		m_pDM->GetAniCtrl()->SetSpeed(0.8f);
	}
}

void CFSM_TheresaC::Charge2_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Charge2)
	{
		m_pEffectMaker->CreateEffect_Charge2();
		PlaySound_Effect(Sound_Charge2_Effect);
		PlaySound_Charge_RandomVoice();

		m_checkEffect = true;
	}
	if (!m_checkAttack && m_pDM->GetAniTimeline() > 0.21f)
	{
		m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_Axe(), 1.6f, HitInfo::Str_Airborne, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 0.3f, _float3(2.f, 0.f, 0.f));
		m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_AxeStick(), 1.f, HitInfo::Str_Airborne, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 0.2f, _float3(1.f, 0.f, 0.f));
		m_checkAttack = true;
	}

	if (!m_checkShot && !m_checkShake && m_pDM->GetAniTimeline() > 0.18f)
	{
		CStageControlTower::GetInstance()->SetCameraCustomShot(2.8f, 2.5f, D3DXToRadian(12.f));
		m_checkShot = true;
	}
	if (!m_checkShake && m_pDM->GetAniTimeline() > 0.23f)
	{
		CStageControlTower::GetInstance()->GetCameraMan()->ShakeCamera_Theresa_Charge2Impact(Engine::GET_MAIN_CAM->GetTransform()->GetPosition());

		m_checkShake = true;
		m_checkShot = false;
	}
	
	if (!m_checkShot && m_pDM->GetAniTimeline() > 0.33f)
	{
		CStageControlTower::GetInstance()->SetCameraCustomShot(3.f, 2.f, D3DXToRadian(10.f));
		m_checkShot = true;
	}

	if (m_pDM->GetAniTimeline() > 0.25f)
		OffAxeCollider();

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_WeaponSkill(0.5f))
		return;
	if (CheckAction_Ultra(0.5f))
		return;
	if (CheckAction_ChargeAttack())
		return;
	if (CheckAction_ChargeAttack_End())
		return;
}

void CFSM_TheresaC::Charge2_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);

	m_pTheresa->Off_Axe();
	OffAxeCollider();

	m_pTheresa->SetCCImmune(false);
	m_pDM->GetAniCtrl()->SetSpeed(1.f);
}

void CFSM_TheresaC::Attack_QTE_Init(void)
{
}

void CFSM_TheresaC::Attack_QTE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Charge1);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(true);

	ResetCheckMembers();

	m_pTheresa->On_Axe();
	m_pTheresa->SetCCImmune(true);
}

void CFSM_TheresaC::Attack_QTE_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_Effect_Charge1)
	{
		m_pEffectMaker->CreateEffect_Charge1();
		PlaySound_Effect(Sound_Charge1_Effect);
		PlaySound_Charge_RandomVoice();

		m_checkEffect = true;
	}
	if (!m_checkAttack && m_pDM->GetAniTimeline() > Delay_Effect_Charge1)
	{
		OnAxeCollider();
		m_checkAttack = true;
	}

	if (!m_checkShot && !m_checkShake && m_pDM->GetAniTimeline() > 0.21f)
	{
		CStageControlTower::GetInstance()->SetCameraCustomShot(2.8f, 2.5f, D3DXToRadian(12.f));
		m_checkShot = true;
	}
	if (!m_checkShake && m_pDM->GetAniTimeline() > 0.26f)
	{
		CStageControlTower::GetInstance()->GetCameraMan()->ShakeCamera_Theresa_Charge1Impact(Engine::GET_MAIN_CAM->GetTransform()->GetPosition());
		m_checkShake = true;
		m_checkShot = false;
	}

	if (!m_checkShot && m_pDM->GetAniTimeline() > 0.35f)
	{
		CStageControlTower::GetInstance()->SetCameraCustomShot(3.f, 2.f, D3DXToRadian(10.f));
		m_checkShot = true;
	}

	if (m_pDM->GetAniTimeline() > 0.4f)
	{
		OffAxeCollider();
		m_pStageControlTower->OffSlowExceptPlayer();
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack1))
		return;
	if (CheckAction_WeaponSkill(0.5f))
		return;
	if (CheckAction_Ultra(0.5f))
		return;
	if (CheckAction_ChargeAttack_End())
		return;
}

void CFSM_TheresaC::Attack_QTE_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);

	m_pTheresa->Off_Axe();
	OffAxeCollider();
	m_pTheresa->SetCCImmune(false);
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
	if (m_pDM->GetAniTimeline() > 0.95f)
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
	if (m_pDM->GetAniTimeline() > 0.95)
	{
		m_pTheresa->SetIsEnabled(false);
		m_pStageControlTower->BattonTouch();
		return;
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
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_TheresaC::Stun_Update(float deltaTime)
{
}

void CFSM_TheresaC::Stun_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_TheresaC::SwitchIn_Init(void)
{
}

void CFSM_TheresaC::SwitchIn_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SwitchIn);
	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();

	m_checkShake = false;
	PlaySound_Effect(L"Swap.wav");

	m_pEffectMaker->CreateEffect_Switching();
}

void CFSM_TheresaC::SwitchIn_Update(float deltaTime)
{
	if (!m_checkShake && m_pDM->GetAniTimeline() > 0.127)
	{
		m_pStageControlTower->GetCameraMan()->GetCameraShake()->Preset_Land();
		m_checkShake = true;
	}


	if (m_pDM->IsAnimationEnd())
	{
		if (m_pTheresa->GetIsQTESwitch())
		{
			m_pTheresa->SetIsQTESwitch(false);
			ChangeState(Name_Charge0);
			return;
		}
		else
		{
			ChangeState(Name_StandBy);
			return;
		}
	}
}

void CFSM_TheresaC::SwitchIn_End(void)
{
	CStageControlTower::GetInstance()->EndSwitching();
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
	if (m_pDM->GetAniTimeline() > 0.75)
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
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(true);
	m_pDM->ChangeAniSet(Index_Ultra);
	ResetCheckMembers();

	m_pTheresa->Off_Sword();
	m_ultraAxeOnOff = false;
	m_ultraImpact = false;

	m_pEffectMaker->CreateEffect_Ultra_Charge();
	m_pDM->GetAniCtrl()->SetSpeed(0.8f);

	PlaySound_Voice(Sound_Ult_Voice);
	PlaySound_Effect(Sound_Ult);

	m_pStageControlTower->GetCameraMan()->SetCustomShot(2.f, 1.5f, D3DXToRadian(20.f));
	m_pStageControlTower->GetCameraMan()->SetTargetingMidRatio(0.65f);

	CStageControlTower::GetInstance()->SetEnvType(CStageControlTower::TheresaUlt);
	m_pTheresa->SetCCImmune(true);
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
		m_pEffectMaker->CreateEffect_Ultra_ChargeSmoke();

		m_pStageControlTower->GetCameraMan()->SetCustomShot(3.5f, 2.5f, D3DXToRadian(25.f));
	}

	if (!m_checkAttack && m_pDM->GetAniTimeline() > 0.34)
	{
		OffAxeCollider();
		m_checkAttack = true;
		m_ultraAxeOnOff = false;
	}

	if (!m_checkAttack2nd  && m_pDM->GetAniTimeline() > 0.35)
	{
		OnAxeCollider();
		m_checkAttack2nd = true;
	}

	if (!m_checkAttack3th && m_pDM->GetAniTimeline() > 0.472)
	{
		OffAxeCollider();
		m_checkAttack3th = true;
	}

	if (!m_checkAttack4th && m_pDM->GetAniTimeline() > 0.585)
	{
		OnAxeCollider();
		m_checkAttack4th = true;
	}

	if (!m_ultraImpact && m_pDM->GetAniTimeline() > 0.605f)
	{
		OffAxeCollider();
		m_pTheresa->ActiveAttackBall(m_pTheresa->GetAttackBall_AxeImpact(), 4.f, HitInfo::Str_High, HitInfo::CC_None, m_pTheresa->GetAxePivotWorldMatrix(), 1.f, _float3(2.f, 0.f, 0.f));
		m_pStageControlTower->GetCameraMan()->GetCameraShake()->Preset_Kiana_UltraActive();
		m_pEffectMaker->CreateEffect_Ultra_Bomb();
		m_ultraImpact = true;
	}

	if (CheckAction_StandBy_Timeout(0.9f))
		return;
}

void CFSM_TheresaC::Ultra_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);
	m_ultraUsed = true;
	m_pTheresa->GetAttackBall_AxeImpact()->SetIsEnabled(false);

	m_pStageControlTower->GetCameraMan()->SetTargetingMidRatio(0.5f);

	CStageControlTower::GetInstance()->SetEnvType(CStageControlTower::NoColoring);

	m_pTheresa->Off_Axe();
	m_pTheresa->SetCCImmune(false);
}

void CFSM_TheresaC::CastCross_Init(void)
{
}

void CFSM_TheresaC::CastCross_Enter(void)
{
	m_pDM->ChangeAniSet(Index_CastCross);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	m_pTheresa->Off_Sword();
	m_pTheresa->Off_Axe();
}

void CFSM_TheresaC::CastCross_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(0.5f))
		return;
	if (CheckAction_Run_OnAction(0.5f))
		return;
	if (CheckAction_Attack(Name_Attack1, 0.5f))
		return;
	if (CheckAction_Ultra(0.5f))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::CastCross_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_TheresaC::RunStopRight_Init(void)
{
}

void CFSM_TheresaC::RunStopRight_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopRight);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(true);
	m_chargeEnterTimer = 0.f;
}

void CFSM_TheresaC::RunStopRight_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(0.1f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_TheresaC::RunStopRight_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);
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
	if (CheckAction_Evade_OnAction(0.1f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_WeaponSkill())
		return;
	if (CheckAction_StandBy_Timeout())
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
	m_pDM->RepeatAniSet(Index_Hit_H);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pStageControlTower->SetVertCorrecting(true);

	PlaySound_SelectChannel(Sound_HIT_Effect, (_uint)EChannelID::PLAYERHIT);
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
	m_pStageControlTower->ActorControl_SetInputLock(false);
	m_pStageControlTower->SetVertCorrecting(false);
}

void CFSM_TheresaC::Hit_L_Init(void)
{
}

void CFSM_TheresaC::Hit_L_Enter(void)
{
	m_pDM->RepeatAniSet(Index_Hit_L);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	PlaySound_SelectChannel(Sound_HIT_Effect, (_uint)EChannelID::PLAYERHIT);
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
	m_pStageControlTower->ActorControl_SetInputLock(false);
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

 	CreateState(CFSM_TheresaC, pState, FastRun)
 		AddState(pState, Name_FastRun);

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
 	CreateState(CFSM_TheresaC, pState, Attack_QTE)
 		AddState(pState, Name_Attack_QTE);

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
