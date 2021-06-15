#include "Stdafx.h"
#include "HitsUiC.h"
#include "Object.h"

CHitsUiC::CHitsUiC()
{
}

CHitsUiC::~CHitsUiC()
{
	OnDestroy();
}

SP(Engine::CComponent) CHitsUiC::MakeClone(Engine::CObject *pObject)
{
	SP(CHitsUiC) spClone(new CHitsUiC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CHitsUiC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
	m_hitsCount = 0;
}

void CHitsUiC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CHitsUiC::FixedUpdate(SP(CComponent) spThis)
{

}

void CHitsUiC::Update(SP(CComponent) spThis)
{
}

void CHitsUiC::LateUpdate(SP(CComponent) spThis)
{

}

void CHitsUiC::OnDestroy()
{
}

void CHitsUiC::OnEnable()
{
	__super::OnEnable();
}

void CHitsUiC::OnDisable()
{
	__super::OnDisable();
	m_hitsCount = 0;
}

void CHitsUiC::AddHitsCount(_int value)
{
	m_hitsCount += value;
	GetOwner()->GetComponent<Engine::CTextC>()->ChangeMessage(std::to_wstring(m_hitsCount));
}
