#include "stdafx.h"
#include "BossStagePhaseControl.h"
#include "StageControlTower.h"
#include "Valkyrie.h"

#include "MovieDirector.h"
#include "PatternMachineC.h"
#include "ClientPatterns.h"
#include "BattleUiManager.h"
#include "Monster.h"

CBossStagePhaseControl::CBossStagePhaseControl()
{
}


CBossStagePhaseControl::~CBossStagePhaseControl()
{
}

void CBossStagePhaseControl::Update(void)
{
	switch (m_curPhase)
	{
	case UNDEFINED:
		++m_curPhase;
		break;

	case (_int)ETwoStagePhase::ReadyStage:
		CStageControlTower::GetInstance()->SetDirectorMode(true);
		++m_curPhase;
		break;

	case (_int)ETwoStagePhase::PlayerSummon:
		if (m_pCT->GetCurrentActor()->GetComponent<Engine::CStateMachineC>()->CompareState(L"Appear") == false)
		{
			++m_curPhase;
		}
		break;
	case (_int)ETwoStagePhase::WarningAlarm:
		m_warningTimer += GET_DT;

		if (!m_warningSpawn && m_warningTimer > 0.5f)
		{
			SP(Engine::CObject) spObj;
			spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Warning_Ring", true, (_uint)Engine::ELayerID::Effect);

			CValkyrie* pActor = CStageControlTower::GetInstance()->GetCurrentActor();
			spObj->GetTransform()->SetParent(pActor->GetTransform());
			spObj->GetTransform()->AddPositionY(pActor->GetMesh()->GetHalfYOffset());
			spObj->GetTransform()->SetSize(1.5f, 1.5f, 1.5f);

			m_warningSpawn = true;
		}

		if (!m_fadeOut && m_warningTimer > 3.5f)
		{
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_BlackFadeOut();
			m_fadeOut = true;
		}

		if (m_warningTimer > 4.f)
		{
			++m_curPhase;
		}
		break;

		//Before being collised with PhaseChanger0
	case (_int)ETwoStagePhase::CreateBoss:
		m_spBronya = std::dynamic_pointer_cast<CMonster>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MB_Bronya", true, (_uint)ELayerID::Enemy, L"MB_Bronya"));
		m_spBronya->GetTransform()->SetPosition(0.f, 0.f, 0.f);
		m_spBronya->SelectChannelID();
		m_spBronya->SetIsEnabled(true);
		++m_curPhase;
		break;
		//After being collided with PhaseChanger0
	case (_int)ETwoStagePhase::BossMovie:
		if (false == m_isBossMovieOn)
		{
			m_spBronya->GetTransform()->SetPosition(186.21f, -3.0f, -0.84f);

			// movie
			CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_BronyaBorn();
			m_isBossMovieOn = true;
			++m_curPhase;
		}
		break;

	case (_int)ETwoStagePhase::Boss:
		if (!m_isBossMovieOn)
		{
			CStageControlTower::GetInstance()->SetDirectorMode(false);
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			Engine::CSoundManager::GetInstance()->PlayBGM(L"BronyaBGM.mp3");
			Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
			m_isBossMovieOn = false;
		}

		if (m_spBronya->GetComponent<CPatternMachineC>()->GetOnDie())
			++m_curPhase;
		break;
		//After killing Boss
	case (_int)ETwoStagePhase::BossEnd:
		CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_WinningSlow();
		++m_curPhase;
		break;
	case (_int)ETwoStagePhase::WinningSlow:
		if (!CStageControlTower::GetInstance()->GetMovieDirector()->GetIsOnAir())
		{
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
			m_victoryTimer = 0.f;
			++m_curPhase;
		}
		break;
	case (_int)ETwoStagePhase::WaitVictoryMovie:
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
	case (_int)ETwoStagePhase::VictoryMovie:
		m_victoryTimer += GET_DT;
		if (m_victoryTimer > 4.f)
		{
			OpenStageResult();
			++m_curPhase;
		}
		break;

		//Result screen
	case (_int)ETwoStagePhase::StageResult:
		break;
	default:
		break;
	}
}


void CBossStagePhaseControl::OpenStageResult(void)
{
	CBattleUiManager::GetInstance()->BattleEnd();
}
