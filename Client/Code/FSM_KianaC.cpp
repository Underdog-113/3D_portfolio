#include "stdafx.h"
#include "FSM_KianaC.h"

#include "AttackTrail_Client.h"
#include "ObjectFactory.h"
#include "State.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "FSMDefine_Kiana.h"
#include "StageControlTower.h"
#include "Kiana.h"


CFSM_KianaC::CFSM_KianaC()
{
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

	RegisterAllState();

	__super::Start(spThis);

	m_pDM = static_cast<Engine::CDynamicMeshData*>(m_pKiana->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
	m_pStageControlTower = CStageControlTower::GetInstance();

	SetStartState(L"Appear");
	m_curState->DoEnter();
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

	CreateState(CFSM_KianaC, pState, Hit_H)
		AddState(pState, Name_Hit_H);

	CreateState(CFSM_KianaC, pState, Hit_L)
		AddState(pState, Name_Hit_L);

	CreateState(CFSM_KianaC, pState, Idle_01)
		AddState(pState, Name_Idle_01);

	CreateState(CFSM_KianaC, pState, Idle_1to2)
		AddState(pState, Name_Idle_1to2);

	CreateState(CFSM_KianaC, pState, Idle_02)
		AddState(pState, Name_Idle_02);

	CreateState(CFSM_KianaC, pState, Idle_2to3)
		AddState(pState, Name_Idle_2to3);

	CreateState(CFSM_KianaC, pState, Idle_03)
		AddState(pState, Name_Idle_03);

	CreateState(CFSM_KianaC, pState, Idle_3to4)
		AddState(pState, Name_Idle_3to4);

	CreateState(CFSM_KianaC, pState, Idle_4to5)
		AddState(pState, Name_Idle_4to5);

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

	CreateState(CFSM_KianaC, pState, Skill_10)
		AddState(pState, Name_Skill_10);
}

void CFSM_KianaC::FixRootMotionOffset(_uint index)
{
	m_pKiana->GetComponent<Engine::CMeshC>()->GetRootMotion()->OnFixRootMotionOffset(index);
}


void CFSM_KianaC::CreateEffect(std::wstring name)
{

	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(L"AttackTrail_Client", true, (_int)ELayerID::Effect, L"Cube0");

	//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spMeshEffect->GetComponent<Engine::CMeshC>()->AddMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetisEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackTrail_01");
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackTrail_12");
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshTrailShader);

	spMeshEffect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	spMeshEffect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	//spMeshEffect->GetTransform()->AddRotationX(D3DXToRadian(90.f));
}

void CFSM_KianaC::CreateEffect_Attack1()
{
	auto effect = m_pKiana->CreateEffect(L"Kiana_Attack_0");
	effect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(0.5f, 0.5f, 0.5f));
	effect->GetTransform()->SetRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CFSM_KianaC::CreateEffect_Attack2()
{
	auto effect = m_pKiana->CreateEffect(L"Kiana_Attack_1");
	effect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(0.5f, 0.5f, 0.5f));
	effect->GetTransform()->SetRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CFSM_KianaC::CreateEffect_Attack3()
{
	auto effect = m_pKiana->CreateEffect(L"Kiana_Attack_2");
	effect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(0.5f, 0.5f, 0.5f));
	effect->GetTransform()->SetRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CFSM_KianaC::CreateEffect_Attack4()
{
	auto effect = m_pKiana->CreateEffect(L"Kiana_Attack_3");
	effect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(0.5f, 0.5f, 0.5f));
	effect->GetTransform()->SetRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CFSM_KianaC::CreateEffect_Attack5()
{
	auto effect = m_pKiana->CreateEffect(L"Kiana_Attack_4");
	effect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(0.5f, 0.5f, 0.5f));
	effect->GetTransform()->SetRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

