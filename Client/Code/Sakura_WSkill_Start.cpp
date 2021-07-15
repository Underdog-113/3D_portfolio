#include "stdafx.h"
#include "..\Header\Sakura_WSkill_Start.h"

_uint CSakura_WSkill_Start::m_s_uniqueID = 0;

CSakura_WSkill_Start::CSakura_WSkill_Start()
{
}


CSakura_WSkill_Start::~CSakura_WSkill_Start()
{
}

SP(CSakura_WSkill_Start) CSakura_WSkill_Start::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_WSkill_Start) spInstance(new CSakura_WSkill_Start, Engine::SmartDeleter<CSakura_WSkill_Start>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_WSkill_Start::MakeClone()
{
	SP(CSakura_WSkill_Start) spClone(new CSakura_WSkill_Start, Engine::SmartDeleter<CSakura_WSkill_Start>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSakura_WSkill_Start::Awake()
{
	__super::Awake();

}

void CSakura_WSkill_Start::Start()
{
	__super::Start();

	m_fAlpha = 1.f;
}

void CSakura_WSkill_Start::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_WSkill_Start::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_spTransform->AddSizeX(0.7f * GET_DT);
	m_spTransform->AddSizeY(0.5f * GET_DT);
	m_spTransform->AddSizeZ(0.7f * GET_DT);
	m_spTransform->AddRotationY(-10.f * GET_DT);

	m_fAlpha -= 2.5f * GET_DT;


}

void CSakura_WSkill_Start::LateUpdate()
{
	__super::LateUpdate();

}

void CSakura_WSkill_Start::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->CommitChanges();
}

void CSakura_WSkill_Start::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSakura_WSkill_Start::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSakura_WSkill_Start::OnDestroy()
{
	__super::OnDestroy();

}

void CSakura_WSkill_Start::OnEnable()
{
	__super::OnEnable();

}

void CSakura_WSkill_Start::OnDisable()
{
	__super::OnDisable();

}

void CSakura_WSkill_Start::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
