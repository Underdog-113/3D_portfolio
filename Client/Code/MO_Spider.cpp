#include "stdafx.h"
#include "..\Header\MO_Spider.h"

#include "FSM_SpiderC.h"

_uint CMO_Spider::m_s_uniqueID = 0;

CMO_Spider::CMO_Spider()
{
}

CMO_Spider::~CMO_Spider()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Spider::MakeClone(void)
{
	SP(CMO_Spider) spClone(new CMO_Spider, Engine::SmartDeleter<CMO_Spider>);
	__super::InitClone(spClone);

	spClone->m_spTransform		= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh			= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics		= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader			= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture		= spClone->GetComponent<Engine::CTextureC>();
	
	spClone->m_spStateMachine	= spClone->GetComponent<CFSM_SpiderC>();
	return spClone;
}

void CMO_Spider::Awake(void)
{
	__super::Awake();	

	m_spStateMachine = AddComponent<CFSM_SpiderC>();
}

void CMO_Spider::Start(void)
{
	__super::Start();
	
	m_spMesh->OnRootMotion();
}

void CMO_Spider::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Spider::Update(void)
{
	__super::Update();
}

void CMO_Spider::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Spider::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CMO_Spider::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Spider::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CMO_Spider::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMO_Spider::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CMO_Spider::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Spider::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Spider::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Spider::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Spider::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Spider::Chase_Target(_float baseAngle, _float3 targetPos, _float speed, _float deltaTime)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0; D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}


SP(CMO_Spider) CMO_Spider::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Spider) spInstance(new CMO_Spider, Engine::SmartDeleter<CMO_Spider>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}