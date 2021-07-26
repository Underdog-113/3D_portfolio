#ifndef THREESTAGEPHASECONTROL_H
#define THREESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CThreeStagePhaseControl final : public CPhaseControl
{
public:
	enum class EThreeStagePhase
	{
		PlayerSummon		,			// 두두둥장
		BeforeFirstFight	,			// 이동 -> 트리거 들어가면 적 소환
		FirstFightBegin		,			// 전투 -> 다잡으면 끝?
		//FirstFightEnd		,			// 모름 왜있는지 모르겠는데 그냥 페이즈 넘김
		BeforeSecondFight	,			// 이동 -> 포탈타는게 여기
		GotoSecondFloor		,			// 포탈 -> 2층 이동
		SecondFightBegin	,			// 전투
		SecondFightEnd		,			// 예비 
		BeforeThirdFight	,			// 이동 -> 트리거
		ThirdFightBegin		,			// 전투
		//ThirdFightEnd		,			// 예비
		BeforeBoss			,			// 이동 -> 트리거
		WarningAlarm		,
		BossBegin			,			// 전투
		BossEnd				,			// 예비
		WinningSlow			,
		WaitVictoryMovie	,
		VictoryMovie		,
		StageResult			,
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
					_bool		m_warningSpawn = false;
					_bool		m_portalEnter = false;
					_bool		m_portalMove = false;
					_bool		m_portalEnd = false;
					
					_float		m_warningTimer = 0.f;
					_float		m_victoryTimer = 0.f;
					_float		m_warpTimer = 0.f;
};

#endif