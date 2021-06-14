#include "stdafx.h"
#include "Kiana_CatPaw_Atk03.h"

#pragma region Engine
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#pragma endregion

CKiana_CatPaw_Atk03::CKiana_CatPaw_Atk03()
{
}


CKiana_CatPaw_Atk03::~CKiana_CatPaw_Atk03()
{
	OnDestroy();
}

SP(CKiana_CatPaw_Atk03) CKiana_CatPaw_Atk03::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_CatPaw_Atk03) spInstance(new CKiana_CatPaw_Atk03, Engine::SmartDeleter<CKiana_CatPaw_Atk03>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_CatPaw_Atk03::MakeClone(void)
{
	SP(CKiana_CatPaw_Atk03) spClone(new CKiana_CatPaw_Atk03, Engine::SmartDeleter<CKiana_CatPaw_Atk03>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_CatPaw_Atk03::Awake(void)
{
	__super::Awake();
	m_dataID = (_int)EDataID::Player;
	m_layerID = (_int)ELayerID::Player;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CKiana_CatPaw_Atk03::Start(void)
{
	__super::Start();

	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetReplay(false);
}

void CKiana_CatPaw_Atk03::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_CatPaw_Atk03::Update(void)
{
	__super::Update();
}

void CKiana_CatPaw_Atk03::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana_CatPaw_Atk03::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CKiana_CatPaw_Atk03::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk03::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CKiana_CatPaw_Atk03::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk03::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CKiana_CatPaw_Atk03::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk03::OnDestroy(void)
{
	__super::OnDestroy();
}

void CKiana_CatPaw_Atk03::OnEnable(void)
{
	__super::OnEnable();
}

void CKiana_CatPaw_Atk03::OnDisable(void)
{
	__super::OnDisable();
}

void CKiana_CatPaw_Atk03::SetBasicName(void)
{
}

