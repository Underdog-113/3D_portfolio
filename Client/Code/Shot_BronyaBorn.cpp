#include "stdafx.h"
#include "..\Header\Shot_BronyaBorn.h"

#include "AniCtrl.h"
#include "PhaseControl.h"

CShot_BronyaBorn::CShot_BronyaBorn()
{
}


CShot_BronyaBorn::~CShot_BronyaBorn()
{
}

void CShot_BronyaBorn::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));


	m_pBronya = Engine::GET_CUR_SCENE->FindObjectWithKey(L"MB_Bronya").get();
	m_pBronyaAniCtrl = m_pBronya->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl();
	m_pBronyaAniCtrl->SetIsMovieOn(true);
	m_savedAnimIndex = m_pBronyaAniCtrl->GetCurIndex();
	m_pBronya->GetComponent<Engine::CStateMachineC>()->ChangeState(L"IDLE");
}

void CShot_BronyaBorn::Enter()
{

}

void CShot_BronyaBorn::Action()
{
	CShot::Action();

	if (m_prevPlayTime < m_pOnAirTake->GetPlayTimer())
		m_pBronyaAniCtrl->PlayOnMovie(GET_DT);

	m_prevPlayTime = m_pOnAirTake->GetPlayTimer();
}

void CShot_BronyaBorn::Cut()
{
	m_pBronyaAniCtrl->SetIsMovieOn(false);

	CStageControlTower::GetInstance()->GetMovieDirector()->CutCurrentTake();
	CStageControlTower::GetInstance()->GetPhaseControl()->IncreasePhase();
}

void CShot_BronyaBorn::Rollback()
{
	m_pBronyaAniCtrl->SetIsMovieOn(false);
}
