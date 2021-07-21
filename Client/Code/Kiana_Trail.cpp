#include "stdafx.h"
#include "..\Header\Kiana_Trail.h"

_uint CKiana_Trail::m_s_uniqueID = 0;

CKiana_Trail::CKiana_Trail()
{
}


CKiana_Trail::~CKiana_Trail()
{
}

SP(CKiana_Trail) CKiana_Trail::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_Trail) spInstance(new CKiana_Trail, Engine::SmartDeleter<CKiana_Trail>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Trail::MakeClone()
{
	SP(CKiana_Trail) spClone(new CKiana_Trail, Engine::SmartDeleter<CKiana_Trail>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CKiana_Trail::Awake()
{
	__super::Awake();
}

void CKiana_Trail::Start()
{
	__super::Start();
	m_fTrailAlpha = 1.f;
}

void CKiana_Trail::FixedUpdate()
{
	__super::FixedUpdate();
}

void CKiana_Trail::Update()
{
	__super::Update();

	if (m_fTrailAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fTrailAlpha -= 2.3f * GET_PLAYER_DT;

}

void CKiana_Trail::LateUpdate()
{
	__super::LateUpdate();
}

void CKiana_Trail::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

	pEffect->SetFloat("gTrailAlpha", m_fTrailAlpha);

	pEffect->CommitChanges();
}

void CKiana_Trail::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CKiana_Trail::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CKiana_Trail::OnDestroy()
{
	__super::OnDestroy();
}

void CKiana_Trail::OnEnable()
{
	__super::OnEnable();
}

void CKiana_Trail::OnDisable()
{
	__super::OnDisable();
}

void CKiana_Trail::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
