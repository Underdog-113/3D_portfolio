#ifndef ONESTAGEPHASECONTROL_H
#define ONESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class COneStagePhaseControl final : public CPhaseControl
{
public:
	enum class EOneStagePhase
	{
		PlayerSummon		,
		Conversation		,
		BeforeFirstFight1	,
		FirstFight1Begin	,
		FirstFight1End	,
		FirstFight2Begin	,
		FirstFight2End		,
		BeforeMidBoss		,
		MidBossBegin		,
		MidBossEnd,
		ReadyVictoryCutScene,
		VictoryCutScene,
		StageResult			,
		StageResult_Idle	,
		NumOfPhse			
	};
public:
	COneStagePhaseControl();
	~COneStagePhaseControl();

public:
					void		Update				(void) override;

private:
	void PlayerSummonPhase();
	void EnterConversationPhase();

	

public:
					void					OpenStageResult		(void);
					_bool					m_isSoundChange = false;

					SP(COneConversationC)		m_spConversation = nullptr;
};

#endif