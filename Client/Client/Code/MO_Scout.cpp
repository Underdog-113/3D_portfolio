#include "stdafx.h"
#include "..\Header\MO_Scout.h"


CMO_Scout::CMO_Scout()
{
}

SP(Engine::CObject) CMO_Scout::MakeClone(void)
{
	SP(CMO_Scout) spClone(new CMO_Scout, Engine::SmartDeleter<CMO_Scout>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMO_Scout::Awake(void)
{
	__super::Awake();
}

void CMO_Scout::Start(void)
{
	__super::Start();
}

void CMO_Scout::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Scout::Update(void)
{
	__super::Update();
}

void CMO_Scout::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Scout::PreRender(void)
{
	m_spComponentToRender->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Scout::Render(void)
{
	m_spComponentToRender->Render(GetComponent<Engine::CGraphicsC>());
}

void CMO_Scout::PostRender(void)
{
	m_spComponentToRender->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Scout::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Scout::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Scout::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Scout::SetBasicName(void)
{
}

SP(CMO_Scout) CMO_Scout::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Scout) spInstance(new CMO_Scout, Engine::SmartDeleter<CMO_Scout>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

