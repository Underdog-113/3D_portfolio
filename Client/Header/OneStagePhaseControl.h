#ifndef ONESTAGEPHASECONTROL_H
#define ONESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class COneStagePhaseControl final : public CPhaseControl
{
public:
	enum class EOneStagePhase
	{
		PlayerSummon		,
		BeforeFirstFight	,
		FirstFightBegin		,
		FirstFightEnd		,
		BeforeSecondFight	,
		SecondFightBegin	,
		SecondFightEnd		,
		BeforeMidBoss		,
		MidBossBegin		,
		MidBossEnd			,
//		BeforeBoss			= 10,
//		BossBegin			= 11,
//		BossEnd				= 12,
		StageResult			,
		StageResult_Idle	,
		NumOfPhse			
	};
public:
	COneStagePhaseControl();
	~COneStagePhaseControl();

public:
					void		Update				(void) override;

public:
					void		OpenStageResult		(void);
};

#endif