#include "Stdafx.h"
#include "TimerC.h"

CTimerC::CTimerC()
{
}

CTimerC::~CTimerC()
{
	OnDestroy();
}

SP(Engine::CComponent) CTimerC::MakeClone(Engine::CObject *pObject)
{
	SP(CTimerC) spClone(new CTimerC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CTimerC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CTimerC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_value = 0;
}

void CTimerC::FixedUpdate(SP(CComponent) spThis)
{

}

void CTimerC::Update(SP(CComponent) spThis)
{
	m_value = min(m_value + (GET_DT * 30), m_time);

	_float m_totalTime = m_value;
	_int minute = (int)m_totalTime / 60;
	_int second = (int)m_totalTime % 60;
	
	GetOwner()->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(minute) + L" : " + std::to_wstring(second));
}

void CTimerC::LateUpdate(SP(CComponent) spThis)
{

}

void CTimerC::OnDestroy()
{
}

void CTimerC::OnEnable()
{
	__super::OnEnable();
}

void CTimerC::OnDisable()
{
	__super::OnDisable();
}
