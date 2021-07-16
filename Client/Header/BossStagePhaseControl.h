#ifndef BOSSSTAGEPHASECONTROL_H
#define BOSSSTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CBossStagePhaseControl final : public CPhaseControl
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
	CBossStagePhaseControl();
	~CBossStagePhaseControl();

public:
					void		Update				(void) override;

public:
					void		OpenStageResult		(void);

					_bool		m_isSoundChange = false;
};

#endif