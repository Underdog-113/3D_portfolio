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
#include "StageCameraMan.h"
#include "TimeSeeker.h"
#include "PhaseControl.h"

#include "OneStagePhaseControl.h"
#include "ThreeStagePhaseControl.h"
#include "MeshShader.h"

#include "TrapObject.h"
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
	m_pCameraMan = new CStageCameraMan;
	m_pTimeSeeker = new CTimeSeeker;

	if (m_mode != WithoutUI)
		m_pLinker->SetControlTower(this);
	m_pActorController->SetControlTower(this);
	m_pDealer->SetControlTower(this);

}


void CStageControlTower::Update(void)
{
	if (m_mode != WithoutUI)
		m_pLinker->UpdateLinker();

	m_pTimeSeeker->UpdateTimeSeeker();

	m_pCameraMan->UpdateCameraMan();

	m_pActorController->UpdateController();

	if (m_pPhaseControl)
		m_pPhaseControl->Update();

	if (m_spCurTarget && m_spCurTarget->GetDeleteThis() || !CBattleUiManager::GetInstance()->IsMonsterStateOn())
	{
		RemoveTarget();
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_1))
		SwitchValkyrie(Wait_1);
	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_2))
		SwitchValkyrie(Wait_2);

	if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_DOWN(KEY_R))
		m_pPhaseControl->ChangePhase((_int)COneStagePhaseControl::EOneStagePhase::StageResult);

	if (GetIsPerfectEvadeMode())
	{
		Engine::CMeshShader* pMeshShader =
			static_cast<Engine::CMeshShader*>(Engine::CShaderManager::GetInstance()->GetShader((_int)Engine::EShaderID::MeshShader));
		pMeshShader->SetAddColor(_float4(0.4f, 0, 0, 0));
	}
	else
	{
		Engine::CMeshShader* pMeshShader =
			static_cast<Engine::CMeshShader*>(Engine::CShaderManager::GetInstance()->GetShader((_int)Engine::EShaderID::MeshShader));
		pMeshShader->SetAddColor(_float4(0, 0, 0, 0));
	}

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
	SAFE_DELETE(m_pCameraMan)
	SAFE_DELETE(m_pTimeSeeker)
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

void CStageControlTower::ActorControl_SetInputLock(bool lock)
{
	m_pActorController->SetInputLock_ByAni(lock);
}

void CStageControlTower::SetCurrentMainCam(SP(Engine::CCamera) pCam)
{
	m_pActorController->SetCurrentMainCam(pCam);
	m_pCameraMan->SetCamera(pCam);
}

void CStageControlTower::IncreasePhase()
{
	m_pPhaseControl->IncreasePhase();
}

void CStageControlTower::ChangePhase(EOneStagePhase phaseType)
{
	m_pPhaseControl->ChangePhase((_int)phaseType);
}

void CStageControlTower::ActAttack()
{
	if (!m_spCurTarget)
		m_pCameraMan->OnAttackDirectionCorrecting();
}

void CStageControlTower::ActEvade()
{
}

bool CStageControlTower::ActSkill()
{
	if (!m_pCurActor->CheckSkillUseable())
		return false;

	m_pCurActor->UseSkill();
	m_pLinker->Skill();
	return true;
}

bool CStageControlTower::ActUltra()
{
	if (!m_pCurActor->CheckUltraUseable())
		return false;

	m_pCurActor->UseUltra();
	m_pLinker->Ultra();
	return true;
}

