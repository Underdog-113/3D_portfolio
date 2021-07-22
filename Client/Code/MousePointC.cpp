#include "Stdafx.h"
#include "MousePointC.h"

CMousePointC::CMousePointC()
{

}

CMousePointC::~CMousePointC()
{
	OnDestroy();
}

SP(Engine::CComponent) CMousePointC::MakeClone(Engine::CObject *pObject)
{
	SP(CMousePointC) spClone(new CMousePointC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CMousePointC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CMousePointC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CMousePointC::FixedUpdate(SP(CComponent) spThis)
{

}

void CMousePointC::Update(SP(CComponent) spThis)
{
	_float3 pos = Engine::CInputManager::GetInstance()->GetMousePos();

	pos.x += 7;
	pos.y += -9;
	pos.z = 1.0f;
	GetOwner()->GetTransform()->SetPosition(pos);
}

void CMousePointC::LateUpdate(SP(CComponent) spThis)
{

}

void CMousePointC::OnDestroy()
{
}

void CMousePointC::OnEnable()
{
	__super::OnEnable();
}

void CMousePointC::OnDisable()
{
	__super::OnDisable();
}