#pragma once

#include "EngineStdafx.h"
#include "ClientStructure.h"

#define SETSTAT_MONSTER(pStat, statName)	\
pStat->GetBase##statName##() + pStat->GetGrow##statName##() * (pStat->GetLevel() - 1)

typedef struct _Monster_Stage_Status
{
	virtual void SetupStatus(BaseStat* pStat)
	{
		maxHp = SETSTAT_MONSTER(pStat, Hp);
		curHp = maxHp;
		buffHp = 0.f;

		curAtk = SETSTAT_MONSTER(pStat, Atk);
		buffAtk = 0.f;

		curDef = SETSTAT_MONSTER(pStat, Def);
		buffDef = 0.f;
	}

	GETTOR_SETTOR(std::wstring, name, L"The king of Guro", name)

	GETTOR_SETTOR(_float, curHp, 0.f, CurHp)
	GETTOR_SETTOR(_float, maxHp, 0.f, MaxHp)
	GETTOR_SETTOR(_float, buffHp, 0.f, BuffHp)

	GETTOR_SETTOR(_float, curAtk, 0.f, CurAtk)
	GETTOR_SETTOR(_float, buffAtk, 0.f, BuffAtk)

	GETTOR_SETTOR(_float, curDef, 0.f, CurDef)
	GETTOR_SETTOR(_float, buffDef, 0.f, BuffDef)

	GETTOR_SETTOR(_float, breakGauge, 100.f, breakGauge)
}M_Stat;