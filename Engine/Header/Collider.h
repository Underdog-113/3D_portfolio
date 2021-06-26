#ifndef COLLIDER_H
#define COLLIDER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CCollider abstract
{
protected:
	explicit								CCollider			(void);
	virtual								   ~CCollider			(void);

public:
	virtual			SP(CCollider)			MakeClone			(CCollisionC* pCC) PURE;

	virtual			void					Awake				(void) PURE;
	virtual			void					OnDestroy			(void) PURE;

	virtual			void					OnEnable			(void) PURE;
	virtual			void					OnDisable			(void) PURE;

//Interface
public:
	virtual			void					UpdatePosition		(void) PURE;
					void					UpdateBS			(void);
protected:
	virtual			void					MakeBS				(void) PURE;
protected:
	GETTOR_SETTOR	(CCollisionC*,			m_pOwner,			nullptr,		Owner)

	GETTOR_SETTOR	(_int,					m_collisionID,		UNDEFINED,		CollisionID)
	GETTOR_SETTOR	(_int,					m_colliderType,		UNDEFINED,		ColliderType)

	GETTOR_SETTOR	(_bool,					m_isTrigger,		false,			IsTrigger)

	//�θ� ������ǥ
	GETTOR_SETTOR	(_float3,				m_offsetOrigin,		ZERO_VECTOR,	OffsetOrigin)
	//���� ��ǥ
	GETTOR_SETTOR	(_float3,				m_offset,			ZERO_VECTOR,	Offset)
	//BoundingSphere�� ������.
	GETTOR_SETTOR	(_float,				m_radiusBS,			0,				RadiusBS)
};

END

#endif // COLLIDER_H
