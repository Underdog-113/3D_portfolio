#include "stdafx.h"
#include "..\Header\Kiana_Ult_Plane.h"


CKiana_Ult_Plane::CKiana_Ult_Plane()
{
}


CKiana_Ult_Plane::~CKiana_Ult_Plane()
{
	OnDestroy();

}

SP(CKiana_Ult_Plane) CKiana_Ult_Plane::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_Ult_Plane) spInstance(new CKiana_Ult_Plane, Engine::SmartDeleter<CKiana_Ult_Plane>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Ult_Plane::MakeClone()
{
	SP(CKiana_Ult_Plane) spClone(new CKiana_Ult_Plane, Engine::SmartDeleter<CKiana_Ult_Plane>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetPosition(_float3(0.f, 0.f, 0.f));
	spClone->m_spTransform->SetRotation(_float3(0.f, 0.f, 0.f));
	spClone->m_spTransform->SetSize(_float3(0.5f, 0.5f, 0.5f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CKiana_Ult_Plane::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CKiana_Ult_Plane::Start()
{
	__super::Start();

}

void CKiana_Ult_Plane::FixedUpdate()
{
	__super::FixedUpdate();

}

void CKiana_Ult_Plane::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
		m_fAlpha = 1.f;
	}	

	m_spTransform->AddSizeX(1.2f * GET_DT);
	m_spTransform->AddSizeZ(1.2f * GET_DT);

	m_fAlpha -= 0.5f * GET_DT;
}

void CKiana_Ult_Plane::LateUpdate()
{
	__super::LateUpdate();

}

void CKiana_Ult_Plane::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CKiana_Ult_Plane::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_Ult_Plane::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CKiana_Ult_Plane::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CKiana_Ult_Plane::OnEnable()
{
	__super::OnEnable();
}

void CKiana_Ult_Plane::OnDisable()
{
	__super::OnDisable();
}

void CKiana_Ult_Plane::SetBasicName()
{
}