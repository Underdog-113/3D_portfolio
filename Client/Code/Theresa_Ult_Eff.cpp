#include "stdafx.h"
#include "..\Header\Theresa_Ult_Eff.h"


CTheresa_Ult_Eff::CTheresa_Ult_Eff()
{
}


CTheresa_Ult_Eff::~CTheresa_Ult_Eff()
{
	OnDestroy();
}

SP(CTheresa_Ult_Eff) CTheresa_Ult_Eff::Create(_bool isStatic, Engine::CScene* pScene)
{
	SP(CTheresa_Ult_Eff) spInstance(new CTheresa_Ult_Eff, Engine::SmartDeleter<CTheresa_Ult_Eff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_Eff::MakeClone()
{
	SP(CTheresa_Ult_Eff) spClone(new CTheresa_Ult_Eff, Engine::SmartDeleter<CTheresa_Ult_Eff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CTheresa_Ult_Eff::Awake()
{
	__super::Awake();
}

void CTheresa_Ult_Eff::Start()
{
	__super::Start();

	m_spTheresaUltCharge
		= std::dynamic_pointer_cast<CMeshEffect_Client>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Theresa_Ult_Charge", true, (_int)Engine::ELayerID::Effect));

	m_spTheresaUltCharge->GetComponent<Engine::CMeshC>()->SetMeshData(L"Charge");
	m_spTheresaUltCharge->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTheresaUltCharge->GetComponent<Engine::CTextureC>()->AddTexture(L"Charge");
	m_spTheresaUltCharge->GetComponent<Engine::CTextureC>()->AddTexture(L"Charge");
	m_spTheresaUltCharge->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	m_spTheresaUltCharge->GetComponent<Engine::CTransformC>()->SetPosition(_float3(this->GetTransform()->GetPosition().x, 0.f, this->GetTransform()->GetPosition().z));


	m_spTheresaUltSmoke
		= std::dynamic_pointer_cast<CMeshEffect_Client>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Theresa_Ult_Smoke", true, (_int)Engine::ELayerID::Effect));

	m_spTheresaUltSmoke->GetComponent<Engine::CMeshC>()->SetMeshData(L"Smoke");
	m_spTheresaUltSmoke->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTheresaUltSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"smoke");
	m_spTheresaUltSmoke->GetComponent<Engine::CTextureC>()->AddTexture(L"smoke");
	m_spTheresaUltSmoke->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	m_spTheresaUltSmoke->GetComponent<Engine::CTransformC>()->SetPosition(_float3(this->GetTransform()->GetPosition().x, 0.f, this->GetTransform()->GetPosition().z));
}

void CTheresa_Ult_Eff::FixedUpdate()
{
	__super::FixedUpdate();

}

void CTheresa_Ult_Eff::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		if (m_spTheresaUltCharge != nullptr)
			m_spTheresaUltCharge->SetDeleteThis(true);

		if (m_spTheresaUltSmoke != nullptr)
			m_spTheresaUltSmoke->SetDeleteThis(true);

		/*if (m_spKianaUltPlane != nullptr)
			m_spKianaUltPlane->SetDeleteThis(true);*/

		this->SetDeleteThis(true);
	}

	m_fAlpha -= 0.5f * GET_PLAYER_DT;

}

void CTheresa_Ult_Eff::LateUpdate()
{
	__super::LateUpdate();

}

void CTheresa_Ult_Eff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	
}

void CTheresa_Ult_Eff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_Ult_Eff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_Ult_Eff::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CTheresa_Ult_Eff::OnEnable()
{
	__super::OnEnable();
}

void CTheresa_Ult_Eff::OnDisable()
{
	__super::OnDisable();
}

void CTheresa_Ult_Eff::SetBasicName()
{
}
