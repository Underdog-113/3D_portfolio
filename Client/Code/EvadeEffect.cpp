#include "stdafx.h"
#include "..\Header\EvadeEffect.h"


_uint CEvadeEffect::m_s_uniqueID = 0;


CEvadeEffect::CEvadeEffect()
{
}


CEvadeEffect::~CEvadeEffect()
{
}

SP(CEvadeEffect) CEvadeEffect::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CEvadeEffect) spInstance(new CEvadeEffect, Engine::SmartDeleter<CEvadeEffect>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CEvadeEffect::MakeClone()
{
	SP(CEvadeEffect) spClone(new CEvadeEffect, Engine::SmartDeleter<CEvadeEffect>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(_float3(1.f, 1.f, 1.f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CEvadeEffect::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Stage02_NonAlpha_Church01_2");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	m_spTexture->AddTexture(L"S02_Church");
	m_spTexture->AddTexture(L"Eff_Noise_08");
	m_spTexture->AddTexture(L"S02_Church_E");
	m_spShader->AddShader((_int)EShaderID::ReverseDissolveShader);
}

void CEvadeEffect::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CEvadeEffect::FixedUpdate()
{
	__super::FixedUpdate();

}

void CEvadeEffect::Update()
{
	__super::Update();
	
	if (Engine::IMKEY_PRESS(KEY_Q) && m_fAlpha <= 1.f)
	{
		m_fAlpha += 1.f * GET_DT;
	}
	if (Engine::IMKEY_PRESS(KEY_E) && m_fAlpha >= 0.f)
	{
		m_fAlpha -= 1.f * GET_DT;
	}

}

void CEvadeEffect::LateUpdate()
{
	__super::LateUpdate();

}

void CEvadeEffect::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);

	pEffect->CommitChanges();
}

void CEvadeEffect::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CEvadeEffect::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CEvadeEffect::OnDestroy()
{
	__super::OnDestroy();

}

void CEvadeEffect::OnEnable()
{
	__super::OnEnable();

}

void CEvadeEffect::OnDisable()
{
	__super::OnDisable();

}

void CEvadeEffect::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
