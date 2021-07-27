#include "stdafx.h"
#include "..\Header\Shot_ReturnCameraToActor.h"

#include "Valkyrie.h"

CShot_ReturnCameraToActor::CShot_ReturnCameraToActor()
{
}


CShot_ReturnCameraToActor::~CShot_ReturnCameraToActor()
{
}

void CShot_ReturnCameraToActor::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

}

void CShot_ReturnCameraToActor::Enter()
{
	m_pCameraMan->GetPivot()->GetTransform()
		->SetPosition(CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition());

	m_pCameraMan->ReturnToMidShot();

	CStageControlTower::GetInstance()->GetCurrentActor()->GetStateMachine()->ChangeState(L"StandBy");
}

void CShot_ReturnCameraToActor::Action()
{
	CShot::Action();
}

void CShot_ReturnCameraToActor::Cut()
{
}

void CShot_ReturnCameraToActor::Rollback()
{
}
