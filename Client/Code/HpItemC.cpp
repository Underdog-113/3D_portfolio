#include "Stdafx.h"
#include "OneConversationC.h"
#include "HpItemC.h"

CHpItemC::CHpItemC()
{
}

CHpItemC::~CHpItemC()
{
	OnDestroy();
}

SP(Engine::CComponent) CHpItemC::MakeClone(Engine::CObject *pObject)
{
	SP(CHpItemC) spClone(new CHpItemC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CHpItemC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CHpItemC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	
}

void CHpItemC::FixedUpdate(SP(CComponent) spThis)
{

}

void CHpItemC::Update(SP(CComponent) spThis)
{
}

void CHpItemC::LateUpdate(SP(CComponent) spThis)
{

}

void CHpItemC::OnDestroy()
{
}

void CHpItemC::OnEnable()
{
	__super::OnEnable();
}

void CHpItemC::OnDisable()
{
	__super::OnDisable();
}

