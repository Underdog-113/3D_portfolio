#include "stdafx.h"
#include "AttackBox.h"
#include "Valkyrie.h"
#include "Monster.h"
#include "StageControlTower.h"


_uint CAttackBox::m_s_uniqueID = 0;
CAttackBox::CAttackBox()
{
}


CAttackBox::~CAttackBox()
{
	OnDestroy();
}

SP(CAttackBox) CAttackBox::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CAttackBox) spInstance(new CAttackBox, Engine::SmartDeleter<CAttackBox>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CAttackBox::MakeClone(void)
{
	SP(CAttackBox) spClone(new CAttackBox, Engine::SmartDeleter<CAttackBox>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CAttackBox::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Attack;
	m_dataID	= UNDEFINED;
	m_addExtra	= true;
	m_isEnabled = false;

	m_spCollision	= AddComponent<Engine::CCollisionC>();
}

void CAttackBox::Start(void)
{
	__super::Start();
	
	if (m_pOwner == nullptr)
	{
		MSG_BOX(__FILE__, L"Owner is empty in CAttackBox::Start()");
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

	auto col = Engine::CObbCollider::Create(m_collisionID);
	col->SetIsTrigger(true);
	m_spCollision->AddCollider(col);

	AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	AddComponent<Engine::CDebugC>();
	AddComponent<Engine::CShaderC>();
}

void CAttackBox::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CAttackBox::Update(void)
{
	__super::Update();
	
}

void CAttackBox::LateUpdate(void)
{
	__super::LateUpdate();
	
	//m_spTransform->UpdateParentMatrix(m_pParentMatrix);

	_float3 pos = _float3(m_pParentMatrix->_41, m_pParentMatrix->_42, m_pParentMatrix->_43);
	m_spTransform->SetPosition(pos);

}

void CAttackBox::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CAttackBox::OnEnable(void)
{
	__super::OnEnable();
	
}

void CAttackBox::OnDisable(void)
{
	__super::OnDisable();
	
	m_vCollided.clear();
}

void CAttackBox::OnCollisionEnter(Engine::_CollisionInfo ci)
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

		CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo);
	}
	else
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(pObject);
		CMonster* pMonster = static_cast<CMonster*>(m_pOwner);

		CStageControlTower::GetInstance()->HitValkyrie(pMonster, pValkyrie, m_hitInfo);
	}
}

void CAttackBox::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CAttackBox::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CAttackBox::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
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

		CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo);
	}
	else
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(pObject);
		CMonster* pMonster = static_cast<CMonster*>(m_pOwner);

		CStageControlTower::GetInstance()->HitValkyrie(pMonster, pValkyrie, m_hitInfo);
	}
}

void CAttackBox::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBox::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBox::SetupBox(CObject * pOwner, _mat * pParentMat, _float3 size, _float3 offset, _float3 rotOffset, HitInfo info)
{
	m_pOwner = pOwner;

	m_pParentMatrix = pParentMat;
	m_hitInfo = info;

	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetSize(size);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetHalfSize(size / 2.f);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetOffsetOrigin(offset);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetRotOffset(rotOffset);
}

void CAttackBox::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
