#include "stdafx.h"
#include "..\Header\MO_Axe.h"


CMO_Axe::CMO_Axe()
{
}

SP(Engine::CObject) CMO_Axe::MakeClone(void)
{
	SP(CMO_Axe) spClone(new CMO_Axe, Engine::SmartDeleter<CMO_Axe>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMO_Axe::Awake(void)
{
	__super::Awake();
}

void CMO_Axe::Start(void)
{
	__super::Start();
}

void CMO_Axe::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Axe::Update(void)
{
	__super::Update();
}

void CMO_Axe::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Axe::PreRender(void)
{
	m_spComponentToRender->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Axe::Render(void)
{
	m_spComponentToRender->Render(GetComponent<Engine::CGraphicsC>());
}

void CMO_Axe::PostRender(void)
{
	m_spComponentToRender->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Axe::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Axe::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Axe::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Axe::SetBasicName(void)
{
}

SP(CMO_Axe) CMO_Axe::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Axe) spInstance(new CMO_Axe, Engine::SmartDeleter<CMO_Axe>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
