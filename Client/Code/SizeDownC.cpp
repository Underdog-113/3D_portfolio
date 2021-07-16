#include "Stdafx.h"
#include "SizeUpC.h"

CSizeDownC::CSizeDownC()
{
}

CSizeDownC::~CSizeDownC()
{
	OnDestroy();
}

SP(Engine::CComponent) CSizeDownC::MakeClone(Engine::CObject *pObject)
{
	SP(CSizeDownC) spClone(new CSizeDownC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CSizeDownC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CSizeDownC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_end = false;
	m_oldSize = GetOwner()->GetTransform()->GetSize();
}

void CSizeDownC::FixedUpdate(SP(CComponent) spThis)
{

}

void CSizeDownC::Update(SP(CComponent) spThis)
{
	if (m_end)
		return;

	GetOwner()->GetComponent<Engine::CTransformC>()->SetSize(m_oldSize * m_size);

	if (m_size >= 1)
	{
		m_size = m_size - (GET_DT * m_speed);
	}
	else
	{
		m_end = true;
		m_size = 1;
	}
}

void CSizeDownC::LateUpdate(SP(CComponent) spThis)
{

}

void CSizeDownC::OnDestroy()
{
}

void CSizeDownC::OnEnable()
{
	__super::OnEnable();
}

void CSizeDownC::OnDisable()
{
	__super::OnDisable();
}
