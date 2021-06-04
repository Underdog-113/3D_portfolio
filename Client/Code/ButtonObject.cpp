#include "stdafx.h"
#include "ButtonObject.h"

CButtonObject::CButtonObject()
{
}

CButtonObject::~CButtonObject()
{
}

SP(CButtonObject) CButtonObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CButtonObject) spInstance(new CButtonObject, Engine::SmartDeleter<CButtonObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CButtonObject::MakeClone(void)
{
	SP(CButtonObject) spClone(new CButtonObject);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
	return SP(CObject)();
}

void CButtonObject::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::UI;	
	m_addExtra = true;

}

void CButtonObject::Start(void)
{
	__super::Start();
}

void CButtonObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CButtonObject::Update(void)
{
	__super::Update();
}

void CButtonObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CButtonObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CButtonObject::OnEnable(void)
{
	__super::OnEnable();
}

void CButtonObject::OnDisable(void)
{
	__super::OnDisable();
}

void CButtonObject::SetBasicName(void)
{
}

void CButtonObject::aa()
{
}