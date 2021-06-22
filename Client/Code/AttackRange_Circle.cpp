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
	spClone->m_spTransform->SetRotation(_float3(0.f, 0.f, 0.f));

	return spClone;
}

void CAttackRange_Circle::Awake()
{
	__super::Awake();
}

void CAttackRange_Circle::Start()
{
	__super::Start();

	m_pAttackRange_Circle_Diffuse
		= std::dynamic_pointer_cast<CDecoObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"DecoObject", true, (_int)Engine::ELayerID::Effect, L"AttackRange1"));

	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetMeshData(L"AttackRange_Circle");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetisEffectMesh(true);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTextureC>()->AddTexture(L"FrameRed");
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AttackRangeShader);
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetSize(_float3(0.f, 0.f, 0.f));
	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetPositionY(0.1f);
	m_pAttackRange_Circle_Diffuse->SetParent(this);
	
	m_pAttackRange_Circle_Alpha	= 
		std::dynamic_pointer_cast<CDecoObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"DecoObject", true, (_int)Engine::ELayerID::Effect, L"AttackRange"));

	m_pAttackRange_Circle_Alpha->GetComponent<Engine::CMeshC>()->SetMeshData(L"AttackRange_Circle");
	m_pAttackRange_Circle_Alpha->GetComponent<Engine::CMeshC>()->SetisEffectMesh(true);
	m_pAttackRange_Circle_Alpha->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_pAttackRange_Circle_Alpha->GetComponent<Engine::CTextureC>()->AddTexture(L"FrameRed");
	m_pAttackRange_Circle_Alpha->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackHint_Circle_02");
	m_pAttackRange_Circle_Alpha->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AttackRangeShader);
	m_pAttackRange_Circle_Alpha->GetComponent<Engine::CTransformC>()->SetSize(_float3(1.f, 1.f, 1.f));
	m_pAttackRange_Circle_Alpha->SetParent(this);


}

void CAttackRange_Circle::FixedUpdate()
{
	__super::FixedUpdate();
}

void CAttackRange_Circle::Update()
{
	__super::Update();


	if (m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->GetSize().x >=
		m_pAttackRange_Circle_Alpha->GetComponent<Engine::CTransformC>()->GetSize().x)
	{
		m_pAttackRange_Circle_Alpha->SetDeleteThis(true);
		m_pAttackRange_Circle_Diffuse->SetDeleteThis(true);
		SetDeleteThis(true);
	}

	m_fSize += 0.5f * GET_DT;

	m_pAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetSize(_float3(m_fSize, 0.f, m_fSize));

}

void CAttackRange_Circle::LateUpdate()
{
	__super::LateUpdate();
}
void CAttackRange_Circle::PreRender(LPD3DXEFFECT pEffect)
{
	return;
}

void CAttackRange_Circle::Render(LPD3DXEFFECT pEffect)
{
	return;
}

void CAttackRange_Circle::PostRender(LPD3DXEFFECT pEffect)
{
	return;
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
