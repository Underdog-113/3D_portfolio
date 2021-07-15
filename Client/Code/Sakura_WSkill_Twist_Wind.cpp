#include "stdafx.h"
#include "..\Header\Sakura_WSkill_Twist_Wind.h"

_uint CSakura_WSkill_Twist_Wind::m_s_uniqueID = 0;

CSakura_WSkill_Twist_Wind::CSakura_WSkill_Twist_Wind()
{
}


CSakura_WSkill_Twist_Wind::~CSakura_WSkill_Twist_Wind()
{
}

SP(CSakura_WSkill_Twist_Wind) CSakura_WSkill_Twist_Wind::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_WSkill_Twist_Wind) spInstance(new CSakura_WSkill_Twist_Wind, Engine::SmartDeleter<CSakura_WSkill_Twist_Wind>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_WSkill_Twist_Wind::MakeClone()
{
	SP(CSakura_WSkill_Twist_Wind) spClone(new CSakura_WSkill_Twist_Wind, Engine::SmartDeleter<CSakura_WSkill_Twist_Wind>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSakura_WSkill_Twist_Wind::Awake()
{
	__super::Awake();
	//m_spTransform->SetSizeX(0.7f);
	//m_spTransform->SetSizeZ(0.7f);
}

void CSakura_WSkill_Twist_Wind::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
}

void CSakura_WSkill_Twist_Wind::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_WSkill_Twist_Wind::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fUVSpeed += 0.25f * GET_DT;
	m_spTransform->AddRotationY(20.f * GET_DT);
	m_spTransform->SetPosition(m_spTransform->GetOwner()->GetTransform()->GetPosition());
	m_spTransform->SetSize(m_spTransform->GetOwner()->GetTransform()->GetSize());
}

void CSakura_WSkill_Twist_Wind::LateUpdate()
{
	__super::LateUpdate();
}

void CSakura_WSkill_Twist_Wind::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", -m_fUVSpeed);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->CommitChanges();
}

void CSakura_WSkill_Twist_Wind::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSakura_WSkill_Twist_Wind::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSakura_WSkill_Twist_Wind::OnDestroy()
{
	__super::OnDestroy();

}

void CSakura_WSkill_Twist_Wind::OnEnable()
{
	__super::OnEnable();

}

void CSakura_WSkill_Twist_Wind::OnDisable()
{
	__super::OnDisable();

}

void CSakura_WSkill_Twist_Wind::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
