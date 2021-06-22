#include "stdafx.h"
#include "StageControlTower.h"

#include "DamageObjectPool.h"
#include "InputManager.h"
#include "Layer.h"

#include "Valkyrie.h"
#include "Monster.h"

#include "UILinker.h"
#include "StatusDealer.h"

IMPLEMENT_SINGLETON(CStageControlTower)


void CStageControlTower::Awake(void)
{
}

void CStageControlTower::Start(CreateMode mode)
{
	m_pInput = Engine::CInputManager::GetInstance();

	m_mode = mode;
	if (m_mode != WithoutUI)
		m_pLinker = new CUILinker;
	m_pDealer = new CStatusDealer;

	if (m_mode != WithoutUI)
		m_pLinker->SetControlTower(this);
	m_pDealer->SetControlTower(this);
}


void CStageControlTower::Update(void)
{
	MoveControl();
	if (m_mode != WithoutUI)
		StageUIControl();

}

void CStageControlTower::OnDestroy()
{
	if (m_mode != WithoutUI)
		SAFE_DELETE(m_pLinker)
	SAFE_DELETE(m_pDealer)
}

void CStageControlTower::AddSquadMember(SP(Engine::CObject) pValkyrie)
{
	if (m_vSquad.size() == 3)
	{
		MSG_BOX(__FILE__, L"Camera mode enum is broken in LateUpdate");
		ABORT;
	}


	m_vSquad.emplace_back(pValkyrie);

	m_pCurActor = static_cast<CValkyrie*>(m_vSquad[Actor].get());
}


void CStageControlTower::MoveControl()
{
	if (m_inputLock_ByAni)
	{
		ReserveMoveOrder();
	}
	else
	{
		if (!CheckMoveOrder())
			return;
	}

	if (!m_rotateLock)
	{
		RotateCurrentActor();
	}
}

bool CStageControlTower::CheckMoveOrder()
{
	bool isMove = false;

	// up
	if (m_pInput->KeyUp(StageKey_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Left;
		
	}
	if (m_pInput->KeyUp(StageKey_Move_Right))
	{
		m_moveFlag &= ~MoveFlag_Right;
		
	}
	if (m_pInput->KeyUp(StageKey_Move_Forward))
	{
		m_moveFlag &= ~MoveFlag_Forward;
		
	}
	if (m_pInput->KeyUp(StageKey_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Back;
		
	}

	// down
	if (m_pInput->KeyPress(StageKey_Move_Left))
	{
		m_moveFlag &= ~MoveFlag_Right;
		m_moveFlag |= MoveFlag_Left;
		
	}
	if (m_pInput->KeyPress(StageKey_Move_Right))
	{
		m_moveFlag |= MoveFlag_Right;
		m_moveFlag &= ~MoveFlag_Left;
		
	}

	if (m_pInput->KeyPress(StageKey_Move_Forward))
	{
		m_moveFlag |= MoveFlag_Forward;
		m_moveFlag &= ~MoveFlag_Back;
		
	}
	if (m_pInput->KeyPress(StageKey_Move_Back))
	{
		m_moveFlag &= ~MoveFlag_Forward;
		m_moveFlag |= MoveFlag_Back;
		
	}

	if (m_mode != WithoutUI)
		m_pLinker->MoveJoyStick();	// ui interact

	if (!m_moveFlag)
		return false;
	if (m_rotateByTarget)
		return true;

	m_moveOrderDir = ZERO_VECTOR;

	if (m_moveFlag & MoveFlag_Left)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_moveOrderDir -= right;
	}

	if (m_moveFlag & MoveFlag_Right)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_moveOrderDir += right;
	}

	if (m_moveFlag & MoveFlag_Forward)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_moveOrderDir += forward;
	}

	if (m_moveFlag & MoveFlag_Back)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_moveOrderDir -= forward;

	}

	m_moveOrderDir.y = 0.f;
	D3DXVec3Normalize(&m_moveOrderDir, &m_moveOrderDir);

	if (m_prevMoveFlag != m_moveFlag)
		m_rotateLock = false;

	m_prevMoveFlag = m_moveFlag;
	return true;
}

