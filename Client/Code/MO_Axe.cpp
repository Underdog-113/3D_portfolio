#include "stdafx.h"
#include "..\Header\MO_Axe.h"

#include "FSM_AxeC.h"

_uint CMO_Axe::m_s_uniqueID = 0;

CMO_Axe::CMO_Axe()
{
}

CMO_Axe::~CMO_Axe()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Axe::MakeClone(void)
{
	SP(CMO_Axe) spClone(new CMO_Axe, Engine::SmartDeleter<CMO_Axe>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMO_Axe::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_AxeC>();
}

void CMO_Axe::Start(void)
{
	__super::Start();

	m_spMesh->OnRootMotion();
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

void CMO_Axe::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Axe::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMO_Axe::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
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
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Axe::ApplyHitInfo(HitInfo info)
{
}

void CMO_Axe::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0; D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForwardUp(dir, UP_VECTOR);
}

SP(CMO_Axe) CMO_Axe::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Axe) spInstance(new CMO_Axe, Engine::SmartDeleter<CMO_Axe>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
