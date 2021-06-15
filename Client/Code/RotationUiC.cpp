#include "Stdafx.h"
#include "RotationUiC.h"
#include "Object.h"

CRotationUiC::CRotationUiC()
{
}

CRotationUiC::~CRotationUiC()
{
	OnDestroy();
}

SP(Engine::CComponent) CRotationUiC::MakeClone(Engine::CObject *pObject)
{
	SP(CRotationUiC) spClone(new CRotationUiC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CRotationUiC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CRotationUiC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CRotationUiC::FixedUpdate(SP(CComponent) spThis)
{

}

void CRotationUiC::Update(SP(CComponent) spThis)
{
	GetOwner()->GetTransform()->AddRotationZ(m_speed * GET_DT);
}

void CRotationUiC::LateUpdate(SP(CComponent) spThis)
{

}

void CRotationUiC::OnDestroy()
{
}

void CRotationUiC::OnEnable()
{
	__super::OnEnable();
}

void CRotationUiC::OnDisable()
{
	__super::OnDisable();
}