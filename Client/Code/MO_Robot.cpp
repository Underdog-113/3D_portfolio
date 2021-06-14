#include "stdafx.h"
#include "..\Header\MO_Robot.h"


CMO_Robot::CMO_Robot()
{
}

SP(Engine::CObject) CMO_Robot::MakeClone(void)
{
	SP(CMO_Robot) spClone(new CMO_Robot, Engine::SmartDeleter<CMO_Robot>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMO_Robot::Awake(void)
{
	__super::Awake();
}

void CMO_Robot::Start(void)
{
	__super::Start();
}

void CMO_Robot::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Robot::Update(void)
{
	__super::Update();
}

void CMO_Robot::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Robot::PreRender(void)
{
	m_spMesh->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Robot::Render(void)
{
	m_spMesh->Render(GetComponent<Engine::CGraphicsC>());
}

void CMO_Robot::PostRender(void)
{
	m_spMesh->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Robot::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Robot::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Robot::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Robot::SetBasicName(void)
{
}

SP(CMO_Robot) CMO_Robot::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Robot) spInstance(new CMO_Robot, Engine::SmartDeleter<CMO_Robot>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
