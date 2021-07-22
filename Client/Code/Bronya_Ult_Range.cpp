#include "stdafx.h"
#include "..\Header\Bronya_Ult_Range.h"

_uint CBronya_Ult_Range::m_s_uniqueID = 0;

CBronya_Ult_Range::CBronya_Ult_Range()
{
}


CBronya_Ult_Range::~CBronya_Ult_Range()
{
	OnDestroy();
}

SP(CBronya_Ult_Range) CBronya_Ult_Range::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Range) spInstance(new CBronya_Ult_Range, Engine::SmartDeleter<CBronya_Ult_Range>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Range::MakeClone()
{
	SP(CBronya_Ult_Range) spClone(new CBronya_Ult_Range, Engine::SmartDeleter<CBronya_Ult_Range>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Ult_Range::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"AttackRange_Circle");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"FrameRed");
	m_spTexture->AddTexture(L"AttackHint_Circle_02");
	m_spShader->AddShader((_int)EShaderID::AttackRangeShader);
	m_spTransform->SetSize(_float3(0.2f, 0.2f, 0.2f));

}

void CBronya_Ult_Range::Start()
{
	__super::Start();

	m_spAttackRange_Circle_Diffuse
		= std::dynamic_pointer_cast<CDecoObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"DecoObject", true, (_int)Engine::ELayerID::Effect, L"AttackRange1"));

	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetMeshData(L"AttackRange_Circle");
	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackHint_Circle_02");
	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CTextureC>()->AddTexture(L"FrameRed");
	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AttackRangeShader);
	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetSize(_float3(0.f, 0.f, 0.f));
	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetPosition(_float3(this->GetTransform()->GetPosition().x, this->GetTransform()->GetPosition().y + 0.1f, this->GetTransform()->GetPosition().z));
	
}

void CBronya_Ult_Range::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Range::Update()
{
	__super::Update();

	// 원본의 객체는 호출한 곳에서 멤버로 만들어서 삭제

	if (m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->GetSize().x >=
		this->GetComponent<Engine::CTransformC>()->GetSize().x)
	{
		m_fSize = 0.f;
	}

	m_fSize += 0.5f * GET_DT;

	m_spAttackRange_Circle_Diffuse->GetComponent<Engine::CTransformC>()->SetSize(_float3(m_fSize, 0.f, m_fSize));
}

void CBronya_Ult_Range::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Ult_Range::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Range::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Ult_Range::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Range::OnDestroy()
{
	__super::OnDestroy();

	if (nullptr != m_spAttackRange_Circle_Diffuse)
		m_spAttackRange_Circle_Diffuse->SetDeleteThis(true);
}

void CBronya_Ult_Range::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Range::OnDisable()
{
	__super::OnDisable();

	m_spAttackRange_Circle_Diffuse->SetDeleteThis(true);
}

void CBronya_Ult_Range::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
