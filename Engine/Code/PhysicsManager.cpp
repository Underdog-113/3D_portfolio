#include "EngineStdafx.h"
#include "PhysicsManager.h"
#include "SimulationEventCallback.h"

USING(Engine)
IMPLEMENT_SINGLETON(CPhysicsManager)

PxFilterFlags CollisionFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
									PxFilterObjectAttributes attributes1, PxFilterData filterData1,
									PxPairFlags & pairFlags, const void * constantBlock, PxU32 constantBlockSize);

PxDefaultAllocator		CPhysicsManager::m_s_pxAllocatorCallback	= {};
PxDefaultErrorCallback	CPhysicsManager::m_s_pxErrorCallback		= {};


void CPhysicsManager::Awake(void)
{
	m_pFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, m_s_pxAllocatorCallback, m_s_pxErrorCallback);
	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, PxTolerancesScale());
	if(m_pPhysics == NULL)
	{
		MSG_BOX(__FILE__, L"Failed creating PhysicsSDK in CPhysicsManager::Awake()");
		ABORT;
	}
	
	m_pSimulationEventCallback = new CSimulationEventCallback;
	m_pDispatcher = PxDefaultCpuDispatcherCreate(2);

	PxSceneDesc sceneDesc(m_pPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -9.81f, 0);
	sceneDesc.cpuDispatcher = m_pDispatcher;
	sceneDesc.filterShader = CollisionFilterShader;
	sceneDesc.simulationEventCallback = m_pSimulationEventCallback;
	sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
	m_pScene = m_pPhysics->createScene(sceneDesc);


	m_pMaterial = m_pPhysics->createMaterial(0.5f, 0.5f, 0.6f);
}

void CPhysicsManager::Start(void)
{
}

void CPhysicsManager::FixedUpdate(void)
{
	m_pScene->simulate(GET_DT);
}

void CPhysicsManager::OnDestroy(void)
{
	m_pPhysics->release();
	m_pFoundation->release();
}

void CPhysicsManager::OnEnable(void)
{
}

void CPhysicsManager::OnDisable(void)
{
}

void CPhysicsManager::AddActor(PxActor * pActor)
{
	m_vActors.emplace_back(pActor);
	m_pScene->addActor(*pActor);
}

void CPhysicsManager::RemoveActor(PxActor * pActor)
{
	for (auto& iter = m_vActors.begin(); iter != m_vActors.end(); ++iter)
	{
		if ((*iter) == pActor)
		{
			m_vActors.erase(iter);
			break;
		}
	}

	m_pScene->removeActor(*pActor);

	
}



void CPhysicsManager::SetupFiltering(PxRigidActor * pActor, PxU32 filterGroup, PxU32 filterMask)
{
	PxFilterData filterData;
	filterData.word0 = filterGroup;
	filterData.word1 = filterMask;

	const PxU32 numShapes = pActor->getNbShapes();
	PxShape** shapes = new PxShape*[numShapes];



	pActor->getShapes(shapes, numShapes);
	for (PxU32 i = 0; i < numShapes; ++i)
	{
		PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}

	delete[] shapes;
}


PxFilterFlags CollisionFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
									PxFilterObjectAttributes attributes1, PxFilterData filterData1,
									PxPairFlags & pairFlags, const void * constantBlock, PxU32 constantBlockSize)
{
	if (!(filterData0.word0 & filterData1.word1) || !(filterData0.word1 & filterData1.word0))
		return PxFilterFlag::eKILL;

	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags	= PxPairFlag::eNOTIFY_TOUCH_FOUND
					| PxPairFlag::eNOTIFY_TOUCH_LOST
					| PxPairFlag::eDETECT_DISCRETE_CONTACT
					| PxPairFlag::eNOTIFY_CONTACT_POINTS;
					
		return PxFilterFlag::eDEFAULT;
	}
	else
	{
		pairFlags	= PxPairFlag::eSOLVE_CONTACT
					| PxPairFlag::eNOTIFY_TOUCH_FOUND
					| PxPairFlag::eNOTIFY_TOUCH_LOST
					| PxPairFlag::eDETECT_DISCRETE_CONTACT
					| PxPairFlag::eNOTIFY_CONTACT_POINTS
					| PxPairFlag::ePOST_SOLVER_VELOCITY;

		return PxFilterFlag::eDEFAULT;
	}
}

