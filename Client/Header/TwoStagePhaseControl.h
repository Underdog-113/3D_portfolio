#ifndef TWOSTAGEPHASECONTROL_H
#define TWOSTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CTwoStagePhaseControl final : public CPhaseControl
{
public:
	enum class ETwoStagePhase
	{
		PlayerSummon		,
		BeforeBoss			,
		BossBegin			,
		BossEnd				,
		StageResult			,
		StageResult_Idle	,
		NumOfPhse			
	};
public:
	CTwoStagePhaseControl();
	~CTwoStagePhaseControl();

public:
					void		Update				(void) override;

public:
					void		OpenStageResult		(void);
};

#endif