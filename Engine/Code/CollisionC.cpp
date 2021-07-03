#include "EngineStdafx.h"
#include "CollisionC.h"
#include "Collider.h"
#include "Object.h"
#include "DebugCollider.h"

USING(Engine)
CCollisionC::CCollisionC(void)
{
}

CCollisionC::~CCollisionC(void)
{
	OnDestroy();
}

SP(CComponent) CCollisionC::MakeClone(CObject* pObject)
{
	SP(CCollisionC) spClone(new CCollisionC);
	__super::InitClone(spClone, pObject);

	for (auto& collider : m_vColliders)
		spClone->m_vColliders.emplace_back(collider->MakeClone(spClone.get()));

	spClone->m_resolveIn	= m_resolveIn;

	return spClone;
}

void CCollisionC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();
		CScene*	pOwnerScene		= m_pOwner->GetScene();

		AddColliderFromFile();
	}
}

void CCollisionC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	m_spTransform = m_pOwner->GetComponent<CTransformC>();
	m_spRigidbody = m_pOwner->GetComponent<CRigidBodyC>();

	CCollisionManager::GetInstance()->AddCollisionToManager(std::dynamic_pointer_cast<CCollisionC>(spThis));
	for (auto& collider : m_vColliders)
		CCollisionManager::GetInstance()->AddColliderToManager(collider);
}

void CCollisionC::FixedUpdate(SP(CComponent) spThis)
{
}

void CCollisionC::Update(SP(CComponent) spThis)
{
}

void CCollisionC::LateUpdate(SP(CComponent) spSelf)
{
	for (auto& collider : m_vColliders)
		collider->UpdatePosition();
}

void CCollisionC::OnDestroy(void)
{
	for (auto& collider : m_vColliders)
	{
		collider->SetOwner(nullptr);
		collider.reset();
	}

	m_vColliders.clear();
}

void CCollisionC::OnEnable(void)
{
	__super::OnEnable();

	for (auto& collider : m_vColliders)
		collider->SetIsEnabled(true);

	m_vCurCollisions.clear();
	m_vPreCollisions.clear();
	m_vPreTriggers.clear();
	m_vCurTriggers.clear();
}

void CCollisionC::OnDisable(void)
{
	__super::OnDisable();

	for (auto& collider : m_vColliders)
		collider->SetIsEnabled(false);
}

void CCollisionC::AddCollider(SP(CCollider) spCollider, _bool isTrigger)
{
	spCollider->SetOwner(this);
	spCollider->SetIsTrigger(isTrigger);
	m_vColliders.emplace_back(spCollider);


	SP(CDebugC) spDebugC = m_pOwner->GetComponent<CDebugC>();

	if (spDebugC != nullptr)
		spDebugC->AddDebugCollider(spCollider.get());
}

void CCollisionC::AddCollisionInfo(_CollisionInfo collisionInfo)
{
	m_vCurCollisions.emplace_back(collisionInfo);
}

void CCollisionC::AddTriggeredCC(CCollisionC* pCC)
{
	m_vCurTriggers.emplace_back(pCC);
}

void CCollisionC::DeleteCollider(_int index)
{
	auto& iter = m_vColliders.begin();
	m_vColliders[index]->SetOwner(nullptr);
	m_vColliders[index].reset();
	m_vColliders.erase(iter + index);

	SP(CDebugC) spDebug;
	if (spDebug = m_pOwner->GetComponent<CDebugC>())
	{
		spDebug->GetDebugCollider()[index]->SetDeleteThis(true);
		spDebug->DeleteDebugCollider(index);
	}
}

