#include "stdafx.h"
#include "StatusDealer.h"

#include "UILinker.h"

CStatusDealer::CStatusDealer()
{
}


CStatusDealer::~CStatusDealer()
{
}

bool CStatusDealer::Damage_VtoM(V_Stat * pSrc, M_Stat * pDst, _float dmgRate)
{
	_float mhp = pDst->GetCurHp();
	_float mdef = pDst->GetCurDef() + pDst->GetBuffDef();

	_float vatk = pSrc->GetCurAtk() + pSrc->GetBuffAtk();
	_float vcrt = pSrc->GetCurCrt() + pSrc->GetBuffCrt();

	_int chance = rand() % 100;
	_float crtRate = vcrt > chance ? 2.f : 1.f;

	_float damage = (vatk * dmgRate) * crtRate * (mdef / (mdef * 1000.f));
	
	// font
	
	mhp -= damage;


	if (mhp < 0.f)
	{
		pDst->SetCurHp(0.f);
		m_pLinker->MonsterHpSet(0.f);	// ui interactive

		return true;
	}

	pDst->SetCurHp(mhp);
	m_pLinker->MonsterHpSet(mhp);	// ui interactive
	return false;
}

bool CStatusDealer::Damage_MtoV(M_Stat * pSrc, V_Stat * pDst, _float dmgRate)
{
	_float vhp = pDst->GetCurHp();
	_float vdef = pDst->GetCurDef() + pDst->GetBuffDef();

	_float matk = pSrc->GetCurAtk() + pSrc->GetBuffAtk();
	
	_float damage = (matk * dmgRate) * (vdef / (vdef * 1000.f));

	// font

	vhp -= damage;
	
	if (vhp < 0.f)
	{
		pDst->SetCurHp(0.f);
		m_pLinker->MonsterHpSet(vhp);	// ui interactive
		return true;
	}

	pDst->SetCurHp(vhp);
	m_pLinker->MonsterHpSet(vhp);	// ui interactive
	return false;
}

void CStatusDealer::HpUp_Solo(Chara_Stat * pStat, _float value)
{
	_float hp = pStat->GetCurHp();

	hp += value;

	if (hp > pStat->GetMaxHp())
		hp = pStat->GetMaxHp();

	pStat->SetCurHp(hp);
	m_pLinker->PlayerHpSet(hp);		// ui interactive
}

void CStatusDealer::HpDown_Solo(Chara_Stat * pStat, _float value)
{
	_float hp = pStat->GetCurHp();

	hp -= value;

	if (hp < 0.f)
		hp = 1.f;

	pStat->SetCurHp(hp);
	m_pLinker->PlayerHpSet(hp);		// ui interactive
}

void CStatusDealer::SpUp(V_Stat * pStat, _float value)
{
	_float sp = pStat->GetCurSp();

	sp += value;


	if (sp > pStat->GetMaxSp())
		sp = pStat->GetMaxSp();

	pStat->SetCurSp(sp);
	m_pLinker->PlayerSpSet(sp);		// ui interactive
	// sp font
}

void CStatusDealer::SpDown(V_Stat * pStat, _float value)
{
	_float sp = pStat->GetCurSp();

	sp -= value;

	if (sp < 0.f)
		sp = 0.f;

	pStat->SetCurSp(sp);
	m_pLinker->PlayerSpSet(sp);		// ui interactive
}

bool CStatusDealer::BreakGauge(M_Stat * pStat, _float value)
{
	return true;
}
