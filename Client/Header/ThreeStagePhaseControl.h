#ifndef THREESTAGEPHASECONTROL_H
#define THREESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CThreeStagePhaseControl final : public CPhaseControl
{
public:
	enum class EThreeStagePhase
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
		BeforeBoss,
		BossBegin,
		BossEnd,
		StageResult			,
		StageResult_Idle	,
		NumOfPhse			
	};
public:
	CThreeStagePhaseControl();
	~CThreeStagePhaseControl();

public:
					void		Update				(void) override;

public:
					void		OpenStageResult		(void);
};

#endif