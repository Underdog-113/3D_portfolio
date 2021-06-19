#include "stdafx.h"
#include "PhaseChanger.h"


_uint CPhaseChanger::m_s_uniqueID = 0;
CPhaseChanger::CPhaseChanger()
{
}


CPhaseChanger::~CPhaseChanger()
{
	OnDestroy();
}

SP(CPhaseChanger) CPhaseChanger::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CPhaseChanger) spInstance(new CPhaseChanger, Engine::SmartDeleter<CPhaseChanger>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPhaseChanger::MakeClone(void)
{
	SP(CPhaseChanger) spClone(new CPhaseChanger, Engine::SmartDeleter<CPhaseChanger>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CPhaseChanger::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Map;
	m_dataID	= UNDEFINED;

	m_addExtra = true;

	m_spCollision	= AddComponent<Engine::CCollisionC>();
}

void CPhaseChanger::Start(void)
{
	__super::Start();
	
}

void CPhaseChanger::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CPhaseChanger::Update(void)
{
	__super::Update();
	
}

void CPhaseChanger::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CPhaseChanger::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CPhaseChanger::OnEnable(void)
{
	__super::OnEnable();
	
}

void CPhaseChanger::OnDisable(void)
{
	__super::OnDisable();
	
}

void CPhaseChanger::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
