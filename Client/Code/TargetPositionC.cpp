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
	if (m_target != nullptr)
	{
		auto cam = Engine::CCameraManager::GetInstance()->GetCamera(Engine::GET_CUR_SCENE->GetObjectKey() + L"BasicCamera");

		_float3 T = m_target->GetTransform()->GetPosition();
		T.y += m_target->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		_float3 pos2D = cam->WorldToScreenPoint(T);
		pos2D.z = 0.f;

		GetOwner()->GetTransform()->SetPosition(pos2D);
	}
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
