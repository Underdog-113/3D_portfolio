#include "stdafx.h"
#include "..\Header\KianaUIAnim.h"

_uint CKianaUIAnim::m_s_uniqueID = 0;


CKianaUIAnim::CKianaUIAnim()
{
}


CKianaUIAnim::~CKianaUIAnim()
{
}

SP(CKianaUIAnim) CKianaUIAnim::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKianaUIAnim) spInstance(new CKianaUIAnim, Engine::SmartDeleter<CKianaUIAnim>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKianaUIAnim::MakeClone(void)
{
	SP(CKianaUIAnim) spClone(new CKianaUIAnim, Engine::SmartDeleter<CKianaUIAnim>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKianaUIAnim::Awake(void)
{
	__super::Awake();
	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CKianaUIAnim::Start(void)
{
	__super::Start();

	m_spMesh->SetMeshData(L"Kiana_UI");
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spShader->AddShader((_int)Engine::EShaderID::MeshShader);
}

void CKianaUIAnim::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKianaUIAnim::Update(void)
{
	__super::Update();

}

void CKianaUIAnim::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKianaUIAnim::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKianaUIAnim::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKianaUIAnim::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CKianaUIAnim::RenderPerShader(void)
{
	m_spMesh->RenderPerShader(m_spGraphics);
}

void CKianaUIAnim::OnDestroy(void)
{
	__super::OnDestroy();

}

void CKianaUIAnim::OnEnable(void)
{
	__super::OnEnable();

}

void CKianaUIAnim::OnDisable(void)
{
	__super::OnDisable();
}

void CKianaUIAnim::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
