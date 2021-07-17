#include "stdafx.h"
#include "..\Header\Sakura_DashShade.h"

#include "AniCtrl.h"

_uint CSakura_DashShade::m_s_uniqueID = 0;

CSakura_DashShade::CSakura_DashShade()
{
}


CSakura_DashShade::~CSakura_DashShade()
{
}

SP(CSakura_DashShade) CSakura_DashShade::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_DashShade) spInstance(new CSakura_DashShade, Engine::SmartDeleter<CSakura_DashShade>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_DashShade::MakeClone()
{
	SP(CSakura_DashShade) spClone(new CSakura_DashShade, Engine::SmartDeleter<CSakura_DashShade>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	return spClone;
}

void CSakura_DashShade::Awake()
{
	__super::Awake();
	m_addExtra = true;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);
	m_spMesh->SetMeshData(L"Sakura_Wp");
	m_spMesh->OffRootMotion();
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
	m_spTexture = AddComponent<Engine::CTextureC>();	

	for(_uint i = 0; i < m_spMesh->GetMeshData()->GetSubsetCount(); ++i)
		m_spTexture->AddTexture(L"LaserColor");
}

void CSakura_DashShade::Start()
{
	__super::Start();
	m_spTransform->SetSize(1.2f, 1.2f, 1.2f);
	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->ChangeAniSet_NoBlend(m_iAnimIdx);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_fAlpha = 0.7f;
}

void CSakura_DashShade::FixedUpdate()
{
	__super::FixedUpdate();
}

void CSakura_DashShade::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 1.f * GET_PLAYER_DT;
}

void CSakura_DashShade::LateUpdate()
{
	__super::LateUpdate();

}

void CSakura_DashShade::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->CommitChanges();

}

void CSakura_DashShade::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CSakura_DashShade::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CSakura_DashShade::RenderPerShader(void)
{
	m_spMesh->RenderPerShader(m_spGraphics);
}

void CSakura_DashShade::OnDestroy()
{
	__super::OnDestroy();
}

void CSakura_DashShade::OnEnable()
{
	__super::OnEnable();

}

void CSakura_DashShade::OnDisable()
{
	__super::OnDisable();

}

void CSakura_DashShade::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
