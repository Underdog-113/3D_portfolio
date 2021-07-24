#include "stdafx.h"
#include "..\Header\Shot_SlowAll.h"


CShot_SlowAll::CShot_SlowAll()
{
}


CShot_SlowAll::~CShot_SlowAll()
{
}

void CShot_SlowAll::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

}

void CShot_SlowAll::Enter()
{
	Engine::CFRC::GetInstance()->SetDtCoef(m_desc.timeSpeed);	
}

void CShot_SlowAll::Action()
{
	CShot::Action();
}

void CShot_SlowAll::Cut()
{
	Engine::CFRC::GetInstance()->SetDtCoef(1.f);
}

void CShot_SlowAll::Rollback()
{
	Engine::CFRC::GetInstance()->SetDtCoef(1.f);
}