bool CStageControlTower::FindTarget(HitInfo::CrowdControl cc)
{
	Engine::CLayer* pLayer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers()[(_int)ELayerID::Enemy];
	std::vector<SP(Engine::CObject)> monsterList = pLayer->GetGameObjects();

	if (monsterList.empty())
		return false;

	std::vector<SP(Engine::CObject)> filteredMonsterList;
	int count = 0;
	for (auto& iter : monsterList)
	{
		CMonster* mon = (CMonster*)iter.get();
		if (mon->GetIsEnabled() && !mon->GetComponent<CPatternMachineC>()->GetOnDie())
		{

			switch (cc)
			{
			case _Hit_Info::CC_None:
				++count;
				break;
			case _Hit_Info::CC_Stun:
				++count;
				break;
			case _Hit_Info::CC_Sakura:
			{
				CMonster* pMonster = (CMonster*)iter.get();
				M_Stat* pStat = pMonster->GetStat();

				if (pStat->GetSakuraCounter() > 0)
					filteredMonsterList.emplace_back(iter);
				++count;
			}
				break;
			case _Hit_Info::CC_Airborne:
				++count;
				break;
			default:
				break;
			}
		}

	}

	if (count == 0)
		return false;

	// 1. 우선 플레이어와의 거리를 재고 가까운순
	SP(Engine::CObject) spTarget = nullptr;
	_float minDistance = 5.f;

	_float3 valkyrieForward = m_pCurActor->GetTransform()->GetForward();
	valkyrieForward.y = 0.f;

	_float3 valkyriePos = m_pCurActor->GetTransform()->GetPosition() + valkyrieForward;
	valkyriePos.y = 0.f;
	
	if (!filteredMonsterList.empty())
	{
		// 상태이상 필터링 몬스터
		for (auto& iter : filteredMonsterList)
		{
			if (!iter->GetIsEnabled() || iter->GetComponent<CPatternMachineC>()->GetOnDie())
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
	}
	else
	{
		// 모든 적
		for (auto& iter : monsterList)
		{
			if (!iter->GetIsEnabled() || iter->GetComponent<CPatternMachineC>()->GetOnDie())
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
	}

	if (m_spCurTarget)
	{
		CMonster* pMon = (CMonster*)m_spCurTarget.get();
	}

	if (m_mode == WithoutUI)
		return false;

	if (spTarget && m_spCurTarget == spTarget)
	{
		m_pActorController->TargetingOn();
		m_pCameraMan->SetIsTargeting(true);

		m_pLinker->OnTargetMarker();
		return true;
	}
	else if (spTarget)
	{
		m_spCurTarget = spTarget;

		m_pActorController->TargetingOn();
		m_pCameraMan->SetIsTargeting(true);

		// ui interaction
		m_pLinker->MonsterInfoSet();
				
		// ui interaction
		m_pLinker->OnTargetMarker();

		return true;
	}

	return false;
}

void CStageControlTower::LookTarget()
{
	if(m_spCurTarget)
	m_pActorController->LookHittedDirection(m_spCurTarget->GetTransform()->GetPosition());
}

void CStageControlTower::RemoveTarget()
{
	m_spCurTarget.reset();
	m_spCurTarget = nullptr;
}

void CStageControlTower::HitMonster(Engine::CObject * pValkyrie, Engine::CObject * pMonster, HitInfo info, _float3 hitPoint)
{
	if (!pMonster || pMonster->GetComponent<CPatternMachineC>()->GetOnDie())
		return;

	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);
	CMonster* pM = static_cast<CMonster*>(pMonster);

	// 타격하는 발키리의 타입 설정
	

	// 1. 데미지 교환 ( 죽은거까지 판정 때려주세요 )
	_float damage = 0.f;
	bool isDead = m_pDealer->Damage_VtoM(pV->GetStat(), pM->GetStat(), info.GetDamageRate(), &damage);

	CDamageObjectPool::GetInstance()->AddDamage(
		pMonster, hitPoint,
		_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Blue");

	// 2. 슬라이더 조정
	m_pLinker->MonsterHpDown(damage);

	// 4. 콤보수?

	if (m_mode != WithoutUI)
		m_pLinker->Hit_Up();
	
	// 5. 플레이어 sp 획득
	m_pDealer->SpUp(m_pCurActor->GetStat(), 3.f);

	// 6. 보스면 스턴 게이지 깎아주세요

	// 7. 이펙트
	SP(Engine::CObject) spSoftEffect
		= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MonsterHitEffect", true);
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
	V_Stat::Valkyrie_Type valkyrieType = pV->GetStat()->GetType();
	_TCHAR* fileName = L"";

	switch (valkyrieType)
	{
	case V_Stat::Valkyrie_Type::KIANA:
		fileName = L"KianaAttackHit.wav";
		break;
	case V_Stat::Valkyrie_Type::THERESA:
		fileName = L"TeressaAttackHit.wav";
		break;
	case V_Stat::Valkyrie_Type::SAKURA:
		fileName = L"SakuraAttackHit.wav";
		break;
	}
	Engine::CSoundManager::GetInstance()->StopSound((_uint)pM->GetHitChannelID());
	Engine::CSoundManager::GetInstance()->StartSound(fileName, (_uint)pM->GetHitChannelID());

	// 9. shake
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Low:
		m_pCameraMan->ShakeCamera_Low(hitPoint);
		break;
	case HitInfo::Str_High:
		m_pTimeSeeker->OnAttackImpactSlow();
		break;
	case HitInfo::Str_Airborne:
		m_pTimeSeeker->OnAttackImpactSlow();
		break;
	default:
		break;
	}


	// 3. 몬스터 히트 패턴으로 ( 위에서 죽었으면 죽은걸로 )

	if (isDead)
	{
		pM->MonsterDead();

		if (m_spCurTarget.get() == pM)
		{
			m_pLinker->OffTargetMarker();
			m_pLinker->OffMonsterInfo();
			m_spCurTarget = nullptr;

			FindTarget();
		}

	}
	else
	{
		pM->ApplyHitInfo(info);
	}
}

void CStageControlTower::HitValkyrie(Engine::CObject * pMonster, Engine::CObject * pValkyrie, HitInfo info, _float3 hitPoint)
{
	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);
	_bool isDead = false;
	_float damage = 0.f;

	if (pV->GetIsEvade())
		return;

	// 1. 데미지 교환 ( 죽은거까지 판정 때려주세요 )
	if (pMonster->GetLayerID() == (_int)ELayerID::Map)
	{
		CTrapObject* pT = static_cast<CTrapObject*>(pMonster);
		isDead = m_pDealer->Damage_MtoV(pT->GetStat(), pV->GetStat(), info.GetDamageRate(), &damage);
	}
	else if (pMonster->GetLayerID() == (_int)ELayerID::Enemy)
	{
		CMonster* pM = static_cast<CMonster*>(pMonster);
		isDead = m_pDealer->Damage_MtoV(pM->GetStat(), pV->GetStat(), info.GetDamageRate(), &damage);
	}

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

		m_pActorController->LookHittedDirection(pMonster->GetTransform()->GetPosition());
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
	m_pCurActor->GetComponent<Engine::CMeshC>()->GetRootMotion()->ResetPrevMoveAmount();
	                                                        
	m_pCurActor->GetTransform()->SetPosition(pos);
	m_pCurActor->GetTransform()->SetRotation(rot);
	
	// 1. 대기 슬롯 이미지 바꿔주고
	// 3. 스킬 ui도
	// 4. 카메라 타겟팅 바꿔주기


	m_pCurActor->SetIsEnabled(true);
	m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchIn");

	m_pCameraMan->SetIsSwitching(true);
}

