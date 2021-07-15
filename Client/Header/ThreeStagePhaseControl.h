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
		BeforeThirdFight	,
		ThirdFightBegin		,
		ThirdFightEnd		,
		BeforeBoss			,
		BossBegin			,
		BossEnd				,
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
					_bool		m_isSoundChange = false;
};

#endif