#include "stdafx.h"
#include "MO_Scout.h"

#include "FSM_ScoutC.h"
#include "AttackBall.h"
#include "AttackBox.h"

_uint CMO_Scout::m_s_uniqueID = 0;

CMO_Scout::CMO_Scout()
{
}

CMO_Scout::~CMO_Scout()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Scout::MakeClone(void)
{
	SP(CMO_Scout) spClone(new CMO_Scout, Engine::SmartDeleter<CMO_Scout>);

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

void CMO_Scout::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_ScoutC>();
	m_spPatternMachine->AddNecessaryPatterns(CScoutBornPattern::Create(), 
		CScoutDiePattern::Create(), 
		CScoutBasePattern::Create(), 
		CScoutHitPattern::Create(),
		CScoutAirbornePattern::Create());
	m_spPatternMachine->AddPattern(CScoutShoot2Pattern::Create());
	m_spPatternMachine->AddPattern(CScoutShoot3Pattern::Create());
}

void CMO_Scout::Start(void)
{
	__super::Start();

	m_spTransform->SetSize(0.7f, 0.7f, 0.7f);
	//m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(10.f);
	stat.SetBaseAtk(15.f);
	stat.SetBaseDef(5.f);

	stat.SetGrowHp(3.f);
	stat.SetGrowAtk(1.1f);
	stat.SetGrowDef(0.2f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);
	m_pStat->SetOnSuperArmor(true);

	m_pSuperArmor->SetHitL(false);
	m_pSuperArmor->SetHitH(false);
	m_pSuperArmor->SetAirborne(true);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);

	m_pAttackBox = std::dynamic_pointer_cast<CAttackBox>(m_pScene->GetObjectFactory()->AddClone(L"AttackBox", true)).get();
	m_pAttackBox->SetOwner(this);
}

void CMO_Scout::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Scout::Update(void)
{
	__super::Update();
}

void CMO_Scout::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Scout::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Scout::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMO_Scout::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Scout::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Scout::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Scout::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Scout::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Scout::ApplyHitInfo(HitInfo info)
{
	__super::ApplyHitInfo(info);

	if (true == m_pStat->GetOnPatternShield())
	{
		return;
	}

	// attack strength
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage: // hit 모션 없는 대미지
		break;
	case HitInfo::Str_Low:
		if (false == m_pSuperArmor->GetHitL())
		{
			this->GetComponent<CPatternMachineC>()->SetOnHitL(true);
		}
		else if (true == m_pSuperArmor->GetHitL())
		{
			if (false == m_pStat->GetOnSuperArmor()) this->GetComponent<CPatternMachineC>()->SetOnHitL(true);
		}
		break;
	case HitInfo::Str_High:
		if (false == m_pSuperArmor->GetHitH())
		{
			this->GetComponent<CPatternMachineC>()->SetOnHitH(true);
		}
		else if (true == m_pSuperArmor->GetHitH())
		{
			if (false == m_pStat->GetOnSuperArmor()) this->GetComponent<CPatternMachineC>()->SetOnHitH(true);
		}
		break;
	case HitInfo::Str_Airborne:
		if (false == m_pSuperArmor->GetAirborne())
		{
			this->GetComponent<CPatternMachineC>()->SetOnAirBorne(true);
		}
		else if (true == m_pSuperArmor->GetAirborne())
		{
			if (false == m_pStat->GetOnSuperArmor())
			{
				this->GetComponent<CPatternMachineC>()->SetOnAirBorne(true);
			}
		}
		break;
	}

	// crowd control
}

SP(CMO_Scout) CMO_Scout::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Scout) spInstance(new CMO_Scout, Engine::SmartDeleter<CMO_Scout>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMO_Scout::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForwardUp(dir, UP_VECTOR);
}

void CMO_Scout::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

void CMO_Scout::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

