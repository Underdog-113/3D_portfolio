#include "stdafx.h"
#include "..\Header\Stage_Wall_barrier.h"

_uint CStage_Wall_barrier::m_s_uniqueID = 0;

// 벽에 닿은 플레이어의 방향에 생성

CStage_Wall_barrier::CStage_Wall_barrier()
{
}


CStage_Wall_barrier::~CStage_Wall_barrier()
{
}

SP(CStage_Wall_barrier) CStage_Wall_barrier::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CStage_Wall_barrier) spInstance(new CStage_Wall_barrier, Engine::SmartDeleter<CStage_Wall_barrier>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CStage_Wall_barrier::MakeClone()
{
	SP(CStage_Wall_barrier) spClone(new CStage_Wall_barrier, Engine::SmartDeleter<CStage_Wall_barrier>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CStage_Wall_barrier::Awake()
{
	__super::Awake();
	_float _size = 0.1f;
	m_spTransform->SetSize(_float3(_size, _size, _size));
	m_spMesh->SetMeshData(L"Wall_barrier");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Scene barrier");
	m_spTexture->AddTexture(L"Scene barrier");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);

}

void CStage_Wall_barrier::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CStage_Wall_barrier::FixedUpdate()
{
	__super::FixedUpdate();

}

void CStage_Wall_barrier::Update()
{
	__super::Update();
}

void CStage_Wall_barrier::LateUpdate()
{
	__super::LateUpdate();

}

void CStage_Wall_barrier::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->CommitChanges();
}

void CStage_Wall_barrier::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CStage_Wall_barrier::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CStage_Wall_barrier::OnDestroy()
{
	__super::OnDestroy();

}

void CStage_Wall_barrier::OnEnable()
{
	__super::OnEnable();

}

void CStage_Wall_barrier::OnDisable()
{
	__super::OnDisable();

}

void CStage_Wall_barrier::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
