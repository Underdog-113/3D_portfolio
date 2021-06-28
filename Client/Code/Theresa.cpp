#include "stdafx.h"
#include "Theresa.h"

#include "FSM_TheresaC.h"
#include "DynamicMeshData.h"

CTheresa::CTheresa()
{
}


CTheresa::~CTheresa()
{
	OnDestroy();
}

SP(CTheresa) CTheresa::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa) spInstance(new CTheresa, Engine::SmartDeleter<CTheresa>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa::MakeClone(void)
{
	SP(CTheresa) spClone(new CTheresa, Engine::SmartDeleter<CTheresa>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_TheresaC>();
	return spClone;
}

void CTheresa::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_TheresaC>();
}

void CTheresa::Start(void)
{
	__super::Start();

	m_spMesh->OnRootMotion();

	m_spTransform->SetSize(0.5f, 0.5f, 0.5f);

	// status
	V_WarshipStat stat;

	m_pStat = new V_Theresa_Stat;
	m_pStat->SetType(V_Stat::THERESA);
	m_pStat->SetupStatus(&stat);

	if (m_isWait)
	{
		__super::FixedUpdate();
		__super::Update();
		__super::LateUpdate();
		SetIsEnabled(false);
	}
}

void CTheresa::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTheresa::Update(void)
{
	__super::Update();


}

void CTheresa::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTheresa::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CTheresa::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CTheresa::OnDestroy(void)
{
	__super::OnDestroy();

	SAFE_DELETE(m_pStat)
}

void CTheresa::OnEnable(void)
{
	__super::OnEnable();
}

void CTheresa::OnDisable(void)
{
	__super::OnDisable();
}

void CTheresa::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CTheresa::ApplyHitInfo(HitInfo info)
{
}
