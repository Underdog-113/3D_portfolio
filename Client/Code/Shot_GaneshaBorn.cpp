#include "stdafx.h"
#include "..\Header\Shot_GaneshaBorn.h"

#include "AniCtrl.h"
#include "PhaseControl.h"

CShot_GaneshaBorn::CShot_GaneshaBorn()
{
}


CShot_GaneshaBorn::~CShot_GaneshaBorn()
{
}

void CShot_GaneshaBorn::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));


	m_pGanesha = Engine::GET_CUR_SCENE->FindObjectWithKey(L"MB_Ganesha").get();
	m_pActorAniCtrl = m_pGanesha->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl();
	m_pActorAniCtrl->SetIsMovieOn(true);
	m_savedAnimIndex = m_pActorAniCtrl->GetCurIndex();
	m_pGanesha->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Born");
}

void CShot_GaneshaBorn::Enter()
{
	//m_pActorAniCtrl->ChangeAniSet_NoBlend(m_victoryAnimIndex);
	//m_pGanesha->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Born");
	m_pGanesha->SetIsEnabled(true);
}

void CShot_GaneshaBorn::Action()
{
	CShot::Action();

	if (m_prevPlayTime < m_pOnAirTake->GetPlayTimer())
		m_pActorAniCtrl->PlayOnMovie(GET_DT);

	m_prevPlayTime = m_pOnAirTake->GetPlayTimer();
}

void CShot_GaneshaBorn::Cut()
{
	m_pActorAniCtrl->SetIsMovieOn(false);
}

void CShot_GaneshaBorn::Rollback()
{
	m_pActorAniCtrl->SetIsMovieOn(false);
}
