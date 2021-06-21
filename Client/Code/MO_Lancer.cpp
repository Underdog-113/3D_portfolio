#include "stdafx.h"
#include "..\Header\MO_Lancer.h"


CMO_Lancer::CMO_Lancer()
{
}

SP(Engine::CObject) CMO_Lancer::MakeClone(void)
{
	SP(CMO_Lancer) spClone(new CMO_Lancer, Engine::SmartDeleter<CMO_Lancer>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMO_Lancer::Awake(void)
{
	__super::Awake();
}

void CMO_Lancer::Start(void)
{
	__super::Start();
}

void CMO_Lancer::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Lancer::Update(void)
{
	__super::Update();
}

void CMO_Lancer::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Lancer::PreRender(LPD3DXEFFECT pEffect)
{
}

void CMO_Lancer::Render(LPD3DXEFFECT pEffect)
{
}

void CMO_Lancer::PostRender(LPD3DXEFFECT pEffect)
{
}

void CMO_Lancer::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Lancer::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Lancer::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Lancer::SetBasicName(void)
{
}

void CMO_Lancer::ApplyHitInfo(HitInfo info)
{
}

SP(CMO_Lancer) CMO_Lancer::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Lancer) spInstance(new CMO_Lancer, Engine::SmartDeleter<CMO_Lancer>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

