#include "stdafx.h"
#include "FSM_KianaC.h"

#include "SoundManager.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "Kiana.h"
#include "State.h"
#include "FSMDefine_Kiana.h"
#include "AttackBall.h"

#include "AttackTrail_Client.h"
#include "StageControlTower.h"
#include "EffectMaker_Kiana.h"

CFSM_KianaC::CFSM_KianaC()
{
}

CFSM_KianaC::~CFSM_KianaC()
{
	OnDestroy();
}

SP(Engine::CComponent) CFSM_KianaC::MakeClone(Engine::CObject * pObject)
{
	//SP(CFSM_KianaC) spClone = MakeStateMachineClone<CFSM_KianaC>(pObject);

	SP(CFSM_KianaC) spClone(new CFSM_KianaC);

	__super::InitClone(spClone, pObject);

	for (auto pState : m_stateList)
	{
		spClone->m_stateList.emplace(pState.first, pState.second->MakeClone(spClone.get()));
	}

	return spClone;
}

void CFSM_KianaC::Awake(void)
{
	__super::Awake();
}
 
void CFSM_KianaC::Start(SP(CComponent) spThis)
{
	m_pKiana = static_cast<CKiana*>(m_pOwner);
	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pKiana->GetComponent<Engine::CMeshC>()->GetMeshData());
	m_pEffectMaker = new CEffectMaker_Kiana(m_pKiana);
	
	RegisterAllState();

	__super::Start(spThis);

	m_pStageControlTower = CStageControlTower::GetInstance();

	//m_pDM->GetAniCtrl()->SetSpeed(0.5f);
	SetStartState(Name_Appear);
	m_curState->DoEnter();
}

void CFSM_KianaC::OnDestroy()
{
	__super::OnDestroy();

	delete m_pEffectMaker;
}

void CFSM_KianaC::FixRootMotionOffset(_uint index)
{
	m_pKiana->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}


bool CFSM_KianaC::CheckAction_Attack(const std::wstring& switchStateName, float coolTime /*= Cool_Attack*/)
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

bool CFSM_KianaC::CheckAction_Evade_OnAction(float coolTime)
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

bool CFSM_KianaC::CheckAction_EvadeForward(float coolTime)
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

bool CFSM_KianaC::CheckAction_EvadeBackward(float coolTime)
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

bool CFSM_KianaC::CheckAction_StandBy_Timeout(float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		ChangeState(Name_StandBy);
		return true;
	}

	return false;
}

bool CFSM_KianaC::CheckAction_Run(float coolTime)
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

bool CFSM_KianaC::CheckAction_Run_OnAction(float coolTime)
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

bool CFSM_KianaC::CheckAction_Run_End()
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
		else if(timeline > 0.55)
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

bool CFSM_KianaC::CheckAction_StandBy()
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

bool CFSM_KianaC::CheckAction_Idle()
{
	m_idleTimer += GET_PLAYER_DT;
	if (m_idleTimer > 3.f)
	{
		switch (m_idleMotionIndex)
		{
		case 0:
			ChangeState(Name_Idle_01);
			break;
		case 1:
			ChangeState(Name_Idle_02);
			break;
		case 2:
			ChangeState(Name_Idle_03);
			break;
		default:
			break;
		}
		++m_idleMotionIndex;
		if (m_idleMotionIndex == 3)
			m_idleMotionIndex = 0;
		return true;
	}

	return false;
}

bool CFSM_KianaC::CheckAction_Emotion(const std::wstring & switchStateName, float coolTime)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		ChangeState(switchStateName);
		return true;
	}

	return false;
}

bool CFSM_KianaC::CheckAction_BranchAttack()
{
	if (Engine::IMKEY_DOWN(StageKey_Attack))
	{
		// Branch Attack
		if (m_pDM->GetAniTimeline() > Cool_BranchAttack)
		{
			ChangeState(Name_Attack_3_Branch);
			return true;
		}
	}

	return false;
}

