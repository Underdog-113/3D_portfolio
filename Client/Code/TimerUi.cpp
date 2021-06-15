#include "Stdafx.h"
#include "TimerUi.h"
#include "Object.h"

CTimerUi::CTimerUi()
{
}

CTimerUi::~CTimerUi()
{
	OnDestroy();
}

SP(Engine::CComponent) CTimerUi::MakeClone(Engine::CObject *pObject)
{
	SP(CTimerUi) spClone(new CTimerUi);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CTimerUi::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CTimerUi::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CTimerUi::FixedUpdate(SP(CComponent) spThis)
{

}

void CTimerUi::Update(SP(CComponent) spThis)
{
}

void CTimerUi::LateUpdate(SP(CComponent) spThis)
{

}

void CTimerUi::OnDestroy()
{
}

void CTimerUi::OnEnable()
{
	__super::OnEnable();
}

void CTimerUi::OnDisable()
{
	__super::OnDisable();
}