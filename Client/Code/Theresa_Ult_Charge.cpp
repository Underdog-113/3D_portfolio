#include "stdafx.h"
#include "..\Header\Theresa_Ult_Charge.h"


CTheresa_Ult_Charge::CTheresa_Ult_Charge()
{
}


CTheresa_Ult_Charge::~CTheresa_Ult_Charge()
{
}

SP(CTheresa_Ult_Charge) CTheresa_Ult_Charge::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_Ult_Charge) spInstance(new CTheresa_Ult_Charge, Engine::SmartDeleter<CTheresa_Ult_Charge>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_Charge::MakeClone()
{
	SP(CTheresa_Ult_Charge) spClone(new CTheresa_Ult_Charge, Engine::SmartDeleter<CTheresa_Ult_Charge>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CTheresa_Ult_Charge::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CTheresa_Ult_Charge::Start()
{
	__super::Start();
}

void CTheresa_Ult_Charge::FixedUpdate()
{
	__super::FixedUpdate();
}

void CTheresa_Ult_Charge::Update()
{
	__super::Update();
}

void CTheresa_Ult_Charge::LateUpdate()
{
	__super::LateUpdate();
}

void CTheresa_Ult_Charge::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", true);
}

void CTheresa_Ult_Charge::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Ult_Charge::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_Ult_Charge::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CTheresa_Ult_Charge::OnEnable()
{
	__super::OnEnable();
}

void CTheresa_Ult_Charge::OnDisable()
{
	__super::OnDisable();
}

void CTheresa_Ult_Charge::SetBasicName()
{
}