bool CFSM_KianaC::CheckAction_RunBS_To_Run()
{
	if (m_pDM->GetAniTimeline() > Cool_End - 0.25f)
	{
		ChangeState(Name_Run);
		return true;
	}
	return false;
}

bool CFSM_KianaC::CheckAction_Ultra()
{
	if (Engine::IMKEY_DOWN(StageKey_Ult))
	{
		auto pStat = m_pKiana->GetStat();
		if (pStat->GetCurSp() < pStat->GetUltraCost())
			return false;

		ChangeState(Name_Ultra);
		return true;
	}
	return false;
}

void CFSM_KianaC::PlayActionSound(const std::wstring & soundName, Engine::EChannelID channel)
{
	TCHAR* name = (TCHAR*)soundName.c_str();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)channel);
	Engine::CSoundManager::GetInstance()->StartSound(name, (_uint)channel);
}

void CFSM_KianaC::PlaySound_Voice(const std::wstring & soundName)
{
	TCHAR* name = (TCHAR*)soundName.c_str();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::PLAYER);
	Engine::CSoundManager::GetInstance()->StartSound(name, (_uint)Engine::EChannelID::PLAYER);
}

void CFSM_KianaC::PlaySound_Effect(const std::wstring & soundName)
{
	TCHAR* name = (TCHAR*)soundName.c_str();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::PLAYEREFFECT);
	Engine::CSoundManager::GetInstance()->StartSound(name, (_uint)Engine::EChannelID::PLAYEREFFECT);
}

void CFSM_KianaC::PlaySound_Attack_RandomVoice()
{
	_uint idx = rand() % 6;
	if (m_prevAttackSoundIndex == idx)
		idx = (m_prevAttackSoundIndex + 1) % 6;
	
	switch (idx)
	{
	case 0:
		PlaySound_Voice(Sound_Attack_Voice_0);
		break;
	case 1:
		PlaySound_Voice(Sound_Attack_Voice_1);
		break;
	case 2:
		PlaySound_Voice(Sound_Attack_Voice_2);
		break;
	case 3:
		PlaySound_Voice(Sound_Attack_Voice_3);
		break;
	case 4:
		PlaySound_Voice(Sound_Attack_Voice_4);
		break;
	case 5:
		PlaySound_Voice(Sound_Attack_Voice_5);
		break;
	default:
		break;
	}

	m_prevAttackSoundIndex = idx;
}

void CFSM_KianaC::PlaySound_Attack_RandomRun()
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

void CFSM_KianaC::PlaySound_Attack_RandomEvade()
{
	_uint idx = rand() % 2;

	switch (idx)
	{
	case 0:
		PlaySound_Effect(Sound_Evade_0);
		break;
	case 1:
		PlaySound_Effect(Sound_Evade_1);
		break;
	}
}

void CFSM_KianaC::PlaySound_Attack_RandomHit()
{
	//_uint idx = rand() % 4;
	//if (m_prevHitSoundIndex == idx)
	//	idx = (m_prevHitSoundIndex + 1) % 4;

	//switch (idx)
	//{
	//case 0:
	//	PlaySound_Effect(Sound_HIT_0);
	//	break;
	//case 1:
	//	PlaySound_Effect(Sound_HIT_1);
	//	break;
	//case 2:
	//	PlaySound_Effect(Sound_HIT_2);
	//	break;
	//case 3:
	//	PlaySound_Effect(Sound_HIT_3);
	//	break;
	//default:
	//	break;
	//}

	//m_prevHitSoundIndex = idx;

	PlaySound_Effect(Sound_HIT);
}


void CFSM_KianaC::ResetCheckMembers()
{
	m_checkUltraRing = false;
	m_checkUltraAtk = false;
	m_checkEffect = false;
	m_checkEffectSecond = false;
}

void CFSM_KianaC::ResetCheckMembers_Hit()
{
}


void CFSM_KianaC::StandBy_Init(void)
{
	m_pDM->SetLoopAnim(Index_StandBy);
}

