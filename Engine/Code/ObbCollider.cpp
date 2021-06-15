#include "EngineStdafx.h"
#include "ObbCollider.h"


USING(Engine)
CObbCollider::CObbCollider()
{
}


CObbCollider::~CObbCollider()
{
	OnDestroy();
}

SP(CObbCollider) CObbCollider::Create(_int collisionID, _float3 size, _float3 offset, _float3 rotOffset)
{
	SP(CObbCollider) spInstance(new CObbCollider, SmartDeleter<CObbCollider>);
	spInstance->SetCollisionID(collisionID);
	spInstance->SetSize(size);
	spInstance->SetHalfSize(size / 2.f);
	spInstance->SetOffsetOrigin(offset);
	spInstance->SetRotOffset(rotOffset);

	spInstance->Awake();

	return spInstance;
}

SP(CCollider) CObbCollider::MakeClone(CCollisionC * pCC)
{
	SP(CObbCollider) spClone(new CObbCollider, SmartDeleter<CObbCollider>);
	
	//Create 
	spClone->SetCollisionID(m_collisionID);
	spClone->SetOffsetOrigin(m_offsetOrigin);
	spClone->SetSize(m_size);
	spClone->SetHalfSize(m_halfSize);
	spClone->SetRotOffset(m_rotOffset);

	//Awake
	spClone->SetRadiusBS(m_radiusBS);
	spClone->SetColliderType(m_colliderType);

	//MakeClone
	spClone->SetOwner(pCC);

	return spClone;
}

void CObbCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_uint)EColliderType::OBB;
}

void CObbCollider::OnDestroy(void)
{
}

void CObbCollider::OnEnable(void)
{
}

void CObbCollider::OnDisable(void)
{
}

void CObbCollider::UpdatePosition(void)
{
	__super::UpdatePosition();
	
	SP(CTransformC) spOwnerTransform = m_pOwner->GetTransform();

	_mat rotateX, rotateY, rotateZ, result;

	D3DXMatrixRotationX(&rotateX, m_pOwner->GetTransform()->GetRotation().x + m_rotOffset.x);
	D3DXMatrixRotationY(&rotateY, m_pOwner->GetTransform()->GetRotation().y + m_rotOffset.y);
	D3DXMatrixRotationZ(&rotateZ, m_pOwner->GetTransform()->GetRotation().z + m_rotOffset.z);
	_float hey = m_pOwner->GetTransform()->GetRotation().z + m_rotOffset.z;
	result = rotateX * rotateY * rotateZ;

	D3DXVec3TransformNormal(&m_right,	&RIGHT_VECTOR,		&result);
	D3DXVec3TransformNormal(&m_up,		&UP_VECTOR,			&result);
	D3DXVec3TransformNormal(&m_forward, &FORWARD_VECTOR,	&result);
}

_float CObbCollider::SqDistFromPoint(_float3 const& point)
{
	_float3 closest = ClosestFromPoint(point);

	return D3DXVec3Dot(&(closest - point), &(closest - point));
}

_float3 CObbCollider::ClosestFromPoint(_float3 const& point)
{
	_float3 center = m_pOwner->GetTransform()->GetPosition() + m_offset;
	_float3 dir = point - center;

	_float3 closest = center;
	
	_mat worldMat = m_pOwner->GetTransform()->GetWorldMatrix();

	_float3 orientedAxis[3] = {m_right, m_up, m_forward};

	for (_int i = 0; i < 3; ++i)
	{
		D3DXVec3Normalize(&orientedAxis[i], &orientedAxis[i]);
		_float dist = D3DXVec3Dot(&dir, &orientedAxis[i]);

		if (dist > m_halfSize[i]) dist = m_halfSize[i];
		if (dist < -m_halfSize[i]) dist = -m_halfSize[i];

		closest += (dist * orientedAxis[i]);
	}

	return closest;
}

//검증 필요
_float3 CObbCollider::SurfacePoint(_float3 const & dir)
{
	_float dotDirRight		= D3DXVec3Dot(&dir, &m_right);
	_float dotDirUp			= D3DXVec3Dot(&dir, &m_up);
	_float dotDirForward	= D3DXVec3Dot(&dir, &m_forward);

	_float3 projOnRight		= dotDirRight * m_right;
	_float3 projOnUp		= dotDirUp * m_up;
	_float3 projOnForward	= dotDirForward * m_forward;

	_float porSize	= D3DXVec3Length(&projOnRight);
	_float pouSize	= D3DXVec3Length(&projOnUp);
	_float pofSize	= D3DXVec3Length(&projOnForward);

	SP(CTransformC) spTransform = m_pOwner->GetTransform();
	_float3 hitPoint;
	_float3 proportion(porSize / m_halfSize.x, pouSize / m_halfSize.y, pofSize / m_halfSize.z);

	if (proportion.x > proportion.y && proportion.x > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.x;
	else if (proportion.y > proportion.z)
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.y;
	else
		hitPoint = spTransform->GetPosition() + m_offset + dir / proportion.z;

	return hitPoint;
}

void CObbCollider::MakeBS(void)
{
	_float3 minPos = m_offsetOrigin - m_halfSize;
	_float3 maxPos = m_offsetOrigin + m_halfSize;

	m_radiusBS = D3DXVec3Length(&(maxPos - minPos)) / 2.f;
}
