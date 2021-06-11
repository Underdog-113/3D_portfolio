#include "EngineStdafx.h"
#include "PhysicsManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CPhysicsManager)

PxDefaultAllocator CPhysicsManager::m_s_pxAllocatorCallback = {};
PxDefaultErrorCallback CPhysicsManager::m_s_pxErrorCallback = {};
void CPhysicsManager::Awake(void)
{
	m_pFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, m_s_pxAllocatorCallback, m_s_pxErrorCallback);
	if (m_pFoundation == nullptr)
	{
		MSG_BOX(__FILE__, L"Failed creating Foundation in CPhysicsManager::Awake()");
		ABORT;
	}

	m_pPVD = PxCreatePvd(*m_pFoundation);
	PxPvdTransport* pTransport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	m_pPVD->connect(*pTransport, PxPvdInstrumentationFlag::eALL);

	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, PxTolerancesScale(), true, m_pPVD);

	PxCookingParams cookingParams(m_pPhysics->getTolerancesScale());
	m_pCooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_pFoundation, cookingParams);

	if (m_pCooking == nullptr)
	{
		MSG_BOX(__FILE__, L"Failed creating cooking in CPhysicsManager::Awake()");
		ABORT;
	}


	if (!PxInitExtensions(*m_pPhysics, m_pPVD))
	{
		MSG_BOX(__FILE__, L"Failed initializing extension in CPhysicsManager::Awake()");
		ABORT;
	}

	m_pDispatcher = PxDefaultCpuDispatcherCreate(2);

	PxSceneDesc sceneDesc(m_pPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -9.81f, 0);
	sceneDesc.cpuDispatcher = m_pDispatcher;
	sceneDesc.filterShader = CollisionFilterShader;
	m_pScene = m_pPhysics->createScene(sceneDesc);
	m_pMaterial = m_pPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	
}

void CPhysicsManager::Start(void)
{
}

void CPhysicsManager::FixedUpdate(void)
{
}

void CPhysicsManager::Update(void)
{
}

void CPhysicsManager::LateUpdate(void)
{
}

void CPhysicsManager::OnDestroy(void)
{
}

void CPhysicsManager::OnEnable(void)
{
}

void CPhysicsManager::OnDisable(void)
{
}



void CPhysicsManager::SetupFiltering(PxRigidActor * pActor, PxU32 filterGroup, PxU32 filterMask)
{
	PxFilterData filterData;
	filterData.word0 = filterGroup;
	filterData.word1 = filterMask;

	const PxU32 numShapes = pActor->getNbShapes();
	PxShape** shapes = new (PxShape**)[numShapes];
	
	pActor->getShapes(shapes, numShapes);
	for (PxU32 i = 0; i < numShapes; ++i)
	{
		PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}

	delete [] shapes;
}


PxFilterFlags CollisionFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
									PxFilterObjectAttributes attributes1, PxFilterData filterData1, 
									PxPairFlags & pairFlags, const void * constantBlock, PxU32 constantBlockSize)
{
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}

	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	if ((filterData0.word0 & filterData1.word1) && (filterData0.word1 & filterData1.word0))
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return PxFilterFlag::eDEFAULT;
}