void CStageControlTower::ReserveMoveOrder()
{
	bool isMove = false;

	// up
	if (m_pInput->KeyUp(StageKey_Move_Left))
	{
		m_reserveMoveFlag &= ~MoveFlag_Left;		
	}
	if (m_pInput->KeyUp(StageKey_Move_Right))
	{
		m_reserveMoveFlag &= ~MoveFlag_Right;		
	}
	if (m_pInput->KeyUp(StageKey_Move_Forward))
	{
		m_reserveMoveFlag &= ~MoveFlag_Forward;		
	}
	if (m_pInput->KeyUp(StageKey_Move_Back))
	{
		m_reserveMoveFlag &= ~MoveFlag_Back;
	}

	// down
	if (m_pInput->KeyPress(StageKey_Move_Left))
	{
		m_reserveMoveFlag &= ~MoveFlag_Right;
		m_reserveMoveFlag |= MoveFlag_Left;		
	}
	if (m_pInput->KeyPress(StageKey_Move_Right))
	{
		m_reserveMoveFlag |= MoveFlag_Right;
		m_reserveMoveFlag &= ~MoveFlag_Left;		
	}

	if (m_pInput->KeyPress(StageKey_Move_Forward))
	{
		m_reserveMoveFlag |= MoveFlag_Forward;
		m_reserveMoveFlag &= ~MoveFlag_Back;		
	}
	if (m_pInput->KeyPress(StageKey_Move_Back))
	{
		m_reserveMoveFlag &= ~MoveFlag_Forward;
		m_reserveMoveFlag |= MoveFlag_Back;		
	}

	if (m_mode != WithoutUI)
		m_pLinker->MoveJoyStick();	// ui interact

	if (!m_reserveMoveFlag)
		return;
	if (m_rotateByTarget)
		return;

	m_reserveMoveOrderDir = ZERO_VECTOR;

	if (m_reserveMoveFlag & MoveFlag_Left)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_reserveMoveOrderDir -= right;
	}

	if (m_reserveMoveFlag & MoveFlag_Right)
	{
		_float3 right = m_spCurMainCam->GetTransform()->GetRight();
		right = _float3(right.x, 0.f, right.z);
		D3DXVec3Normalize(&right, &right);
		m_reserveMoveOrderDir += right;
	}

	if (m_reserveMoveFlag & MoveFlag_Forward)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_reserveMoveOrderDir += forward;
	}

	if (m_reserveMoveFlag & MoveFlag_Back)
	{
		_float3 forward = m_spCurMainCam->GetTransform()->GetForward();
		forward = _float3(forward.x, 0.f, forward.z);
		D3DXVec3Normalize(&forward, &forward);
		m_reserveMoveOrderDir -= forward;

	}

	m_reserveMoveOrderDir.y = 0.f;
	D3DXVec3Normalize(&m_reserveMoveOrderDir, &m_reserveMoveOrderDir);

}

void CStageControlTower::RotateCurrentActor()
{
	SP(Engine::CTransformC) pActorTransform = m_pCurActor->GetTransform();
	
	float rotSpeedRate = m_rotSpeedHighRate;

	_float3 actorForward = pActorTransform->GetForward();
	actorForward = _float3(actorForward.x, 0.f, actorForward.z);
	float angleSynchroRate = D3DXVec3Dot(&m_moveOrderDir, &actorForward);

	if (angleSynchroRate > 0.95f)
		rotSpeedRate = m_rotSpeedLowRate;

	_float3 rotAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&rotAxis, &actorForward, &m_moveOrderDir);
	D3DXVec3Normalize(&rotAxis, &rotAxis);
	
	if (rotAxis.y > 0.f)
		m_pCurActor->GetTransform()->AddRotationY(m_rotSpeed * rotSpeedRate * GET_DT);
	else
		m_pCurActor->GetTransform()->AddRotationY(-m_rotSpeed * rotSpeedRate * GET_DT);


	if (angleSynchroRate > 0.99f)
	{
		if (rotAxis.y > 0.f)
			m_pCurActor->GetTransform()->AddRotationY(D3DXToRadian(0.9f));
		else
			m_pCurActor->GetTransform()->AddRotationY(D3DXToRadian(-0.9f));

		m_rotateLock = true;
		m_rotateByTarget = false;
	}

}

void CStageControlTower::SetInputLock_ByAni(bool lock)
{
	m_inputLock_ByAni = lock;
	
	if (lock)
	{
		// start attack
		if (m_moveFlag)
		{
			//move
			m_reserveMoveFlag = m_moveFlag;
			m_prevMoveFlag = m_moveFlag;
		}
		else
		{
			//stop
			m_reserveMoveFlag = m_prevMoveFlag;
			m_prevMoveFlag = 0;
		}
	}
	else
	{
		if (m_reserveMoveFlag)
		{
			if (m_prevMoveFlag != m_reserveMoveFlag)
			{
				// move
				m_rotateLock = false;

				m_moveFlag = m_reserveMoveFlag;
				m_moveOrderDir = m_reserveMoveOrderDir;
			}
		}
		else
		{
			// stop
			m_rotateLock = true;
			m_moveFlag = 0;
			m_prevMoveFlag = 0;
		}
	}
}

