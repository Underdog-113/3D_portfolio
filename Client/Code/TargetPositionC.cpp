#include "Stdafx.h"
#include "TargetPositionC.h"

CTargetPositionC::CTargetPositionC()
{
}

CTargetPositionC::~CTargetPositionC()
{
	OnDestroy();
}

SP(Engine::CComponent) CTargetPositionC::MakeClone(Engine::CObject *pObject)
{
	SP(CTargetPositionC) spClone(new CTargetPositionC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CTargetPositionC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CTargetPositionC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CTargetPositionC::FixedUpdate(SP(CComponent) spThis)
{

}

void CTargetPositionC::Update(SP(CComponent) spThis)
{
	_float3 pos2D = Engine::GET_MAIN_CAM->WorldToScreenPoint(m_target->GetTransform()->GetPosition());
	GetOwner()->GetTransform()->SetPosition(pos2D);
}

void CTargetPositionC::LateUpdate(SP(CComponent) spThis)
{

}

void CTargetPositionC::OnDestroy()
{
}

void CTargetPositionC::OnEnable()
{
	__super::OnEnable();
}

void CTargetPositionC::OnDisable()
{
	__super::OnDisable();
}