void CFSM_KianaC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
	m_idleTimer = 0.f;
}

void CFSM_KianaC::StandBy_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;

	if (CheckAction_Run())
		return;

	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	
	if (CheckAction_Ultra())
		return;

	if (CheckAction_Idle())
		return;
}

void CFSM_KianaC::StandBy_End(void)
{
}

void CFSM_KianaC::Stun_Init(void)
{
}

void CFSM_KianaC::Appear_Init(void)
{
}

void CFSM_KianaC::Appear_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Appear);
	//m_pKiana->GetComponent<Engine::CMeshC>()->GetRootMotion()->SetIsVerticalAnim(true);
}

void CFSM_KianaC::Appear_Update(float deltaTime)
{
	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		switch (m_appearOption)
		{
		case CFSM_KianaC::None:
			ChangeState(Name_StandBy);
			break;
		case CFSM_KianaC::QTE:
			ChangeState(Name_Attack_QTE);
			break;
		default:
			break;
		}
		return;
	}
}

void CFSM_KianaC::Appear_End(void)
{
	m_appearOption = None;
	//m_pKiana->GetComponent<Engine::CMeshC>()->GetRootMotion()->SetIsVerticalAnim(false);
}

void CFSM_KianaC::Attack_1_Init(void)
{
}

void CFSM_KianaC::Attack_1_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_1);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	ResetCheckMembers();
	m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
}

void CFSM_KianaC::Attack_1_Update(float deltaTime)
{
	if (!m_checkUltraRing && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk01 - 0.1f)
	{
		//m_pKiana->UltraAtk_Ring(CKiana::ATK01);
		m_checkUltraRing = true;
	} 

	if (!m_checkUltraAtk && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk01)
	{
		m_pKiana->UltraAtk(CKiana::ATK01);
		m_checkUltraAtk = true;
	}

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk01)
	{
		m_pEffectMaker->CreateEffect_Attack1();
		PlaySound_Attack_RandomVoice();

		if (m_pKiana->GetUltraMode())
			PlaySound_Effect(Sound_Ult_Att_0);
		else
			PlaySound_Effect(Sound_Attack_1_Effect);

		m_checkEffect = true;
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack_2, 0.3f))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_1_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_pKiana->UnActiveAttackBall();
}

void CFSM_KianaC::Attack_2_Init(void)
{
	FixRootMotionOffset(Index_Attack_2);
}

void CFSM_KianaC::Attack_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
	m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetLeftHandWorldMatrix(), 0.3f);

}

void CFSM_KianaC::Attack_2_Update(float deltaTime)
{

	if (!m_checkUltraAtk && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk02)
	{
		//m_pKiana->UltraAtk_Ring(CKiana::ATK02);
		m_pKiana->UltraAtk(CKiana::ATK02);
		m_checkUltraAtk = true;
	}
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk02)
	{
		m_pEffectMaker->CreateEffect_Attack2();
		m_checkEffect = true;
		
		PlaySound_Attack_RandomVoice();
		
		if (m_pKiana->GetUltraMode())
			PlaySound_Effect(Sound_Ult_Att_1);
		else
			PlaySound_Effect(Sound_Attack_2_Effect);
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_BranchAttack())
		return;
	if (CheckAction_Attack(Name_Attack_3))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_2_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_pKiana->UnActiveAttackBall();
}

void CFSM_KianaC::Attack_3_Init(void)
{
	FixRootMotionOffset(Index_Attack_3);
}

void CFSM_KianaC::Attack_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3);
	m_pStageControlTower->ActorControl_SetInputLock(true); 
	ResetCheckMembers();
	m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightHandWorldMatrix(), 0.3f);
}

