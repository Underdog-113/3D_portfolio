#include "stdafx.h"
#include "..\Header\TheresaCharge_Att.h"


CTheresaCharge_Att::CTheresaCharge_Att()
{
}


CTheresaCharge_Att::~CTheresaCharge_Att()
{
	OnDestroy();
}

SP(CTheresaCharge_Att) CTheresaCharge_Att::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresaCharge_Att) spInstance(new CTheresaCharge_Att, Engine::SmartDeleter<CTheresaCharge_Att>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresaCharge_Att::MakeClone()
{
	SP(CTheresaCharge_Att) spClone(new CTheresaCharge_Att, Engine::SmartDeleter<CTheresaCharge_Att>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CTheresaCharge_Att::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Charge_Fire");
	m_spMesh->SetIsEffectMesh(true);
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spTexture->AddTexture(L"Fire_Alpha");
	m_spTexture->AddTexture(L"Grenade_Explosion");
	m_spShader->AddShader((_int)EShaderID::FireShader);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTransform->SetSize(_float3(0.05f, 0.05f, 0.05f));

}

void CTheresaCharge_Att::Start()
{
	__super::Start();
	m_spTransform->SetRotationY(m_spTransform->GetOwner()->GetTransform()->GetRotation().y);
	m_spTransform->AddRotationY(D3DXToRadian(-90));
	m_spTransform->AddPosition(m_spTransform->GetRight() * 1.f);

	m_spTheresaSmoke
		= std::dynamic_pointer_cast<CMeshEffect_Client>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MoveUpSmoke", true, (_int)Engine::ELayerID::Effect));	
	m_spTheresaSmoke->GetComponent<Engine::CTransformC>()->SetPosition(m_spTransform->GetOwner()->GetTransform()->GetPosition());
	m_spTheresaSmoke->GetComponent<Engine::CTransformC>()->SetRotationY(m_spTransform->GetOwner()->GetTransform()->GetRotation().y);
	m_fUVSpeed = 0.f;
	m_fAlpha = 1.f;

}

void CTheresaCharge_Att::FixedUpdate()
{
	__super::FixedUpdate();
}

void CTheresaCharge_Att::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		if (m_spTheresaSmoke != nullptr)
			m_spTheresaSmoke->SetDeleteThis(true);

		this->SetDeleteThis(true);
	}

	m_spTransform->AddSizeX(0.01f * GET_PLAYER_DT);
	m_spTransform->AddSizeY(0.01f * GET_PLAYER_DT);
	m_fAlpha -= 0.8f * GET_PLAYER_DT;
	m_fUVSpeed += GET_PLAYER_DT;
}

void CTheresaCharge_Att::LateUpdate()
{
	__super::LateUpdate();
}

void CTheresaCharge_Att::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);
	pEffect->CommitChanges();
}

void CTheresaCharge_Att::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresaCharge_Att::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresaCharge_Att::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CTheresaCharge_Att::OnEnable()
{
	__super::OnEnable();
}

void CTheresaCharge_Att::OnDisable()
{
	__super::OnDisable();
}

void CTheresaCharge_Att::SetBasicName()
{
}
