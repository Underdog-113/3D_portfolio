#include "stdafx.h"
#include "Kiana_CatPaw_Atk04.h"

#pragma region Engine
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#pragma endregion

CKiana_CatPaw_Atk04::CKiana_CatPaw_Atk04()
{
}


CKiana_CatPaw_Atk04::~CKiana_CatPaw_Atk04()
{
	OnDestroy();
}

SP(CKiana_CatPaw_Atk04) CKiana_CatPaw_Atk04::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_CatPaw_Atk04) spInstance(new CKiana_CatPaw_Atk04, Engine::SmartDeleter<CKiana_CatPaw_Atk04>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_CatPaw_Atk04::MakeClone(void)
{
	SP(CKiana_CatPaw_Atk04) spClone(new CKiana_CatPaw_Atk04, Engine::SmartDeleter<CKiana_CatPaw_Atk04>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_CatPaw_Atk04::Awake(void)
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

void CKiana_CatPaw_Atk04::Start(void)
{
	__super::Start();

	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetReplay(false);
}

void CKiana_CatPaw_Atk04::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_CatPaw_Atk04::Update(void)
{
	__super::Update();

	m_tempTimer += GET_DT;

	if (m_tempTimer > m_tempDuration)
	{
		m_tempTimer = 0.f;
		SetIsEnabled(false);
	}
}

void CKiana_CatPaw_Atk04::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana_CatPaw_Atk04::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CKiana_CatPaw_Atk04::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk04::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CKiana_CatPaw_Atk04::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk04::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CKiana_CatPaw_Atk04::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk04::OnDestroy(void)
{
	__super::OnDestroy();
}

void CKiana_CatPaw_Atk04::OnEnable(void)
{
	__super::OnEnable();
	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(1.f);
	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->ChangeAniSet(0);
}

void CKiana_CatPaw_Atk04::OnDisable(void)
{
	__super::OnDisable();
	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->GetAniCtrl()->ResetTime();
	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0.f);
}

void CKiana_CatPaw_Atk04::SetBasicName(void)
{
}