void CCollisionC::AddColliderFromFile(void)
{
	_bool			isStatic	= m_pOwner->GetIsStatic();
	_int			dataID		= m_pOwner->GetDataID();
	std::wstring	objectKey	= m_pOwner->GetObjectKey();
	CScene*			pOwnerScene	= m_pOwner->GetScene();
	std::wstring	varKey;


	for (_int i = 0; i < (_int)EColliderType::NumOfCT; ++i)
	{
		_int numOfCollider;
		varKey = L"numOf_Type" + std::to_wstring(i) + L"_Collider";
		pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, varKey, numOfCollider);

		SP(CCollider) spCollider;
		_float3 offset;
		_int collisionID;
		for (_int j = 0; j < numOfCollider; ++j)
		{
			std::wstring index = std::to_wstring(j);
			switch (i)
			{
			case (_int)EColliderType::Point:
			{
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"PointCollider_" + index + L"_offset", offset);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"PointCollider_" + index + L"_collisionID", collisionID);
				spCollider = CPointCollider::Create(collisionID, offset);
				break;
			}
			case (_int)EColliderType::Ray:
			{
				_float3 dir;
				_float len;
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"RayCollider_" + index + L"_offset", offset);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"RayCollider_" + index + L"_dir", dir);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"RayCollider_" + index + L"_len", len);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"RayCollider_" + index + L"_collisionID", collisionID);
				spCollider = CRayCollider::Create(collisionID, offset, dir, len);
				break;
			}
			case (_int)EColliderType::Sphere:
			{
				_float radius;
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"SphereCollider_" + index + L"_radius", radius);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"SphereCollider_" + index + L"_offset", offset);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"SphereCollider_" + index + L"_collisionID", collisionID);

				spCollider = CSphereCollider::Create(collisionID, radius, offset);
				break;
			}
			case (_int)EColliderType::AABB:
			{
				_float3 size;
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"AabbCollider_" + index + L"_size", size);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"AabbCollider_" + index + L"_offset", offset);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"AabbCollider_" + index + L"_collisionID", collisionID);

				spCollider = CAabbCollider::Create(collisionID, size, offset);
				break;
			}
			case (_int)EColliderType::OBB:
			{
				_float3 size;
				_float3 rotOffset;
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"ObbCollider_" + index + L"_size", size);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"ObbCollider_" + index + L"_offset", offset);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"ObbCollider_" + index + L"_rotOffset", rotOffset);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"ObbCollider_" + index + L"_collisionID", collisionID);

				spCollider = CObbCollider::Create(collisionID, size, offset);
				break;
			}
			default:
			{
				MSG_BOX(__FILE__, L"EColliderType::NumOfCT is broken");
				ABORT;
				break;
			}
			}

			AddCollider(spCollider);
		}
	}
}

void CCollisionC::ProcessCollisions(void)
{
	if (m_vCurCollisions.size() == 0 && m_vPreCollisions.size() == 0)
		return;

	for (auto& curColInfo : m_vCurCollisions)
	{
		_bool alreadyThere = false;
		for (auto& it = m_vPreCollisions.begin(); it != m_vPreCollisions.end(); ++it)
		{
			CCollisionC* pPreCollidedCC = (*it).pOtherCollider->GetOwner();
			CCollisionC* pCurCollidedCC = curColInfo.pOtherCollider->GetOwner();
			if (pPreCollidedCC == pCurCollidedCC)
			{
				m_pOwner->OnCollisionStay(curColInfo);
				alreadyThere = true;
				m_vPreCollisions.erase(it);
				break;
			}
		}

		if (alreadyThere == false)
			m_pOwner->OnCollisionEnter(curColInfo);
	}

	for (auto& preColInfo : m_vPreCollisions)
		m_pOwner->OnCollisionExit(preColInfo);

	m_vPreCollisions.clear();
	m_vPreCollisions = m_vCurCollisions;
	m_vCurCollisions.clear();
}

void CCollisionC::ProcessTriggers(void)
{
	if (m_vCurTriggers.size() == 0 && m_vPreTriggers.size() == 0)
		return;

	for (auto& curTrigger : m_vCurTriggers)
	{
		if (curTrigger->GetOwner() == nullptr)
			continue;

		_bool alreadyThere = false;
		for (auto& it = m_vPreTriggers.begin(); it != m_vPreTriggers.end(); ++it)
		{
			if ((*it) == curTrigger)
			{
				m_pOwner->OnTriggerStay(curTrigger);
				alreadyThere = true;
				m_vPreTriggers.erase(it);
				break;
			}
		}

		if (alreadyThere == false)
			m_pOwner->OnTriggerEnter(curTrigger);
	}

	for (auto& preTrigger : m_vPreTriggers)
		m_pOwner->OnTriggerExit(preTrigger);

	m_vPreTriggers.clear();
	m_vPreTriggers = m_vCurTriggers;
	m_vCurTriggers.clear();
}
