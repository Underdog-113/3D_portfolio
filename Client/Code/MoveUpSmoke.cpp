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
	m_spTransform->SetRotationZ(D3DXToRadian(-90.f));
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

	m_fAlpha -= 0.5f * GET_DT;
	m_fUVSpeed += GET_DT;
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
	pEffect->SetBool("gPlayingAnim", true);
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
