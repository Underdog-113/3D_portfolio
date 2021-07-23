#include "stdafx.h"
#include "PhaseChanger.h"
#include "MapObject2D.h"
#include "Monster.h"
#include "StageControlTower.h"
#include "PhaseControl.h"
#include "MonsterSpawnBeam.h"

_uint CPhaseChanger::m_s_uniqueID = 0;
CPhaseChanger::CPhaseChanger()
{
}


CPhaseChanger::~CPhaseChanger()
{
	OnDestroy();
}

SP(CPhaseChanger) CPhaseChanger::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CPhaseChanger) spInstance(new CPhaseChanger, Engine::SmartDeleter<CPhaseChanger>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPhaseChanger::MakeClone(void)
{
	SP(CPhaseChanger) spClone(new CPhaseChanger, Engine::SmartDeleter<CPhaseChanger>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CPhaseChanger::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Map;
	m_dataID	= UNDEFINED;

	m_addExtra = true;

	m_spCollision	= AddComponent<Engine::CCollisionC>();
	AddComponent<Engine::CDebugC>();
}

void CPhaseChanger::Start(void)
{
	__super::Start();
	
}

void CPhaseChanger::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CPhaseChanger::Update(void)
{
	__super::Update();
	
	

	if (m_timerStart)
	{
		m_spawnTimer += GET_DT;

		_uint enabledEnemy = 0;
		for (auto& monster : m_vMonster)
		{
			if (true == monster->GetIsBoss())
			{
				monster->OnEnable();
			}

			if (monster->GetDeleteThis() || monster->GetIsEnabled())
			{
				++enabledEnemy;
				continue;
			}

			if (monster->GetSpawnTimer() <= m_spawnTimer)
			{
				//빔 생성 or Enabled를 켜서 활성화를 시키든 하면서
				//빔의 몬스터 포인터를 줘요.

				if (false == monster->GetIsBoss())
				{
					SP(CMonsterSpawnBeam) spMonsterSpawnBeam =
						std::dynamic_pointer_cast<CMonsterSpawnBeam>(monster->GetScene()->GetObjectFactory()->AddClone(L"MonsterSpawnBeam", true));
					spMonsterSpawnBeam->SetMonster(monster);
					spMonsterSpawnBeam->GetTransform()->SetPosition(monster->GetTransform()->GetPosition());
					spMonsterSpawnBeam->GetTransform()->AddPositionY(10);
					monster->SetSpawnTimer(FLT_MAX);
				}
			}
		}

		if (enabledEnemy == m_vMonster.size())
			m_timerStart = false;
	}
	if (m_vMonster.size() == 0)
		CStageControlTower::GetInstance()->IncreasePhase();

	if (CStageControlTower::GetInstance()->GetPhaseControl()->GetCurPhase() == m_phaseToDie)
	{
		m_deleteThis = true;
		return;
	}
}

void CPhaseChanger::LateUpdate(void)
{
	__super::LateUpdate();
	
	for (auto& iter = m_vMonster.begin(); iter != m_vMonster.end();)
	{
		if ((*iter)->GetDeleteThis())
		{
			(*iter).reset();
			iter = m_vMonster.erase(iter);
		}
		else
			++iter;
	}
}

void CPhaseChanger::OnDestroy(void)
{
	__super::OnDestroy();
	
	for (auto& restrictLine : m_vRestrictLine)
	{
		restrictLine->SetDeleteThis(true);
		restrictLine.reset();
	}

	m_vRestrictLine.clear();
}

void CPhaseChanger::OnEnable(void)
{
	__super::OnEnable();
	
}

void CPhaseChanger::OnDisable(void)
{
	__super::OnDisable();
	
}

void CPhaseChanger::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	for (auto& restrictLine : m_vRestrictLine)
		restrictLine->SetIsEnabled(true);

	CStageControlTower::GetInstance()->IncreasePhase();
	m_spCollision->SetIsEnabled(false);
	m_timerStart = true;
}

void CPhaseChanger::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CPhaseChanger::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CPhaseChanger::AddRestrictLine(SP(CMapObject2D) spRestrictLine, SP(CStage_Wall) spEffect)
{
	//spRestrictLine->SetIsEnabled(false);
	spRestrictLine->SetWallEffect(spEffect);
	m_vRestrictLine.emplace_back(spRestrictLine);
}

void CPhaseChanger::AddMonster(SP(CMonster) spMonster)
{
	spMonster->SetIsEnabled(false);
	m_vMonster.emplace_back(spMonster);
}

void CPhaseChanger::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
