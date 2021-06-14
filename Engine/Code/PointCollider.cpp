#include "EngineStdafx.h"
#include "PointCollider.h"


USING(Engine)
CPointCollider::CPointCollider()
{
}


CPointCollider::~CPointCollider()
{
	OnDestroy();
}

SP(CPointCollider) CPointCollider::Create(_float3 offset)
{
	SP(CPointCollider) spInstance(new CPointCollider, SmartDeleter<CPointCollider>);
	spInstance->SetOffsetOrigin(offset);
	spInstance->Awake();

	return spInstance;
}

CCollider * CPointCollider::MakeClone(CCollisionC * pCC)
{
	CPointCollider* pPointClone = new CPointCollider;
	pPointClone->SetOffsetOrigin(m_offsetOrigin);
	pPointClone->SetRadiusBS(m_radiusBS);
	pPointClone->SetColliderType(m_colliderType);
	

	pPointClone->SetOwner(pCC);

	return pPointClone;
}

void CPointCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_uint)EColliderType::Point;
}

void CPointCollider::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CPointCollider::OnEnable(void)
{
}

void CPointCollider::OnDisable(void)
{
}

void CPointCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
}

void CPointCollider::MakeBS(void)
{
	m_radiusBS = 0.f;
}
