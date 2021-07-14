#include "stdafx.h"
#include "MO_Sickle.h"

#include "FSM_SickleC.h"
#include "AttackBall.h"

_uint CMO_Sickle::m_s_uniqueID = 0;

CMO_Sickle::CMO_Sickle()
{
}

CMO_Sickle::~CMO_Sickle()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Sickle::MakeClone(void)
{
	SP(CMO_Sickle) spClone(new CMO_Sickle, Engine::SmartDeleter<CMO_Sickle>);
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

void CMO_Sickle::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_SickleC>();
	m_spPatternMachine->AddNecessaryPatterns(CSickleBornPattern::Create(), 
											 CSickleDiePattern::Create(), 
											 CSickleBasePattern::Create(),
											 CSickleHitPattern::Create(), 
											 CSickleAirbornePattern::Create(),
											 CSickleStunPattern::Create());
}

void CMO_Sickle::Start(void)
{
	__super::Start();

	//m_spTransform->SetSize(1.3f, 1.3f, 1.3f);
	//m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(2445.f);
	//stat.SetBaseHp(445.f);
	stat.SetBaseAtk(36.f);
	stat.SetBaseDef(12.f);

	stat.SetGrowHp(6.f);
	stat.SetGrowAtk(1.5f);
	stat.SetGrowDef(0.5f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);
	m_pStat->SetHPMagnification(2);
	m_pStat->SetOnSuperArmor(true);
	m_pStat->SetMaxBreakGauge(145.f);
	m_pStat->SetCurBreakGauge(m_pStat->GetMaxBreakGauge());

	m_pSuperArmor->SetHitL(false);
	m_pSuperArmor->SetHitH(false);
	m_pSuperArmor->SetAirborne(true);
	m_pSuperArmor->SetStun(true);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);
	
	FindRightHand();
}

void CMO_Sickle::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Sickle::Update(void)
{
	__super::Update();

	UpdatePivotMatrices();
}

void CMO_Sickle::LateUpdate(void)
{
	__super::LateUpdate();
	
}


void CMO_Sickle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}


void CMO_Sickle::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}


void CMO_Sickle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Sickle::OnDestroy(void)
{
	delete m_pRightHand_World;

	__super::OnDestroy();
}

void CMO_Sickle::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Sickle::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Sickle::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Sickle::ApplyHitInfo(HitInfo info)
{
	__super::ApplyHitInfo(info);

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
			if (false == m_pStat->GetOnSuperArmor()) this->GetComponent<CPatternMachineC>()->SetOnAirBorne(true);
		}
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
		break;
	}
}

void CMO_Sickle::FindRightHand()
{
	m_pRightHand_Frame = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameByName(/*"Bip001_R_Finger12"*/"Bone030");
	m_pRightHand_BoneOffset = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameOffsetMatrix(/*"Bip001_R_Finger12"*/"Bone030");

	m_pRightHand_World = new _mat;
	*m_pRightHand_World = *m_pRightHand_BoneOffset * m_pRightHand_Frame->CombinedTransformMatrix;

	
	m_pAttackBall->SetParentMatrix(m_pRightHand_World);
}

void CMO_Sickle::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForwardUp(dir, UP_VECTOR);
}

void CMO_Sickle::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

void CMO_Sickle::UpdatePivotMatrices(void)
{
	if (m_pRightHand_World)
	{
		//_float3 offset = _float3(0.f, 0.00173f, 0.005370005f);
		//_float3 offset = _float3(0.f, 0.f, 0.f);

		//D3DXVec3Normalize(&offset, &offset);
		//_mat offsetMat;
		//D3DXMatrixIdentity(&offsetMat);
		//D3DXMatrixTranslation(&offsetMat, offset.x, offset.y, offset.z);

		//_mat combMat = offsetMat * m_pRightHand_Frame->CombinedTransformMatrix;
		//
		//_float3 rootMotionPos = m_spMesh->GetRootMotionPos();
		//combMat._41 -= rootMotionPos.x;
		////combMat._42 -= rootMotionPos.y;
		//combMat._43 -= rootMotionPos.z;

		//*m_pRightHand_World = combMat * m_spTransform->GetWorldMatrix();

		_mat combMat = m_pRightHand_Frame->CombinedTransformMatrix;
		_float3 rootMotionPos = m_spMesh->GetRootMotionPos();
		combMat._41 -= rootMotionPos.x;
		combMat._43 -= rootMotionPos.z;

		*m_pRightHand_World = combMat * m_spTransform->GetWorldMatrix();
	}
}

void CMO_Sickle::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

SP(CMO_Sickle) CMO_Sickle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Sickle) spInstance(new CMO_Sickle, Engine::SmartDeleter<CMO_Sickle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