bool CFSM_KianaC::CheckAction_Attack(const std::wstring& switchStateName, float coolTime /*= Cool_Attack*/)
{
	if (Engine::IMKEY_DOWN(StageKey_Attack))
	{
		if (m_pDM->GetAniTimeline() > coolTime)
		{
			ChangeState(switchStateName);
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

bool CFSM_KianaC::CheckAction_StandBy_Timeout(float coolTime /*= Cool_End*/)
{
	if (m_pDM->GetAniTimeline() > coolTime)
	{
		ChangeState(Name_StandBy);
		return true;
	}

	return false;
}

bool CFSM_KianaC::CheckAction_Run()
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
	if (m_pDM->GetAniTimeline() > Cool_End)
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
		ChangeState(Name_Skill_10);
		return true;
	}
	return false;
}


void CFSM_KianaC::StandBy_Init(void)
{
}

void CFSM_KianaC::StandBy_Enter(void)
{
	m_pDM->ChangeAniSet(Index_StandBy);
}

void CFSM_KianaC::StandBy_Update(float deltaTime)
{
	if (CheckAction_Run())
		return;

	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;

	if (CheckAction_EvadeBackward(0.f))
		return;

	if (CheckAction_Ultra())
		return;

	if (Engine::IMKEY_DOWN(StageKey_QTE))
	{
		ChangeState(Name_Appear);
		m_appearOption = QTEAppear;
		return;
	}

	if (Engine::IMKEY_DOWN(StageKey_Test_Emotion))
	{
		ChangeState(Name_Idle_01);
		return;
	}

	if (Engine::IMKEY_DOWN(StageKey_Test_Hit_L))
	{
		ChangeState(Name_Hit_L);
		return;
	}

	if (Engine::IMKEY_DOWN(StageKey_Test_Hit_H))
	{
		ChangeState(Name_Hit_H);
		return;
	}
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
		case CFSM_KianaC::QTEAppear:
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
	m_pStageControlTower->SetInputLock_ByAni(true);

	m_checkUltraRing = false;
	m_checkUltraAtk = false;
	m_checkEffect = false;
}

void CFSM_KianaC::Attack_1_Update(float deltaTime)
{
	if (!m_checkUltraRing && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk01 - 0.1f)
	{
		m_pKiana->UltraAtk_Ring(CKiana::ATK01);
		m_checkUltraRing = true;
	}

	if (!m_checkUltraAtk && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk01)
	{
		m_pKiana->UltraAtk(CKiana::ATK01);
		m_checkUltraAtk = true;
	}

	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk01)
	{
		CreateEffect_Attack1();
		m_checkEffect = true;
	}

	if (CheckAction_Attack(Name_Attack_2, 0.3f))
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_1_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_2_Init(void)
{
	FixRootMotionOffset(Index_Attack_2);
}

void CFSM_KianaC::Attack_2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_2);
	m_pStageControlTower->SetInputLock_ByAni(true);
	m_checkUltraAtk = false;
	m_checkEffect = false;
}

void CFSM_KianaC::Attack_2_Update(float deltaTime)
{
	if (!m_checkUltraAtk && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk02)
	{
		m_pKiana->UltraAtk(CKiana::ATK02);
		m_checkUltraAtk = true;
	}
	if (!m_checkEffect && m_pDM->GetAniTimeline() > Delay_CreateCatPaw_Atk02)
	{
		CreateEffect_Attack2();
		m_checkEffect = true;
	}

	if (CheckAction_BranchAttack())
		return;
	if (CheckAction_Attack(Name_Attack_3))
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_2_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_3_Init(void)
{
	FixRootMotionOffset(Index_Attack_3);
}

void CFSM_KianaC::Attack_3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3);
	m_pStageControlTower->SetInputLock_ByAni(true);
	m_checkUltraAtk = false;
	m_checkEffect = false;
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
		CreateEffect_Attack3();
		m_checkEffect = true;
	}

	if (CheckAction_Attack(Name_Attack_4))
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_3_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_3_Branch_Init(void)
{
	FixRootMotionOffset(Index_Attack_3_Branch);
}

void CFSM_KianaC::Attack_3_Branch_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_3_Branch);
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_3_Branch_Update(float deltaTime)
{
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
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_4_Init(void)
{
	FixRootMotionOffset(Index_Attack_4);
}

void CFSM_KianaC::Attack_4_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_4);
	m_pStageControlTower->SetInputLock_ByAni(true);
	m_checkUltraAtk = false;
	m_checkEffect = false;
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
		CreateEffect_Attack4();
		m_checkEffect = true;
	}

	if (CheckAction_Attack(Name_Attack_5))
		return;
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_4_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_4_Branch_Init(void)
{
	FixRootMotionOffset(Index_Attack_4_Branch);
}

void CFSM_KianaC::Attack_4_Branch_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_4_Branch);
	m_pStageControlTower->SetInputLock_ByAni(true);
}

void CFSM_KianaC::Attack_4_Branch_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction())
		return;
	if (CheckAction_Run_OnAction(Cool_RunOnAttack))
		return;

	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Attack_4_Branch_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_5_Init(void)
{
	FixRootMotionOffset(Index_Attack_5);
}

void CFSM_KianaC::Attack_5_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_5);
	m_pStageControlTower->SetInputLock_ByAni(true);
	m_checkUltraAtk = false;
	m_checkEffect = false;
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
		CreateEffect_Attack5();
		m_checkEffect = true;
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
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Attack_QTE_Init(void)
{
	FixRootMotionOffset(Index_Attack_QTE);
}

void CFSM_KianaC::Attack_QTE_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Attack_QTE);
	m_pStageControlTower->SetInputLock_ByAni(true);
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
	m_pStageControlTower->SetInputLock_ByAni(false);
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
	m_pDM->ChangeAniSet(Index_EvadeBackward);
	m_pStageControlTower->SetInputLock_ByAni(true);
}

