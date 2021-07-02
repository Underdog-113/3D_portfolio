#include "stdafx.h"
#include "StageControlTower.h"

#include "DamageObjectPool.h"
#include "InputManager.h"
#include "Layer.h"

#include "Valkyrie.h"
#include "Monster.h"
#include "PatternMachineC.h"

#include "UILinker.h"
#include "StatusDealer.h"
#include "ActorController.h"
#include "PhaseControl.h"

#include "OneStagePhaseControl.h"
IMPLEMENT_SINGLETON(CStageControlTower)
void CStageControlTower::Awake(void)
{
}

void CStageControlTower::Start(CreateMode mode)
{
	m_mode = mode;
	if (m_mode != WithoutUI)
		m_pLinker = new CUILinker;
	m_pActorController = new CActorController;
	m_pDealer = new CStatusDealer;


	if (m_mode != WithoutUI)
		m_pLinker->SetControlTower(this);
	m_pActorController->SetControlTower(this);
	m_pDealer->SetControlTower(this);
}


void CStageControlTower::Update(void)
{
	if (m_mode != WithoutUI)
		m_pLinker->UpdateLinker();

	m_pActorController->UpdateController();

	if (m_pPhaseControl)
		m_pPhaseControl->Update();

	if (m_spCurTarget && m_spCurTarget->GetDeleteThis())
	{
		m_spCurTarget.reset();
		m_spCurTarget = nullptr;
	}


	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_1))
		SwitchValkyrie(Wait_1);
	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_2))
		SwitchValkyrie(Wait_2);

	if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_DOWN(KEY_R))
		m_pPhaseControl->ChangePhase((_int)COneStagePhaseControl::EOneStagePhase::StageResult);

	
}

