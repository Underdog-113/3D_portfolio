#include "stdafx.h"
#include "..\Header\MO_Ninza.h"

#include "FSM_SickleC.h"
#include "AttackBall.h"

_uint CMO_Ninza::m_s_uniqueID = 0;

CMO_Ninza::CMO_Ninza()
{
}

CMO_Ninza::~CMO_Ninza()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Ninza::MakeClone(void)
{
	SP(CMO_Ninza) spClone(new CMO_Ninza, Engine::SmartDeleter<CMO_Ninza>);

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

void CMO_Ninza::Awake(void)
{
	__super::Awake();

	//m_spPatternMachine->AddNecessaryPatterns(CNinzaBornPattern::Create(), CNinzaDiePattern::Create(), CNinzaBasePattern::Create(), CNinzaHitPattern::Create());
}

void CMO_Ninza::Start(void)
{
	__super::Start();

	//m_spTransform->SetSize(1.7f, 1.7f, 1.7f);
	m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(225.f);
	stat.SetBaseAtk(28.f);
	stat.SetBaseDef(7.f);

	stat.SetGrowHp(6.f);
	stat.SetGrowAtk(2.1f);
	stat.SetGrowDef(0.2f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOffset(_float3(0, 1, 0));
	m_pAttackBall->SetOwner(this);
}

void CMO_Ninza::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Ninza::Update(void)
{
	__super::Update();
}

void CMO_Ninza::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Ninza::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Ninza::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMO_Ninza::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Ninza::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Ninza::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Ninza::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Ninza::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Ninza::ApplyHitInfo(HitInfo info)
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

SP(CMO_Ninza) CMO_Ninza::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Ninza) spInstance(new CMO_Ninza, Engine::SmartDeleter<CMO_Ninza>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMO_Ninza::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}

void CMO_Ninza::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

void CMO_Ninza::UpdatePivotMatrices(void)
{
}

void CMO_Ninza::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

