#include "stdafx.h"
#include "..\Header\Kiana_Ult_Eff.h"


CKiana_Ult_Eff::CKiana_Ult_Eff()
{
}


CKiana_Ult_Eff::~CKiana_Ult_Eff()
{
	OnDestroy();
}

SP(CKiana_Ult_Eff) CKiana_Ult_Eff::Create(_bool isStatic ,Engine::CScene* pScene)
{
	SP(CKiana_Ult_Eff) spInstance(new CKiana_Ult_Eff, Engine::SmartDeleter<CKiana_Ult_Eff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_Ult_Eff::MakeClone()
{
	SP(CKiana_Ult_Eff) spClone(new CKiana_Ult_Eff, Engine::SmartDeleter<CKiana_Ult_Eff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetPosition(_float3(0.f, 0.f, 0.f));
	spClone->m_spTransform->SetRotation(_float3(0.f, 0.f, 0.f));
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;

}

void CKiana_Ult_Eff::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CKiana_Ult_Eff::Start()
{
	__super::Start();
	
	m_spKianaUltRing
		= std::dynamic_pointer_cast<CMeshEffect_Client>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Kiana_Ult_Ring", true, (_int)Engine::ELayerID::Effect));

	m_spKianaUltRing->GetComponent<Engine::CMeshC>()->SetMeshData(L"Burst_Ring");
	m_spKianaUltRing->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	m_spKianaUltRing->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spKianaUltRing->GetComponent<Engine::CTextureC>()->AddTexture(L"burst_ring");
	m_spKianaUltRing->GetComponent<Engine::CTextureC>()->AddTexture(L"burst_ring");
	m_spKianaUltRing->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);


	m_spKianaUltPlane
		= std::dynamic_pointer_cast<CMeshEffect_Client>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Kiana_Ult_Plane", true, (_int)Engine::ELayerID::Effect));

	m_spKianaUltPlane->GetComponent<Engine::CMeshC>()->SetMeshData(L"DissolvePlane");
	m_spKianaUltPlane->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	m_spKianaUltPlane->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spKianaUltPlane->GetComponent<Engine::CTextureC>()->AddTexture(L"ExplosionWarning");
	m_spKianaUltPlane->GetComponent<Engine::CTextureC>()->AddTexture(L"Eff_Noise");
	m_spKianaUltPlane->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::DissolveShader);
	

	m_spKianaUltShield
		= std::dynamic_pointer_cast<CMeshEffect_Client>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Kiana_Ult_Shield", true, (_int)Engine::ELayerID::Effect));

	m_spKianaUltShield->GetComponent<Engine::CMeshC>()->SetMeshData(L"BurstShield");
	m_spKianaUltShield->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	m_spKianaUltShield->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spKianaUltShield->GetComponent<Engine::CTextureC>()->AddTexture(L"ExplosionWarning");
	m_spKianaUltShield->GetComponent<Engine::CTextureC>()->AddTexture(L"ExplosionWarning");
	m_spKianaUltShield->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	
}

void CKiana_Ult_Eff::FixedUpdate()
{
	__super::FixedUpdate();
}

void CKiana_Ult_Eff::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		if (m_spKianaUltShield != nullptr)
			m_spKianaUltShield->SetDeleteThis(true);

		if (m_spKianaUltRing != nullptr)
			m_spKianaUltRing->SetDeleteThis(true);

		if (m_spKianaUltPlane != nullptr)
			m_spKianaUltPlane->SetDeleteThis(true);

		this->SetDeleteThis(true);
	}

	m_spTransform->AddRotationY(1.f * GET_DT);
	m_fAlpha -= 0.3f * GET_DT;

}

void CKiana_Ult_Eff::LateUpdate()
{
	__super::LateUpdate();
}

void CKiana_Ult_Eff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CKiana_Ult_Eff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_Ult_Eff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CKiana_Ult_Eff::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CKiana_Ult_Eff::OnEnable()
{
	__super::OnEnable();

}

void CKiana_Ult_Eff::OnDisable()
{
	__super::OnDisable();
}

void CKiana_Ult_Eff::SetBasicName()
{
}