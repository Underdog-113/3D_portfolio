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

	__super::Start(spThis);

	RegisterAllState();

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pSakura->GetComponent<Engine::CMeshC>()->GetMeshData());
	m_pStageControlTower = CStageControlTower::GetInstance();

	SetStartState(Name_StandBy);
	m_curState->DoEnter();
}

void CFSM_SakuraC::FixRootMotionOffset(_uint index)
{
	m_pSakura->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}

void CFSM_SakuraC::ResetCheckMembers()
{
	//m_checkEffect = false;
	//m_checkEffectSecond = false;
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

bool CFSM_SakuraC::CheckAction_Run()
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

bool CFSM_SakuraC::CheckAction_Run_OnAction(float coolTime)
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

bool CFSM_SakuraC::CheckAction_Idle()
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

bool CFSM_SakuraC::CheckAction_RunBS_To_Run()
{
	if (m_pDM->GetAniTimeline() > Cool_End - 0.25f)
	{
		ChangeState(Name_Run);
		return true;
	}
	return false;
}


void CFSM_SakuraC::Appear_Init(void)
{
}

void CFSM_SakuraC::Appear_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Appear);
}

void CFSM_SakuraC::Appear_Update(float deltaTime)
{
	if (m_pDM->GetAniCtrl()->IsItEnd())
	{
		switch (m_appearOption)
		{
		case CFSM_SakuraC::None:
			ChangeState(Name_StandBy);
			break;
		case CFSM_SakuraC::QTE:
			ChangeState(Name_StandBy);
			break;
		default:
			break;
		}
		return;
	}
}

void CFSM_SakuraC::Appear_End(void)
{
	m_appearOption = None;
}

void CFSM_SakuraC::StandBy_Init(void)
{
}

void CFSM_SakuraC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
}

void CFSM_SakuraC::StandBy_Update(float deltaTime)
{
	if (CheckAction_Run())
		return;

// 	if (CheckAction_Attack(Name_ATTACK1, 0.f))
// 		return;

	if (CheckAction_EvadeBackward(0.f))
		return;

	//if (CheckAction_Ultra())
	//	return;

// 	if (Engine::IMKEY_DOWN(StageKey_QTE))
// 	{
// 		ChangeState(Name_APPEAR);
// 		m_appearOption = QTE;
// 		return;
// 	}

}

void CFSM_SakuraC::StandBy_End(void)
{
}

void CFSM_SakuraC::Run_Init(void)
{
}

void CFSM_SakuraC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);
}

void CFSM_SakuraC::Run_Update(float deltaTime)
{
	//m_runSoundTimer += GET_DT;
	//if (m_runSoundTimer > 0.3f)
	//{
	//	m_runSoundTimer = 0.f;
	//	PlaySound_Attack_RandomRun();
	//}


	if (CheckAction_Run_End())
		return;
// 	if (CheckAction_Attack(Name_ATTACK1, 0.f))
// 		return;
	if (CheckAction_EvadeForward())
		return;
	//if (CheckAction_Ultra())
	//	return;
}

void CFSM_SakuraC::Run_End(void)
{
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

	if (CheckAction_RunBS_To_Run())
		return;

	if (CheckAction_Run_End())
		return;

	if (CheckAction_Idle())
		return;
// 	if (CheckAction_Attack(Name_ATTACK1, 0.f))
// 		return;
	if (CheckAction_EvadeForward())
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
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Run())
		return;
	//if (CheckAction_Attack(Name_ATTACK1, 0.f))
	//	return;
	if (CheckAction_EvadeForward())
		return;
	//if (CheckAction_Ultra())
	//	return;
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
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Run())
		return;
// 	if (CheckAction_Attack(Name_ATTACK2, 0.f))
// 		return;
	if (CheckAction_EvadeForward())
		return;
	// 	if (CheckAction_Ultra())
	// 		return;
}

void CFSM_SakuraC::RunStopRight_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::EvadeForward_Init(void)
{
}

void CFSM_SakuraC::EvadeForward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_EvadeForward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_SakuraC::EvadeForward_Update(float deltaTime)
{
	if (CheckAction_Run_OnAction(0.5f))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_SakuraC::EvadeForward_End(void)
{
	m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::EvadeBackward_Init(void)
{
}

void CFSM_SakuraC::EvadeBackward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_EvadeBackward);
	m_pStageControlTower->ActorControl_SetInputLock(true);
}

void CFSM_SakuraC::EvadeBackward_Update(float deltaTime)
{
	if (CheckAction_Run_OnAction(0.5f))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}


void CFSM_SakuraC::EvadeBackward_End(void)
{
	 m_pStageControlTower->ActorControl_SetInputLock(false);
}

void CFSM_SakuraC::SwitchIn_Init(void)
{
}

void CFSM_SakuraC::SwitchIn_Enter(void)
{
	m_pDM->ChangeAniSet(Index_switchin);
}

void CFSM_SakuraC::SwitchIn_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_SakuraC::SwitchIn_End(void)
{
}

void CFSM_SakuraC::SwitchOut_Init(void)
{
}

void CFSM_SakuraC::SwitchOut_Enter(void)
{
	m_pDM->ChangeAniSet(Index_switchrole);
}

void CFSM_SakuraC::SwitchOut_Update(float deltaTime)
{
	if (m_pDM->GetAniTimeline() > 0.6)
	{
		m_pSakura->SetIsEnabled(false);
		return;
	}
}

void CFSM_SakuraC::SwitchOut_End(void)
{
}

void CFSM_SakuraC::RegisterAllState()
{
	Engine::CState* pState;

	CreateState(CFSM_SakuraC, pState, StandBy)
		AddState(pState, Name_StandBy);

	CreateState(CFSM_SakuraC, pState, Run)
		AddState(pState, Name_Run);

	CreateState(CFSM_SakuraC, pState, RunBS)
		AddState(pState, Name_RunBS);

	CreateState(CFSM_SakuraC, pState, RunStopLeft)
		AddState(pState, Name_RunStopLeft);

	CreateState(CFSM_SakuraC, pState, RunStopRight)
		AddState(pState, Name_RunStopRight);

	CreateState(CFSM_SakuraC, pState, EvadeForward)
		AddState(pState, Name_EvadeForward);

	CreateState(CFSM_SakuraC, pState, EvadeBackward)
		AddState(pState, Name_EvadeBackward);

	CreateState(CFSM_SakuraC, pState, SwitchIn)
		AddState(pState, Name_switchin);

	CreateState(CFSM_SakuraC, pState, SwitchOut)
		AddState(pState, Name_switchrole);
}