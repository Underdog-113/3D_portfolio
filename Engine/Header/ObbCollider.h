#ifndef OBBCOLLIDER_H
#define OBBCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CObbCollider final : public CCollider
{
	SMART_DELETER_REGISTER
private:
	explicit							CObbCollider		(void);
	virtual							   ~CObbCollider		(void);

public:
	static			SP(CObbCollider)	Create				(_int collisionID, 
															 _float3 size = ONE_VECTOR, 
															 _float3 offset = ZERO_VECTOR, 
															 _float3 rotOffset = ZERO_VECTOR);

					SP(CCollider)		MakeClone			(CCollisionC* pCC) override;

					void				Awake				(void) override;
					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;
					void				OnDisable			(void) override;

					void				UpdatePosition		(void) override;
public:
					_float				SqDistFromPoint		(_float3 const& point);
					_float3				ClosestFromPoint	(_float3 const& point);
					_float3				SurfacePoint		(_float3 const& dir);
private:
					void				MakeBS				(void) override;
protected:
	GETTOR_SETTOR	(_float3,			m_halfSize,			ONE_VECTOR,			HalfSize)
	GETTOR_SETTOR	(_float3,			m_size,				ONE_VECTOR,			Size)
	GETTOR_SETTOR	(_float3,			m_rotOffset,		ZERO_VECTOR,		RotOffset)

	GETTOR_SETTOR	(_float3,			m_right,			RIGHT_VECTOR,		Right)
	GETTOR_SETTOR	(_float3,			m_up,				UP_VECTOR,			Up)
	GETTOR_SETTOR	(_float3,			m_forward,			FORWARD_VECTOR,		Forward)
};
END
#endif