#include "stdafx.h"
#include "..\Header\MeshEffect.h"

_uint CMeshEffect::m_s_uniqueID = 0;

CMeshEffect::CMeshEffect()
{
}


CMeshEffect::~CMeshEffect()
{
}

SP(CMeshEffect) CMeshEffect::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMeshEffect) spInstance(new CMeshEffect, Engine::SmartDeleter<CMeshEffect>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMeshEffect::MakeClone()
{
	SP(CMeshEffect) spClone(new CMeshEffect, Engine::SmartDeleter<CMeshEffect>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CMeshEffect::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CMeshEffect::Start()
{
	__super::Start();
}

void CMeshEffect::FixedUpdate()
{
	__super::FixedUpdate();
}

void CMeshEffect::Update()
{
	__super::Update();
}

void CMeshEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CMeshEffect::PreRender()
{
	m_spMesh->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CMeshEffect::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(GetComponent<Engine::CGraphicsC>(), pEffect);
}

void CMeshEffect::Render()
{
	m_spMesh->Render(GetComponent<Engine::CGraphicsC>());
}

void CMeshEffect::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(GetComponent<Engine::CGraphicsC>(), pEffect);
}

void CMeshEffect::PostRender()
{
	m_spMesh->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CMeshEffect::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(GetComponent<Engine::CGraphicsC>(), pEffect);
}

void CMeshEffect::OnDestroy()
{
	__super::OnDestroy();
}

void CMeshEffect::OnEnable()
{
	__super::OnEnable();
}

void CMeshEffect::OnDisable()
{
	__super::OnDisable();
}

void CMeshEffect::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

