#include "stdafx.h"
#include "..\Header\Sickle_Trail.h"

_uint CSickle_Trail::m_s_uniqueID = 0;

CSickle_Trail::CSickle_Trail()
{
}


CSickle_Trail::~CSickle_Trail()
{
}

SP(CSickle_Trail) CSickle_Trail::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSickle_Trail) spInstance(new CSickle_Trail, Engine::SmartDeleter<CSickle_Trail>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSickle_Trail::MakeClone()
{
	SP(CSickle_Trail) spClone(new CSickle_Trail, Engine::SmartDeleter<CSickle_Trail>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSickle_Trail::Awake()
{
	__super::Awake();

}

void CSickle_Trail::Start()
{
	__super::Start();
	m_fTrailAlpha = 1.f;
}

void CSickle_Trail::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSickle_Trail::Update()
{
	__super::Update();

	if (m_fTrailAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fTrailAlpha -= 2.3f * GET_DT;
}

void CSickle_Trail::LateUpdate()
{
	__super::LateUpdate();
}

void CSickle_Trail::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gTrailAlpha", m_fTrailAlpha);
}

void CSickle_Trail::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSickle_Trail::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSickle_Trail::OnDestroy()
{
	__super::OnDestroy();

}

void CSickle_Trail::OnEnable()
{
	__super::OnEnable();

}

void CSickle_Trail::OnDisable()
{
	__super::OnDisable();

}

void CSickle_Trail::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
