#include "stdafx.h"
#include "..\Header\MB_Ganesha.h"

#include "FSM_GaneshaC.h"

_uint CMB_Ganesha::m_s_uniqueID = 0;

CMB_Ganesha::CMB_Ganesha()
{
}

CMB_Ganesha::~CMB_Ganesha()
{
	OnDestroy();
}

SP(Engine::CObject) CMB_Ganesha::MakeClone(void)
{
	SP(CMB_Ganesha) spClone(new CMB_Ganesha, Engine::SmartDeleter<CMB_Ganesha>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_GaneshaC>();

	return spClone;
}

void CMB_Ganesha::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_GaneshaC>();
}

void CMB_Ganesha::Start(void)
{
	__super::Start();

	m_spMesh->OnRootMotion();
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

void CMB_Ganesha::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMB_Ganesha::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMB_Ganesha::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
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
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

SP(CMB_Ganesha) CMB_Ganesha::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMB_Ganesha) spInstance(new CMB_Ganesha, Engine::SmartDeleter<CMB_Ganesha>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMB_Ganesha::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0; D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}