void CStageControlTower::SetCameraMidTake()
{
	m_pCameraMan->SetMidTake();
}

void CStageControlTower::SetCameraFarTake()
{
	m_pCameraMan->SetFarTake();
}

void CStageControlTower::SetCameraCustomTake(_float dstMaxDistance, _float changeSpeed, _float dstXAngle)
{
	m_pCameraMan->SetCustomTake(dstMaxDistance, changeSpeed, dstXAngle);
}

void CStageControlTower::OffCameraTargeting()
{
	m_pCameraMan->SetIsTargeting(false);
}

void CStageControlTower::EndSwitching()
{
	m_pCameraMan->SetIsSwitching(false);
}


void CStageControlTower::OnPerfectEvadeMode()
{
	m_pTimeSeeker->OnPerfectEvadeMode();
}

_bool CStageControlTower::GetIsPerfectEvadeMode()
{
	return m_pTimeSeeker->GetIsPerfectEvadeMode();
}

void CStageControlTower::OnSakuraUltraActive()
{
	m_pTimeSeeker->OnSakuraUltraActive();
}

void CStageControlTower::OffSakuraUltraActive()
{
	m_pTimeSeeker->OffSakuraUltraActive();
}


_float CStageControlTower::GetPlayerDeltaTime()
{
	return m_pTimeSeeker->GetPlayerDeltaTime();
}
