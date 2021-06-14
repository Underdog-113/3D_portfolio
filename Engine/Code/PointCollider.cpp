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

SP(CPointCollider) CPointCollider::Create(_int collisionID, _float3 offset)
{
	SP(CPointCollider) spInstance(new CPointCollider, SmartDeleter<CPointCollider>);
	spInstance->SetCollisionID(collisionID);
	spInstance->SetOffsetOrigin(offset);
	spInstance->Awake();

	return spInstance;
}

SP(CCollider) CPointCollider::MakeClone(CCollisionC * pCC)
{
	SP(CPointCollider) spClone(new CPointCollider, SmartDeleter<CPointCollider>);
	spClone->SetOffsetOrigin(m_offsetOrigin);
	spClone->SetRadiusBS(m_radiusBS);
	spClone->SetColliderType(m_colliderType);
	spClone->SetCollisionID(m_collisionID);
	spClone->SetOwner(pCC);

	return spClone;
}

void CPointCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_uint)EColliderType::Point;
}

void CPointCollider::OnDestroy(void)
{	
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
