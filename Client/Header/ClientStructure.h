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

	

	typedef struct _Character_Stage_Status
	{
		virtual void SetupStatus(Base_Stat* baseStat)
		{
			maxHp = SETSTAT_SQUAD(baseStat, Hp);
			curHp = maxHp;
			buffHp = 0.f;

			curAtk = SETSTAT_SQUAD(baseStat, Atk);
			buffAtk = 0.f;

			curDef = SETSTAT_SQUAD(baseStat, Def);
			buffDef = 0.f;
		}


		GETTOR_SETTOR	(_float, curHp,		0.f,	CurHp)
		GETTOR_SETTOR	(_float, maxHp,		0.f,	MaxHp)
		GETTOR_SETTOR	(_float, buffHp,	0.f,	BuffHp)

		GETTOR_SETTOR	(_float, curAtk,	0.f,	CurAtk)
		GETTOR_SETTOR	(_float, buffAtk,	0.f,	BuffAtk)
			
		GETTOR_SETTOR	(_float, curDef,	0.f,	CurDef)
		GETTOR_SETTOR	(_float, buffDef,	0.f,	BuffDef)
			
	}Chara_Stat;


	typedef struct _Valkyrie_Stage_Status : public Chara_Stat
	{
		enum Valkyrie_Type { KIANA, THERESA, SAKURA };

		virtual void SetupStatus(Base_Stat* baseStat) override
		{
			Chara_Stat::SetupStatus(baseStat);

			maxSp = SETSTAT_SQUAD(baseStat, Sp);
			curSp = maxHp;
			buffSp = 0.f;

			curCrt = SETSTAT_SQUAD(baseStat, Crt);
			buffCrt = 0.f;
		}


		// base status - kiana A rank level 1
			
		GETTOR_SETTOR	(Valkyrie_Type, type, KIANA,	Type)

		GETTOR_SETTOR	(_float, curSp,		0.f,	CurSp)
		GETTOR_SETTOR	(_float, maxSp,		0.f,	MaxSp)
		GETTOR_SETTOR	(_float, buffSp,	0.f,	BuffSp)

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
	}Kiana_Stat;
	
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
	}Theresa_Stat;
	
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
	}Sakura_Stat;
	


	typedef struct _Monster_Stage_Status : public Chara_Stat
	{
		GETTOR_SETTOR	(_float, breakGauge,	100.f,	breakGauge)
	}M_Stat;