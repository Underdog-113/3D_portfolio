#ifndef AABBCOLLIDER_H
#define AABBCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CAabbCollider final : public CCollider
{
	SMART_DELETER_REGISTER
private:
	explicit		CAabbCollider		(void);
	virtual		   ~CAabbCollider		(void);

public:
	static		SP(CAabbCollider)	Create					(_int collisionID, 
															 _float3 size = ONE_VECTOR, 
															 _float3 offset = ZERO_VECTOR);
				SP(CCollider)		MakeClone				(CCollisionC* pCC) override;

				void				Awake					(void) override;
				void				OnDestroy				(void) override;

				void				OnEnable				(void) override;
				void				OnDisable				(void) override;

				void				UpdatePosition			(void) override;

public:
				_float				SqDistFromPoint			(_float3 const& point);
				_float3				ClosestFromPoint		(_float3 const& point);
				_float3				SurfacePoint			(_float3 const& dir);
				_float3				SurfacePointFromInside	(_float3 const& dir, _float3 const& pos);
private:
				void				MakeBS					(void) override;

protected:
	GETTOR_SETTOR	(_float3,		m_halfSize,		ONE_VECTOR,		HalfSize)
	GETTOR_SETTOR	(_float3,		m_size,			ONE_VECTOR,		Size)
};
END
#endif