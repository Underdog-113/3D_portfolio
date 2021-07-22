#include "stdafx.h"
#include "..\Header\Lancer_Att_Range.h"

_uint CLancer_Att_Range::m_s_uniqueID = 0;

CLancer_Att_Range::CLancer_Att_Range()
{
}


CLancer_Att_Range::~CLancer_Att_Range()
{
}

SP(CLancer_Att_Range) CLancer_Att_Range::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CLancer_Att_Range) spInstance(new CLancer_Att_Range, Engine::SmartDeleter<CLancer_Att_Range>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CLancer_Att_Range::MakeClone()
{
	SP(CLancer_Att_Range) spClone(new CLancer_Att_Range, Engine::SmartDeleter<CLancer_Att_Range>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CLancer_Att_Range::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Lancer_Att_Range");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Sign");
	m_spTexture->AddTexture(L"Sign");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CLancer_Att_Range::Start()
{
	__super::Start();
	m_fAlpha = 0.3f;

	m_pAttackRange_Circle_Diffuse
		= std::dynamic_pointer_cast<CDecoObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"DecoObject", true, (_int)Engine::ELayerID::Effect, L"AttackRange1"));

	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetMeshData(L"AttackRange_Circle");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackHint_Fan");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetPosition(_float3(this->GetTransform()->GetPosition().x, this->GetTransform()->GetPosition().y, this->GetTransform()->GetPosition().z));
}

void CLancer_Att_Range::FixedUpdate()
{
	__super::FixedUpdate();

}

void CLancer_Att_Range::Update()
{
	__super::Update();

}

void CLancer_Att_Range::LateUpdate()
{
	__super::LateUpdate();

}

void CLancer_Att_Range::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CLancer_Att_Range::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CLancer_Att_Range::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CLancer_Att_Range::OnDestroy()
{
	__super::OnDestroy();

}

void CLancer_Att_Range::OnEnable()
{
	__super::OnEnable();

}

void CLancer_Att_Range::OnDisable()
{
	__super::OnDisable();

}

void CLancer_Att_Range::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
