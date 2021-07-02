#include "stdafx.h"
#include "..\Header\Sakura_Charge_Att.h"


CSakura_Charge_Att::CSakura_Charge_Att()
{
}


CSakura_Charge_Att::~CSakura_Charge_Att()
{
	OnDestroy();
}

SP(CSakura_Charge_Att) CSakura_Charge_Att::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_Charge_Att) spInstance(new CSakura_Charge_Att, Engine::SmartDeleter<CSakura_Charge_Att>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_Charge_Att::MakeClone()
{
	SP(CSakura_Charge_Att) spClone(new CSakura_Charge_Att, Engine::SmartDeleter<CSakura_Charge_Att>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CSakura_Charge_Att::Awake()
{
	__super::Awake();
}

void CSakura_Charge_Att::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CSakura_Charge_Att::FixedUpdate()
{
	__super::FixedUpdate();
}

void CSakura_Charge_Att::Update()
{
	__super::Update();

	if (m_spTransform->GetSize().x  <= 0.f || m_spTransform->GetSize().y <= 0.f)
	{
		this->SetDeleteThis(true);
	}
	m_spTransform->AddSizeX(-4.5f * GET_DT);
	m_spTransform->AddSizeY(-4.5f * GET_DT);
	m_spTransform->AddSizeZ(4.5f * GET_DT);
	//m_fAlpha += 8.f * GET_DT;

}

void CSakura_Charge_Att::LateUpdate()
{
	__super::LateUpdate();
}

void CSakura_Charge_Att::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gTrailAlpha", m_fAlpha);
}

void CSakura_Charge_Att::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CSakura_Charge_Att::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CSakura_Charge_Att::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 0.f;
}

void CSakura_Charge_Att::OnEnable()
{
	__super::OnEnable();
}

void CSakura_Charge_Att::OnDisable()
{
	__super::OnDisable();
}

void CSakura_Charge_Att::SetBasicName()
{
}