void CFSM_KianaC::Attack_3_Update(float deltaTime)
{
	if (!m_checkUltraAtk && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk03)
	{
		m_pKiana->UltraAtk(CKiana::ATK03);
		m_checkUltraAtk = true;
	}
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk03)
	{
		m_pEffectMaker->CreateEffect_Attack3();
		m_checkEffect = true;

		PlaySound_Attack_RandomVoice();

		if (m_pKiana->GetUltraMode())
			PlaySound_Effect(Sound_Ult_Att_1);
		else
			PlaySound_Effect(Sound_Attack_3_Effect);
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack_4))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_3_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_pKiana->UnActiveAttackBall();
}

void CFSM_KianaC::Attack_3_Branch_Init(void)
{
	FixRootMotionOffset(Index_Attack_3_Branch);
}

void CFSM_KianaC::Attack_3_Branch_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3_Branch);
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_checkEffect = false;
}

void CFSM_KianaC::Attack_3_Branch_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Branch_Atk03)
	{
		//CreateEffect_Attack4();
		m_checkEffect = true;

		PlaySound_Voice(Sound_Branch_Voice_0);

		if (m_pKiana->GetUltraMode())
			PlaySound_Effect(Sound_Branch_0);
		else
			PlaySound_Effect(Sound_Branch_0);
	}

	if (m_pDM->GetAniTimeline() > Cool_BranchAttack3to4)
	{
		ChangeState(Name_Attack_4_Branch);
		return;
	}
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
}

void CFSM_KianaC::Attack_3_Branch_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_KianaC::Attack_4_Init(void)
{
	FixRootMotionOffset(Index_Attack_4);
}

void CFSM_KianaC::Attack_4_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_4);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
	m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
}

void CFSM_KianaC::Attack_4_Update(float deltaTime)
{
	if (!m_checkUltraAtk && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk04)
	{
		m_pKiana->UltraAtk(CKiana::ATK04);
		m_checkUltraAtk = true;
	}

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk04)
	{
		m_pEffectMaker->CreateEffect_Attack4();

		if (m_pKiana->GetUltraMode())
		{
			m_pEffectMaker->CreateEffect_Claw4();
		}

		m_checkEffect = true;

		PlaySound_Attack_RandomVoice();

		if (m_pKiana->GetUltraMode())
			PlaySound_Effect(Sound_Ult_Att_2);
		else
			PlaySound_Effect(Sound_Attack_4_Effect);
	}

	if (!m_checkEffectSecond && m_pDM->GetAniTimeline() > 0.15f)
	{
		m_pEffectMaker->CreateEffect_Attack4();
		m_checkEffectSecond = true;
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Attack(Name_Attack_5))
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_4_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_pKiana->UnActiveAttackBall();
}

void CFSM_KianaC::Attack_4_Branch_Init(void)
{
	FixRootMotionOffset(Index_Attack_4_Branch);
}

void CFSM_KianaC::Attack_4_Branch_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_4_Branch);
	m_pStageControlTower->ActorControl_SetInputLock(true);

	m_checkEffect = false;
}

void CFSM_KianaC::Attack_4_Branch_Update(float deltaTime)
{
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Branch_Atk04)
	{
		//CreateEffect_Attack4();
		m_checkEffect = true;

		PlaySound_Voice(Sound_Branch_Voice_1);

		if (m_pKiana->GetUltraMode())
			PlaySound_Effect(Sound_Branch_1);
		else
			PlaySound_Effect(Sound_Branch_1);
	}

	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_4_Branch_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_KianaC::Attack_5_Init(void)
{
	FixRootMotionOffset(Index_Attack_5);
}

void CFSM_KianaC::Attack_5_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_5);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	ResetCheckMembers();
	m_pKiana->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, m_pKiana->GetRightToeWorldMatrix(), 0.3f);
}

void CFSM_KianaC::Attack_5_Update(float deltaTime)
{
	if (!m_checkUltraAtk && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk05)
	{
		m_pKiana->UltraAtk(CKiana::ATK05);
		m_checkUltraAtk = true;
	}

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk05)
	{
		m_pEffectMaker->CreateEffect_Attack5();
		m_checkEffect = true;

		PlaySound_Attack_RandomVoice();

		if (m_pKiana->GetUltraMode())
			PlaySound_Effect(Sound_Ult_Att_3);
		else
			PlaySound_Effect(Sound_Attack_5_Effect);
	}


	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;

}

