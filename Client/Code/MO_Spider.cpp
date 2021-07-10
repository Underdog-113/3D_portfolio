#include "stdafx.h"
#include "..\Header\MO_Spider.h"

#include "FSM_SpiderC.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

_uint CMO_Spider::m_s_uniqueID = 0;

CMO_Spider::CMO_Spider()
{
}

CMO_Spider::~CMO_Spider()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Spider::MakeClone(void)
{
	SP(CMO_Spider) spClone(new CMO_Spider, Engine::SmartDeleter<CMO_Spider>);
	__super::InitClone(spClone);

	spClone->m_spTransform		= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh			= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics		= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader			= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture		= spClone->GetComponent<Engine::CTextureC>();
	
	spClone->m_spRigidBody		= spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision		= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug			= spClone->GetComponent<Engine::CDebugC>();
	
	spClone->m_spStateMachine	= spClone->GetComponent<CFSM_SpiderC>();
	spClone->m_spPatternMachine = spClone->GetComponent<CPatternMachineC>();

	return spClone;
}

void CMO_Spider::Awake(void)
{
	__super::Awake();	

	m_spStateMachine = AddComponent<CFSM_SpiderC>();
	m_spPatternMachine->AddNecessaryPatterns(CSpiderBornPattern::Create(), CSpiderDiePattern::Create(), CSpiderBasePattern::Create(), CSpiderHitPattern::Create());
}

void CMO_Spider::Start(void)
{
	__super::Start();

	m_spTransform->SetRotationY(D3DXToRadian(90));
	
	m_spMesh->OnRootMotion();
	
	BaseStat stat;
	stat.SetBaseHp(321.f);
	stat.SetBaseAtk(120.f);
	stat.SetBaseDef(22.f);

	stat.SetGrowHp(10.f);
	stat.SetGrowAtk(1.2f);
	stat.SetGrowDef(1.f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);
	m_pStat->SetOnSuperArmor(true);
	m_pStat->SetMaxBreakGauge(9999.f);
	m_pStat->SetCurBreakGauge(9999.f);

	m_pSuperArmor->SetHitL(true);
	m_pSuperArmor->SetHitH(true);
	m_pSuperArmor->SetAirborne(true);
	SetWeakTime(7.f);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true, (_int)ELayerID::Attack, L"Explosion")).get();
	m_pAttackBall->GetTransform()->SetSize(6.f, 6.f, 6.f);
	m_pAttackBall->SetOwner(this);
}

void CMO_Spider::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Spider::Update(void)
{
	__super::Update();
}

void CMO_Spider::LateUpdate(void)
{
	__super::LateUpdate();
}


void CMO_Spider::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}


void CMO_Spider::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}


void CMO_Spider::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Spider::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Spider::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Spider::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Spider::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Spider::ApplyHitInfo(HitInfo info)
{
	__super::ApplyHitInfo(info);

	if (true == m_pStat->GetOnSuperArmor())
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
			//if (true == m_pStat->GetOnSuperArmor()) break;
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
			//if (true == m_pStat->GetOnSuperArmor()) break;
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
			//if (true == m_pStat->GetOnSuperArmor()) break;
			if (false == m_pStat->GetOnSuperArmor()) this->GetComponent<CPatternMachineC>()->SetOnAirBorne(true);
		}
		break;
	}
}

void CMO_Spider::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForwardUp(dir, UP_VECTOR);
}


SP(CMO_Spider) CMO_Spider::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Spider) spInstance(new CMO_Spider, Engine::SmartDeleter<CMO_Spider>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMO_Spider::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

SP(Engine::CObject) CMO_Spider::CreateEffect(std::wstring name)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(L"AttackTrail_Client", true, (_int)Engine::ELayerID::Effect, L"Cube0");

	//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetIsEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"K_Trail");
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"K_Trail");
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::MeshTrailShader);

	spMeshEffect->GetTransform()->SetPosition(GetTransform()->GetPosition());
	spMeshEffect->GetTransform()->AddPositionY(GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	//spMeshEffect->GetTransform()->AddRotationX(D3DXToRadian(90.f));

	return spMeshEffect;
}
