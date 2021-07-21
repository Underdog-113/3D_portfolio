#include "stdafx.h"
#include "..\Header\Shot_ActorVictory.h"

#include "Valkyrie.h"
#include "AniCtrl.h"

CShot_ActorVictory::CShot_ActorVictory()
{
}


CShot_ActorVictory::~CShot_ActorVictory()
{
}

void CShot_ActorVictory::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc);

	SetIsEndless(true);
	memcpy(&m_desc, pDesc, sizeof(Desc));


	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	m_pActorAniCtrl = pActor->GetMesh()->GetFirstMeshData_Dynamic()->GetAniCtrl();
	m_pActorAniCtrl->SetIsMovieOn(true);
	m_savedAnimIndex = m_pActorAniCtrl->GetCurIndex();

// 	switch (pActor->GetStat()->GetType())
// 	{
// 	case V_Stat::KIANA:
// 		m_victoryAnimIndex = 29;
// 		m_victoryIdleAnimIndex = 30;
// 		break;
// 	case V_Stat::THERESA:
// 		m_victoryAnimIndex = 29;
// 		m_victoryIdleAnimIndex = 30;
// 		break;
// 	case V_Stat::SAKURA:
// 		m_victoryAnimIndex = 32;
// 		m_victoryIdleAnimIndex = 33;
// 		break;
// 	default:
//		break;
// 	}
}

void CShot_ActorVictory::Enter()
{
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	//m_pActorAniCtrl->ChangeAniSet_NoBlend(m_victoryAnimIndex);
	pActor->GetStateMachine()->ChangeState(L"Victory");
}

void CShot_ActorVictory::Action()
{
	CShot::Action();

	if(m_prevPlayTime < m_pOnAirTake->GetPlayTimer())
		m_pActorAniCtrl->PlayOnMovie(GET_DT);

	m_prevPlayTime = m_pOnAirTake->GetPlayTimer();
}

void CShot_ActorVictory::Cut()
{
	m_pActorAniCtrl->SetIsMovieOn(false);
}

void CShot_ActorVictory::Rollback()
{
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	pActor->GetStateMachine()->ChangeState(L"StandBy");
	m_pActorAniCtrl->SetIsMovieOn(false);
}
