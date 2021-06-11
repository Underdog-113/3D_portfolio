#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CPhysicsManager final : public CEngine
{
	DECLARE_SINGLETON(CPhysicsManager)

public:
				void						Awake				(void) override;
				void						Start				(void);

				void						FixedUpdate			(void);
				void						Update				(void);
				void						LateUpdate			(void);	

				void						OnDestroy			(void);

				void						OnEnable			(void);
				void						OnDisable			(void);


public:
				PxRigidStatic*				CreateStatic		(PxTransform& transform, PxGeometry& geometry, PxReal density);
				PxRigidDynamic*				CreateDynamic		(PxTransform& transform, PxGeometry& geometry, PxReal density);



private:
				//PxFilterFlags				CollisionFilterShader		(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
				//														 PxFilterObjectAttributes attributes1, PxFilterData filterData1,
				//														 PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);

				void						SetupFiltering				(PxRigidActor* pActor, PxU32 filterGroup, PxU32 filterMask);

private:
	static		PxDefaultAllocator			m_s_pxAllocatorCallback;
	static		PxDefaultErrorCallback		m_s_pxErrorCallback;

				PxFoundation*				m_pFoundation;
				PxPvd*						m_pPVD;
				PxPhysics*					m_pPhysics;
				PxCooking*					m_pCooking;
				PxScene*					m_pScene;
				PxMaterial*					m_pMaterial;

				PxDefaultCpuDispatcher*		m_pDispatcher;
};
END
#endif