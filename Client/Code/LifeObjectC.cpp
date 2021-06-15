#include "Stdafx.h"
#include "LifeObjectC.h"
#include "Object.h"

CLifeObjectC::CLifeObjectC()
{
}

CLifeObjectC::~CLifeObjectC()
{
	OnDestroy();
}

SP(Engine::CComponent) CLifeObjectC::MakeClone(Engine::CObject *pObject)
{
	SP(CLifeObjectC) spClone(new CLifeObjectC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CLifeObjectC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CLifeObjectC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CLifeObjectC::FixedUpdate(SP(CComponent) spThis)
{

}

void CLifeObjectC::Update(SP(CComponent) spThis)
{
	m_lifeTime -= GET_DT;

	if (m_lifeTime <= 0)
	{
		GetOwner()->SetIsEnabled(false);
	}
}

void CLifeObjectC::LateUpdate(SP(CComponent) spThis)
{

}

void CLifeObjectC::OnDestroy()
{
}

void CLifeObjectC::OnEnable()
{
	__super::OnEnable();
}

void CLifeObjectC::OnDisable()
{
	__super::OnDisable();
}
