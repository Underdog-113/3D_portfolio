#include "stdafx.h"
#include "..\Header\AttackRange_Circle.h"
#include "DecoObject.h"

_uint CAttackRange_Circle::m_s_uniqueID = 0;

CAttackRange_Circle::CAttackRange_Circle()
{
}


CAttackRange_Circle::~CAttackRange_Circle()
{
	OnDestroy();
}

SP(CAttackRange_Circle) CAttackRange_Circle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CAttackRange_Circle) spInstance(new CAttackRange_Circle, Engine::SmartDeleter<CAttackRange_Circle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CAttackRange_Circle::MakeClone()
{
	SP(CAttackRange_Circle) spClone(new CAttackRange_Circle, Engine::SmartDeleter<CAttackRange_Circle>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CAttackRange_Circle::Awake()
{
	__super::Awake();

	m_spMesh->SetMeshData(L"AttackRange_Circle");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"AttackHint_Circle_02");
	m_spTexture->AddTexture(L"FrameRed");
	m_spShader->AddShader((_int)EShaderID::AttackRangeShader);
}

void CAttackRange_Circle::Start()
{
	__super::Start();

	m_fAlpha = 0.2f;

	m_pAttackRange_Circle_Diffuse
		= std::dynamic_pointer_cast<CDecoObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"DecoObject", true, (_int)Engine::ELayerID::Effect, L"AttackRange1"));

	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetMeshData(L"AttackRange_Circle");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackHint_Circle_02");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTextureC>()->AddTexture(L"FrameRed");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AttackRangeShader);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetSize(_float3(0.f, 0.f, 0.f));
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetPosition(_float3(this->GetTransform()->GetPosition().x, this->GetTransform()->GetPosition().y - 0.1f, this->GetTransform()->GetPosition().z));



}

void CAttackRange_Circle::FixedUpdate()
{
	__super::FixedUpdate();
}

void CAttackRange_Circle::Update()
{
	__super::Update();


	if (m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->GetSize().x >=
		this->GetComponent<Engine::CTransformC>()->GetSize().x)
	{
		m_pAttackRange_Circle_Diffuse->SetDeleteThis(true);
		SetDeleteThis(true);
	}

	m_fSize += 0.05f * GET_DT;

	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetSize(_float3(m_fSize, 0.f, m_fSize));

}

void CAttackRange_Circle::LateUpdate()
{
	__super::LateUpdate();
}
void CAttackRange_Circle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->CommitChanges();

}

void CAttackRange_Circle::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CAttackRange_Circle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CAttackRange_Circle::OnDestroy()
{
	__super::OnDestroy();
}

void CAttackRange_Circle::OnEnable()
{
	__super::OnEnable();
}

void CAttackRange_Circle::OnDisable()
{
	__super::OnDisable();
}

void CAttackRange_Circle::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
