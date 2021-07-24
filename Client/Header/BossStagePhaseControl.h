#ifndef BOSSSTAGEPHASECONTROL_H
#define BOSSSTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CMonster;
class CBossStagePhaseControl final : public CPhaseControl
{
public:
	enum class ETwoStagePhase
	{
		ReadyStage,
		PlayerSummon		,
		WarningAlarm		,
		CreateBoss			,
		BossMovie			,
		Boss				,
		BossEnd				,
		WinningSlow			,
		WaitVictoryMovie	,
		VictoryMovie		,
		StageResult			,
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



private:
	SP(CMonster) m_spBronya = nullptr;
	
	_float m_warningTimer = 0.f;
	_bool m_warningSpawn = false;
	_bool m_fadeOut = false;
	_bool m_isBossMovieOn = false;

	_bool m_bossBattleBGM = false;

	_float m_victoryTimer = 0.f;

};

#endif