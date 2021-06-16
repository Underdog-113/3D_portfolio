#include "stdafx.h"
#include "..\Header\AttackTrail.h"

_uint CAttackTrail::m_s_uniqueID = 0;

CAttackTrail::CAttackTrail()
{
}


CAttackTrail::~CAttackTrail()
{
	OnDestroy();
}

SP(CAttackTrail) CAttackTrail::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CAttackTrail) spInstance(new CAttackTrail, Engine::SmartDeleter<CAttackTrail>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CAttackTrail::MakeClone()
{
	SP(CAttackTrail) spClone(new CAttackTrail, Engine::SmartDeleter<CAttackTrail>);
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

void CAttackTrail::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CAttackTrail::Start()
{
	__super::Start();
	m_fTrailAlpha = 1.f;
}

void CAttackTrail::FixedUpdate()
{
	__super::FixedUpdate();
}

void CAttackTrail::Update()
{
	__super::Update();

	if (m_fTrailAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fTrailAlpha -= 1.f * GET_DT;

}

void CAttackTrail::LateUpdate()
{
	__super::LateUpdate();
}

void CAttackTrail::PreRender()
{
	m_spMesh->PreRender(m_spGraphics);
}

void CAttackTrail::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

}

void CAttackTrail::Render()
{

	m_spMesh->Render(m_spGraphics);
}

void CAttackTrail::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

	pEffect->SetFloat("gTrailAlpha", m_fTrailAlpha);
}

void CAttackTrail::PostRender()
{
	m_spMesh->PostRender(m_spGraphics);
}

void CAttackTrail::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CAttackTrail::OnDestroy()
{
	__super::OnDestroy();
}

void CAttackTrail::OnEnable()
{
	__super::OnEnable();
}

void CAttackTrail::OnDisable()
{
	__super::OnDisable();
}

void CAttackTrail::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
