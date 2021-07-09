#include "Stdafx.h"
#include "SizeUpC.h"

CSizeUpC::CSizeUpC()
{
}

CSizeUpC::~CSizeUpC()
{
	OnDestroy();
}

SP(Engine::CComponent) CSizeUpC::MakeClone(Engine::CObject *pObject)
{
	SP(CSizeUpC) spClone(new CSizeUpC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CSizeUpC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CSizeUpC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CSizeUpC::FixedUpdate(SP(CComponent) spThis)
{

}

void CSizeUpC::Update(SP(CComponent) spThis)
{
	
}

void CSizeUpC::LateUpdate(SP(CComponent) spThis)
{

}

void CSizeUpC::OnDestroy()
{
}

void CSizeUpC::OnEnable()
{
	__super::OnEnable();
}

void CSizeUpC::OnDisable()
{
	__super::OnDisable();
}
