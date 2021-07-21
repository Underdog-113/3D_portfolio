#include "stdafx.h"
#include "..\Header\MainRoomBG.h"

_uint CMainRoomBG::m_s_uniqueID = 0;

CMainRoomBG::CMainRoomBG()
{
}


CMainRoomBG::~CMainRoomBG()
{
	OnDestroy();

}

SP(CMainRoomBG) CMainRoomBG::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMainRoomBG) spInstance(new CMainRoomBG, Engine::SmartDeleter<CMainRoomBG>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMainRoomBG::MakeClone(void)
{
	SP(CMainRoomBG) spClone(new CMainRoomBG, Engine::SmartDeleter<CMainRoomBG>);
	__super::InitClone(spClone);


	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CMainRoomBG::Awake(void)
{
	__super::Awake();

	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetMeshData(L"Cloud");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spTexture->AddTexture(L"Stage_LevelMatrix_Winter_BG04");
	m_spTexture->AddTexture(L"Stage_LevelMatrix_Winter_BG04");
	m_spShader->AddShader((_int)Engine::EShaderID::MeshShader);
}

void CMainRoomBG::Start(void)
{
	__super::Start();
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_fAlpha = 1.f;
}

void CMainRoomBG::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CMainRoomBG::Update(void)
{
	__super::Update();
}

void CMainRoomBG::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMainRoomBG::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->SetBool("g_AlphaTestEnabled", true);
	pEffect->CommitChanges();
}

void CMainRoomBG::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CMainRoomBG::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CMainRoomBG::OnDestroy(void)
{
	__super::OnDestroy();

}

void CMainRoomBG::OnEnable(void)
{
	__super::OnEnable();

}

void CMainRoomBG::OnDisable(void)
{
	__super::OnDisable();

}

void CMainRoomBG::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
