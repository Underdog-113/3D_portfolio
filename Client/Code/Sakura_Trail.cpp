#include "stdafx.h"
#include "..\Header\Sakura_Trail.h"

_uint CSakura_Trail::m_s_uniqueID = 0;

CSakura_Trail::CSakura_Trail()
{
}


CSakura_Trail::~CSakura_Trail()
{
}

SP(CSakura_Trail) CSakura_Trail::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_Trail) spInstance(new CSakura_Trail, Engine::SmartDeleter<CSakura_Trail>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_Trail::MakeClone()
{
	SP(CSakura_Trail) spClone(new CSakura_Trail, Engine::SmartDeleter<CSakura_Trail>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSakura_Trail::Awake()
{
	__super::Awake();

}

void CSakura_Trail::Start()
{
	__super::Start();
	m_fTrailAlpha = 1.f;

}

void CSakura_Trail::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_Trail::Update()
{
	__super::Update();

	if (m_fTrailAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fTrailAlpha -= 2.3f * GET_PLAYER_DT;
}

void CSakura_Trail::LateUpdate()
{
	__super::LateUpdate();

}

void CSakura_Trail::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gTrailAlpha", m_fTrailAlpha);
	pEffect->SetFloat("gEmissionPow", 0.2f);

	pEffect->CommitChanges();
}

void CSakura_Trail::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CSakura_Trail::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CSakura_Trail::OnDestroy()
{
	__super::OnDestroy();
}

void CSakura_Trail::OnEnable()
{
	__super::OnEnable();
}

void CSakura_Trail::OnDisable()
{
	__super::OnDisable();
}

void CSakura_Trail::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
