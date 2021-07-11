#include "stdafx.h"
#include "UILinker.h"

#include "BattleUiManager.h"
#include "StageControlTower.h"
#include "ActorController.h"
#include "Valkyrie.h"
#include "Monster.h"

CUILinker::CUILinker()
{
	m_pUIManager = CBattleUiManager::GetInstance();
}


CUILinker::~CUILinker()
{
}

void CUILinker::UpdateLinker(void)
{
	// target hp

	// wp skill cool
	// ult cool

	// player hp
	PlayerHpSet();
	// player sp
	PlayerSpSet();


}

void CUILinker::SwitchValkyrie(WaitSlot slot, V_Stat::Valkyrie_Type switchIn, V_Stat::Valkyrie_Type switchOut)
{
	SwitchValkyrie_Actor(switchIn);

	switch (slot)
	{
	case CUILinker::Up:
		SwitchValkyrie_UpSlot(switchOut);
		break;
	case CUILinker::Down:
		SwitchValkyrie_DownSlot(switchOut);
			break;
	default:
		break;
	}
	
}

void CUILinker::SwitchValkyrie_UpSlot(V_Stat::Valkyrie_Type switchOut)
{
	CValkyrie* wait1member = static_cast<CValkyrie*>(m_pCT->GetSquad()[CStageControlTower::Wait_1].get());
	V_Stat* stat = wait1member->GetStat();

	switch (switchOut)
	{
	case V_Stat::Valkyrie_Type::KIANA:
		m_pUIManager->WaitingPlayerState(
			0,
			L"Kiana_Battle",
			L"AvatarShengWu",
			stat->GetCurHp() / stat->GetMaxHp() * 100.f,
			stat->GetCurSp() / stat->GetMaxSp() * 100.f);
		break;
	case V_Stat::Valkyrie_Type::THERESA:
		m_pUIManager->WaitingPlayerState(
			0,
			L"Teresa_Battle",
			L"AvatarJiXie",
			stat->GetCurHp() / stat->GetMaxHp() * 100.f,
			stat->GetCurSp() / stat->GetMaxSp() * 100.f);
		m_pUIManager->SpecialUICanvasOff();
		break;
	case V_Stat::Valkyrie_Type::SAKURA:
		m_pUIManager->WaitingPlayerState(
			0,
			L"Sakura_Battle",
			L"AvatarYiNeng",
			stat->GetCurHp() / stat->GetMaxHp() * 100.f,
			stat->GetCurSp() / stat->GetMaxSp() * 100.f);
		break;
	default:
		break;
	}
}

void CUILinker::SwitchValkyrie_DownSlot(V_Stat::Valkyrie_Type switchOut)
{
	CValkyrie* wait1member = static_cast<CValkyrie*>(m_pCT->GetSquad()[CStageControlTower::Wait_1].get());
	V_Stat* stat = wait1member->GetStat();

	switch (switchOut)
	{
	case V_Stat::Valkyrie_Type::KIANA:
		m_pUIManager->WaitingPlayerState(
			1,
			L"Kiana_Battle",
			L"AvatarShengWu",
			stat->GetCurHp() / stat->GetMaxHp() * 100.f,
			stat->GetCurSp() / stat->GetMaxSp() * 100.f);
		break;
	case V_Stat::Valkyrie_Type::THERESA:
		m_pUIManager->WaitingPlayerState(
			1,
			L"Teresa_Battle",
			L"AvatarJiXie",
			stat->GetCurHp() / stat->GetMaxHp() * 100.f,
			stat->GetCurSp() / stat->GetMaxSp() * 100.f);
		m_pUIManager->SpecialUICanvasOff();
		break;
	case V_Stat::Valkyrie_Type::SAKURA:
		m_pUIManager->WaitingPlayerState(
			1,
			L"Sakura_Battle",
			L"AvatarYiNeng",
			stat->GetCurHp() / stat->GetMaxHp() * 100.f,
			stat->GetCurSp() / stat->GetMaxSp() * 100.f);
		break;
	default:
		break;
	}
}


void CUILinker::SwitchValkyrie_Actor(V_Stat::Valkyrie_Type switchIn)
{
	switch (switchIn)
	{
	case V_Stat::Valkyrie_Type::KIANA:
		m_pUIManager->PlayerChange(
			L"Skill_Kiana_PT_001",
			L"Skill_Kiana_PT_003",
			L"Skill_Kiana_PT_004",
			L"Skill_Kiana_Weapon_09",
			10,
			100,
			0, 0, 0); // 회피,궁,아이템스킬
		break;
	case V_Stat::Valkyrie_Type::THERESA:
		m_pUIManager->PlayerChange(
			L"Skill_Theresa_0",
			L"Skill_Theresa_1",
			L"Skill_Theresa_2",
			L"Skill_Theresa_3",
			20,
			100,
			0, 0, 0); // 회피,궁,아이템스킬
		m_pUIManager->SpecialUICanvasOn();
		break;
	case V_Stat::Valkyrie_Type::SAKURA:
		m_pUIManager->PlayerChange(
			L"Skill_Sakura_0",
			L"Skill_Sakura_1",
			L"Skill_Sakura_2",
			L"Skill_Sakura_3",
			10,
			11,
			0,0,0); // 회피,궁,아이템스킬
		break;
	default:
		break;
	}

}

void CUILinker::PlayerHpSet()
{
	auto pStat = m_pCT->GetCurrentActor()->GetStat();

	m_pUIManager->PlayerHpMax(pStat->GetMaxHp());
	m_pUIManager->PlayerHp(pStat->GetCurHp());
}

void CUILinker::PlayerSpSet()
{
	auto pStat = m_pCT->GetCurrentActor()->GetStat();

	m_pUIManager->PlayerSpMax(pStat->GetMaxSp());
	m_pUIManager->PlayerSp(pStat->GetCurSp());
}

void CUILinker::MoveJoyStick()
{
	auto pActorController = m_pCT->GetActorController();
	_ubyte flag;
	if (pActorController->GetInputLock_ByAni())
	{
		flag = pActorController->GetReserveMoveFlag();
	}
	else
	{
		flag = pActorController->GetMoveFlag();
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

}

void CUILinker::Evade()
{
	m_pCT->OffCameraTargeting();
}

void CUILinker::Attack()
{
	m_pCT->FindTarget();
}

void CUILinker::SwapToOne(void)
{
}

void CUILinker::SwapToTwo(void)
{
}

void CUILinker::MonsterHpDown(_float damage)
{
	m_pUIManager->MonsterHpDown(damage);
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
		m_pUIManager->OnTargetUI(pTarget, 3.f);
}

void CUILinker::OffTargetMarker(void)
{
	m_pUIManager->OffTargetUI();
}

void CUILinker::MonsterInfoSet()
{
	M_Stat* pStat = ((CMonster*)m_pCT->GetCurrentTarget().get())->GetStat();

	std::wstring name = pStat->Getname();
	_float hp = pStat->GetCurHp();
	_float maxHp = pStat->GetMaxHp();
	std::wstring monsterProperty = L"UP";
	_int hpMagnification = pStat->GetHPMagnification();

	m_pUIManager->MonsterState(name, maxHp, hp, hpMagnification, monsterProperty);
}

void CUILinker::OffMonsterInfo(void)
{
	m_pUIManager->MonsterStateEnd();
}
