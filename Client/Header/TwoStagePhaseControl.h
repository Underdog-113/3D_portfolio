#ifndef TWOSTAGEPHASECONTROL_H
#define TWOSTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CTwoStagePhaseControl final : public CPhaseControl
{
public:
	enum class ETwoStagePhase
	{
		PlayerSummon		,
		Conversation		,
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

private:
					void		EnterConversationPhase(void);
public:
					void		OpenStageResult		(void);

					_bool		m_isSoundChange = false;

					SP(CTwoConversationC)		m_spConversation = nullptr;
};

#endif