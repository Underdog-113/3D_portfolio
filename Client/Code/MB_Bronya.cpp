#include "stdafx.h"
#include "..\Header\MB_Bronya.h"
#include "DynamicMeshData.h"

#include "FSM_BronyaC.h"
#include "AttackBall.h"
#include "AttackBox.h"

#include "Bronya_Weapon.h"
#include "BronyaBullet.h"
#include "BronyaGrenade.h"
#include "Layer.h"

_uint CMB_Bronya::m_s_uniqueID = 0;

CMB_Bronya::CMB_Bronya()
{
}

CMB_Bronya::~CMB_Bronya()
{
	OnDestroy();
}

SP(Engine::CObject) CMB_Bronya::MakeClone(void)
{
	SP(CMB_Bronya) spClone(new CMB_Bronya, Engine::SmartDeleter<CMB_Bronya>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_BronyaC>();
	spClone->m_spPatternMachine = spClone->GetComponent<CPatternMachineC>();

	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();

	return spClone;
}

void CMB_Bronya::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_BronyaC>();
}

void CMB_Bronya::Start(void)
{
	__super::Start();
	
	m_spPatternMachine->AddNecessaryPatterns(CBronyaBornPattern::Create(),
		CBronyaDiePattern::Create(),
		CBronyaBasePattern::Create(),
		CBronyaHitPattern::Create(),
		CBronyaAirbornePattern::Create(),
		CBronyaStunPattern::Create());
	//m_spPatternMachine->AddPattern(CBronyaShoot1Pattern::Create()); // Pshield on
	//m_spPatternMachine->AddPattern(CBronyaThrow1Pattern::Create());
	//m_spPatternMachine->AddPattern(CBronyaShock1Pattern::Create()); // Pshield on
	//m_spPatternMachine->AddPattern(CBronyaShock2Pattern::Create()); // Pshield on
	//m_spPatternMachine->AddPattern(CBronyaEscapePattern::Create());
	//m_spPatternMachine->AddPattern(CBronyaSkillUltraPattern::Create()); // Pshield on
	m_spPatternMachine->AddPattern(CBronyaArsenalPattern::Create()); // Pshield on
	//m_spPatternMachine->AddPattern(CBronyaFlashBangPattern::Create()); // Pshield on

	m_spTransform->SetSize(0.5f, 0.5f, 0.5f);
	m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	//stat.SetBaseHp(11277.f);
	stat.SetBaseHp(2000.f);
	stat.SetBaseAtk(110.f);
	stat.SetBaseDef(37.f);

	stat.SetGrowHp(750.f);
	stat.SetGrowAtk(10.35f);
	stat.SetGrowDef(5.9f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);
	m_pStat->SetHPMagnification(6);
	m_pStat->SetOnSuperArmor(true);
	m_pStat->SetMaxBreakGauge(2700.f);
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
	
	m_spWeapon = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Weapon", true, (_uint)ELayerID::Enemy, L"Bronya_Weapon");

	EquipWeapon();
	ArsenalEffectPosLoad();
	BulletReload();
	EquipBomb();
	EquipGrenade();
	SetupEscapePos();

	m_fAlpha = 1.f;
}

void CMB_Bronya::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMB_Bronya::Update(void)
{
	__super::Update();

	SP(Engine::CTransformC) pWeaponTransform;
	pWeaponTransform = m_spWeapon->GetTransform();


	m_actualBoneMat = *m_pParentBoneMat;
	_float3 rootMotionPos = m_spMesh->GetRootMotionPos();
	m_actualBoneMat._41 -= rootMotionPos.x;
	m_actualBoneMat._43 -= rootMotionPos.z;
	m_actualBoneMat *= m_spTransform->GetWorldMatrix();
	
	pWeaponTransform->SetParentMatrix(&m_actualBoneMat);

	if (0.f >= m_pStat->GetCurBreakGauge() && false == GetComponent<CPatternMachineC>()->GetOnStun())
	{
		GetComponent<CPatternMachineC>()->SetOnStun(true);
	}
}

void CMB_Bronya::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMB_Bronya::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("g_Alpha", m_fAlpha);
	pEffect->CommitChanges();
}

void CMB_Bronya::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMB_Bronya::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMB_Bronya::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMB_Bronya::OnEnable(void)
{
	__super::OnEnable();
}

void CMB_Bronya::OnDisable(void)
{
	__super::OnDisable();
}

void CMB_Bronya::OnCollisionEnter(Engine::_CollisionInfo ci)
{
}

void CMB_Bronya::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CMB_Bronya::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CMB_Bronya::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
}

