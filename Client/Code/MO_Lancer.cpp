#include "stdafx.h"
#include "MO_Lancer.h"

#include "FSM_LancerC.h"
#include "AttackBall.h"

_uint CMO_Lancer::m_s_uniqueID = 0;

CMO_Lancer::CMO_Lancer()
{
}

CMO_Lancer::~CMO_Lancer()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Lancer::MakeClone(void)
{
	SP(CMO_Lancer) spClone(new CMO_Lancer, Engine::SmartDeleter<CMO_Lancer>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();
	spClone->m_spPatternMachine = spClone->GetComponent<CPatternMachineC>();

	return spClone;
}

void CMO_Lancer::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_LancerC>();
	m_spPatternMachine->AddNecessaryPatterns(CLancerBornPattern::Create(), CLancerDiePattern::Create(), CLancerBasePattern::Create(), CLancerHitPattern::Create());
	m_spPatternMachine->AddPattern(CLancerAttack2Pattern::Create());
}

void CMO_Lancer::Start(void)
{
	__super::Start();

	m_spTransform->SetSize(0.8f, 0.8f, 0.8f);
	//m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(522.f);
	stat.SetBaseAtk(31.f);
	stat.SetBaseDef(15.f);

	stat.SetGrowHp(9.f);
	stat.SetGrowAtk(2.8f);
	stat.SetGrowDef(1.f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOffset(_float3(0, 1, 0));
	m_pAttackBall->SetOwner(this);
}

void CMO_Lancer::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Lancer::Update(void)
{
	__super::Update();
}

void CMO_Lancer::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Lancer::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Lancer::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMO_Lancer::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Lancer::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Lancer::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Lancer::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Lancer::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Lancer::ApplyHitInfo(HitInfo info)
{
	// attack strength
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage:
		break;
	case HitInfo::Str_Low:
		this->GetComponent<CPatternMachineC>()->SetOnHitL(true);
		break;
	case HitInfo::Str_High:
		this->GetComponent<CPatternMachineC>()->SetOnHitH(true);
		break;
	case HitInfo::Str_Airborne:
		break;
	}

	// crowd control
}

SP(CMO_Lancer) CMO_Lancer::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Lancer) spInstance(new CMO_Lancer, Engine::SmartDeleter<CMO_Lancer>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMO_Lancer::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}

void CMO_Lancer::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

void CMO_Lancer::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

