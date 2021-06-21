#include "stdafx.h"
#include "Kiana_CatPaw_Atk05.h"

#pragma region Engine
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#pragma endregion

CKiana_CatPaw_Atk05::CKiana_CatPaw_Atk05()
{
}


CKiana_CatPaw_Atk05::~CKiana_CatPaw_Atk05()
{
	OnDestroy();
}

SP(CKiana_CatPaw_Atk05) CKiana_CatPaw_Atk05::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_CatPaw_Atk05) spInstance(new CKiana_CatPaw_Atk05, Engine::SmartDeleter<CKiana_CatPaw_Atk05>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_CatPaw_Atk05::MakeClone(void)
{
	SP(CKiana_CatPaw_Atk05) spClone(new CKiana_CatPaw_Atk05, Engine::SmartDeleter<CKiana_CatPaw_Atk05>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_CatPaw_Atk05::Awake(void)
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

void CKiana_CatPaw_Atk05::Start(void)
{
	__super::Start();

	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetReplay(false);
}

void CKiana_CatPaw_Atk05::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_CatPaw_Atk05::Update(void)
{
	__super::Update();

	m_tempTimer += GET_DT;

	if (m_tempTimer > m_tempDuration)
	{
		m_tempTimer = 0.f;
		SetIsEnabled(false);
	}
}

void CKiana_CatPaw_Atk05::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana_CatPaw_Atk05::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk05::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk05::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk05::OnDestroy(void)
{
	__super::OnDestroy();
}

void CKiana_CatPaw_Atk05::OnEnable(void)
{
	m_spMesh->GetFirstMeshData_Dynamic()->ResetAnimation();
	__super::OnEnable();
}

void CKiana_CatPaw_Atk05::OnDisable(void)
{
	__super::OnDisable();
	m_spMesh->GetFirstMeshData_Dynamic()->ResetAnimation();
}

void CKiana_CatPaw_Atk05::SetBasicName(void)
{
}