void CMB_Bronya::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CMB_Bronya::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CMB_Bronya::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMB_Bronya::ApplyHitInfo(HitInfo info)
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
		break;
	}

	// crowd control
	switch (info.GetCrowdControlType())
	{
	case HitInfo::CC_None:
		break;
	case HitInfo::CC_Stun:
		break;
	case HitInfo::CC_Sakura:
		break;
	case HitInfo::CC_Airborne:
		break;
	}
}

void CMB_Bronya::MonsterDead()
{
	__super::MonsterDead();

	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

void CMB_Bronya::EquipWeapon()
{
	if (m_pParentBoneMat == nullptr)
	{
		Engine::CDynamicMeshData* pDM =
			static_cast<Engine::CDynamicMeshData*>(m_spMesh->GetMeshData());

		if (nullptr == pDM)
		{
			MSG_BOX(__FILE__, L"ParentMat is Not Found SceneName : MB_Bronya.cpp 107");
			ABORT;
		}

		const Engine::D3DXFRAME_DERIVED* pFrm = pDM->GetFrameByName("Bip002_L_Forearm");

		if (nullptr == pFrm)
		{
			MSG_BOX(__FILE__, L"pFrm is Not Found SceneName :  MB_Bronya.cpp 115");
			ABORT;
		}

		m_pParentBoneMat = &pFrm->CombinedTransformMatrix;
		m_pParentWorldMat = &m_spTransform->GetWorldMatrix();
	}

	m_spWeapon->GetTransform()->SetRotation(_float3(30.2f, 23.8f, 1.6f));
	m_spWeapon->GetTransform()->SetPosition(_float3(1.1f, -0.22f, -0.6f));
}

void CMB_Bronya::ArsenalEffectPosLoad()
{
	auto& pDataStore = Engine::GET_CUR_SCENE->GetDataStore();

	pDataStore->GetValue(true, (_int)EDataID::Enemy, L"Bronya_ArsenalEffect", L"numOfEffect", m_maxArsenalEffectCnt);
	for (_int i = 0; i < m_maxArsenalEffectCnt; ++i)
	{
		_float3 position;
		pDataStore->GetValue(true, (_int)EDataID::Enemy, L"Bronya_ArsenalEffect", L"ring_" + std::to_wstring(i), position);
		m_vRingEffectPos.emplace_back(position);

		pDataStore->GetValue(true, (_int)EDataID::Enemy, L"Bronya_ArsenalEffect", L"range_" + std::to_wstring(i), position);
		m_vRangeEffectPos.emplace_back(position);
	}
}

void CMB_Bronya::BulletReload()
{
	for (_int i = 0; i < 22; ++i)
	{
		m_vBullets.emplace_back(std::dynamic_pointer_cast<CBronyaBullet>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"BronyaBullet", true, (_uint)ELayerID::Enemy, L"BronyaBullet")));
		m_vBullets[i]->SetIsEnabled(false);
	}
}

void CMB_Bronya::EquipBomb()
{
	for (_int i = 0; i < m_maxArsenalEffectCnt; ++i)
	{
		m_vExplosions.emplace_back(std::dynamic_pointer_cast<CBronyaBullet>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"BronyaBullet", true, (_uint)ELayerID::Enemy, L"BronyaBullet")));
		m_vExplosions[i]->SetIsEnabled(false);
		m_vExplosions[i]->GetTransform()->SetSize(0.001f, 0.001f, 0.001f);
		m_vExplosions[i]->GetTransform()->SetPosition(m_vRangeEffectPos[i]);
		m_vExplosions[i]->SetMove(false);
	}
}

void CMB_Bronya::EquipGrenade()
{
	for (_int i = 0; i < 3; ++i)
	{
		m_vGrenades.emplace_back(std::dynamic_pointer_cast<CBronyaGrenade>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"BronyaGrenade", true, (_uint)ELayerID::Enemy, L"BronyaGrenade")));
		m_vGrenades[i]->SetIsEnabled(false);
		m_vGrenades[i]->GetTransform()->SetSize(2.f, 2.f, 2.f);
	}
}

void CMB_Bronya::SetupEscapePos()
{
	auto& pDataStore = Engine::GET_CUR_SCENE->GetDataStore();

	pDataStore->GetValue(true, (_int)EDataID::Enemy, L"Bronya_Escape", L"numOfEscape", m_maxEscapePos);

	for (_int i = 0; i < m_maxEscapePos; ++i)
	{
		_float3 position;
		pDataStore->GetValue(true, (_int)EDataID::Enemy, L"Bronya_Escape", L"Escape_" + std::to_wstring(i), position);
		m_vEscapePos.emplace_back(position);
	}
}

SP(CMB_Bronya) CMB_Bronya::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMB_Bronya) spInstance(new CMB_Bronya, Engine::SmartDeleter<CMB_Bronya>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
