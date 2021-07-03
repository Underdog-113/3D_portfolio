#include "EngineStdafx.h"
#include "CollisionManager.h"
#include "SphereCollider.h"
#include "Object.h"
#include "CollisionHelper.h"
#include "DataStore.h"
 
 


USING(Engine)
IMPLEMENT_SINGLETON(CCollisionManager)

void CCollisionManager::Awake(void)
{
	__super::Awake();
	InitCollisionChecker();
}

void CCollisionManager::Start(_int numOfColliderID)
{
	m_numOfColliderID = numOfColliderID;
	for (int i = 0; i < m_numOfColliderID; ++i)
	{
		std::vector<SP(CCollider)> colliders;
		m_vColliders.emplace_back(colliders);

		std::vector<_int> collisionMap;
		m_vCollisionMap.emplace_back(collisionMap);
	}
}

void CCollisionManager::FixedUpdate(void)
{
}

void CCollisionManager::Update(void)
{
	for (_int i = 0; i < m_numOfColliderID; ++i)
	{
		for (auto& spCollider : m_vColliders[i])
		{
			//모든 CollisionComponent가 CheckCollision을 한다면,
			//하나의 충돌에 대해서 양쪽 CollisionComponent가 CollisionInfo를 쏠 거야.
			//ANS: Layer1이 Layer2를 체크해야할 레이어로 놓는다면
			//Layer2는 Layer1을 체크해야할 레이어에 놓지 않으면 됨.
			if (spCollider->GetOwner()->GetOwner() != nullptr && spCollider->GetIsEnabled())
			{
				CheckCollision(spCollider);
			}
		}
	}


	for (auto& spCollision : m_vCollisions)
	{
		if (spCollision->GetOwner() != nullptr && spCollision->GetIsEnabled())
		{
			spCollision->ProcessCollisions();
			spCollision->ProcessTriggers();
		}
	}

}

void CCollisionManager::LateUpdate(void)
{
	for (auto& it = m_vCollisions.begin(); it != m_vCollisions.end();)
	{
		if ((*it)->GetOwner() == nullptr)
		{
			(*it).reset();
			it = m_vCollisions.erase(it);
		}
		else
			++it;
	}
	
	for (int i = 0; i < m_numOfColliderID; ++i)
	{
		for (auto& it = m_vColliders[i].begin(); it != m_vColliders[i].end();)
		{
			if ((*it)->GetOwner() == nullptr)
			{
				(*it).reset();
				it = m_vColliders[i].erase(it);
			}
			else
				++it;
		}
	}
}


void CCollisionManager::OnDestroy(void)
{
	m_vColliders.clear();
}

void CCollisionManager::OnEnable(void)
{
}

void CCollisionManager::OnDisable(void)
{
}
void CCollisionManager::CheckCollision(SP(CCollider) spCollider)
{
	std::vector<_int>& checkingLayer = GetLayersToCheck(spCollider->GetCollisionID());
	_bool isItCollided;

	for (auto& layerID : checkingLayer)
	{
		for (auto& checkCollider : m_vColliders[layerID])
		{
			if (checkCollider == spCollider || !checkCollider->GetOwner()->GetIsEnabled())
				continue;

			if (CollisionHelper::CheckColliderBS(spCollider, checkCollider) == true)
			{
				_int myCType = spCollider->GetColliderType();
				_int checkCType = checkCollider->GetColliderType();

				

				isItCollided = (m_fpCollisionChecker[myCType][checkCType])(spCollider, checkCollider, false);
			}
		}
	}
}

void CCollisionManager::AddCollisionToManager(SP(CCollisionC) spCC)
{
	m_vCollisions.emplace_back(spCC);
}

void CCollisionManager::AddColliderToManager(SP(CCollider) spCollider)
{
	m_vColliders[spCollider->GetCollisionID()].emplace_back(spCollider);
}

_bool CCollisionManager::CheckCollisionInstant(SP(CCollider) spCollider, _int checkingLayer)
{
	_bool isItCollided = false;
	for (auto& checkCollider : m_vColliders[checkingLayer])
	{
		isItCollided = false;

		//콜라이더 간의 BS 체크
		if (CollisionHelper::CheckColliderBS(spCollider, checkCollider) == true)
		{
			_int myCType = spCollider->GetColliderType();
			_int checkCType = checkCollider->GetColliderType();
			isItCollided = (m_fpCollisionChecker[myCType][checkCType])(spCollider, checkCollider, true);
		}
	}

	return isItCollided;
}

std::vector<_int>& CCollisionManager::GetLayersToCheck(_int colliderID)
{
	return m_vCollisionMap[colliderID];
}

void CCollisionManager::InitCollisionChecker(void)
{
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::Point]	= CollisionHelper::PointPoint;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::Ray]		= CollisionHelper::PointRay;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::Sphere]	= CollisionHelper::PointSphere;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::AABB]		= CollisionHelper::PointAabb;
	m_fpCollisionChecker[(_int)EColliderType::Point][(_int)EColliderType::OBB]		= CollisionHelper::PointObb;
	
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::Point]		= CollisionHelper::PointRay;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::Ray]		= CollisionHelper::RayRay;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::Sphere]		= CollisionHelper::RaySphere;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::AABB]		= CollisionHelper::RayAabb;
	m_fpCollisionChecker[(_int)EColliderType::Ray][(_int)EColliderType::OBB]		= CollisionHelper::RayObb;
	
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::Point]	= CollisionHelper::PointSphere;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::Ray]		= CollisionHelper::RaySphere;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::Sphere]	= CollisionHelper::SphereSphere;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::AABB]	= CollisionHelper::SphereAabb;
	m_fpCollisionChecker[(_int)EColliderType::Sphere][(_int)EColliderType::OBB]		= CollisionHelper::SphereObb;
	
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::Point]		= CollisionHelper::PointAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::Ray]		= CollisionHelper::RayAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::Sphere]	= CollisionHelper::SphereAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::AABB]		= CollisionHelper::AabbAabb;
	m_fpCollisionChecker[(_int)EColliderType::AABB][(_int)EColliderType::OBB]		= CollisionHelper::AabbObb;
	
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::Point]		= CollisionHelper::PointObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::Ray]		= CollisionHelper::RayObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::Sphere]		= CollisionHelper::SphereObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::AABB]		= CollisionHelper::AabbObb;
	m_fpCollisionChecker[(_int)EColliderType::OBB][(_int)EColliderType::OBB]		= CollisionHelper::ObbObb;
}

void CCollisionManager::InitCollisionMap(void)
{
	for (_uint i = 0; i < m_vCollisionMap.size(); ++i)
	{
		_int numOfLayerToCheck = 0;
		std::wstring varKey = L"numOfLayerToCheck" + std::to_wstring(i);
		GET_CUR_SCENE->GET_VALUE(true, m_dataID, m_objectKey, varKey, numOfLayerToCheck);

		for (_int j = 0; j < numOfLayerToCheck; ++j)
		{
			_int checkLayer = -1;
			varKey = L"Layer" + std::to_wstring(i) + L"_Check" + std::to_wstring(j);
			GET_CUR_SCENE->GET_VALUE(true, m_dataID, m_objectKey, varKey, checkLayer);

			m_vCollisionMap[i].push_back(checkLayer);
		}
	}
	return;
}


