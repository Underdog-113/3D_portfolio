#include "stdafx.h"
#include "..\Header\Kiana_Ult_Trail.h"

_uint CKiana_Ult_Trail::m_s_uniqueID = 0;

CKiana_Ult_Trail::CKiana_Ult_Trail()
{
}


CKiana_Ult_Trail::~CKiana_Ult_Trail()
{
}

SP(CKiana_Ult_Trail) CKiana_Ult_Trail::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_Ult_Trail) spInstance(new CKiana_Ult_Trail, Engine::SmartDeleter<CKiana_Ult_Trail>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Ult_Trail::MakeClone()
{
	SP(CKiana_Ult_Trail) spClone(new CKiana_Ult_Trail, Engine::SmartDeleter<CKiana_Ult_Trail>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_Ult_Trail::Awake()
{
	__super::Awake();
}

void CKiana_Ult_Trail::Start()
{
	__super::Start();
	m_fTrailAlpha = 1.f;
}

void CKiana_Ult_Trail::FixedUpdate()
{
	__super::FixedUpdate();
}

void CKiana_Ult_Trail::Update()
{
	__super::Update();

	if (m_fTrailAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fTrailAlpha -= 2.3f * GET_DT;
}

void CKiana_Ult_Trail::LateUpdate()
{
	__super::LateUpdate();
}

void CKiana_Ult_Trail::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gTrailAlpha", m_fTrailAlpha);
}

void CKiana_Ult_Trail::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_Ult_Trail::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CKiana_Ult_Trail::OnDestroy()
{
	__super::OnDestroy();
}

void CKiana_Ult_Trail::OnEnable()
{
	__super::OnEnable();
}

void CKiana_Ult_Trail::OnDisable()
{
	__super::OnDisable();
}

void CKiana_Ult_Trail::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
