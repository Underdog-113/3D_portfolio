#include "EngineStdafx.h"
#include "AabbCollider.h"

USING(Engine)
CAabbCollider::CAabbCollider()
{
}


CAabbCollider::~CAabbCollider()
{
	OnDestroy();
}

SP(CAabbCollider) CAabbCollider::Create(_int collisionID, _float3 size, _float3 offset)
{
	SP(CAabbCollider) spInstance(new CAabbCollider, SmartDeleter<CAabbCollider>);
	spInstance->SetCollisionID(collisionID);
	spInstance->SetOffsetOrigin(offset);
	spInstance->SetOffset(offset);
	spInstance->SetSize(size);
	spInstance->SetHalfSize(size / 2.f);
	spInstance->Awake();

	return spInstance;
}

SP(CCollider) CAabbCollider::MakeClone(CCollisionC * pCC)
{
	SP(CAabbCollider) spClone(new CAabbCollider, SmartDeleter<CAabbCollider>);
	spClone->SetCollisionID(m_collisionID);
	spClone->SetSize(m_size);
	spClone->SetHalfSize(m_halfSize);
	spClone->SetOffsetOrigin(m_offsetOrigin);
	spClone->SetOffset(m_offsetOrigin);
	spClone->SetRadiusBS(m_radiusBS);
	spClone->SetColliderType(m_colliderType);
	spClone->SetOwner(pCC);

	return spClone;
}

void CAabbCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_uint)EColliderType::AABB;
}

void CAabbCollider::OnDestroy(void)
{
}

void CAabbCollider::OnEnable(void)
{
}

void CAabbCollider::OnDisable(void)
{
}

void CAabbCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
}

_float CAabbCollider::SqDistFromPoint(_float3 const& point)
{
	_float sqDist = 0.f;
	
	_float3 minPos = m_pOwner->GetTransform()->GetPosition() + m_offset - m_halfSize;
	_float3 maxPos = m_pOwner->GetTransform()->GetPosition() + m_offset + m_halfSize;

	for (int i = 0; i < 3; ++i)
	{
		if (point[i] < minPos[i]) sqDist += (minPos[i] - point[i]) * (minPos[i] - point[i]);
		if (point[i] > maxPos[i]) sqDist += (point[i] - maxPos[i]) * (point[i] - maxPos[i]);
	}

	return sqDist;
}

_float3 CAabbCollider::ClosestFromPoint(_float3 const& point)
{
	_float3 closestPoint = ZERO_VECTOR;

	_float3 minPos = m_pOwner->GetTransform()->GetPosition() + m_offset - m_halfSize;
	_float3 maxPos = m_pOwner->GetTransform()->GetPosition() + m_offset + m_halfSize;

	for (int i = 0; i < 3; ++i)
	{
		if (point[i] < minPos[i])		closestPoint[i] = minPos[i];
		else if (point[i] > maxPos[i])	closestPoint[i] = maxPos[i];
		else							closestPoint[i] = point[i];
		
	}

	return closestPoint;
}

_float3 CAabbCollider::SurfacePoint(_float3 const& dir)
{
	SP(CTransformC) spTransform = m_pOwner->GetTransform();
	_float3 hitPoint;
	_float3 proportion(abs(dir.x / m_halfSize.x), abs(dir.y / m_halfSize.y), abs(dir.z / m_halfSize.z));
	if (proportion.x > proportion.y && proportion.x > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.x;
	else if (proportion.y > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.y;
	else
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.z;

	return hitPoint;
}

_float3 CAabbCollider::SurfacePointFromInside(_float3 const & dir, _float3 const & pos)
{
	SP(CTransformC) spTransform = m_pOwner->GetTransform();
	_float3 hitPoint;

	_float xDet = (m_halfSize.x - (abs(pos.x - (spTransform->GetPosition().x + m_offset.x))));
	_float yDet = (m_halfSize.y - (abs(pos.y - (spTransform->GetPosition().y + m_offset.y))));
	_float zDet = (m_halfSize.z - (abs(pos.z - (spTransform->GetPosition().z + m_offset.z))));

	if (xDet == 0 || yDet == 0 || zDet == 0)
		return pos;

	_float3 proportion(abs(dir.x / xDet), 
					   abs(dir.y / yDet), 
					   abs(dir.z / zDet));

	if (proportion.x > proportion.y && proportion.x > proportion.z)
		hitPoint = pos + dir / proportion.x;
	else if (proportion.y > proportion.z)
		hitPoint = pos + dir / proportion.y;
	else
		hitPoint = pos + dir / proportion.z;

	return hitPoint;
}

void CAabbCollider::MakeBS(void)
{
	_float3 minPos = m_offsetOrigin - m_halfSize;
	_float3 maxPos = m_offsetOrigin + m_halfSize;

	m_radiusBS = D3DXVec3Length(&(maxPos - minPos)) / 2.f;
}
