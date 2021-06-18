#pragma once
#include "EngineStdafx.h"
#include "ClientStructure.h"

#define SETSTAT_VALKYRIE(pStat, statName)	\
pStat->GetBase##statName##() + pStat->GetGrow##statName##() * (pStat->GetLevel() - 1) + pStat->GetWeapon##statName##()

	typedef struct _Character_Warship_Status : public BaseStat
	{
		// base status - kiana A rank level 1
		GETTOR_SETTOR(_float,	baseSp,		140.f,	BaseSp)
		GETTOR_SETTOR(_float,	baseCrt,	6.f,	BaseCrt)
		GETTOR_SETTOR(_float,	baseCurExp,	0.f,	BaseCurExp)
		GETTOR_SETTOR(_float,	baseMaxExp,	1000.f, BaseMaxExp)
			
		GETTOR_SETTOR(_float,	growSp,		0.35f,	GrowSp)
		GETTOR_SETTOR(_float,	growCrt,	0.23f,	GrowCrt)
		GETTOR_SETTOR(_float,	growMaxExp,	80.f,	GrowMaxExp)

		GETTOR_SETTOR(_float,	weaponHp,	0.f,	WeaponHp)
		GETTOR_SETTOR(_float,	weaponSp,	0.f,	WeaponSp)
		GETTOR_SETTOR(_float,	weaponAtk,	0.f,	WeaponAtk)
		GETTOR_SETTOR(_float,	weaponDef,	0.f,	WeaponDef)
		GETTOR_SETTOR(_float,	weaponCrt,	0.f,	WeaponCrt)
	}V_WarshipStat;
	

	typedef struct _Valkyrie_Stage_Status
	{
		enum Valkyrie_Type { KIANA, THERESA, SAKURA };

		void SetupStatus(V_WarshipStat* pStat)
		{
			maxHp = SETSTAT_VALKYRIE(pStat, Hp);
			curHp = maxHp;
			buffHp = 0.f;

			curAtk = SETSTAT_VALKYRIE(pStat, Atk);
			buffAtk = 0.f;

			curDef = SETSTAT_VALKYRIE(pStat, Def);
			buffDef = 0.f;

			maxSp = SETSTAT_VALKYRIE(pStat, Sp);
			curSp = maxSp;
			buffSp = 0.f;

			curCrt = SETSTAT_VALKYRIE(pStat, Crt);
			buffCrt = 0.f;
		}
		
		// base status - kiana A rank level 1
			
		GETTOR_SETTOR	(Valkyrie_Type, type, KIANA,	Type)

		GETTOR_SETTOR	(_float, curHp,		0.f,	CurHp)
		GETTOR_SETTOR	(_float, maxHp,		0.f,	MaxHp)
		GETTOR_SETTOR	(_float, buffHp,	0.f,	BuffHp)

		GETTOR_SETTOR	(_float, curSp,		0.f,	CurSp)
		GETTOR_SETTOR	(_float, maxSp,		0.f,	MaxSp)
		GETTOR_SETTOR	(_float, buffSp,	0.f,	BuffSp)
			
		GETTOR_SETTOR	(_float, curAtk,	0.f,	CurAtk)
		GETTOR_SETTOR	(_float, buffAtk,	0.f,	BuffAtk)
			
		GETTOR_SETTOR	(_float, curDef,	0.f,	CurDef)
		GETTOR_SETTOR	(_float, buffDef,	0.f,	BuffDef)

		GETTOR_SETTOR	(_float, curCrt,	0.f,	CurCrt)
		GETTOR_SETTOR	(_float, buffCrt,	0.f,	BuffCrt)			

		GETTOR_SETTOR	(_float, skillCooltime,	8.f,	SkillCoolTime)
		GETTOR_SETTOR	(_float, skillCost,		7.f,	SkillCost)
			
		GETTOR_SETTOR	(_float, ultraCooltime,	10.f,	UltraCoolTime)
		GETTOR_SETTOR	(_float, ultraCost,		20.f,	UltraCost)
			
			
	}V_Stat;
	
	
	typedef struct _Kiana_Stage_Status : public _Valkyrie_Stage_Status
	{
		// base status - kiana A rank level 1			

		GETTOR_SETTOR	(_float, attack1,		0.f,	Attack1)
		GETTOR_SETTOR	(_float, attack2,		0.f,	Attack2)
		GETTOR_SETTOR	(_float, attack3,		0.f,	Attack3)
		GETTOR_SETTOR	(_float, attack4,		0.f,	Attack4)
		GETTOR_SETTOR	(_float, attack5,		0.f,	Attack5)
			
		GETTOR_SETTOR	(_float, attack4_1,		0.f,	Attack4_1)
		GETTOR_SETTOR	(_float, attack4_2,		0.f,	Attack4_2)
			
		GETTOR_SETTOR	(_float, attackQTE,		0.f,	AttackQTE)
		GETTOR_SETTOR	(_float, WPSkill,		0.f,	WPSkill)

			
		GETTOR_SETTOR	(_float, ultraBuff,		0.f,	UltraBuff)
	}V_Kiana_Stat;
	
	typedef struct _Theresa_Stage_Status : public _Valkyrie_Stage_Status
	{
		// base status - kiana A rank level 1			

		GETTOR_SETTOR	(_float, attack1,		0.f,	Attack1)
		GETTOR_SETTOR	(_float, attack2,		0.f,	Attack2)
		GETTOR_SETTOR	(_float, attack3,		0.f,	Attack3)
		GETTOR_SETTOR	(_float, attack4,		0.f,	Attack4)
		GETTOR_SETTOR	(_float, attack5,		0.f,	Attack5)
			
		GETTOR_SETTOR	(_float, attack4_1,		0.f,	Attack4_1)
		GETTOR_SETTOR	(_float, attack4_2,		0.f,	Attack4_2)
			
		GETTOR_SETTOR	(_float, attackQTE,		0.f,	AttackQTE)
		GETTOR_SETTOR	(_float, WPSkill,		0.f,	WPSkill)

			
		GETTOR_SETTOR	(_float, ultraBuff,		0.f,	UltraBuff)
	}V_Theresa_Stat;
	
	typedef struct _Sakura_Stage_Status : public _Valkyrie_Stage_Status
	{
		// base status - kiana A rank level 1			

		GETTOR_SETTOR	(_float, attack1,		0.f,	Attack1)
		GETTOR_SETTOR	(_float, attack2,		0.f,	Attack2)
		GETTOR_SETTOR	(_float, attack3,		0.f,	Attack3)
		GETTOR_SETTOR	(_float, attack4,		0.f,	Attack4)
		GETTOR_SETTOR	(_float, attack5,		0.f,	Attack5)
			
		GETTOR_SETTOR	(_float, attack4_1,		0.f,	Attack4_1)
		GETTOR_SETTOR	(_float, attack4_2,		0.f,	Attack4_2)
			
		GETTOR_SETTOR	(_float, attackQTE,		0.f,	AttackQTE)
		GETTOR_SETTOR	(_float, WPSkill,		0.f,	WPSkill)

			
		GETTOR_SETTOR	(_float, ultraBuff,		0.f,	UltraBuff)
	}V_Sakura_Stat;
	
	