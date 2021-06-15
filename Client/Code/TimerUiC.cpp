#include "Stdafx.h"
#include "TimerUiC.h"
#include "Object.h"
#include <cmath>

CTimerUiC::CTimerUiC()
{
}

CTimerUiC::~CTimerUiC()
{
	OnDestroy();
}

SP(Engine::CComponent) CTimerUiC::MakeClone(Engine::CObject *pObject)
{
	SP(CTimerUiC) spClone(new CTimerUiC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CTimerUiC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CTimerUiC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_totalTime = 0;
}

void CTimerUiC::FixedUpdate(SP(CComponent) spThis)
{

}

void CTimerUiC::Update(SP(CComponent) spThis)
{
	m_totalTime += GET_DT;
	_int minute = (int)m_totalTime / 60;
	_int second = (int)m_totalTime % 60;
	GetOwner()->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(minute) + L" : " + std::to_wstring(second));
}

void CTimerUiC::LateUpdate(SP(CComponent) spThis)
{
#
}

void CTimerUiC::OnDestroy()
{
}

void CTimerUiC::OnEnable()
{
	__super::OnEnable();
}

void CTimerUiC::OnDisable()
{
	__super::OnDisable();
}