#include "stdafx.h"
#include "AttackBall.h"
#include "Valkyrie.h"
#include "Monster.h"
#include "StageControlTower.h"


_uint CAttackBall::m_s_uniqueID = 0;
CAttackBall::CAttackBall()
{
}


CAttackBall::~CAttackBall()
{
}

SP(CAttackBall) CAttackBall::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CAttackBall) spInstance(new CAttackBall, Engine::SmartDeleter<CAttackBall>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CAttackBall::MakeClone(void)
{
	SP(CAttackBall) spClone(new CAttackBall, Engine::SmartDeleter<CAttackBall>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CAttackBall::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Attack;
	m_dataID	= UNDEFINED;
	m_addExtra	= true;

	m_spCollision	= AddComponent<Engine::CCollisionC>();
}

void CAttackBall::Start(void)
{
	__super::Start();
	
	if (m_pOwner == nullptr)
	{
		MSG_BOX(__FILE__, L"Owner is empty in CAttackBall::Start()");
		ABORT;
	}	
	
	if (m_pOwner->GetLayerID() == (_int)ELayerID::Player)
	{
		m_collisionID = (_int)ECollisionID::PlayerAttack;
	}
	else
	{
		m_collisionID = (_int)ECollisionID::EnemyAttack;
	}

	m_spCollision->AddCollider(Engine::CSphereCollider::Create(m_collisionID, 0));
	AddComponent<Engine::CDebugC>();
}

void CAttackBall::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CAttackBall::Update(void)
{
	__super::Update();
	
}

void CAttackBall::LateUpdate(void)
{
	__super::LateUpdate();
	
	m_spTransform->UpdateParentMatrix(m_pParentMatrix);
}

void CAttackBall::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CAttackBall::OnEnable(void)
{
	__super::OnEnable();
	
}

void CAttackBall::OnDisable(void)
{
	__super::OnDisable();
	
	m_vCollided.clear();
}

void CAttackBall::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	Engine::CObject* pObject = pCollisionC->GetOwner();

	for (auto& object : m_vCollided)
	{
		if (pObject == object)
			return;
	}

	if (m_collisionID == (_int)ECollisionID::PlayerAttack)
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(m_pOwner);
		CMonster* pMonster = static_cast<CMonster*>(pObject);

		CStageControlTower::GetInstance()->GetStatDealer()->Damage_VtoM(pValkyrie->GetStat(), pMonster->GetStat(), m_damage);
	}
	else
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(pObject);
		CMonster* pMonster = static_cast<CMonster*>(m_pOwner);

		CStageControlTower::GetInstance()->GetStatDealer()->Damage_VtoM(pValkyrie->GetStat(), pMonster->GetStat(), m_damage);
	}
}

void CAttackBall::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBall::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBall::SetupBall(CObject* pOwner, _mat* pParentMat, _float radius, _float damage)
{
	m_pOwner = pOwner;
	m_spTransform->SetParent(pOwner->GetTransform());

	m_pParentMatrix = pParentMat;
	m_damage = damage;
}

void CAttackBall::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
