#ifndef  CCOLLISIONMANAGER_H
#define  CCOLLISIONMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CCollisionManager final : public CEngine
{
	DECLARE_SINGLETON(CCollisionManager)
public:
				void				Awake					(void) override;
				void				Start					(_int numOfColliderID);

				void				FixedUpdate				(void);
				void				Update					(void);
				void				LateUpdate				(void);

				void				OnDestroy				(void);

				void				OnEnable				(void);
				void				OnDisable				(void);

public:
				void				AddCollisionToManager	(SP(CCollisionC) spCC);
				void				AddColliderToManager	(SP(CCollider) spCollider);

				_bool				CheckCollisionInstant	(SP(CCollider) spCollider, _int checkingLayer);
				std::vector<_int>&	GetLayersToCheck		(_int colliderID);
				
				void				InitCollisionMap		(void);

private:
				void				InitCollisionChecker	(void);
				void				CheckCollision			(SP(CCollider) spCollider);
				
private:
	std::vector<std::vector<_int>> m_vCollisionMap;

	std::vector<SP(CCollisionC)> m_vCollisions;
	std::vector<std::vector<SP(CCollider)>> m_vColliders;

	typedef std::function<_bool(SP(CCollider), SP(CCollider), _bool)>	_COLLISION_CHECKER;
	typedef std::array<std::array <_COLLISION_CHECKER, (_int)EColliderType::NumOfCT>, (_int)EColliderType::NumOfCT> _COLLISION_CHECKER_2D;
	_COLLISION_CHECKER_2D m_fpCollisionChecker;

	GETTOR		(_int,				m_numOfColliderID,		UNDEFINED,		NumOfColliderID)
};

END
#endif // ! CColliderManager_H