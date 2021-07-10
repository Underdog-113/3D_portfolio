#include "stdafx.h"
#include "StatusDealer.h"

#include "UILinker.h"

CStatusDealer::CStatusDealer()
{
}


CStatusDealer::~CStatusDealer()
{
}

bool CStatusDealer::Damage_VtoM(V_Stat * pSrc, M_Stat * pDst, _float dmgRate, _float* resDmg)
{
	_float mhp = pDst->GetCurHp();
	_float mdef = pDst->GetCurDef() + pDst->GetBuffDef();

	_float vatk = pSrc->GetCurAtk() + pSrc->GetBuffAtk();
	_float vcrt = pSrc->GetCurCrt() + pSrc->GetBuffCrt();
	
	_float pureDamage = vatk * dmgRate;

	_int chance = rand() % 1000;
	_float randRate = (_float)chance / 1000.f + 0.5f;	// 0.5 ~ 1.5
	_float crtRate = vcrt / 100.f;
	_float crtDamage = pureDamage * 2.f * crtRate * randRate;

	_float totalDamage = pureDamage + crtDamage;

	_float decrease = totalDamage * (mdef / (mdef + 1000.f));

	_float finalDamage = totalDamage - decrease;
	*resDmg = finalDamage;
	// font
	mhp -= finalDamage;

	std::cout << "mhp: " << mhp << std::endl;
	system("cls");
	if (mhp < 0.f)
	{
		pDst->SetCurHp(0.f);

		return true;
	}

	pDst->SetCurHp(mhp);
	return false;
}

bool CStatusDealer::Damage_MtoV(M_Stat * pSrc, V_Stat * pDst, _float dmgRate, _float* resDmg)
{
	_float vhp = pDst->GetCurHp();
	_float vdef = pDst->GetCurDef() + pDst->GetBuffDef();

	_float matk = pSrc->GetCurAtk() + pSrc->GetBuffAtk();

	_float totalDamage = matk * dmgRate;
	
	_float decrease = totalDamage * (vdef / (vdef + 1000.f));

	_float finalDamage = totalDamage - decrease;

	// font

	vhp -= finalDamage;
	*resDmg = finalDamage;
	
	if (vhp < 0.f)
	{
		pDst->SetCurHp(0.f);
		return true;
	}

	pDst->SetCurHp(vhp);
	return false;
}

void CStatusDealer::HpUp_Valkyrie(V_Stat * pStat, _float value)
{
	_float hp = pStat->GetCurHp();

	hp += value;

	if (hp > pStat->GetMaxHp())
		hp = pStat->GetMaxHp();

	pStat->SetCurHp(hp);
}

void CStatusDealer::HpDown_Valkyrie(V_Stat * pStat, _float value)
{
	_float hp = pStat->GetCurHp();

	hp -= value;

	if (hp < 0.f)
		hp = 1.f;

	pStat->SetCurHp(hp);
}

void CStatusDealer::SpUp(V_Stat * pStat, _float value)
{
	_float sp = pStat->GetCurSp();

	sp += value;


	if (sp > pStat->GetMaxSp())
		sp = pStat->GetMaxSp();

	pStat->SetCurSp(sp);
	// sp font
}

void CStatusDealer::SpDown(V_Stat * pStat, _float value)
{
	_float sp = pStat->GetCurSp();

	sp -= value;

	if (sp < 0.f)
		sp = 0.f;

	pStat->SetCurSp(sp);
}

bool CStatusDealer::BreakGauge(M_Stat * pStat, _float value)
{
	return true;
}
