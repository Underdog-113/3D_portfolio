#include "stdafx.h"
#include "..\Header\Kiana_Ult_Ring.h"


CKiana_Ult_Ring::CKiana_Ult_Ring()
{
}


CKiana_Ult_Ring::~CKiana_Ult_Ring()
{
}

SP(CKiana_Ult_Ring) CKiana_Ult_Ring::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_Ult_Ring) spInstance(new CKiana_Ult_Ring, Engine::SmartDeleter<CKiana_Ult_Ring>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Ult_Ring::MakeClone()
{
	SP(CKiana_Ult_Ring) spClone(new CKiana_Ult_Ring, Engine::SmartDeleter<CKiana_Ult_Ring>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CKiana_Ult_Ring::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CKiana_Ult_Ring::Start()
{
	__super::Start();

}

void CKiana_Ult_Ring::FixedUpdate()
{
	__super::FixedUpdate();

}

void CKiana_Ult_Ring::Update()
{
	__super::Update();

	m_spTransform->AddSizeX(1.2f * GET_DT);
	m_spTransform->AddSizeZ(1.2f * GET_DT);

	m_fAlpha -= 0.5f * GET_DT;
}

void CKiana_Ult_Ring::LateUpdate()
{
	__super::LateUpdate();

}

void CKiana_Ult_Ring::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CKiana_Ult_Ring::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CKiana_Ult_Ring::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CKiana_Ult_Ring::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CKiana_Ult_Ring::OnEnable()
{
	__super::OnEnable();

}

void CKiana_Ult_Ring::OnDisable()
{
	__super::OnDisable();

}

void CKiana_Ult_Ring::SetBasicName()
{
}
