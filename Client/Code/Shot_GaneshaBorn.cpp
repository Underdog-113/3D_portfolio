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
	m_isSound = false;

	Engine::CSoundManager::GetInstance()->StopAll();
}

void CShot_GaneshaBorn::Action()
{
	CShot::Action();

	if (!m_isSound && m_pOnAirTake->GetPlayTimer() > 1.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000f)
	{
		Engine::CSoundManager::GetInstance()->StartSound(L"Ganesha_Intro.wav", (_uint)EChannelID::PLAYEREFFECT_CH2);
		m_isSound = true;
	}
		

	if (m_prevPlayTime < m_pOnAirTake->GetPlayTimer())
		m_pActorAniCtrl->PlayOnMovie(GET_DT);

	m_prevPlayTime = m_pOnAirTake->GetPlayTimer();
}

void CShot_GaneshaBorn::Cut()
{
	m_pActorAniCtrl->SetIsMovieOn(false);

	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->PlayBGM(L"GaneShaBGM_2.mp3");
	Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);

	CStageControlTower::GetInstance()->SetDirectorMode(false);
}

void CShot_GaneshaBorn::Rollback()
{
	m_pActorAniCtrl->SetIsMovieOn(false);
}
