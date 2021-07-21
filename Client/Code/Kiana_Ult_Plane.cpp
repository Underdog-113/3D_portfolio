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
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CKiana_Ult_Plane::Awake()
{
	__super::Awake();
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

	m_spTransform->AddSizeX(2.3f * GET_PLAYER_DT);
	m_spTransform->AddSizeZ(2.3f * GET_PLAYER_DT);

	m_fAlpha -= 0.8f * GET_PLAYER_DT;
}

void CKiana_Ult_Plane::LateUpdate()
{
	__super::LateUpdate();

}

void CKiana_Ult_Plane::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->CommitChanges();
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
