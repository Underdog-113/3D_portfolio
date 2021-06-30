#include "stdafx.h"
#include "..\Header\Theresa_Ult_Boom.h"

_uint CTheresa_Ult_Boom::m_s_uniqueID = 0;

CTheresa_Ult_Boom::CTheresa_Ult_Boom()
{
}


CTheresa_Ult_Boom::~CTheresa_Ult_Boom()
{
}

SP(CTheresa_Ult_Boom) CTheresa_Ult_Boom::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_Ult_Boom) spInstance(new CTheresa_Ult_Boom, Engine::SmartDeleter<CTheresa_Ult_Boom>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_Boom::MakeClone()
{
	SP(CTheresa_Ult_Boom) spClone(new CTheresa_Ult_Boom, Engine::SmartDeleter<CTheresa_Ult_Boom>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	m_spTransform->SetSizeY(0.f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_Ult_Boom::Awake()
{
	__super::Awake();

}

void CTheresa_Ult_Boom::Start()
{
	__super::Start();

	SP(Engine::CObject) spFireEffect
		= Engine::GET_CUR_SCENE->ADD_CLONE(L"Theresa_Ult_Fire", true, (_int)Engine::ELayerID::Effect, L"MeshEffect0");
	spFireEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ult_Fire");
	spFireEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spFireEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Sword_map");
	spFireEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Ult_Fire");
	spFireEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::FireShader);
	spFireEffect->GetComponent<Engine::CTransformC>()->SetPosition(this->GetTransform()->GetPosition());

	SP(Engine::CObject) spCrackEffect
		= Engine::GET_CUR_SCENE->ADD_CLONE(L"Theresa_Ult_Crack", true, (_int)Engine::ELayerID::Effect, L"MeshEffect0");
	spCrackEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ult_Crack");
	spCrackEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spCrackEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Sword_map");
	spCrackEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Groundcracks_04");
	spCrackEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	spCrackEffect->GetComponent<Engine::CTransformC>()->SetPosition(this->GetTransform()->GetPosition());
	spCrackEffect->GetComponent<Engine::CTransformC>()->SetSizeX(2.f);
	spCrackEffect->GetComponent<Engine::CTransformC>()->SetSizeZ(2.f);

	SP(Engine::CObject) spSmokeEffect
		= Engine::GET_CUR_SCENE->ADD_CLONE(L"Theresa_Ult_Smoke", true, (_int)Engine::ELayerID::Effect, L"MeshEffect0");
	spSmokeEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ult_Smoke");
	spSmokeEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spSmokeEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog03");
	spSmokeEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog03");
	spSmokeEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	spSmokeEffect->GetComponent<Engine::CTransformC>()->SetPosition(this->GetTransform()->GetPosition());
	spSmokeEffect->GetComponent<Engine::CTransformC>()->SetPositionY(0.1f);
	spSmokeEffect->GetComponent<Engine::CTransformC>()->SetSizeX(0.3f);
	spSmokeEffect->GetComponent<Engine::CTransformC>()->SetSizeY(0.f);
	spSmokeEffect->GetComponent<Engine::CTransformC>()->SetSizeZ(0.3f);



	m_fAlpha = 1.f;
}

void CTheresa_Ult_Boom::FixedUpdate()
{
	__super::FixedUpdate();
}

void CTheresa_Ult_Boom::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_spTransform->AddSizeX(0.5f * GET_DT);
	m_spTransform->AddSizeY(0.5f * GET_DT);
	m_spTransform->AddSizeZ(0.5f * GET_DT);

	m_fAlpha -= 1.5f * GET_DT;
}

void CTheresa_Ult_Boom::LateUpdate()
{
	__super::LateUpdate();
}

void CTheresa_Ult_Boom::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);

}

void CTheresa_Ult_Boom::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Ult_Boom::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CTheresa_Ult_Boom::OnDestroy()
{
	__super::OnDestroy();

}

void CTheresa_Ult_Boom::OnEnable()
{
	__super::OnEnable();

}

void CTheresa_Ult_Boom::OnDisable()
{
	__super::OnDisable();

}

void CTheresa_Ult_Boom::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