void CStageControlTower::OnDestroy()
{
	if (m_mode != WithoutUI)
	{
		SAFE_DELETE(m_pLinker)
	}
	SAFE_DELETE(m_pActorController)
	SAFE_DELETE(m_pDealer)
	SAFE_DELETE(m_pPhaseControl)
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

void CStageControlTower::ActorControl_SetCurrentMainCam(SP(Engine::CCamera) pCam)
{
	m_pActorController->SetCurrentMainCam(pCam);
}

void CStageControlTower::ActorControl_SetInputLock(bool lock)
{
	m_pActorController->SetInputLock_ByAni(lock);
}

void CStageControlTower::IncreasePhase()
{
	m_pPhaseControl->IncreasePhase();
}

void CStageControlTower::ChangePhase(EOneStagePhase phaseType)
{
	m_pPhaseControl->ChangePhase((_int)phaseType);
}

void CStageControlTower::FindTarget()
{
	Engine::CLayer* pLayer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers()[(_int)ELayerID::Enemy];
	std::vector<SP(Engine::CObject)> monsterList = pLayer->GetGameObjects();

	if (monsterList.empty())
		return;

	int count = 0;
	for (auto& iter : monsterList)
	{
		if (iter->GetIsEnabled())
			++count;
	}

	if (count == 0)
		return;

	// 1. 우선 플레이어와의 거리를 재고 가까운순
	SP(Engine::CObject) spTarget = m_spCurTarget;
	_float minDistance = 5.f;

	_float3 valkyrieForward = m_pCurActor->GetTransform()->GetForward();
	valkyrieForward.y = 0.f;

	_float3 valkyriePos = m_pCurActor->GetTransform()->GetPosition() + valkyrieForward;
	valkyriePos.y = 0.f;
	
	for (auto& iter : monsterList)
	{
		if(!iter->GetIsEnabled())
			continue;

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
		m_pActorController->TargetingOn();

		// ui interaction
		m_pLinker->MonsterInfoSet();
		
		// ui interaction
		m_pLinker->OnTargetMarker();
	}

	
}

void CStageControlTower::HitMonster(Engine::CObject * pValkyrie, Engine::CObject * pMonster, HitInfo info, _float3 hitPoint)
{
	if (!pMonster || pMonster->GetComponent<CPatternMachineC>()->GetOnDie())
		return;

	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);
	CMonster* pM = static_cast<CMonster*>(pMonster);

	// 1. 데미지 교환 ( 죽은거까지 판정 때려주세요 )
	_float damage = 0.f;
	bool isDead = m_pDealer->Damage_VtoM(pV->GetStat(), pM->GetStat(), info.GetDamageRate(), &damage);
	m_pLinker->MonsterHpDown(damage);

	CDamageObjectPool::GetInstance()->AddDamage(
		pMonster, hitPoint,
		_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Blue");

	// 2. 슬라이더 조정

	// 3. 몬스터 히트 패턴으로 ( 위에서 죽었으면 죽은걸로 )
	
	if (isDead)
	{
		// two many things
		pM->MonsterDead();
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
	SP(Engine::CObject) spSoftEffect
		= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MonsterHitEffect", true);
	spSoftEffect->GetComponent<Engine::CGraphicsC>();
	spSoftEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Hit_Yellow");
	spSoftEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Hit_Yellow");
	spSoftEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);

	_float3 monsterPos = pMonster->GetTransform()->GetPosition();
	monsterPos.y += pMonster->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
	_float3 monToHit = hitPoint - monsterPos;
	float len = D3DXVec3Length(&monToHit) * 0.75f;
	D3DXVec3Normalize(&monToHit, &monToHit);

	spSoftEffect->GetTransform()->SetPosition(monsterPos + monToHit * len);

	float randSize = 1.5f + rand() % 2 * 0.5f;
	spSoftEffect->GetTransform()->SetSize(randSize, randSize, randSize);

	// 8. 사운드

}

void CStageControlTower::HitValkyrie(Engine::CObject * pMonster, Engine::CObject * pValkyrie, HitInfo info, _float3 hitPoint)
{
	CMonster* pM = static_cast<CMonster*>(pMonster);
	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);

	// 1. 데미지 교환 ( 죽은거까지 판정 때려주세요 )
	_float damage = 0.f;
	bool isDead = m_pDealer->Damage_MtoV(pM->GetStat(), pV->GetStat(), info.GetDamageRate(), &damage);
	CDamageObjectPool::GetInstance()->AddDamage(
		pValkyrie, hitPoint,
		_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Purple");

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

void CStageControlTower::SwitchValkyrie(Squad_Role role)
{
	if (m_vSquad.size() < 3)
		return;

	m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchOut");

	_float3 pos = m_pCurActor->GetTransform()->GetPosition();
	_float3 rot = m_pCurActor->GetTransform()->GetRotation();
	
	switch (role)
	{
	case CStageControlTower::Wait_1:
	{
		auto pSwapValkyrie = m_vSquad[Actor];
		m_vSquad[Actor] = m_vSquad[Wait_1];
		m_vSquad[Wait_1] = pSwapValkyrie;
		m_pCurActor = static_cast<CValkyrie*>(m_vSquad[Actor].get());
		auto wait1Member = static_cast<CValkyrie*>(m_vSquad[Wait_1].get());

		m_pLinker->SwitchValkyrie(
			CUILinker::Up,
			m_pCurActor->GetStat()->GetType(),
			wait1Member->GetStat()->GetType());

	}
		break;
	case CStageControlTower::Wait_2:
	{
		auto pSwapValkyrie = m_vSquad[Actor];
		m_vSquad[Actor] = m_vSquad[Wait_2];
		m_vSquad[Wait_2] = pSwapValkyrie;
		m_pCurActor = static_cast<CValkyrie*>(m_vSquad[Actor].get());
		auto wait2Member = static_cast<CValkyrie*>(m_vSquad[Wait_2].get());

		m_pLinker->SwitchValkyrie(
			CUILinker::Down,
			m_pCurActor->GetStat()->GetType(),
			wait2Member->GetStat()->GetType());
	}
		break;
	}
	                                                        
	m_pCurActor->GetTransform()->SetPosition(pos);
	m_pCurActor->GetTransform()->SetRotation(rot);

	Engine::GET_MAIN_CAM->SetTarget(m_vSquad[Actor]);

	// 1. 대기 슬롯 이미지 바꿔주고
	// 3. 스킬 ui도
	// 4. 카메라 타겟팅 바꿔주기


	m_pCurActor->SetIsEnabled(true);
	m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchIn");
}
