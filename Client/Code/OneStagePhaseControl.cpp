#include "stdafx.h"
#include "OneStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"
#include "Layer.h"
#include "PhaseChanger.h"
#include "Monster.h"

#include "MovieDirector.h"

COneStagePhaseControl::COneStagePhaseControl()
{
}


COneStagePhaseControl::~COneStagePhaseControl()
{
}


void COneStagePhaseControl::Update(void)
{
	switch (m_curPhase)
	{
	case UNDEFINED:
		++m_curPhase;
		break;

	case (_int)EOneStagePhase::ReadyStage:
		CStageControlTower::GetInstance()->SetDirectorMode(true);
		++m_curPhase;
		break;

	case (_int)EOneStagePhase::PlayerSummon:
		if (m_pCT->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->CompareState(L"Appear") == false)
		{
			EnterConversationPhase();
			++m_curPhase;
		}
		// player born
		break;

	case (_int)EOneStagePhase::Conversation:
		if (m_spConversation->IsEnd())
		{
			CStageControlTower::GetInstance()->SetDirectorMode(false);
			++m_curPhase;
		}
		// conversation
		break;

		//Before being collided with PhaseChanger0
	case (_int)EOneStagePhase::BeforeFirstFight1:
		break;

		//After being collided with PhaseChanger0
	case (_int)EOneStagePhase::FirstFight1Begin:
		break;

	case (_int)EOneStagePhase::FirstFight1End:
	{
		SP(Engine::CObject) PhaseChanger = Engine::GET_CUR_SCENE->FindObjectWithKey(L"PhaseChanger");

		std::dynamic_pointer_cast<CPhaseChanger>(PhaseChanger)->SetTimerStart(true);

		SP(CMonster) spMonClone = std::dynamic_pointer_cast<CMonster>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle"));
		spMonClone->GetTransform()->SetPosition(-2.61195f, 0.26f, -0.340873f);
		spMonClone->SelectChannelID();
		spMonClone->SetIsEnabled(true);
		spMonClone->SetSpawnTimer(1.f);
		std::dynamic_pointer_cast<CPhaseChanger>(PhaseChanger)->AddMonster(spMonClone);

		spMonClone = std::dynamic_pointer_cast<CMonster>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle"));
		spMonClone->GetTransform()->SetPosition(-1.14649f, 0.26f, -1.21127f);
		spMonClone->SelectChannelID();
		spMonClone->SetIsEnabled(true);
		spMonClone->SetSpawnTimer(0.5f);
		std::dynamic_pointer_cast<CPhaseChanger>(PhaseChanger)->AddMonster(spMonClone);

		spMonClone = std::dynamic_pointer_cast<CMonster>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MO_Scout", true, (_uint)ELayerID::Enemy, L"MO_Scout"));
		spMonClone->GetTransform()->SetPosition(2.32355f, 0.26f, -0.698635f);
		spMonClone->SelectChannelID();
		spMonClone->SetIsEnabled(true);
		spMonClone->SetSpawnTimer(1.f);
		std::dynamic_pointer_cast<CPhaseChanger>(PhaseChanger)->AddMonster(spMonClone);
	}
	
	++m_curPhase;
		break;

		//After being collided with PhaseChanger0
	case (_int)EOneStagePhase::FirstFight2Begin:

		// ���⼭�� �� ���̸� ����?????
		m_warningTimer = 0.f;
		break;

		//After killing all the enemies
	case (_int)EOneStagePhase::FirstFight2End:
		// �ɾ�ٴϱ�
		// trigger �ߵ��� �Ѿ
		m_warningTimer = 0.f;
		break;

	case (_int)EOneStagePhase::WarningAlarm:
		// ���� 3�� �ڿ� ����
		// �� ���� ����� �ڵ� �־�� ��
		// 3�� �� ���� ������� �Ѿ
		
		m_warningTimer += GET_DT;

		if (m_warningTimer > 3.f)
		{
			++m_curPhase;
		}
		break;

		//After being collided with PhaseChanger2
	case (_int)EOneStagePhase::MidBossBegin:
		// �̵庸���� ����
		// �̵庸�� ������ ����Ǹ� �Ѿ
		break;

		//After killing MidBoss
	case (_int)EOneStagePhase::MidBossEnd:
		CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_WinningSlow();

		++m_curPhase;
		break;

	case (_int)EOneStagePhase::WinningSlow:
		if (!CStageControlTower::GetInstance()->GetMovieDirector()->GetIsOnAir())
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			m_victoryTimer = 0.f;
			++m_curPhase;
		}
		break;

	case (_int)EOneStagePhase::WaitVictoryMovie:

		m_victoryTimer += GET_DT;

		if (m_victoryTimer > 1.f)
		{
			m_victoryTimer = 0.f;
			// movie
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_Victory();

			Engine::CSoundManager::GetInstance()->StartSound(L"Victory.mp3", (_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
			++m_curPhase;
		}
		break;
	case (_int)EOneStagePhase::VictoryMovie:
		m_victoryTimer += GET_DT;
		if (m_victoryTimer > 4.f)
		{
			OpenStageResult();
			++m_curPhase;
		}
		break;

		//Result screen
	case (_int)EOneStagePhase::StageResult:
		break;

		// Wait Change Scene
	case (_int)EOneStagePhase::StageResult_Idle:
		break;

	default:
		break;
	}
}

void COneStagePhaseControl::PlayerSummonPhase()
{
}

void COneStagePhaseControl::EnterConversationPhase()
{
	SP(Engine::CObject) spConversation = Engine::GET_CUR_SCENE->ADD_CLONE(L"EmptyObject", true, (_uint)ELayerID::Player, L"");
	spConversation->AddComponent<COneConversationC>();

	m_spConversation = spConversation->GetComponent<COneConversationC>();
}

void COneStagePhaseControl::OpenStageResult(void)
{
	CBattleUiManager::GetInstance()->BattleEnd();
}
