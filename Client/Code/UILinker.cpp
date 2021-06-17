#include "stdafx.h"
#include "UILinker.h"

#include "BattleUiManager.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

CUILinker::CUILinker()
{
}


CUILinker::~CUILinker()
{
}

void CUILinker::PlayerHpSet()
{
	m_pUIManager->PlayerHp(m_pCT->GetCurrentActor()->GetStat()->GetCurHp());
}

void CUILinker::PlayerSpSet()
{
	m_pUIManager->PlayerSp(m_pCT->GetCurrentActor()->GetStat()->GetCurSp());
}
void CUILinker::MoveJoyStick(JoyStick_Dir dir)
{
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

void CUILinker::SwapToOne(void)
{
}

void CUILinker::SwapToTwo(void)
{
}

void CUILinker::Hit_Up()
{
}

void CUILinker::TargetMarker(void)
{
}

void CUILinker::MonsterInfoSet()
{
	//std::wstring name, _float hp, std::wstring property
}

void CUILinker::MonsterHpSet()
{
	//_float value
}
