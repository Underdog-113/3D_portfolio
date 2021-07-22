#include "stdafx.h"
#include "..\Header\MonsterSpawnEff.h"


CMonsterSpawnEff::CMonsterSpawnEff()
{
}


CMonsterSpawnEff::~CMonsterSpawnEff()
{
}

SP(CMonsterSpawnEff) CMonsterSpawnEff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMonsterSpawnEff) spInstance(new CMonsterSpawnEff, Engine::SmartDeleter<CMonsterSpawnEff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMonsterSpawnEff::MakeClone()
{
	SP(CMonsterSpawnEff) spClone(new CMonsterSpawnEff, Engine::SmartDeleter<CMonsterSpawnEff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CMonsterSpawnEff::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"SpawnEff");
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Ability_aura");
	m_spTexture->AddTexture(L"Ability_aura");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
	m_spTransform->SetSize(_float3(0.05f, 0.05f, 0.05f));		
}

void CMonsterSpawnEff::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CMonsterSpawnEff::FixedUpdate()
{
	__super::FixedUpdate();

}

void CMonsterSpawnEff::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}
	m_spTransform->AddRotationY(30.f * GET_DT);

	m_fAlpha -= 1.f * GET_DT;
}

void CMonsterSpawnEff::LateUpdate()
{
	__super::LateUpdate();

}

void CMonsterSpawnEff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gTrailAlpha", m_fAlpha);
}

void CMonsterSpawnEff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CMonsterSpawnEff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CMonsterSpawnEff::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 0.f;
}

void CMonsterSpawnEff::OnEnable()
{
	__super::OnEnable();

}

void CMonsterSpawnEff::OnDisable()
{
	__super::OnDisable();

}

void CMonsterSpawnEff::SetBasicName()
{
}
