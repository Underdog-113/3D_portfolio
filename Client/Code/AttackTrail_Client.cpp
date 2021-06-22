#include "stdafx.h"
#include "..\Header\AttackTrail_Client.h"

_uint CAttackTrail_Client::m_s_uniqueID = 0;

CAttackTrail_Client::CAttackTrail_Client()
{
}


CAttackTrail_Client::~CAttackTrail_Client()
{
	OnDestroy();
}

SP(CAttackTrail_Client) CAttackTrail_Client::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CAttackTrail_Client) spInstance(new CAttackTrail_Client, Engine::SmartDeleter<CAttackTrail_Client>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CAttackTrail_Client::MakeClone()
{
	SP(CAttackTrail_Client) spClone(new CAttackTrail_Client, Engine::SmartDeleter<CAttackTrail_Client>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetPosition(_float3(0.f, 0.f, 0.f));
	spClone->m_spTransform->SetRotation(_float3(0.f, 0.f, 0.f));
	spClone->GetComponent<Engine::CTransformC>()->SetPositionZ(2.f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CAttackTrail_Client::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CAttackTrail_Client::Start()
{
	__super::Start();
	m_fTrailAlpha = 1.f;
}

void CAttackTrail_Client::FixedUpdate()
{
	__super::FixedUpdate();
}

void CAttackTrail_Client::Update()
{
	__super::Update();

	if (m_fTrailAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	if (Engine::IMKEY_DOWN(KEY_LEFT))
	{
		m_fTrailAlpha = 1.f;
	}

	//m_fTrailAlpha -= 2.3f * GET_DT;

	if (Engine::IMKEY_PRESS(KEY_CONTROL))
	{
		m_spTransform->AddRotationZ(D3DXToRadian(1.f));
	}
}

void CAttackTrail_Client::LateUpdate()
{
	__super::LateUpdate();
}

void CAttackTrail_Client::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}


void CAttackTrail_Client::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

	pEffect->SetFloat("gTrailAlpha", m_fTrailAlpha);
}


void CAttackTrail_Client::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CAttackTrail_Client::OnDestroy()
{
	__super::OnDestroy();
}

void CAttackTrail_Client::OnEnable()
{
	__super::OnEnable();
}

void CAttackTrail_Client::OnDisable()
{
	__super::OnDisable();
}

void CAttackTrail_Client::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
