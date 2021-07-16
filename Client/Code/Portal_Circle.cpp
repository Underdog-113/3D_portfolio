#include "stdafx.h"
#include "..\Header\Portal_Circle.h"

_uint CPortal_Circle::m_s_uniqueID = 0;

CPortal_Circle::CPortal_Circle()
{
}


CPortal_Circle::~CPortal_Circle()
{
}

SP(CPortal_Circle) CPortal_Circle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CPortal_Circle) spInstance(new CPortal_Circle, Engine::SmartDeleter<CPortal_Circle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPortal_Circle::MakeClone()
{
	SP(CPortal_Circle) spClone(new CPortal_Circle, Engine::SmartDeleter<CPortal_Circle>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CPortal_Circle::Awake()
{
	__super::Awake();
	//_float _size = 1.3f;
	//m_spTransform->SetSize(_float3(_size, _size, _size));

}

void CPortal_Circle::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
}

void CPortal_Circle::FixedUpdate()
{
	__super::FixedUpdate();

}

void CPortal_Circle::Update()
{
	__super::Update();
	m_fUVSpeed += 3.2f * GET_DT;
}

void CPortal_Circle::LateUpdate()
{
	__super::LateUpdate();

}

void CPortal_Circle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);
	pEffect->SetBool("gPlayingAnim", true);
	pEffect->SetBool("g_zWriteEnabled", true);

	pEffect->CommitChanges();
}

void CPortal_Circle::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CPortal_Circle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CPortal_Circle::OnDestroy()
{
	__super::OnDestroy();

}

void CPortal_Circle::OnEnable()
{
	__super::OnEnable();

}

void CPortal_Circle::OnDisable()
{
	__super::OnDisable();

}

void CPortal_Circle::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
