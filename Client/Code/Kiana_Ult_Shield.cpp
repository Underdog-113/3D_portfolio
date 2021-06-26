#include "stdafx.h"
#include "..\Header\Kiana_Ult_Shield.h"


CKiana_Ult_Shield::CKiana_Ult_Shield()
{
}


CKiana_Ult_Shield::~CKiana_Ult_Shield()
{
}

SP(CKiana_Ult_Shield) CKiana_Ult_Shield::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_Ult_Shield) spInstance(new CKiana_Ult_Shield, Engine::SmartDeleter<CKiana_Ult_Shield>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Ult_Shield::MakeClone()
{
	SP(CKiana_Ult_Shield) spClone(new CKiana_Ult_Shield, Engine::SmartDeleter<CKiana_Ult_Shield>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetPosition(_float3(0.f, 0.f, 0.f));
	spClone->m_spTransform->SetRotation(_float3(0.f, 0.f, 0.f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CKiana_Ult_Shield::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CKiana_Ult_Shield::Start()
{
	__super::Start();

}

void CKiana_Ult_Shield::FixedUpdate()
{
	__super::FixedUpdate();
}

void CKiana_Ult_Shield::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
		m_fAlpha = 1.f;
	}

	m_fAlpha -= 0.5f * GET_DT;
}

void CKiana_Ult_Shield::LateUpdate()
{
	__super::LateUpdate();
}

void CKiana_Ult_Shield::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CKiana_Ult_Shield::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_Ult_Shield::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CKiana_Ult_Shield::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CKiana_Ult_Shield::OnEnable()
{
	__super::OnEnable();
}

void CKiana_Ult_Shield::OnDisable()
{
	__super::OnDisable();
}

void CKiana_Ult_Shield::SetBasicName()
{
}
