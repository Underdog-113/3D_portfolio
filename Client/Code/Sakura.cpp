#include "stdafx.h"
#include "Sakura.h"

#include "FSM_SakuraC.h"
#include "DynamicMeshData.h"

CSakura::CSakura()
{
}


CSakura::~CSakura()
{
	OnDestroy();
}

SP(CSakura) CSakura::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura) spInstance(new CSakura, Engine::SmartDeleter<CSakura>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura::MakeClone(void)
{
	SP(CSakura) spClone(new CSakura, Engine::SmartDeleter<CSakura>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_SakuraC>();
	return spClone;
}

void CSakura::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_SakuraC>();
}

void CSakura::Start(void)
{
	// status
	V_WarshipStat stat;

	m_pStat = new V_Sakura_Stat;
	m_pStat->SetUltraCost(100.f);
	m_pStat->SetType(V_Stat::SAKURA);
	m_pStat->SetupStatus(&stat);

	__super::Start();

	m_spMesh->OnRootMotion();
	m_spDebug = AddComponent<Engine::CDebugC>();

	m_spTransform->SetSize(1.2f, 1.2f, 1.2f);

	CreatePivotMatrix(&m_pHand_World, &m_pHand_Frame, "Bip001_Prop1");
	CreateAttackBall(&m_pAttackBall);

	if (m_isWait)
	{
		__super::FixedUpdate();
		__super::Update();
		__super::LateUpdate();
		SetIsEnabled(false);
	}

}

void CSakura::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSakura::Update(void)
{
	__super::Update();

	UpdatePivotMatrix(m_pHand_World, m_pHand_Frame);
}

void CSakura::LateUpdate(void)
{
	__super::LateUpdate();
}

void CSakura::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CSakura::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CSakura::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CSakura::OnDestroy(void)
{
	__super::OnDestroy();

	SAFE_DELETE(m_pHand_World)
	SAFE_DELETE(m_pStat)
}

void CSakura::OnEnable(void)
{
	__super::OnEnable();
}

void CSakura::OnDisable(void)
{
	__super::OnDisable();
}

void CSakura::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CSakura::ApplyHitInfo(HitInfo info)
{
}

void CSakura::UseSkill(void)
{
	_float curSp = m_pStat->GetCurSp();
	curSp -= m_pStat->GetSkillCost();
	m_pStat->SetCurSp(curSp);

	m_skillTimer = 0.f;
}

void CSakura::UseUltra(void)
{
	_float curSp = m_pStat->GetCurSp();
	curSp -= m_pStat->GetUltraCost();

	m_pStat->SetCurSp(curSp);
	m_ultraTimer = 0.f;
}
