#include "stdafx.h"
#include "Sakura.h"

#include "FSM_SakuraC.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"
#include "Layer.h"

#include "Monster.h"

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

	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();

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
	m_pStat->SetSkillCost(20.f);
	m_pStat->SetUltraCost(100.f);
	m_pStat->SetType(V_Stat::SAKURA);
	m_pStat->SetupStatus(&stat);

	__super::Start();

	m_spMesh->OnRootMotion();
	m_spDebug = AddComponent<Engine::CDebugC>();

	m_spTransform->SetSize(1.2f, 1.2f, 1.2f);

	//CreatePivotMatrix(&m_pHand_World, &m_pHand_Frame, "Bip001_Prop1");
	CreateAttackBall(&m_pAttackBall);
	CreateAttackBall(&m_pFlashAttackBall);

	m_pAttackBall->SetIsEnabled(false);

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

	m_pAttackBall->GetTransform()->SetPosition(m_spTransform->GetPosition());
	m_pAttackBall->GetTransform()->AddPositionY(m_spMesh->GetHalfYOffset());
	m_pAttackBall->GetTransform()->AddPosition(m_spTransform->GetForward() * 0.5f);
	//UpdatePivotMatrix(m_pHand_World, m_pHand_Frame);

	if (m_8SliceAttack)
	{
		m_8sliceTimer += GET_PLAYER_DT;
		if (m_8sliceTimer > 0.02f)
		{
			m_8sliceTimer = 0.f;
			Act8SliceAttack();
			++m_8sliceCount;
			if (m_8sliceCount == 8)
				m_8SliceAttack = false;
		}
	}

	if (m_infernoMode)
	{
		m_infernoTimer += GET_PLAYER_DT;
		if (m_infernoTimer > 10.f)
			m_infernoMode = false;
	}
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
	m_infernoTimer = 0.f;
	m_pCT->OnSakuraUltraActive();
}

void CSakura::On8SliceAttack(void)
{
	m_8SliceAttack = true;
	m_8sliceCount = 0;
	m_8sliceTimer = 0.f;
}

void CSakura::Act8SliceAttack(void)
{
	Engine::CLayer* pLayer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers()[(_int)ELayerID::Enemy];
	std::vector<SP(Engine::CObject)> monsterList = pLayer->GetGameObjects();

	HitInfo info;
	info.SetDamageRate(0.1f);
	info.SetBreakDamage(20.f);
	info.SetStrengthType(HitInfo::Str_Airborne);
	info.SetCrowdControlType(HitInfo::CC_Airborne);

	for (auto& iter : monsterList)
	{
		CMonster* pMonster = (CMonster*)iter.get();
		if (pMonster->GetIsEnabled() && !pMonster->GetComponent<CPatternMachineC>()->GetOnDie())
		{
			m_pCT->HitMonster(
				this,
				pMonster,
				info,
				pMonster->GetTransform()->GetPosition() + _float3(0.f, pMonster->GetComponent<Engine::CMeshC>()->GetHalfYOffset(), 0.f));
		}
	}
}