void CFSM_KianaC::Attack_5_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_pKiana->UnActiveAttackBall();
}

void CFSM_KianaC::Attack_QTE_Init(void)
{
	FixRootMotionOffset(Index_Attack_QTE);
}

void CFSM_KianaC::Attack_QTE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_QTE);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_KianaC::Attack_QTE_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_QTE_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_KianaC::Die_Init(void)
{
}

void CFSM_KianaC::Die_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Die);
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
	m_pDM->RepeatAniSet(Index_EvadeBackward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	PlaySound_Attack_RandomEvade();

	m_isEvade = true;
	m_pKiana->OffHitbox();
	m_pKiana->SetIsEvade(true);
}

void CFSM_KianaC::EvadeBackward_Update(float deltaTime)
{
	if (m_isEvade && m_pDM->GetAniTimeline() > 0.3)
	{
		m_isEvade = false;
		m_pKiana->OnHitbox();
		m_pKiana->SetIsEvade(false);
	}

	if (!m_isSecondEvade && CheckAction_Evade_OnAction(Cool_Evade + 0.1f))
	{
		m_isSecondEvade = true;
		return;
	}
	if (CheckAction_Attack(Name_Attack_1, 0.4f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Run(0.3f))
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

void CFSM_KianaC::EvadeBackward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_isEvade = false;
	m_pKiana->OnHitbox();
	m_pKiana->SetIsEvade(false);
}

void CFSM_KianaC::EvadeForward_Init(void)
{
}

void CFSM_KianaC::EvadeForward_Enter(void)
{
	m_pDM->RepeatAniSet(Index_EvadeForward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
	PlaySound_Attack_RandomEvade();

	m_isEvade = true;
	m_pKiana->OffHitbox();
	m_pKiana->SetIsEvade(true);
}

void CFSM_KianaC::EvadeForward_Update(float deltaTime)
{
	if (m_isEvade&& m_pDM->GetAniTimeline() > 0.3)
	{
		m_isEvade = false;
		m_pKiana->OnHitbox();
		m_pKiana->SetIsEvade(false);
	}

	if (!m_isSecondEvade && CheckAction_Evade_OnAction(Cool_Evade + 0.1f))
	{
		m_isSecondEvade = true;
		return;
	}
	if (CheckAction_Attack(Name_Attack_1, 0.4f))
	{
		m_isSecondEvade = false;
		return;
	}
	if (CheckAction_Run(0.3f))
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

void CFSM_KianaC::EvadeForward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);

	m_isEvade = false;
	m_pKiana->OnHitbox();
	m_pKiana->SetIsEvade(false);
}

void CFSM_KianaC::Failure_Init(void)
{
}

void CFSM_KianaC::Failure_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Failure);
}

void CFSM_KianaC::Failure_Update(float deltaTime)
{
	if (m_pDM->IsAnimationEnd())
	{
		ChangeState(Name_Failure_Idle);
		return;
	}
}

void CFSM_KianaC::Failure_End(void)
{
}

void CFSM_KianaC::Failure_Idle_Init(void)
{
	m_pDM->SetLoopAnim(Index_Failure_Idle);
}

void CFSM_KianaC::Failure_Idle_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Failure_Idle);
}

void CFSM_KianaC::Failure_Idle_Update(float deltaTime)
{
}

void CFSM_KianaC::Failure_Idle_End(void)
{
}

void CFSM_KianaC::Hit_H_Init(void)
{
}

void CFSM_KianaC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H);

	PlaySound_Attack_RandomHit();
}

void CFSM_KianaC::Hit_H_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Hit_H_End(void)
{
}

void CFSM_KianaC::Hit_L_Init(void)
{
}

void CFSM_KianaC::Hit_L_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_L);

	PlaySound_Attack_RandomHit();
}