void CStageControlTower::StageUIControl()
{
	// target hp

	// wp skill cool
	// ult cool

	// player hp
	m_pLinker->PlayerHpSet();
	// player sp
	m_pLinker->PlayerSpSet();


	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
		m_pLinker->PlayerChange();

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
		m_pLinker->PlayerChange_Test();

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_TAB))
		m_pDealer->HpDown_Valkyrie(m_pCurActor->GetStat(), 33.f);

}

void CStageControlTower::FindTarget()
{
	Engine::CLayer* pLayer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers()[(_int)ELayerID::Enemy];
	std::vector<SP(Engine::CObject)> monsterList = pLayer->GetGameObjects();

	if (monsterList.empty())
		return;

	// 1. 우선 플레이어와의 거리를 재고 가까운순
	SP(Engine::CObject) spTarget = m_spCurTarget;
	_float minDistance = 5.f;

	_float3 valkyriePos = m_pCurActor->GetTransform()->GetPosition();
	valkyriePos.y = 0.f;
	
	for (auto& iter : monsterList)
	{
		_float3 monsterPos = iter->GetTransform()->GetPosition();
		monsterPos.y = 0.f;

		_float distance = D3DXVec3Length(&(valkyriePos - monsterPos));
		if (distance < minDistance)
		{
			minDistance = distance;
			spTarget = iter;
		}
	}

	// 2. 가까운 정도가 비슷할 경우, 플레이어 앞에 있는 녀석으로


	// 3. 같으면 냅두고, 다르면 방향 다시 재설정

	m_spCurTarget = spTarget;


	if (m_mode == WithoutUI)
		return;

	if (m_spCurTarget)
	{
		// ui interaction
		m_pLinker->MonsterInfoSet();
		
		m_rotateLock = false;
		m_rotateByTarget = true;
		_float3 targetPos = m_spCurTarget->GetTransform()->GetPosition();
		targetPos.y = 0.f;
		m_moveOrderDir = targetPos - valkyriePos;
		D3DXVec3Normalize(&m_moveOrderDir, &m_moveOrderDir);

		// ui interaction
		m_pLinker->OnTargetMarker();
	}

	
}

void CStageControlTower::HitMonster(Engine::CObject * pValkyrie, Engine::CObject * pMonster, HitInfo info)
{
	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);
	CMonster* pM = static_cast<CMonster*>(pMonster);

	// 1. 데미지 교환 ( 죽은거까지 판정 때려주세요 )
	_float damage = 0.f;
	bool isDead = m_pDealer->Damage_VtoM(pV->GetStat(), pM->GetStat(), info.GetDamageRate(), &damage);
	m_pLinker->MonsterHpDown(damage);

	CDamageObjectPool::GetInstance()->AddDamage(
		pMonster,
		_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Blue");

	// 2. 슬라이더 조정

	// 3. 몬스터 히트 패턴으로 ( 위에서 죽었으면 죽은걸로 )
	
	if (isDead)
	{
		// two many things
	}
	else
	{
		pM->ApplyHitInfo(info);
	}	

	// 4. 콤보수?

	if (m_mode != WithoutUI)
		m_pLinker->Hit_Up();
	
	// 5. 플레이어 sp 획득

	// 6. 보스면 스턴 게이지 깎아주세요

	// 7. 이펙트

	// 8. 사운드

}

void CStageControlTower::HitValkyrie(Engine::CObject * pMonster, Engine::CObject * pValkyrie, HitInfo info)
{
	CMonster* pM = static_cast<CMonster*>(pMonster);
	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);

	// 1. 데미지 교환 ( 죽은거까지 판정 때려주세요 )
	_float damage = 0.f;
	bool isDead = m_pDealer->Damage_MtoV(pM->GetStat(), pV->GetStat(), info.GetDamageRate(), &damage);
	//CDamageObjectPool::GetInstance()->AddDamage(
	//	pMonster->GetTransform()->GetPosition(),
	//	_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Red");

	// 2. 슬라이더 조정
	m_pLinker->PlayerHpSet();

	// 3. 플레이어 히트 패턴으로 ( 위에서 죽었으면 죽은걸로 )

	if (isDead)
	{
	}
	else
	{
		pV->ApplyHitInfo(info);
	}

	// 4. 히트 이펙트

	// 5. 사운드
}
