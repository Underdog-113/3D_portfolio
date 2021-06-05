#include "stdafx.h"
#include "..\Header\MB_Bronya.h"


CMB_Bronya::CMB_Bronya()
{
}

SP(Engine::CObject) CMB_Bronya::MakeClone(void)
{
	SP(CMB_Bronya) spClone(new CMB_Bronya, Engine::SmartDeleter<CMB_Bronya>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMB_Bronya::Awake(void)
{
	__super::Awake();
}

void CMB_Bronya::Start(void)
{
	__super::Start();
}

void CMB_Bronya::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMB_Bronya::Update(void)
{
	__super::Update();
}

void CMB_Bronya::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMB_Bronya::PreRender(void)
{
	m_spComponentToRender->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CMB_Bronya::Render(void)
{
	m_spComponentToRender->Render(GetComponent<Engine::CGraphicsC>());
}

void CMB_Bronya::PostRender(void)
{
	m_spComponentToRender->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CMB_Bronya::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMB_Bronya::OnEnable(void)
{
	__super::OnEnable();
}

void CMB_Bronya::OnDisable(void)
{
	__super::OnDisable();
}

void CMB_Bronya::SetBasicName(void)
{
}

SP(CMB_Bronya) CMB_Bronya::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMB_Bronya) spInstance(new CMB_Bronya, Engine::SmartDeleter<CMB_Bronya>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

