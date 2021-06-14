#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CSimulationEventCallback;
class ENGINE_DLL CPhysicsManager final : public CEngine
{
	DECLARE_SINGLETON(CPhysicsManager)

public:
				void						Awake				(void) override;
				void						Start				(void);

				void						FixedUpdate			(void);

				void						OnDestroy			(void);

				void						OnEnable			(void);
				void						OnDisable			(void);


public:
				void						AddActor			(PxActor* pActor);
				void						RemoveActor			(PxActor* pActor);

private:
				void						SetupFiltering				(PxRigidActor* pActor, PxU32 filterGroup, PxU32 filterMask);

private:
	typedef		std::vector<PxActor*> _ACTORS;
				_ACTORS						m_vActors;

	static		PxDefaultAllocator			m_s_pxAllocatorCallback;
	static		PxDefaultErrorCallback		m_s_pxErrorCallback;

				PxFoundation*				m_pFoundation;
				PxPhysics*					m_pPhysics;
				PxScene*					m_pScene;
				PxMaterial*					m_pMaterial;

				CSimulationEventCallback*	m_pSimulationEventCallback;

				PxDefaultCpuDispatcher*		m_pDispatcher;
};
END
#endif