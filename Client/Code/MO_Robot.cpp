#include "stdafx.h"
#include "..\Header\MO_Robot.h"

#include "FSM_RobotC.h"
#include "AttackBall.h"

_uint CMO_Robot::m_s_uniqueID = 0;

CMO_Robot::CMO_Robot()
{
}

CMO_Robot::~CMO_Robot()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Robot::MakeClone(void)
{
	SP(CMO_Robot) spClone(new CMO_Robot, Engine::SmartDeleter<CMO_Robot>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_RobotC>();
	spClone->m_spPatternMachine = spClone->GetComponent<CPatternMachineC>();

	return spClone;
}

void CMO_Robot::Awake(void)
{
	__super::Awake();
	m_spStateMachine = AddComponent<CFSM_RobotC>();
	m_spPatternMachine->AddNecessaryPatterns(CRobotBornPattern::Create(), CRobotDiePattern::Create(), CRobotBasePattern::Create(), CRobotHitPattern::Create());
	//m_spPatternMachine->AddPattern(CRobotRunAttackPattern::Create());
	//m_spPatternMachine->AddPattern(CRobotAttack2Pattern::Create());
}

void CMO_Robot::Start(void)
{
	__super::Start();

	//m_spTransform->SetSize(1.f, 1.f, 1.f);
	//m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(849.f);
	stat.SetBaseAtk(43.f);
	stat.SetBaseDef(19.f);

	stat.SetGrowHp(12.f);
	stat.SetGrowAtk(2.f);
	stat.SetGrowDef(1.f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);
}

void CMO_Robot::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Robot::Update(void)
{
	__super::Update();
}

void CMO_Robot::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Robot::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Robot::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMO_Robot::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Robot::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Robot::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Robot::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Robot::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (L"Kiana" == ci.pOtherCollider->GetOwner()->GetOwner()->GetObjectKey())
		m_checkCol = true;
}

void CMO_Robot::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CMO_Robot::OnCollisionExit(Engine::_CollisionInfo ci)
{
	m_checkCol = false;
}

void CMO_Robot::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Robot::ApplyHitInfo(HitInfo info)
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

SP(CMO_Robot) CMO_Robot::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Robot) spInstance(new CMO_Robot, Engine::SmartDeleter<CMO_Robot>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMO_Robot::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}

void CMO_Robot::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

void CMO_Robot::UpdatePivotMatrices(void)
{
}

void CMO_Robot::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}