void CFSM_KianaC::Hit_L_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty - 0.2f))
		return;
	if (CheckAction_Run_OnAction(Cool_HitPenalty))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Hit_L_End(void)
{
}

void CFSM_KianaC::Idle_01_Init(void)
{
	FixRootMotionOffset(Index_Idle_01);
}

void CFSM_KianaC::Idle_01_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle_01);
}

void CFSM_KianaC::Idle_01_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Idle_01_End(void)
{
}


void CFSM_KianaC::Idle_02_Init(void)
{
	FixRootMotionOffset(Index_Idle_02);
}

void CFSM_KianaC::Idle_02_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle_02);
}

void CFSM_KianaC::Idle_02_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Idle_02_End(void)
{
}


void CFSM_KianaC::Idle_03_Init(void)
{
	FixRootMotionOffset(Index_Idle_03);
}

void CFSM_KianaC::Idle_03_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle_03);
}

void CFSM_KianaC::Idle_03_Update(float deltaTime)
{
	if (CheckAction_EvadeBackward(0.f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Idle_03_End(void)
{
}

void CFSM_KianaC::Run_Init(void)
{
	m_pDM->SetLoopAnim(Index_Run);
}

void CFSM_KianaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);
}

void CFSM_KianaC::Run_Update(float deltaTime)
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
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_KianaC::Run_End(void)
{
	m_runSoundTimer = 0.f;
}

void CFSM_KianaC::RunBS_Init(void)
{
}

void CFSM_KianaC::RunBS_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunBS);
}

void CFSM_KianaC::RunBS_Update(float deltaTime)
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
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
}

void CFSM_KianaC::RunBS_End(void)
{
}

void CFSM_KianaC::RunStopLeft_Init(void)
{
}

void CFSM_KianaC::RunStopLeft_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopLeft);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_KianaC::RunStopLeft_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Evade_OnAction(0.1f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_KianaC::RunStopLeft_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_KianaC::RunStopRight_Init(void)
{
}

void CFSM_KianaC::RunStopRight_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopRight);
	m_pStageControlTower->ActorControl_SetInputLock(true);

}

void CFSM_KianaC::RunStopRight_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Evade_OnAction(0.1f))
		return;
	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_KianaC::RunStopRight_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_KianaC::WeaponSkill_Init(void)
{
}

void CFSM_KianaC::WeaponSkill_Enter(void)
{
}

void CFSM_KianaC::WeaponSkill_Update(float deltaTime)
{
}

void CFSM_KianaC::WeaponSkill_End(void)
{
}

void CFSM_KianaC::Stun_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Stun);
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
	m_pDM->ChangeAniSet(Index_SwitchIn);
}

void CFSM_KianaC::SwitchIn_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::SwitchIn_End(void)
{
	CStageControlTower::GetInstance()->EndSwitching();
}

void CFSM_KianaC::SwitchOut_Init(void)
{
}

void CFSM_KianaC::SwitchOut_Enter(void)
{
	m_pDM->ChangeAniSet(Index_SwitchOut);
}

void CFSM_KianaC::SwitchOut_Update(float deltaTime)
{
	if (m_pDM->GetAniTimeline() > 0.75)
	{
		m_pKiana->SetIsEnabled(false);
		return;
	}
}

void CFSM_KianaC::SwitchOut_End(void)
{
}

void CFSM_KianaC::Ultra_Init(void)
{
}

void CFSM_KianaC::Ultra_Enter(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(true);
	m_pDM->ChangeAniSet(Index_Ultra);

	PlaySound_Voice(Sound_Ult_Start_Voice);
	PlaySound_Effect(Sound_Ult_Start);
	m_pEffectMaker->CreateEffect_Ultra();
}

void CFSM_KianaC::Ultra_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Ultra_End(void)
{
	m_pKiana->SetUltraMode(true);
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_KianaC::Victory_Init(void)
{
}

void CFSM_KianaC::Victory_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Victory);
}

