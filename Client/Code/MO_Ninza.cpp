#include "stdafx.h"
#include "..\Header\MO_Ninza.h"


CMO_Ninza::CMO_Ninza()
{
}

SP(Engine::CObject) CMO_Ninza::MakeClone(void)
{
	SP(CMO_Ninza) spClone(new CMO_Ninza, Engine::SmartDeleter<CMO_Ninza>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMO_Ninza::Awake(void)
{
	__super::Awake();
}

void CMO_Ninza::Start(void)
{
	__super::Start();
}

void CMO_Ninza::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Ninza::Update(void)
{
	__super::Update();
}

void CMO_Ninza::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Ninza::PreRender(LPD3DXEFFECT pEffect)
{
}

void CMO_Ninza::Render(LPD3DXEFFECT pEffect)
{
}

void CMO_Ninza::PostRender(LPD3DXEFFECT pEffect)
{
}

void CMO_Ninza::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Ninza::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Ninza::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Ninza::SetBasicName(void)
{
}

void CMO_Ninza::ApplyHitInfo(HitInfo info)
{
}

SP(CMO_Ninza) CMO_Ninza::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Ninza) spInstance(new CMO_Ninza, Engine::SmartDeleter<CMO_Ninza>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

