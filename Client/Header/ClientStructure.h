#pragma once

	typedef struct _Character_Base_Status
	{
		// base status - kiana A rank level 1
		GETTOR_SETTOR(_float,	baseHp,		317.f,	BaseHp)
		GETTOR_SETTOR(_float,	baseAtk,	75.f,	BaseAtk)
		GETTOR_SETTOR(_float,	baseDef,	44.f,	BaseDef)

		GETTOR_SETTOR(_float,	growHp,		11.25f, GrowHp)
		GETTOR_SETTOR(_float,	growAtk,	1.88f,	GrowAtk)
		GETTOR_SETTOR(_float,	growDef,	1.09f,	GrowDef)
		
		GETTOR_SETTOR(_uint,	level,		1,		Level)			
	}BaseStat;
		