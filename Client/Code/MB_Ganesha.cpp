#include "stdafx.h"
#include "..\Header\MB_Ganesha.h"

#include "FSM_GaneshaC.h"
#include "AttackBall.h"
#include "AttackBox.h"

#include "FSMDefine_Ganesha.h"

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
}

void CMB_Ganesha::Start(void)
{
	__super::Start();

	m_spPatternMachine->AddNecessaryPatterns(CGaneshaBornPattern::Create(),
		CGaneshaDiePattern::Create(),
		CGaneshaBasePattern::Create(),
		CGaneshaHitPattern::Create(),
		CGaneshaAirbornePattern::Create(),
		CGaneshaStunPattern::Create());
	m_spPatternMachine->AddPattern(CGaneshaStampPattern::Create());
	//m_spPatternMachine->AddPattern(CGaneshaRoll01Pattern::Create());
	m_spPatternMachine->AddPattern(CGaneshaBurst01Pattern::Create());
	m_spPatternMachine->AddPattern(CGaneshaBurst02Pattern::Create());

	m_spTransform->SetSize(1.3f, 1.3f, 1.3f);
	m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(5500.f);
	stat.SetBaseAtk(117.f);
	stat.SetBaseDef(25.f);

	stat.SetGrowHp(516.f);
	stat.SetGrowAtk(5.1f);
	stat.SetGrowDef(2.9f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->Setname(L"Ganesha");
	m_pStat->SetupStatus(&stat);
	m_pStat->SetHPMagnification(4);
	m_pStat->SetOnSuperArmor(true);
	m_pStat->SetOnBPShield(false);
	//m_pStat->SetMaxBreakGauge(800.f);
	m_pStat->SetMaxBreakGauge(40.f);
	m_pStat->SetCurBreakGauge(m_pStat->GetMaxBreakGauge());
	m_weakTime = 8.f;

	m_pSuperArmor->SetHitL(true);
	m_pSuperArmor->SetHitH(true);
	m_pSuperArmor->SetAirborne(true);
	m_pSuperArmor->SetStun(true);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);

	m_pAttackBox = std::dynamic_pointer_cast<CAttackBox>(m_pScene->GetObjectFactory()->AddClone(L"AttackBox", true)).get();
	m_pAttackBox->SetOwner(this);

	m_targetingHelperRate = 1.5f;
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
	__super::ApplyHitInfo(info);

	if (true == m_pStat->GetOnPatternShield())
	{
		return;
	}

	// attack strength
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage:
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
		break;
	}

	// crowd control
	switch (info.GetCrowdControlType())
	{
	case HitInfo::CC_None:
		break;
	case HitInfo::CC_Stun:
		if (false == m_pSuperArmor->GetStun())
		{
			this->GetComponent<CPatternMachineC>()->SetOnStun(true);
		}
		else if (true == m_pSuperArmor->GetStun())
		{
			if (false == m_pStat->GetOnSuperArmor()) this->GetComponent<CPatternMachineC>()->SetOnStun(true);
		}
		break;
	case HitInfo::CC_Sakura:
		break;
	case HitInfo::CC_Airborne:
		this->GetComponent<CPatternMachineC>()->SetOnAirBorne(true);
		break;
	}
}

void CMB_Ganesha::MonsterDead()
{
	__super::MonsterDead();

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

void CMB_Ganesha::DoubleJump(_float3 mPos)
{
	// effect
	_float fX = 0;
	for (_int i = 0; i < 8; ++i)
	{
		SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_SmokeEff", true);

		// Ganesha Pos X + fX 
		spObj->GetTransform()->SetPositionX(mPos.x + fX - 0.3f);
		spObj->GetTransform()->SetPositionY(mPos.y + 0.1f);
		spObj->GetTransform()->SetPositionZ(mPos.z + (rand() % 2) - 0.5f);
		fX += 0.5f;
	}
}