void CFSM_KianaC::EvadeBackward_Update(float deltaTime)
{
	if (CheckAction_Run_OnAction(0.5f))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::EvadeBackward_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::EvadeForward_Init(void)
{
}	

void CFSM_KianaC::EvadeForward_Enter(void)
{
	m_pDM->ChangeAniSet(Index_EvadeForward);
	m_pStageControlTower->SetInputLock_ByAni(true);
}

void CFSM_KianaC::EvadeForward_Update(float deltaTime)
{
	if (CheckAction_Run_OnAction(0.5f))
		return;
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::EvadeForward_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Hit_H_Init(void)
{
}

void CFSM_KianaC::Hit_H_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Hit_H);
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
}

void CFSM_KianaC::Hit_L_Update(float deltaTime)
{
	if (CheckAction_Evade_OnAction(Cool_HitPenalty))
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
	if (CheckAction_Emotion(Name_Idle_1to2))
		return;
}

void CFSM_KianaC::Idle_01_End(void)
{
}

void CFSM_KianaC::Idle_1to2_Init(void)
{
	FixRootMotionOffset(Index_Idle_1to2);
}

void CFSM_KianaC::Idle_1to2_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle_1to2);
}

void CFSM_KianaC::Idle_1to2_Update(float deltaTime)
{
	if (CheckAction_Emotion(Name_Idle_02))
		return;
}

void CFSM_KianaC::Idle_1to2_End(void)
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
	if (CheckAction_Emotion(Name_Idle_2to3))
		return;
}

void CFSM_KianaC::Idle_02_End(void)
{
}

void CFSM_KianaC::Idle_2to3_Init(void)
{
	FixRootMotionOffset(Index_Idle_2to3);
}

void CFSM_KianaC::Idle_2to3_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle_2to3);
}

void CFSM_KianaC::Idle_2to3_Update(float deltaTime)
{
	if (CheckAction_Emotion(Name_Idle_03))
		return;
}

void CFSM_KianaC::Idle_2to3_End(void)
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
	if (CheckAction_Emotion(Name_Idle_3to4))
		return;
}

void CFSM_KianaC::Idle_03_End(void)
{
}

void CFSM_KianaC::Idle_3to4_Init(void)
{
	FixRootMotionOffset(Index_Idle_3to4);
}

void CFSM_KianaC::Idle_3to4_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle_3to4);
}

void CFSM_KianaC::Idle_3to4_Update(float deltaTime)
{
	if (CheckAction_Emotion(Name_Idle_4to5))
		return;
}

void CFSM_KianaC::Idle_3to4_End(void)
{
}

void CFSM_KianaC::Idle_4to5_Init(void)
{
	FixRootMotionOffset(Index_Idle_4to5);
}

void CFSM_KianaC::Idle_4to5_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Idle_4to5);
}

void CFSM_KianaC::Idle_4to5_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Idle_4to5_End(void)
{
}

void CFSM_KianaC::Run_Init(void)
{
}

void CFSM_KianaC::Run_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Run);
}

void CFSM_KianaC::Run_Update(float deltaTime)
{
	if (CheckAction_Run_End())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_KianaC::Run_End(void)
{
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
	if (CheckAction_RunBS_To_Run())
		return;

	if (CheckAction_Run_End())
		return;

	if (CheckAction_StandBy())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_EvadeForward())
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
	m_pStageControlTower->SetInputLock_ByAni(true);
}

void CFSM_KianaC::RunStopLeft_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_KianaC::RunStopLeft_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::RunStopRight_Init(void)
{
}

void CFSM_KianaC::RunStopRight_Enter(void)
{
	m_pDM->ChangeAniSet(Index_RunStopRight);
	m_pStageControlTower->SetInputLock_ByAni(true);
}

void CFSM_KianaC::RunStopRight_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;

	if (CheckAction_Run())
		return;
	if (CheckAction_Attack(Name_Attack_1, 0.f))
		return;
	if (CheckAction_EvadeForward())
		return;
	if (CheckAction_Ultra())
		return;
}

void CFSM_KianaC::RunStopRight_End(void)
{
	m_pStageControlTower->SetInputLock_ByAni(false);
}

void CFSM_KianaC::Skill_10_Init(void)
{
}

void CFSM_KianaC::Skill_10_Enter(void)
{
	m_pDM->ChangeAniSet(Index_Skill_10);
}

void CFSM_KianaC::Skill_10_Update(float deltaTime)
{
	if (CheckAction_StandBy_Timeout())
		return;
}

void CFSM_KianaC::Skill_10_End(void)
{
	m_pKiana->SetUltraMode(true);
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
}

void CFSM_KianaC::SwitchIn_End(void)
{
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
}

void CFSM_KianaC::SwitchOut_End(void)
{
}
