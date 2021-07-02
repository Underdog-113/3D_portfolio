#include "stdafx.h"
#include "..\Header\MB_Bronya.h"
#include "DynamicMeshData.h"

#include "FSM_BronyaC.h"
#include "AttackBall.h"
#include "AttackBox.h"

#include "Bronya_Weapon.h"

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
	//spClone->m_spRigidBody->SetIsEnabled(false);
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();

	return spClone;
}

void CMB_Bronya::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_BronyaC>();
	m_spPatternMachine->AddNecessaryPatterns(CBronyaBornPattern::Create(), CBronyaDiePattern::Create(), CBronyaBasePattern::Create(), CBronyaHitPattern::Create());
}

void CMB_Bronya::Start(void)
{
	__super::Start();
	
	m_spTransform->SetSize(0.8f, 0.8f, 0.8f);
	//m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(5277.f);
	stat.SetBaseAtk(110.f);
	stat.SetBaseDef(37.f);

	stat.SetGrowHp(750.f);
	stat.SetGrowAtk(10.35f);
	stat.SetGrowDef(5.9f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);

	m_pAttackBox = std::dynamic_pointer_cast<CAttackBox>(m_pScene->GetObjectFactory()->AddClone(L"AttackBox", true)).get();
	m_pAttackBox->SetOwner(this);
	
	EquipWeapon();

}

void CMB_Bronya::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMB_Bronya::Update(void)
{
	__super::Update();

	SP(Engine::CTransformC) pWeaponTransform;
	pWeaponTransform = static_cast<SP(Engine::CTransformC)>(m_pScene->FindObjectByName(L"Bronya_Weapon")->GetComponent<Engine::CTransformC>());


	m_actualBoneMat = *m_pParentBoneMat;
	_float3 rootMotionPos = m_spMesh->GetRootMotionPos();
	m_actualBoneMat._41 -= rootMotionPos.x;
	m_actualBoneMat._43 -= rootMotionPos.z;
	m_actualBoneMat *= m_spTransform->GetWorldMatrix();
	
	pWeaponTransform->SetParentMatrix(&m_actualBoneMat);
}

void CMB_Bronya::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMB_Bronya::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
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

void CMB_Bronya::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

void CMB_Bronya::EquipWeapon()
{
	//고쳐야함
	SP(Engine::CTransformC) pParentTransform;
	pParentTransform = static_cast<SP(Engine::CTransformC)>(m_pScene->FindObjectByName(L"MB_Bronya")->GetComponent<Engine::CTransformC>());

	SP(Engine::CTransformC) pWeaponTransform;
	pWeaponTransform = static_cast<SP(Engine::CTransformC)>(m_pScene->FindObjectByName(L"Bronya_Weapon")->GetComponent<Engine::CTransformC>());

	if (m_pParentBoneMat == nullptr)
	{
		Engine::CDynamicMeshData* pDM =
			static_cast<Engine::CDynamicMeshData*>(m_pScene->FindObjectByName(L"MB_Bronya")->GetComponent<Engine::CMeshC>()->GetMeshData());

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



		m_pParentWorldMat = &pParentTransform->GetWorldMatrix();
	}

	pWeaponTransform->SetRotation(_float3(30.2f, 23.8f, 1.6f));
	pWeaponTransform->SetPosition(_float3(1.1f, -0.22f, -0.6f));
}

SP(CMB_Bronya) CMB_Bronya::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMB_Bronya) spInstance(new CMB_Bronya, Engine::SmartDeleter<CMB_Bronya>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

void CMB_Bronya::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}
