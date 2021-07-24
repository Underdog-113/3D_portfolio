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
	{
		SP(Engine::CObject)& PhaseChanger = Engine::GET_CUR_SCENE->FindObjectWithKey(L"PhaseChanger");
		int a = 5;
	}
	
	++m_curPhase;
		break;

		//After being collided with PhaseChanger0
	case (_int)EOneStagePhase::FirstFight2Begin:

		// 여기서도 다 죽이면 증가?????
		break;

		//After killing all the enemies
	case (_int)EOneStagePhase::FirstFight2End:
		// 걸어다니기
		break;

	case (_int)EOneStagePhase::WarningAlarm:
		++m_curPhase;
		break;

		//After being collided with PhaseChanger2
	case (_int)EOneStagePhase::MidBossBegin:
		break;

		//After killing MidBoss
	case (_int)EOneStagePhase::MidBossEnd:
		//CStageControlTower::GetInstance()->GetMovieDirector()->StartTake(L"Ready_Stage1_Victory");
		++m_curPhase;
		break;

	case (_int)EOneStagePhase::WinningSlow:

		++m_curPhase;
		break;
	case (_int)EOneStagePhase::VictoryMovie:

		++m_curPhase;
		break;

		//Result screen
	case (_int)EOneStagePhase::StageResult:
		++m_curPhase;
		OpenStageResult();
		break;

		// Wait Change Scene
	case (_int)EOneStagePhase::StageResult_Idle:
		if (false == m_isSoundChange)
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->StartSound(L"Victory.mp3", (_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
			m_isSoundChange = true;
		}
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
	Engine::CInputManager::GetInstance()->SetKeyInputEnabled(false);

	CStageControlTower::GetInstance()->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Victory");
	CBattleUiManager::GetInstance()->BattleEnd();
	Engine::CCameraManager::GetInstance()->ChangeCameraMode(Engine::ECameraMode::Edit);
	ShowCursor(true);
}
