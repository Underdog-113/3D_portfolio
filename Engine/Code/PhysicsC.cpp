#include "EngineStdafx.h"
#include "PhysicsC.h"

USING(Engine)
CPhysicsC::CPhysicsC()
{
}


CPhysicsC::~CPhysicsC()
{
}

SP(CComponent) CPhysicsC::MakeClone(CObject * pObject)
{
	SP(CGraphicsC) spClone(new CGraphicsC);
	CComponent::InitClone(spClone, pObject);

	return spClone;
}

void CPhysicsC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();
		CScene*	pOwnerScene		= m_pOwner->GetScene();

		
	}
}

void CPhysicsC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_spCollision	= m_pOwner->GetComponent<CCollisionC>();
	m_spRigidBody	= m_pOwner->GetComponent<CRigidBodyC>();
	m_spTransform	= m_pOwner->GetComponent<CTransformC>();

	if (m_spCollision == nullptr || m_spRigidBody == nullptr)
	{
		MSG_BOX(__FILE__, L"One or more components are missing in CPhysicsC::Start()");
		ABORT;
	}

	
}

void CPhysicsC::FixedUpdate(SP(CComponent) spThis)
{
}

void CPhysicsC::Update(SP(CComponent) spThis)
{
}

void CPhysicsC::LateUpdate(SP(CComponent) spThis)
{
}

void CPhysicsC::OnDestroy(void)
{
}

void CPhysicsC::OnDisable(void)
{
}

void CPhysicsC::OnEnable(void)
{
}
