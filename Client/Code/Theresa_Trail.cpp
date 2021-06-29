#include "stdafx.h"
#include "..\Header\Theresa_Trail.h"

_uint CTheresa_Trail::m_s_uniqueID = 0;

CTheresa_Trail::CTheresa_Trail()
{
}


CTheresa_Trail::~CTheresa_Trail()
{
}

SP(CTheresa_Trail) CTheresa_Trail::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_Trail) spInstance(new CTheresa_Trail, Engine::SmartDeleter<CTheresa_Trail>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Trail::MakeClone()
{
	SP(CTheresa_Trail) spClone(new CTheresa_Trail, Engine::SmartDeleter<CTheresa_Trail>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_Trail::Awake()
{
	__super::Awake();

}

void CTheresa_Trail::Start()
{
	__super::Start();

}

void CTheresa_Trail::FixedUpdate()
{
	__super::FixedUpdate();

}

void CTheresa_Trail::Update()
{
	__super::Update();

	if (m_fTrailAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fTrailAlpha -= 2.3f * GET_DT;
}

void CTheresa_Trail::LateUpdate()
{
	__super::LateUpdate();

}

void CTheresa_Trail::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gTrailAlpha", m_fTrailAlpha);
}

void CTheresa_Trail::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Trail::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_Trail::OnDestroy()
{
	__super::OnDestroy();
}

void CTheresa_Trail::OnEnable()
{
	__super::OnEnable();
}

void CTheresa_Trail::OnDisable()
{
	__super::OnDisable();
}

void CTheresa_Trail::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
