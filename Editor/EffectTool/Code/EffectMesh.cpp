#include "stdafx.h"
#include "..\Header\EffectMesh.h"


CEffectMesh::CEffectMesh()
{
}


CEffectMesh::~CEffectMesh()
{
}

SP(CEffectMesh) CEffectMesh::Create(_bool isStatic, Engine::CScene * pScene)
{
	return SP(CEffectMesh)();
}

SP(Engine::CObject) CEffectMesh::MakeClone()
{
	SP(CEffectMesh) spClone(new CEffectMesh, Engine::SmartDeleter<CEffectMesh>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();

	return spClone;
}

void CEffectMesh::Awake()
{
	__super::Awake();
}

void CEffectMesh::Start()
{
	__super::Start();
	PickComponentToRender();
}

void CEffectMesh::FixedUpdate()
{
	__super::FixedUpdate();
}

void CEffectMesh::Update()
{
	__super::Update();
}

void CEffectMesh::LateUpdate()
{
	__super::LateUpdate();
}

void CEffectMesh::PreRender()
{
	m_spComponentToRender->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CEffectMesh::PreRender(LPD3DXEFFECT pEffect)
{
	m_spComponentToRender->PreRender(GetComponent<Engine::CGraphicsC>(), pEffect);
}

void CEffectMesh::Render()
{
	m_spComponentToRender->Render(GetComponent<Engine::CGraphicsC>());
}

void CEffectMesh::Render(LPD3DXEFFECT pEffect)
{
	m_spComponentToRender->Render(GetComponent<Engine::CGraphicsC>(), pEffect);
}

void CEffectMesh::PostRender()
{
	m_spComponentToRender->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CEffectMesh::PostRender(LPD3DXEFFECT pEffect)
{
	m_spComponentToRender->PostRender(GetComponent<Engine::CGraphicsC>(), pEffect);
}

void CEffectMesh::OnDestroy()
{
	__super::OnDestroy();
}

void CEffectMesh::OnEnable()
{
	__super::OnEnable();
}

void CEffectMesh::OnDisable()
{
	__super::OnDisable();
}

void CEffectMesh::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CEffectMesh::PickComponentToRender(void)
{
	SP(Engine::CMeshC)		spMesh = GetComponent<Engine::CMeshC>();
	SP(Engine::CRectTexC)	spRectTex = GetComponent<Engine::CRectTexC>();
	SP(Engine::CTextC)		spText = GetComponent<Engine::CTextC>();


	if (spMesh != nullptr)
		m_spComponentToRender = spMesh;
	else if (spRectTex != nullptr)
		m_spComponentToRender = spRectTex;
	else if (spText != nullptr)
		m_spComponentToRender = spText;
}
