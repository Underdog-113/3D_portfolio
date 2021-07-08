#pragma once

	typedef struct _Character_Base_Status
	{
		enum Character_Type { Creature, Phychic, Mecha };

		// base status - kiana A rank level			1
		GETTOR_SETTOR(_float,			baseHp,				317.f,			BaseHp)
		GETTOR_SETTOR(_float,			baseAtk,			75.f,			BaseAtk)
		GETTOR_SETTOR(_float,			baseDef,			44.f,			BaseDef)

		GETTOR_SETTOR(_float,			growHp,				11.25f,			GrowHp)
		GETTOR_SETTOR(_float,			growAtk,			1.88f,			GrowAtk)
		GETTOR_SETTOR(_float,			growDef,			1.09f,			GrowDef)
		
		GETTOR_SETTOR(_uint,			level,				1,				Level)
		GETTOR_SETTOR(Character_Type,	type,				Creature,		Type)
	}BaseStat;
		

	typedef struct _Hit_Info
	{
		enum Strength { Str_Damage, Str_Low, Str_High, Str_Airborne };
		enum CrowdControl { CC_None, CC_Stun, CC_Airborne };

		GETTOR_SETTOR(_float,		damageRate,	1.f,	DamageRate)
		GETTOR_SETTOR(Strength,		strength,	Str_Damage,	StrengthType)
		GETTOR_SETTOR(CrowdControl,	statEffect, CC_None,	CrowdControlType)

		GETTOR_SETTOR(_float,		breakDamage,	20.f,	BreakDamage)

	}HitInfo;

	typedef struct _ItemSave
	{
		std::wstring itemName;
		_int count;

	}ItemSave;