void CFSM_KianaC::Victory_Update(float deltaTime)
{
	if (m_pDM->IsAnimationEnd())
	{
		ChangeState(Name_Victory_Idle);
		return;
	}
}

void CFSM_KianaC::Victory_End(void)
{
}

void CFSM_KianaC::Victory_Idle_Init(void)
{
	m_pDM->SetLoopAnim(Index_Victory_Idle);
}

void CFSM_KianaC::Victory_Idle_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Victory_Idle);
}

void CFSM_KianaC::Victory_Idle_Update(float deltaTime)
{
}

void CFSM_KianaC::Victory_Idle_End(void)
{
}

void CFSM_KianaC::RegisterAllState()
{
	Engine::CState* pState;

	CreateState(CFSM_KianaC, pState, Appear)
		AddState(pState, Name_Appear);

	CreateState(CFSM_KianaC, pState, Attack_1)
		AddState(pState, Name_Attack_1);

	CreateState(CFSM_KianaC, pState, Attack_2)
		AddState(pState, Name_Attack_2);

	CreateState(CFSM_KianaC, pState, Attack_3)
		AddState(pState, Name_Attack_3);

	CreateState(CFSM_KianaC, pState, Attack_3_Branch)
		AddState(pState, Name_Attack_3_Branch);

	CreateState(CFSM_KianaC, pState, Attack_4)
		AddState(pState, Name_Attack_4);

	CreateState(CFSM_KianaC, pState, Attack_4_Branch)
		AddState(pState, Name_Attack_4_Branch);

	CreateState(CFSM_KianaC, pState, Attack_5)
		AddState(pState, Name_Attack_5);

	CreateState(CFSM_KianaC, pState, Attack_QTE)
		AddState(pState, Name_Attack_QTE);

	CreateState(CFSM_KianaC, pState, Die)
		AddState(pState, Name_Die);

	CreateState(CFSM_KianaC, pState, EvadeBackward)
		AddState(pState, Name_EvadeBackward);

	CreateState(CFSM_KianaC, pState, EvadeForward)
		AddState(pState, Name_EvadeForward);

	CreateState(CFSM_KianaC, pState, Failure)
		AddState(pState, Name_Failure);

	CreateState(CFSM_KianaC, pState, Failure_Idle)
		AddState(pState, Name_Failure_Idle);

	CreateState(CFSM_KianaC, pState, Hit_H)
		AddState(pState, Name_Hit_H);

	CreateState(CFSM_KianaC, pState, Hit_L)
		AddState(pState, Name_Hit_L);

	CreateState(CFSM_KianaC, pState, Idle_01)
		AddState(pState, Name_Idle_01);

	CreateState(CFSM_KianaC, pState, Idle_02)
		AddState(pState, Name_Idle_02);
	
	CreateState(CFSM_KianaC, pState, Idle_03)
		AddState(pState, Name_Idle_03);

	CreateState(CFSM_KianaC, pState, Run)
		AddState(pState, Name_Run);

	CreateState(CFSM_KianaC, pState, RunBS)
		AddState(pState, Name_RunBS);

	CreateState(CFSM_KianaC, pState, RunStopLeft)
		AddState(pState, Name_RunStopLeft);

	CreateState(CFSM_KianaC, pState, RunStopRight)
		AddState(pState, Name_RunStopRight);

	CreateState(CFSM_KianaC, pState, StandBy)
		AddState(pState, Name_StandBy);

	CreateState(CFSM_KianaC, pState, SwitchIn)
		AddState(pState, Name_SwitchIn);

	CreateState(CFSM_KianaC, pState, SwitchOut)
		AddState(pState, Name_SwitchOut);

	CreateState(CFSM_KianaC, pState, Ultra)
		AddState(pState, Name_Ultra);

	CreateState(CFSM_KianaC, pState, Victory)
		AddState(pState, Name_Victory);

	CreateState(CFSM_KianaC, pState, Victory_Idle)
		AddState(pState, Name_Victory_Idle);

}
