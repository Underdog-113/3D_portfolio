#include "stdafx.h"
#include "..\Header\Stage_Wall.h"

_uint CStage_Wall::m_s_uniqueID = 0;

CStage_Wall::CStage_Wall()
{
}


CStage_Wall::~CStage_Wall()
{
}

SP(CStage_Wall) CStage_Wall::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CStage_Wall) spInstance(new CStage_Wall, Engine::SmartDeleter<CStage_Wall>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CStage_Wall::MakeClone()
{
	SP(CStage_Wall) spClone(new CStage_Wall, Engine::SmartDeleter<CStage_Wall>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CStage_Wall::Awake()
{
	__super::Awake();

	m_spMesh->SetMeshData(L"Stage_Wall");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Wall");
	m_spTexture->AddTexture(L"Wall");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);

}

void CStage_Wall::Start()
{
	__super::Start();
	m_fAlpha = 1.f;

}

void CStage_Wall::FixedUpdate()
{
	__super::FixedUpdate();

}

void CStage_Wall::Update()
{
	__super::Update();

}

void CStage_Wall::LateUpdate()
{
	__super::LateUpdate();

}

void CStage_Wall::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->CommitChanges();
}

void CStage_Wall::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CStage_Wall::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CStage_Wall::OnDestroy()
{
	__super::OnDestroy();

}

void CStage_Wall::OnEnable()
{
	__super::OnEnable();

}

void CStage_Wall::OnDisable()
{
	__super::OnDisable();

}

void CStage_Wall::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
