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
	OnDestroy();
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
	m_isEnabled = false;

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

	auto col = Engine::CSphereCollider::Create(m_collisionID, 0.1f);
	m_spCollision->AddCollider(col, true);
	m_pCollider = (Engine::CSphereCollider*)col.get();

	AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	AddComponent<Engine::CDebugC>();
	AddComponent<Engine::CShaderC>();
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

	_float3 pos = m_spTransform->GetPosition();

 	_float3 offsetPos;
 	D3DXVec3TransformCoord(&offsetPos, &m_offset, m_pParentMatrix);
 	m_spTransform->SetPosition(offsetPos);

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

void CAttackBall::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	Engine::CObject* pObject = ci.pOtherCollider->GetOwner()->GetOwner();

	for (auto& object : m_vCollided)
	{
		if (pObject == object)
			return;
	}

	if (m_collisionID == (_int)ECollisionID::PlayerAttack)
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(m_pOwner);
		CMonster* pMonster = static_cast<CMonster*>(pObject);

		CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo, ci.hitPoint);
	}
	else
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(pObject);
		CMonster* pMonster = static_cast<CMonster*>(m_pOwner);

		CStageControlTower::GetInstance()->HitValkyrie(pMonster, pValkyrie, m_hitInfo, ci.hitPoint);
	}
}

void CAttackBall::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CAttackBall::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CAttackBall::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	Engine::CObject* pObject = pCollisionC->GetOwner();

	for (auto& object : m_vCollided)
	{
		if (pObject == object)
			return;
	}
	m_vCollided.emplace_back(pObject);

	if (m_collisionID == (_int)ECollisionID::PlayerAttack)
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(m_pOwner);
		CMonster* pMonster = static_cast<CMonster*>(pObject);

		_float3 ballPos = m_spTransform->GetPosition();
		_float3 monPos = pMonster->GetTransform()->GetPosition();
		_float3 dir = monPos - ballPos;
		D3DXVec3Normalize(&dir, &dir);
		dir *= m_pCollider->GetRadius();

		CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo, ballPos + dir);
	}
	else
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(pObject);
		CMonster* pMonster = static_cast<CMonster*>(m_pOwner);

		_float3 ballPos = m_spTransform->GetPosition();
		_float3 valkyriePos = pValkyrie->GetTransform()->GetPosition();
		_float3 dir = valkyriePos - ballPos;
		D3DXVec3Normalize(&dir, &dir);
		dir *= m_pCollider->GetRadius();

		CStageControlTower::GetInstance()->HitValkyrie(pMonster, pValkyrie, m_hitInfo, ballPos + dir);
	}
}

void CAttackBall::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBall::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBall::SetupBall(CObject * pOwner, _mat * pParentMat, _float radius, HitInfo info)
{
	m_pOwner = pOwner;

	m_pParentMatrix = pParentMat;

	_float3 pos = _float3(m_pParentMatrix->_41, m_pParentMatrix->_42, m_pParentMatrix->_43);
	m_spTransform->SetPosition(pos);
	m_hitInfo = info;

	static_cast<Engine::CSphereCollider*>(m_spCollision->GetColliders()[0].get())->SetRadius(radius);
	static_cast<Engine::CSphereCollider*>(m_spCollision->GetColliders()[0].get())->UpdateBS();
}

void CAttackBall::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
