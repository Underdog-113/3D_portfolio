#include "stdafx.h"
#include "..\Header\MB_Ganesha.h"


CMB_Ganesha::CMB_Ganesha()
{
}

SP(Engine::CObject) CMB_Ganesha::MakeClone(void)
{
	SP(CMB_Ganesha) spClone(new CMB_Ganesha, Engine::SmartDeleter<CMB_Ganesha>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMB_Ganesha::Awake(void)
{
	__super::Awake();
}

void CMB_Ganesha::Start(void)
{
	__super::Start();
}

void CMB_Ganesha::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMB_Ganesha::Update(void)
{
	__super::Update();
}

void CMB_Ganesha::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMB_Ganesha::PreRender(void)
{
	m_spComponentToRender->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CMB_Ganesha::Render(void)
{
	m_spComponentToRender->Render(GetComponent<Engine::CGraphicsC>());
}

void CMB_Ganesha::PostRender(void)
{
	m_spComponentToRender->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CMB_Ganesha::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMB_Ganesha::OnEnable(void)
{
	__super::OnEnable();
}

void CMB_Ganesha::OnDisable(void)
{
	__super::OnDisable();
}

void CMB_Ganesha::SetBasicName(void)
{
}

SP(CMB_Ganesha) CMB_Ganesha::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMB_Ganesha) spInstance(new CMB_Ganesha, Engine::SmartDeleter<CMB_Ganesha>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

