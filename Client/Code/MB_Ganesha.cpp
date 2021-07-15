#include "stdafx.h"
#include "..\Header\MB_Ganesha.h"

#include "FSM_GaneshaC.h"
#include "AttackBall.h"
#include "AttackBox.h"

_uint CMB_Ganesha::m_s_uniqueID = 0;

CMB_Ganesha::CMB_Ganesha()
{
}

CMB_Ganesha::~CMB_Ganesha()
{
	OnDestroy();
}

SP(Engine::CObject) CMB_Ganesha::MakeClone(void)
{
	SP(CMB_Ganesha) spClone(new CMB_Ganesha, Engine::SmartDeleter<CMB_Ganesha>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_GaneshaC>();
	spClone->m_spPatternMachine = spClone->GetComponent<CPatternMachineC>();

	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();

	return spClone;
}

void CMB_Ganesha::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_GaneshaC>();
	m_spPatternMachine->AddNecessaryPatterns(CGaneshaBornPattern::Create(), 
		CGaneshaDiePattern::Create(), 
		CGaneshaBasePattern::Create(), 
		CGaneshaHitPattern::Create());
	m_spPatternMachine->AddPattern(CGaneshaStampPattern::Create());
	m_spPatternMachine->AddPattern(CGaneshaRoll01Pattern::Create());
	m_spPatternMachine->AddPattern(CGaneshaBurst01Pattern::Create());
	m_spPatternMachine->AddPattern(CGaneshaBurst02Pattern::Create());
}

void CMB_Ganesha::Start(void)
{
	__super::Start();

	m_spTransform->SetSize(1.3f, 1.3f, 1.3f);
	m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(4000.f);
	stat.SetBaseAtk(117.f);
	stat.SetBaseDef(25.f);

	stat.SetGrowHp(516.f);
	stat.SetGrowAtk(5.1f);
	stat.SetGrowDef(2.9f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);
	m_pStat->SetHPMagnification(4);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);

	m_pAttackBox = std::dynamic_pointer_cast<CAttackBox>(m_pScene->GetObjectFactory()->AddClone(L"AttackBox", true)).get();
	m_pAttackBox->SetOwner(this);
}

void CMB_Ganesha::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMB_Ganesha::Update(void)
{
	__super::Update();
}

void CMB_Ganesha::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMB_Ganesha::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMB_Ganesha::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMB_Ganesha::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMB_Ganesha::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMB_Ganesha::OnEnable(void)
{
	__super::OnEnable();
}

void CMB_Ganesha::OnDisable(void)
{
	__super::OnDisable();
}

void CMB_Ganesha::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMB_Ganesha::ApplyHitInfo(HitInfo info)
{
	// attack strength
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage:
		break;
	case HitInfo::Str_Low:
		break;
	case HitInfo::Str_High:
		break;
	case HitInfo::Str_Airborne:
		break;
	}
}

void CMB_Ganesha::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

SP(CMB_Ganesha) CMB_Ganesha::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMB_Ganesha) spInstance(new CMB_Ganesha, Engine::SmartDeleter<CMB_Ganesha>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMB_Ganesha::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForwardUp(dir, UP_VECTOR);
}

