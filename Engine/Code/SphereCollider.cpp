#include "EngineStdafx.h"
#include "SphereCollider.h"
 
#include "Object.h"

USING(Engine)
CSphereCollider::CSphereCollider(void)
{
}

CSphereCollider::~CSphereCollider(void)
{
	OnDestroy();
}

SP(CCollider) CSphereCollider::Create(_int collisionID, _float radius, _float3 offset)
{
	SP(CSphereCollider) spInstance(new CSphereCollider, SmartDeleter<CSphereCollider>);
	spInstance->SetCollisionID(collisionID);
	spInstance->SetRadius(radius);
	spInstance->SetOffsetOrigin(offset);
	spInstance->Awake();

	return spInstance;
}

SP(CCollider) CSphereCollider::MakeClone(CCollisionC * pCC)
{
	SP(CSphereCollider) spClone(new CSphereCollider, SmartDeleter<CSphereCollider>);
	spClone->SetCollisionID(m_collisionID);
	spClone->SetOffsetOrigin(m_offsetOrigin);
	spClone->SetRadius(m_radius);
	spClone->SetRadiusBS(m_radiusBS);
	spClone->SetColliderType(m_colliderType);
	spClone->SetOwner(pCC);

	return spClone;
}

void CSphereCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_int)EColliderType::Sphere;
}

void CSphereCollider::OnDestroy(void)
{
}

void CSphereCollider::OnEnable(void)
{
}

void CSphereCollider::OnDisable(void)
{
}

void CSphereCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
}

void CSphereCollider::MakeBS(void)
{
	m_radiusBS = m_radius;
}
