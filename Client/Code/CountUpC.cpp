#include "Stdafx.h"
#include "CountUpC.h"

CCountUpC::CCountUpC()
{
}

CCountUpC::~CCountUpC()
{
	OnDestroy();
}

SP(Engine::CComponent) CCountUpC::MakeClone(Engine::CObject *pObject)
{
	SP(CCountUpC) spClone(new CCountUpC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CCountUpC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CCountUpC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_value = 0;
}

void CCountUpC::FixedUpdate(SP(CComponent) spThis)
{

}

void CCountUpC::Update(SP(CComponent) spThis)
{
	m_value = min(m_value + (GET_DT * 30), m_count);

	GetOwner()->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring((int)m_value));
}

void CCountUpC::LateUpdate(SP(CComponent) spThis)
{

}

void CCountUpC::OnDestroy()
{
}

void CCountUpC::OnEnable()
{
	__super::OnEnable();
}

void CCountUpC::OnDisable()
{
	__super::OnDisable();
}
