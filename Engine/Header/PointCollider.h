#ifndef POINTCOLLIDER_H
#define POINTCOLLIDER_H

#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CPointCollider final : public CCollider
{
	SMART_DELETER_REGISTER
private:
	explicit						CPointCollider		(void);
	virtual						   ~CPointCollider		(void);

public:
	static		SP(CPointCollider)	Create			(_int collisionID, _float3 offset);
				SP(CCollider)		MakeClone		(CCollisionC* pCC) override;

				void				Awake			(void) override;
				void				OnDestroy		(void) override;

				void				OnEnable		(void) override;
				void				OnDisable		(void) override;

				void				UpdatePosition	(void) override;
private:
				void				MakeBS			(void) override;

};
END
#endif