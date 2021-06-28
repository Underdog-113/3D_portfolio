#ifndef ONESTAGEPHASECONTROL_H
#define ONESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class COneStagePhaseControl final : public CPhaseControl
{
	enum class EOneStagePhase
	{
		PlayerSummon		= 0,
		BeforeFirstFight	= 1,
		FirstFightBegin		= 2,
		FirstFightEnd		= 3,
		BeforeSecondFight	= 4,
		SecondFightBegin	= 5,
		SecondFightEnd		= 6,
		BeforeMidBoss		= 7,
		MidBossBegin		= 8,
		MidBossEnd			= 9,
		BeforeBoss			= 10,
		BossBegin			= 11,
		BossEnd				= 12,
		StageResult			= 13,
		NumOfPhse			= 14
	};
public:
	COneStagePhaseControl();
	~COneStagePhaseControl();

public:
					void		Update		(void) override;
};

#endif