#include "EngineStdafx.h"
#include "Collider.h"


USING(Engine)
CCollider::CCollider(void)
{
}

CCollider::~CCollider(void)
{
}

void CCollider::Awake(void)
{
	MakeBS();
}

void CCollider::UpdatePosition(void)
{
	D3DXVec3TransformNormal(&m_offset, &m_offsetOrigin, &m_pOwner->GetTransform()->GetRotMatrix());
}

void CCollider::UpdateBS(void)
{
	MakeBS();
}
