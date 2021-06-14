#ifndef RAYCOLLIDER_H
#define RAYCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CRayCollider final : public CCollider
{
	SMART_DELETER_REGISTER
private:
	explicit							CRayCollider		(void);
									   ~CRayCollider		(void);
public:
	static			SP(CRayCollider)	Create				(_int collisionID, _float3 offset, _float3 direction, 
															 _float length, ERayType rayType = ERayType::LIMITED);
					SP(CCollider)		MakeClone			(CCollisionC* pCC) override;

					void				Awake				(void) override;
					void				OnDestroy			(void) override;
																   
					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

					void				UpdatePosition		(void) override;

private:
					void				MakeBS				(void) override;
protected:
	GETTOR_SETTOR	(_float3,			m_directionOrigin,	ZERO_VECTOR,		DirectionOrigin)
	GETTOR_SETTOR	(_float3,			m_direction,		ZERO_VECTOR,		Direction)
	GETTOR_SETTOR	(_float,			m_length,			0,					Length)
	GETTOR_SETTOR	(ERayType,			m_rayType,			ERayType::LIMITED,	RayType)
};
END
#endif