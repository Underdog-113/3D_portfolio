#ifndef TWOSTAGEPHASECONTROL_H
#define TWOSTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CMonster;
class CTwoStagePhaseControl final : public CPhaseControl
{
public:
	enum class ETwoStagePhase
	{
		ReadyStage,
		PlayerSummon		,
		Conversation		,
		BeforeEnterBoss		,
		PotalWarp			,
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
	CTwoStagePhaseControl();
	~CTwoStagePhaseControl();

public:
					void		Update				(void) override;

private:
					void		EnterConversationPhase(void);
public:
					void		OpenStageResult		(void);

					_bool		m_isBossMovieOn = false;

					SP(CTwoConversationC)		m_spConversation = nullptr;

					

private:
	SP(CMonster) m_spGanesha = nullptr;

	_float m_warpTimer = 0.f;
	_bool m_portalEnter = false;
	_bool m_portalMove = false;
	_bool m_portalEnd = false;


	_float m_warningTimer = 0.f;
	_bool m_warningSpawn = false;

	_bool m_isBossMovieOff = false;
	_float m_victoryTimer = 0.f;

	_bool m_uiOn = false;

	_float m_uiOnTimer = 0.f;
};

#endif