#include "EngineStdafx.h"
#include "RayCollider.h"
 
#include "Scene.h"
 
#include "Object.h"

USING(Engine)
CRayCollider::CRayCollider()
{
}


CRayCollider::~CRayCollider()
{
	OnDestroy();
}

SP(CRayCollider) CRayCollider::Create(_int collisionID, _float3 offset, _float3 direction, _float length, ERayType rayType)
{
	SP(CRayCollider) spInstance(new CRayCollider, SmartDeleter<CRayCollider>);
	spInstance->SetCollisionID(collisionID);
	spInstance->SetOffsetOrigin(offset);
	spInstance->SetOffset(offset);
	spInstance->SetDirectionOrigin(direction);
	spInstance->SetDirection(direction);
	spInstance->SetLength(length);
	spInstance->SetRayType(rayType);
	spInstance->Awake();

	return spInstance;
}

SP(CCollider) CRayCollider::MakeClone(CCollisionC * pCC)
{
	SP(CRayCollider) spClone(new CRayCollider, SmartDeleter<CRayCollider>);
	spClone->SetCollisionID(m_collisionID);
	spClone->SetOffsetOrigin(m_offsetOrigin);
	spClone->SetOffset(m_offsetOrigin);
	spClone->SetDirectionOrigin(m_directionOrigin);
	spClone->SetDirection(m_directionOrigin);
	spClone->SetLength(m_length);
	spClone->SetRayType(m_rayType);
	spClone->SetColliderType(m_colliderType);
	spClone->SetRadiusBS(m_radiusBS);

	spClone->SetOwner(pCC);

	return spClone;
}

void CRayCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_int)EColliderType::Ray;
}

void CRayCollider::OnDestroy(void)
{
}

void CRayCollider::OnEnable(void)
{
}

void CRayCollider::OnDisable(void)
{
}

void CRayCollider::UpdatePosition(void)
{
	__super::UpdatePosition();

	D3DXVec3TransformNormal(&m_direction, &m_directionOrigin, &m_pOwner->GetTransform()->GetRotMatrix());

}

void CRayCollider::MakeBS(void)
{
	m_radiusBS = m_length;
}
