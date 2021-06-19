#include "stdafx.h"
#include "..\Header\MO_Sickle.h"

#include "FSM_SickleC.h"

_uint CMO_Sickle::m_s_uniqueID = 0;

CMO_Sickle::CMO_Sickle()
{
}

CMO_Sickle::~CMO_Sickle()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Sickle::MakeClone(void)
{
	SP(CMO_Sickle) spClone(new CMO_Sickle, Engine::SmartDeleter<CMO_Sickle>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CMO_Sickle::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_SickleC>();
}

void CMO_Sickle::Start(void)
{
	__super::Start();

	m_spMesh->OnRootMotion();
}

void CMO_Sickle::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Sickle::Update(void)
{
	__super::Update();
}

void CMO_Sickle::LateUpdate(void)
{
	__super::LateUpdate();
}


void CMO_Sickle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}


void CMO_Sickle::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}


void CMO_Sickle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Sickle::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Sickle::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Sickle::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Sickle::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Sickle::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0; D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}

SP(CMO_Sickle) CMO_Sickle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Sickle) spInstance(new CMO_Sickle, Engine::SmartDeleter<CMO_Sickle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
