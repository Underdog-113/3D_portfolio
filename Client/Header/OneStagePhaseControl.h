#ifndef ONESTAGEPHASECONTROL_H
#define ONESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class COneStagePhaseControl final : public CPhaseControl
{
public:
	enum class EOneStagePhase
	{
		ReadyStage			,//0
		PlayerSummon		,//1
		Conversation		,//2
		BeforeFirstFight1	,//3
		FirstFight1Begin	,//4
		FirstFight1End		,//5
		FirstFight2Begin	,//6
		FirstFight2End		,//7
		BeforeMidBoss		,//8
		MidBossBegin		,//9
		MidBossEnd			,//10
		ReadyVictoryCutScene,//11
		VictoryCutScene		,//12
		StageResult			,//13
		StageResult_Idle	,//14
		NumOfPhse			 //15
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