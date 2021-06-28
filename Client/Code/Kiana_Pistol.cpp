#include "stdafx.h"
#include "Kiana_Pistol.h"


CKiana_Pistol::CKiana_Pistol()
{
}


CKiana_Pistol::~CKiana_Pistol()
{
	OnDestroy();
}

SP(CKiana_Pistol) CKiana_Pistol::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_Pistol) spInstance(new CKiana_Pistol, Engine::SmartDeleter<CKiana_Pistol>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Pistol::MakeClone(void)
{
	SP(CKiana_Pistol) spClone(new CKiana_Pistol, Engine::SmartDeleter<CKiana_Pistol>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_Pistol::Awake(void)
{
	__super::Awake();
	m_dataID = (_int)EDataID::Player;
	m_layerID = (_int)ELayerID::Player;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
}

void CKiana_Pistol::Start(void)
{
	__super::Start();
}

void CKiana_Pistol::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_Pistol::Update(void)
{
	__super::Update();
}

void CKiana_Pistol::LateUpdate(void)
{
	__super::LateUpdate();

	//m_spTransform->SetLastWorldMatrix(*m_pParentMatrix);
}

void CKiana_Pistol::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_Pistol::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_Pistol::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_Pistol::OnDestroy(void)
{
	__super::OnDestroy();
}
void CKiana_Pistol::OnEnable(void)
{
	__super::OnEnable();
}

void CKiana_Pistol::OnDisable(void)
{
	__super::OnDisable();
}

void CKiana_Pistol::SetBasicName(void)
{
}
