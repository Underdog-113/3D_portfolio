#include "stdafx.h"
#include "..\Header\Kiana_Pistol_USP45.h"


CKiana_Pistol_USP45::CKiana_Pistol_USP45()
{
}


CKiana_Pistol_USP45::~CKiana_Pistol_USP45()
{
	OnDestroy();
}

SP(CKiana_Pistol_USP45) CKiana_Pistol_USP45::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_Pistol_USP45) spInstance(new CKiana_Pistol_USP45, Engine::SmartDeleter<CKiana_Pistol_USP45>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Pistol_USP45::MakeClone(void)
{
	SP(CKiana_Pistol_USP45) spClone(new CKiana_Pistol_USP45, Engine::SmartDeleter<CKiana_Pistol_USP45>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_Pistol_USP45::Awake(void)
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

void CKiana_Pistol_USP45::Start(void)
{
	__super::Start();
}

void CKiana_Pistol_USP45::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_Pistol_USP45::Update(void)
{
	__super::Update();
}

void CKiana_Pistol_USP45::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana_Pistol_USP45::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_Pistol_USP45::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_Pistol_USP45::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_Pistol_USP45::OnDestroy(void)
{
	__super::OnDestroy();
}
void CKiana_Pistol_USP45::OnEnable(void)
{
	__super::OnEnable();
}

void CKiana_Pistol_USP45::OnDisable(void)
{
	__super::OnDisable();
}

void CKiana_Pistol_USP45::SetBasicName(void)
{
}
