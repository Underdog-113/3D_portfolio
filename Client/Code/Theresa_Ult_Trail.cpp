#include "stdafx.h"
#include "..\Header\Theresa_Ult_Trail.h"

_uint CTheresa_Ult_Trail::m_s_uniqueID = 0;

CTheresa_Ult_Trail::CTheresa_Ult_Trail()
{
}


CTheresa_Ult_Trail::~CTheresa_Ult_Trail()
{
}

SP(CTheresa_Ult_Trail) CTheresa_Ult_Trail::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_Ult_Trail) spInstance(new CTheresa_Ult_Trail, Engine::SmartDeleter<CTheresa_Ult_Trail>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_Trail::MakeClone()
{
	SP(CTheresa_Ult_Trail) spClone(new CTheresa_Ult_Trail, Engine::SmartDeleter<CTheresa_Ult_Trail>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_Ult_Trail::Awake()
{
	__super::Awake();
}

void CTheresa_Ult_Trail::Start()
{
	__super::Start();
	m_bChangeAlpha = false;
	m_fTrailAlpha = 0.f;
}

void CTheresa_Ult_Trail::FixedUpdate()
{
	__super::FixedUpdate();
}

void CTheresa_Ult_Trail::Update()
{
	__super::Update();

	if (m_fTrailAlpha < 0)
	{
		SetDeleteThis(true);
	}

	if (m_bChangeAlpha)
	{
		m_fTrailAlpha -= 1.f * GET_DT;
	}
	else
		m_fTrailAlpha += 0.4f * GET_DT;
}

void CTheresa_Ult_Trail::LateUpdate()
{
	__super::LateUpdate();

	if (m_fTrailAlpha >= 0.4f)
		m_bChangeAlpha = true;

}

void CTheresa_Ult_Trail::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

	pEffect->SetFloat("gAlpha", m_fTrailAlpha);
	pEffect->SetBool("gTrailCheck", m_bChangeAlpha);

}

void CTheresa_Ult_Trail::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Ult_Trail::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_Ult_Trail::OnDestroy()
{
	__super::OnDestroy();
	m_bChangeAlpha = false;
}

void CTheresa_Ult_Trail::OnEnable()
{
	__super::OnEnable();
}

void CTheresa_Ult_Trail::OnDisable()
{
	__super::OnDisable();
}

void CTheresa_Ult_Trail::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
