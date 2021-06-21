#include "stdafx.h"
#include "UILinker.h"

#include "BattleUiManager.h"
#include "StageControlTower.h"
#include "Valkyrie.h"
#include "Monster.h"

CUILinker::CUILinker()
{
	m_pUIManager = CBattleUiManager::GetInstance();
}


CUILinker::~CUILinker()
{
}

void CUILinker::PlayerChange(void)
{
	auto pStat = m_pCT->GetCurrentActor()->GetStat();
	m_pUIManager->PlayerChange(
		pStat->GetCurHp() / pStat->GetMaxHp() * 100.f,
		pStat->GetCurSp() / pStat->GetMaxSp() * 100.f,
		L"Skill_Kiana_PT_001",
		L"Skill_Kiana_PT_003",
		L"Skill_Kiana_PT_004",
		L"Skill_Kiana_Weapon_09",
		L"Defalut",
		L"Defalut");
}

void CUILinker::PlayerChange_Test(void)
{
	auto pStat = m_pCT->GetCurrentActor()->GetStat();
	m_pUIManager->PlayerChange(
		pStat->GetCurHp() / pStat->GetMaxHp() * 100.f,
		pStat->GetCurSp() / pStat->GetMaxSp() * 100.f,
		L"Skill_Kiana_PT_001",
		L"Skill_Kiana_PT_001",
		L"Skill_Kiana_PT_001",
		L"Skill_Kiana_PT_001",
		L"Defalut",
		L"Defalut");
}

void CUILinker::PlayerHpSet()
{
	auto pStat = m_pCT->GetCurrentActor()->GetStat();
	m_pUIManager->PlayerHp(pStat->GetCurHp() / pStat->GetMaxHp() * 100.f);
}

void CUILinker::PlayerSpSet()
{
	auto pStat = m_pCT->GetCurrentActor()->GetStat();
	m_pUIManager->PlayerSp(pStat->GetCurSp() / pStat->GetMaxSp() * 100.f);
}

void CUILinker::MoveJoyStick()
{
	_ubyte flag;
	if (m_pCT->GetInputLock_ByAni())
	{
		flag = m_pCT->GetReserveMoveFlag();
	}
	else
	{
		flag = m_pCT->GetMoveFlag();
	}


	if (flag & MoveFlag_Left)
	{
		if (flag & MoveFlag_Forward)
			m_pUIManager->KeyPad((_uint)LU);
		else if(flag & MoveFlag_Back)
			m_pUIManager->KeyPad((_uint)LD);
		else
			m_pUIManager->KeyPad((_uint)L);
	}
	else if (flag & MoveFlag_Right)
	{
		if (flag & MoveFlag_Forward)
			m_pUIManager->KeyPad((_uint)RU);
		else if (flag & MoveFlag_Back)
			m_pUIManager->KeyPad((_uint)RD);
		else
			m_pUIManager->KeyPad((_uint)R);
	}
	else if (flag & MoveFlag_Forward)
	{
		m_pUIManager->KeyPad((_uint)U);
	}

	else if (flag & MoveFlag_Back)
	{
		m_pUIManager->KeyPad((_uint)D);
	}
	else
	{
		m_pUIManager->KeyPad((_uint)Center);
	}
}

void CUILinker::Skill()
{
	V_Stat* stat = m_pCT->GetCurrentActor()->GetStat();

	_float cost = stat->GetSkillCost();
	_float cooltime = stat->GetSkillCoolTime();
	
	m_pUIManager->SkillExecution(
		CBattleUiManager::Button_Type::SkillButton,
		(_int)cost,
		cooltime);

	OnTargetMarker();
}

void CUILinker::Ultra()
{
	V_Stat* stat = m_pCT->GetCurrentActor()->GetStat();

	_float cost = stat->GetUltraCost();
	_float cooltime = stat->GetUltraCoolTime();

	m_pUIManager->SkillExecution(
		CBattleUiManager::Button_Type::SpecialButton,
		(_int)cost,
		cooltime);

	OnTargetMarker();
}

void CUILinker::Evade()
{
	V_Stat* stat = m_pCT->GetCurrentActor()->GetStat();

	m_pUIManager->SkillExecution(
		CBattleUiManager::Button_Type::EvasionButton,
		0,
		0.1f);
}

void CUILinker::Attack()
{
	V_Stat* stat = m_pCT->GetCurrentActor()->GetStat();

	m_pUIManager->SkillExecution(
		CBattleUiManager::Button_Type::BasicButton,
		0,
		0.1f);

	OnTargetMarker();
}

void CUILinker::SwapToOne(void)
{
}

void CUILinker::SwapToTwo(void)
{
}

void CUILinker::Hit_Up(void)
{
	float time = m_pCT->GetChainLimitTime();
	m_pUIManager->HitCount(time);
}

void CUILinker::OnTargetMarker(void)
{
	auto pTarget = CStageControlTower::GetInstance()->GetCurrentTarget();
	if(pTarget)
		m_pUIManager->TargetUI(pTarget->GetTransform()->GetPosition(), 3.f);
}

void CUILinker::OffTargetMarker(void)
{
	//m_pUIManager->
}

void CUILinker::MonsterInfoSet()
{
	M_Stat* pStat = ((CMonster*)m_pCT->GetCurrentTarget().get())->GetStat();

	std::wstring name = pStat->Getname();
	_float hp = pStat->GetCurHp();
	std::wstring monsterProperty = L"UP";

	m_pUIManager->MonsterState(name, hp, monsterProperty);
}

void CUILinker::MonsterHpSet()
{
	//_float value
}
