#include "stdafx.h"
#include "..\Header\MoveUpSmoke.h"


CMoveUpSmoke::CMoveUpSmoke()
{
}


CMoveUpSmoke::~CMoveUpSmoke()
{
	OnDestroy();
}

SP(CMoveUpSmoke) CMoveUpSmoke::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMoveUpSmoke) spInstance(new CMoveUpSmoke, Engine::SmartDeleter<CMoveUpSmoke>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMoveUpSmoke::MakeClone()
{
	SP(CMoveUpSmoke) spClone(new CMoveUpSmoke, Engine::SmartDeleter<CMoveUpSmoke>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CMoveUpSmoke::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Charge_Att_Smoke");
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"fx_snowfield_fog03");
	m_spTexture->AddTexture(L"fx_snowfield_fog03");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CMoveUpSmoke::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
}

void CMoveUpSmoke::FixedUpdate()
{
	__super::FixedUpdate();
}

void CMoveUpSmoke::Update()
{
	__super::Update();

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}
	m_spTransform->AddSizeX(0.1f * GET_PLAYER_DT);
	m_spTransform->AddSizeY(0.1f * GET_PLAYER_DT);
	m_fAlpha -= 0.5f * GET_PLAYER_DT;
	m_fUVSpeed += GET_PLAYER_DT * 0.5f;
}

void CMoveUpSmoke::LateUpdate()
{
	__super::LateUpdate();
}

void CMoveUpSmoke::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);
	pEffect->SetFloat("gEmissionPow", 1.f);
	pEffect->SetBool("gPlayingAnim", true);
	pEffect->CommitChanges();
}

void CMoveUpSmoke::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMoveUpSmoke::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMoveUpSmoke::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CMoveUpSmoke::OnEnable()
{
	__super::OnEnable();
}

void CMoveUpSmoke::OnDisable()
{
	__super::OnDisable();
}

void CMoveUpSmoke::SetBasicName()
{
}
