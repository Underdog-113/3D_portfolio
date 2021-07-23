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
		VictoryMovie		,
		StageResult			,
		StageResult_Idle	,
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

					_bool		m_isSoundChange = false;

					SP(CTwoConversationC)		m_spConversation = nullptr;

					

private:
	SP(CMonster) m_spGanesha = nullptr;
	_float m_warningTimer = 0.f;
};

#endif