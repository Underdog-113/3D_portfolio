#ifndef THREESTAGEPHASECONTROL_H
#define THREESTAGEPHASECONTROL_H

#include "PhaseControl.h"

class CThreeStagePhaseControl final : public CPhaseControl
{
public:
	enum class EThreeStagePhase
	{
		PlayerSummon		,			// �εε���
		BeforeFirstFight	,			// �̵� -> Ʈ���� ���� �� ��ȯ
		FirstFightBegin		,			// ���� -> �������� ��?
		//FirstFightEnd		,			// �� ���ִ��� �𸣰ڴµ� �׳� ������ �ѱ�
		BeforeSecondFight	,			// �̵� -> ��ŻŸ�°� ����
		GotoSecondFloor		,			// ��Ż -> 2�� �̵�
		SecondFightBegin	,			// ����
		SecondFightEnd		,			// ���� 
		BeforeThirdFight	,			// �̵� -> Ʈ����
		ThirdFightBegin		,			// ����
		//ThirdFightEnd		,			// ����
		BeforeBoss			,			// �̵� -> Ʈ����
		WarningAlarm		,
		BossBegin			,			// ����
		BossEnd				,			// ����
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