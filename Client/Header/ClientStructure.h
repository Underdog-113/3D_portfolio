#pragma once


	typedef struct _Character_Base_Status
	{
		// base status - kiana A rank level 1
		GETTOR_SETTOR(_float,	baseHp,		317.f,	BaseHp)
		GETTOR_SETTOR(_float,	baseSp,		140.f,	BaseSp)
		GETTOR_SETTOR(_float,	baseAtk,	75.f,	BaseAtk)
		GETTOR_SETTOR(_float,	baseDef,	44.f,	BaseDef)
		GETTOR_SETTOR(_float,	baseCrt,	6.f,	BaseCrt)
		GETTOR_SETTOR(_float,	baseExp,	1000.f, BaseExp)

		GETTOR_SETTOR(_float,	growHp,		11.25f, GrowHp)
		GETTOR_SETTOR(_float,	growSp,		0.35f,	GrowSp)
		GETTOR_SETTOR(_float,	growAtk,	1.88f,	GrowAtk)
		GETTOR_SETTOR(_float,	growDef,	1.09f,	GrowDef)
		GETTOR_SETTOR(_float,	growCrt,	0.23f,	GrowCrt)
		GETTOR_SETTOR(_float,	growExp,	80.f,	GrowExp)

		GETTOR_SETTOR(_float,	weaponHp,	0.f,	WeaponHp)
		GETTOR_SETTOR(_float,	weaponSp,	0.f,	WeaponSp)
		GETTOR_SETTOR(_float,	weaponAtk,	0.f,	WeaponAtk)
		GETTOR_SETTOR(_float,	weaponDef,	0.f,	WeaponDef)
		GETTOR_SETTOR(_float,	weaponCrt,	0.f,	WeaponCrt)
		
		GETTOR_SETTOR(_uint,	level,		1,		Level)			
	}Base_Stat;

#define SETSTAT_SQUAD(baseStat, statName)	\
baseStat->GetBase##statName##() + baseStat->GetGrow##statName##() * (baseStat->GetLevel() - 1) + baseStat->GetWeapon##statName##()
	typedef struct _Character_Squad_Status
	{
		_Character_Squad_Status(Base_Stat* baseStat)
		{
			maxHp = SETSTAT_SQUAD(baseStat, Hp);
			curHp = maxHp;
			buffHp = 0.f;

			maxSp = SETSTAT_SQUAD(baseStat, Sp);
			curSp = maxHp;
			buffSp = 0.f;

			curAtk = SETSTAT_SQUAD(baseStat, Atk);
			buffAtk = 0.f;

			curDef = SETSTAT_SQUAD(baseStat, Def);
			buffDef = 0.f;

			curCrt = SETSTAT_SQUAD(baseStat, Crt);
			buffCrt = 0.f;

			skillCooltime = 5.f;
			skillCost = 15.f;

			ultraCooltime = 10.f;
			ultraCost = 100.f;
		}

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

			
		GETTOR_SETTOR	(_float, skillCooltime,	0.f,	SkillCoolTime)
		GETTOR_SETTOR	(_float, skillCost,		0.f,	SkillCost)
			
		GETTOR_SETTOR	(_float, ultraCooltime,	0.f,	UltraCoolTime)
		GETTOR_SETTOR	(_float, ultraCost,		0.f,	UltraCost)

	}Squad_Stat;
