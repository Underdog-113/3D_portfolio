#ifndef ONESTAGEPHASECONTROL_H
#define ONESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class COneStagePhaseControl final : public CPhaseControl
{
public:
	enum class EOneStagePhase
	{
		PlayerSummon		,
		BeforeFirstFight1	,
		FirstFight1Begin	,
		FirstFight1End	,
		FirstFight2Begin	,
		FirstFight2End		,
		//BeforeSecondFight	,
		//SecondFightBegin	,
		//SecondFightEnd	,
		BeforeMidBoss		,
		MidBossBegin		,
		MidBossEnd			,
		//BeforeBoss,
		//BossBegin,
		//BossEnd,
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
					void					OpenStageResult		(void);
					_bool					m_isSoundChange = false;
};

#endif