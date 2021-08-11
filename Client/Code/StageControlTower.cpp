#include "stdafx.h"
#include "StageControlTower.h"

#include "ClientScene.h"
#include "MainRoomScene.h"

#include "Scene.h"
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
#include "MovieDirector.h"
#include "TimeSeeker.h"
#include "PhaseControl.h"

#include "OneStagePhaseControl.h"
#include "ThreeStagePhaseControl.h"
#include "MeshShader.h"

#include "TrapObject.h"
#include "BronyaBullet.h"
#include "BronyaGrenade.h"

IMPLEMENT_SINGLETON(CStageControlTower)

#pragma region EngineFunc

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
	m_pMovieDirector = new CMovieDirector;
	m_pTimeSeeker = new CTimeSeeker;

	if (m_mode != WithoutUI)
		m_pLinker->SetControlTower(this);
	m_pActorController->SetControlTower(this);
	m_pDealer->SetControlTower(this);

	Engine::CInputManager::GetInstance()->SetKeyInputEnabled(true);

	m_time = 5.0f;
}

void CStageControlTower::Init()
{
	switch (static_cast<CValkyrie*>(m_vSquad[Actor].get())->GetStat()->GetType())
	{
	case V_Stat::Valkyrie_Type::KIANA:
		CBattleUiManager::GetInstance()->PlayerChange(
			L"Skill_Kiana_PT_001",
			L"Skill_Kiana_PT_003",
			L"Skill_Kiana_PT_004",
			L"Skill_Kiana_Weapon_09",
			10,
			100,
			0, 0, 0); // 회피,궁,아이템스킬
		break;
	case V_Stat::Valkyrie_Type::THERESA:
		CBattleUiManager::GetInstance()->PlayerChange(
			L"Skill_Theresa_0",
			L"Skill_Theresa_1",
			L"Skill_Theresa_2",
			L"Skill_Theresa_3",
			20,
			100,
			0, 0, 0); // 회피,궁,아이템스킬
		CBattleUiManager::GetInstance()->SpecialUICanvasOn();
		break;
	case V_Stat::Valkyrie_Type::SAKURA:
		CBattleUiManager::GetInstance()->PlayerChange(
			L"Skill_Sakura_0",
			L"Skill_Sakura_1",
			L"Skill_Sakura_2",
			L"Skill_Sakura_3",
			15,
			100,
			0, 0, 0); // 회피,궁,아이템스킬
		break;
	default:
		break;
	}

	if (m_vSquad.size() > 1)
	{
		CValkyrie* wait1member = static_cast<CValkyrie*>(m_vSquad[CStageControlTower::Wait_1].get());
		V_Stat* stat = wait1member->GetStat();

		auto valkyrieType = stat->GetType();
		switch (valkyrieType)
		{
		case V_Stat::Valkyrie_Type::KIANA:
			CBattleUiManager::GetInstance()->WaitingPlayerState(
				0,
				L"Kiana_Battle",
				L"AvatarShengWu",
				stat->GetCurHp() / stat->GetMaxHp() * 100.f,
				stat->GetCurSp() / stat->GetMaxSp() * 100.f,
				0.f);
			break;
		case V_Stat::Valkyrie_Type::THERESA:
			CBattleUiManager::GetInstance()->WaitingPlayerState(
				0,
				L"Teresa_Battle",
				L"AvatarJiXie",
				stat->GetCurHp() / stat->GetMaxHp() * 100.f,
				stat->GetCurSp() / stat->GetMaxSp() * 100.f,
				0.f);
			CBattleUiManager::GetInstance()->SpecialUICanvasOff();
			break;
		case V_Stat::Valkyrie_Type::SAKURA:
			CBattleUiManager::GetInstance()->WaitingPlayerState(
				0,
				L"Sakura_Battle",
				L"AvatarYiNeng",
				stat->GetCurHp() / stat->GetMaxHp() * 100.f,
				stat->GetCurSp() / stat->GetMaxSp() * 100.f,
				0.f);
			break;
		default:
			break;
		}
	}
	if (m_vSquad.size() > 2)
	{
		CValkyrie* wait2member = static_cast<CValkyrie*>(m_vSquad[CStageControlTower::Wait_2].get());
		V_Stat* stat = wait2member->GetStat();

		auto valkyrieType = stat->GetType();
		switch (valkyrieType)
		{
		case V_Stat::Valkyrie_Type::KIANA:
			CBattleUiManager::GetInstance()->WaitingPlayerState(
				1,
				L"Kiana_Battle",
				L"AvatarShengWu",
				stat->GetCurHp() / stat->GetMaxHp() * 100.f,
				stat->GetCurSp() / stat->GetMaxSp() * 100.f,
				0.f);
			break;
		case V_Stat::Valkyrie_Type::THERESA:
			CBattleUiManager::GetInstance()->WaitingPlayerState(
				1,
				L"Teresa_Battle",
				L"AvatarJiXie",
				stat->GetCurHp() / stat->GetMaxHp() * 100.f,
				stat->GetCurSp() / stat->GetMaxSp() * 100.f,
				0.f);
			CBattleUiManager::GetInstance()->SpecialUICanvasOff();
			break;
		case V_Stat::Valkyrie_Type::SAKURA:
			CBattleUiManager::GetInstance()->WaitingPlayerState(
				1,
				L"Sakura_Battle",
				L"AvatarYiNeng",
				stat->GetCurHp() / stat->GetMaxHp() * 100.f,
				stat->GetCurSp() / stat->GetMaxSp() * 100.f,
				0.f);
			break;
		default:
			break;
		}

	}
}

void CStageControlTower::Update(void)
{
	if (!m_isInit)
	{
		Init();
		m_isInit = true;
	}

	if (Engine::IMKEY_PRESS(KEY_SHIFT) && Engine::IMKEY_DOWN(KEY_Q))
	{
		cheat_eternal = !cheat_eternal;
	}

	if (m_mode != WithoutUI)
		m_pLinker->UpdateLinker();

	CheckTargetAirBorne();

	m_pTimeSeeker->UpdateTimeSeeker();

	m_pMovieDirector->UpdateDirector();
	m_pCameraMan->UpdateCameraMan();

	m_pActorController->UpdateController();

	if (m_pPhaseControl)
		m_pPhaseControl->Update();

	if (m_spCurTarget && m_spCurTarget->GetDeleteThis() || !CBattleUiManager::GetInstance()->IsMonsterStateOn())
	{
		RemoveTarget();
	}

	WaitMemberCooltimeUpdate();

	ActSwitching();

	SettingEnvironmentColor();
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
		SAFE_DELETE(m_pMovieDirector)
}

#pragma endregion

#pragma region SettingFunc

SP(Engine::CObject) CStageControlTower::SettingSquad(Engine::CScene * pCurScene)
{
	auto vSquad = CDataManager::GetInstance()->FindSquadData()->GetValkyriesList();

	SP(Engine::CObject) spValkyrie = CreateValkyrie(pCurScene, vSquad[0]);
	AddSquadMember(spValkyrie);


	if (vSquad.size() > 1)
	{
		SP(Engine::CObject) spWaitValkyrie = CreateValkyrie(pCurScene, vSquad[1]);
		static_cast<CValkyrie*>(spWaitValkyrie.get())->SetIsWait(true);
		AddSquadMember(spWaitValkyrie);
	}
	if (vSquad.size() > 2)
	{
		SP(Engine::CObject) spWaitValkyrie = CreateValkyrie(pCurScene, vSquad[2]);
		static_cast<CValkyrie*>(spWaitValkyrie.get())->SetIsWait(true);
		AddSquadMember(spWaitValkyrie);
	}

	return spValkyrie;
}

SP(Engine::CObject) CStageControlTower::CreateValkyrie(Engine::CScene * pCurScene, CValkyrieStatusData* pStatData)
{
	std::wstring name = pStatData->GetName();

	if (!wcscmp(name.c_str(), L"키아나·카스라나"))
	{
		SP(Engine::CObject) spKianaClone = pCurScene->GetObjectFactory()->AddClone(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");
		// 		V_WarshipStat warshipStat;
		// 		warshipStat.SetLevel(pStatData->GetLevel());
		// 		warshipStat.SetWeaponAtk(pStatData->GetWeaponData()->GetDamage());
		// 		warshipStat.SetWeaponCrt(pStatData->GetWeaponData()->GetHoesim());
		// 
		// 		CValkyrie* pValkyrie = static_cast<CValkyrie*>(spKianaClone.get());
		V_WarshipStat warshipStat;
		warshipStat.SetLevel(pStatData->GetLevel() + Kiana_Bonus_Level);

		V_Stat* pStat = new V_Kiana_Stat;
		pStat->SetupStatus(&warshipStat);

		((CValkyrie*)spKianaClone.get())->SetStat(pStat);

		return spKianaClone;
	}
	else if (!wcscmp(name.c_str(), L"테레사·아포칼립스"))
	{
		SP(Engine::CObject) spTheresaClone = pCurScene->GetObjectFactory()->AddClone(L"Theresa", true, (_uint)ELayerID::Player, L"Theresa");

		V_WarshipStat warshipStat;
		warshipStat.SetLevel(pStatData->GetLevel() + Theresa_Bonus_Level);

		V_Stat* pStat = new V_Kiana_Stat;
		pStat->SetupStatus(&warshipStat);

		((CValkyrie*)spTheresaClone.get())->SetStat(pStat);
		return spTheresaClone;
	}
	else if (!wcscmp(name.c_str(), L"야에 사쿠라"))
	{
		SP(Engine::CObject) spSakuraClone = pCurScene->GetObjectFactory()->AddClone(L"Sakura", true, (_uint)ELayerID::Player, L"Sakura");

		V_WarshipStat warshipStat;
		warshipStat.SetLevel(pStatData->GetLevel() + Sakura_Bonus_Level);

		V_Stat* pStat = new V_Kiana_Stat;
		pStat->SetupStatus(&warshipStat);

		((CValkyrie*)spSakuraClone.get())->SetStat(pStat);
		return spSakuraClone;
	}
	else
	{
		MSG_BOX(__FILE__, L"Squad name errrrror");
		ABORT;
	}


	return nullptr;
}

void CStageControlTower::AddSquadMember(SP(Engine::CObject) pValkyrie)
{
	if (m_vSquad.size() == 3)
	{
		MSG_BOX(__FILE__, L"sqaud fullll");
		ABORT;
	}


	m_vSquad.emplace_back(pValkyrie);

	m_pCurActor = static_cast<CValkyrie*>(m_vSquad[Actor].get());
}

void CStageControlTower::SetCurrentMainCam(SP(Engine::CCamera) pCam)
{
	m_pActorController->SetCurrentMainCam(pCam);
	m_pCameraMan->SetCamera(pCam);
}

void CStageControlTower::ActorControl_SetInputLock(bool lock)
{
	m_pActorController->SetInputLock_ByAni(lock);
}

#pragma endregion

#pragma region PlayerInput

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

void CStageControlTower::ActSwitching()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_1))
	{
		if (m_vSquad.size() > 1)
		{
			CValkyrie* pValkyrie = (CValkyrie*)m_vSquad[Wait_1].get();
			if (!pValkyrie->GetIsDead() && pValkyrie->CheckSwitchable())
			{
				SwitchValkyrie(Wait_1);
				m_pLinker->SkillUI_SwitchSetting();
				((CValkyrie*)m_vSquad[Wait_1].get())->SetSwitchTimer(0.f);
			}
		}

	}
	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_2))
	{
		if (m_vSquad.size() > 2)
		{
			CValkyrie* pValkyrie = (CValkyrie*)m_vSquad[Wait_2].get();
			if (!pValkyrie->GetIsDead() && pValkyrie->CheckSwitchable())
			{
				SwitchValkyrie(Wait_2);
				m_pLinker->UltraUI_SwitchSetting();
				((CValkyrie*)m_vSquad[Wait_2].get())->SetSwitchTimer(0.f);
			}
		}
	}
}

void CStageControlTower::SwitchValkyrie(Squad_Role role)
{
	_float3 pos = m_pCurActor->GetTransform()->GetPosition();
	_float3 rot = m_pCurActor->GetTransform()->GetRotation();

	switch (role)
	{
	case CStageControlTower::Wait_1:
	{
		m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchOut");

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
		m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchOut");

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

	m_pCurActor->SetIsEnabled(true);
	m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchIn");
	if (!m_isQTEUsed && m_isQTESwitch)
	{
		CMonster* pMonster = (CMonster*)m_spCurTarget.get();

		_float3 curTargetPos = pMonster->GetTransform()->GetPosition();
		_float3 dir = m_pCurActor->GetTransform()->GetPosition() - curTargetPos;
		dir.y = 0.f;
		D3DXVec3Normalize(&dir, &dir);

		_float colRadius = m_pCurActor->GetHitbox()->GetRadiusBS() * 1.25f + pMonster->GetHitBox()->GetRadiusBS() * 1.25f;

		m_pCurActor->GetTransform()->SetPosition(curTargetPos + dir * colRadius);

		m_pActorController->LookHittedDirection(curTargetPos);

		OnSlowExceptPlayer();
		m_pCurActor->SetIsQTESwitch(true);
		m_isQTEUsed = true;
		m_isQTESwitch = false;
		m_pLinker->QTEButtonEffectOff();
	}

	m_pCameraMan->SetIsSwitching(true);
}

void CStageControlTower::BattonTouch()
{
	if (m_vSquad.size() > 1)
	{
		if (m_vSquad.size() > 2)
		{
			BattonTouch_3Member();
		}
		else
		{
			BattonTouch_2Member();
		}
	}

}

void CStageControlTower::BattonTouch_2Member()
{
	_float3 pos = m_pCurActor->GetTransform()->GetPosition();
	_float3 rot = m_pCurActor->GetTransform()->GetRotation();

	auto wait1Member = static_cast<CValkyrie*>(m_vSquad[Wait_1].get());

	if (wait1Member->GetIsDead())
	{
		// game over
	}
	else
	{
		auto pSwapValkyrie = m_vSquad[Actor];
		m_vSquad[Actor] = m_vSquad[Wait_1];
		m_vSquad[Wait_1] = pSwapValkyrie;

		m_pCurActor = static_cast<CValkyrie*>(m_vSquad[Actor].get());
		auto pWait1 = static_cast<CValkyrie*>(m_vSquad[Wait_1].get());

		m_pLinker->SwitchValkyrie_Actor(m_pCurActor->GetStat()->GetType());
		m_pLinker->SwitchValkyrie_UpSlot(pWait1->GetStat()->GetType());
	}

	m_pCurActor->GetComponent<Engine::CMeshC>()->GetRootMotion()->ResetPrevMoveAmount();

	m_pCurActor->GetTransform()->SetPosition(pos);
	m_pCurActor->GetTransform()->SetRotation(rot);

	m_pCurActor->SetIsEnabled(true);
	m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchIn");

	m_pCameraMan->SetIsSwitching(true);
}

void CStageControlTower::BattonTouch_3Member()
{
	_float3 pos = m_pCurActor->GetTransform()->GetPosition();
	_float3 rot = m_pCurActor->GetTransform()->GetRotation();

	auto wait1Member = static_cast<CValkyrie*>(m_vSquad[Wait_1].get());
	auto wait2Member = static_cast<CValkyrie*>(m_vSquad[Wait_2].get());

	if (wait1Member->GetIsDead())
	{
		// game over
	}
	else if (wait2Member->GetIsDead())
	{
		auto pSwapValkyrie = m_vSquad[Actor];
		m_vSquad[Actor] = m_vSquad[Wait_1];
		m_vSquad[Wait_1] = pSwapValkyrie;
		m_pCurActor = static_cast<CValkyrie*>(m_vSquad[Actor].get());
		auto pWait1 = static_cast<CValkyrie*>(m_vSquad[Wait_1].get());

		m_pLinker->SwitchValkyrie_Actor(m_pCurActor->GetStat()->GetType());
		m_pLinker->SwitchValkyrie_UpSlot(pWait1->GetStat()->GetType());
	}
	else
	{
		auto pSwapValkyrie = m_vSquad[Actor];
		m_vSquad[Actor] = m_vSquad[Wait_1];
		m_vSquad[Wait_1] = m_vSquad[Wait_2];
		m_vSquad[Wait_2] = pSwapValkyrie;

		m_pCurActor = static_cast<CValkyrie*>(m_vSquad[Actor].get());
		auto pWait1 = static_cast<CValkyrie*>(m_vSquad[Wait_1].get());
		auto pWait2 = static_cast<CValkyrie*>(m_vSquad[Wait_2].get());

		m_pLinker->SwitchValkyrie_Actor(m_pCurActor->GetStat()->GetType());
		m_pLinker->SwitchValkyrie_UpSlot(pWait1->GetStat()->GetType());
		m_pLinker->SwitchValkyrie_DownSlot(pWait2->GetStat()->GetType());
	}

	m_pCurActor->GetComponent<Engine::CMeshC>()->GetRootMotion()->ResetPrevMoveAmount();

	m_pCurActor->GetTransform()->SetPosition(pos);
	m_pCurActor->GetTransform()->SetRotation(rot);

	m_pCurActor->SetIsEnabled(true);
	m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchIn");

	m_pCameraMan->SetIsSwitching(true);
}

void CStageControlTower::WaitMemberCooltimeUpdate()
{
	if (m_vSquad.size() > 1)
	{
		static_cast<CValkyrie*>(m_vSquad[Wait_1].get())->CoolTimeUpdate();
		if (m_vSquad.size() > 2)
		{
			static_cast<CValkyrie*>(m_vSquad[Wait_2].get())->CoolTimeUpdate();
		}
	}
}

#pragma endregion

#pragma region StageSystem

bool CStageControlTower::FindTarget(HitInfo::CrowdControl cc)
{
	Engine::CLayer* pLayer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers()[(_int)ELayerID::Enemy];
	std::vector<SP(Engine::CObject)> monsterList = pLayer->GetGameObjects();

	if (monsterList.empty())
		return false;

	std::vector<SP(Engine::CObject)> filteredMonsterList;
	_uint sakuraCounterHigh = 0;
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
				{
					if (pStat->GetSakuraCounter() > sakuraCounterHigh)
					{
						sakuraCounterHigh = pStat->GetSakuraCounter();
					}
					filteredMonsterList.emplace_back(iter);
				}
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
	D3DXVec3Normalize(&valkyrieForward, &valkyrieForward);

	_float3 valkyriePos = m_pCurActor->GetTransform()->GetPosition() + valkyrieForward * 0.2f;
	valkyriePos.y = 0.f;

	if (!filteredMonsterList.empty())
	{
		// 상태이상 필터링 몬스터
		for (auto& iter : filteredMonsterList)
		{
			if (!iter->GetIsEnabled() || iter->GetComponent<CPatternMachineC>()->GetOnDie())
				continue;

			CMonster* pMonster = (CMonster*)iter.get();

			_float3 monsterPos = pMonster->GetTransform()->GetPosition();
			monsterPos.y = 0.f;

			_float distance = D3DXVec3Length(&(valkyriePos - monsterPos));
			if (distance < minDistance && pMonster->GetStat()->GetSakuraCounter() == sakuraCounterHigh)
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

		CBattleUiManager::GetInstance()->MonsterStateTimerReset();
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
	if (m_spCurTarget)
		m_pActorController->LookHittedDirection(m_spCurTarget->GetTransform()->GetPosition());
}

void CStageControlTower::RemoveTarget()
{
	m_spCurTarget.reset();
	m_spCurTarget = nullptr;
}

void CStageControlTower::CheckTargetAirBorne()
{
	if (m_isQTEUsed)
	{
		m_QTEOnTimer += GET_PLAYER_DT;
		if (m_QTEOnTimer > 4.f)
		{
			m_QTEOnTimer = 0.f;
			m_isQTEUsed = false;
		}
		return;
	}

	if (!m_spCurTarget)
	{
		m_pLinker->QTEButtonEffectOff();
		m_isQTESwitch = false;
		return;
	}
	else
	{
		CMonster* mon = (CMonster*)m_spCurTarget.get();
		if (!mon->GetIsEnabled() || mon->GetComponent<CPatternMachineC>()->GetOnDie())
		{
			m_pLinker->QTEButtonEffectOff();
			m_isQTESwitch = false;
			return;
		}
	}

	CMonster* pM = static_cast<CMonster*>(m_spCurTarget.get());

	if (pM->GetComponent<CPatternMachineC>()->GetOnAirBorne())
	{
		m_pLinker->QTEButtonEffectOn();
		m_isQTESwitch = true;
	}
	else
	{
		m_pLinker->QTEButtonEffectOff();
		m_isQTESwitch = false;
	}

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

		}

		if (m_pCurActor->GetStat()->GetType() == V_Stat::THERESA)
		{
			CBattleUiManager::GetInstance()->SpecialUIUp();
			CBattleUiManager::GetInstance()->SpecialUIUp();
		}
	}
	else
	{
		pM->ApplyHitInfo(info);
		CBattleUiManager::GetInstance()->BreakGaugeDown(info.GetBreakDamage());
	}
}

void CStageControlTower::HitValkyrie(Engine::CObject * pMonster, Engine::CObject * pValkyrie, HitInfo info, _float3 hitPoint)
{
	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);
	_bool isDead = false;
	_float damage = 0.f;

	if (pV->GetIsEvade())
		return;
	if (pV->GetIsDead())
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
	else if (pMonster->GetLayerID() == (_int)ELayerID::Prop)
	{
		if (0 == wcscmp(pMonster->GetObjectKey().c_str(), L"BronyaBullet"))
		{
			CBronyaBullet* pM = static_cast<CBronyaBullet*>(pMonster);
			isDead = m_pDealer->Damage_MtoV(pM->GetStat(), pV->GetStat(), info.GetDamageRate(), &damage);
		}
		else
		{
			CBronyaGrenade* pM = static_cast<CBronyaGrenade*>(pMonster);
			isDead = m_pDealer->Damage_MtoV(pM->GetStat(), pV->GetStat(), info.GetDamageRate(), &damage);
		}

	}

	CDamageObjectPool::GetInstance()->AddDamage(
		pValkyrie, hitPoint,
		_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Purple");

	// 2. 슬라이더 조정
	m_pLinker->PlayerHpSet();

	// 3. 플레이어 히트 패턴으로 ( 위에서 죽었으면 죽은걸로 )

	if (cheat_eternal)
	{
		pV->ApplyHitInfo(info);
		m_pActorController->LookHittedDirection(pMonster->GetTransform()->GetPosition());
	}
	else
	{
		if (isDead)
		{
			pV->GetComponent<Engine::CStateMachineC>()->ChangeState(L"Die");
			pV->SetIsDead(true);
		}
		else
		{
			pV->ApplyHitInfo(info);

			m_pActorController->LookHittedDirection(pMonster->GetTransform()->GetPosition());
		}
	}


	// 4. 히트 이펙트


	// 5. 사운드

}

void CStageControlTower::IncreasePhase()
{
	m_pPhaseControl->IncreasePhase();
}

void CStageControlTower::ChangePhase(EOneStagePhase phaseType)
{
	m_pPhaseControl->ChangePhase((_int)phaseType);
}


#pragma endregion

#pragma region ForMember


void CStageControlTower::SetCameraMidShot()
{
	m_pCameraMan->SetMidShot();
}

void CStageControlTower::SetCameraFarShot()
{
	m_pCameraMan->SetFarShot();
}

void CStageControlTower::SetCameraCustomShot(_float dstMaxDistance, _float changeSpeed, _float dstXAngle)
{
	m_pCameraMan->SetCustomShot(dstMaxDistance, changeSpeed, dstXAngle);
}

void CStageControlTower::OffCameraTargeting()
{
	m_pCameraMan->SetIsTargeting(false);
}

void CStageControlTower::EndSwitching()
{
	m_pCameraMan->SetIsSwitching(false);
}

void CStageControlTower::SetVertCorrecting(_bool val)
{
	m_pCameraMan->SetIsVertCorrecting(val);
}


void CStageControlTower::OnPerfectEvadeMode()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)EChannelID::PLAYEREFFECT_CH2);
	Engine::CSoundManager::GetInstance()->StartSound(L"PerpectEvade.wav", (_uint)EChannelID::PLAYEREFFECT_CH2);
	m_pTimeSeeker->OnPerfectEvadeMode();
}

_bool CStageControlTower::GetIsPerfectEvadeMode()
{
	return m_pTimeSeeker->GetIsPerfectEvadeMode();
}

void CStageControlTower::OnSakuraUltraActive()
{
	m_pTimeSeeker->OnSlowExceptPlayer();
}

void CStageControlTower::OffSakuraUltraActive()
{
	m_pTimeSeeker->OffSlowExceptPlayer();
}

void CStageControlTower::OnSlowExceptPlayer()
{
	m_pTimeSeeker->OnSlowExceptPlayer();
}

void CStageControlTower::OffSlowExceptPlayer()
{
	m_pTimeSeeker->OffSlowExceptPlayer();
}

void CStageControlTower::SettingEnvironmentColor()
{
	_float4 color = m_startEnvColor;

	if (m_envColorChange)
	{
		m_envColorTimer += GET_PLAYER_DT;
		if (m_envColorTimer > m_envColorDuration)
		{
			color = m_dstEnvColor;
			m_startEnvColor = m_dstEnvColor;
			m_envColorChange = false;
		}
		else
		{
			color =
			{
				GetLerpFloat(m_startEnvColor.x, m_dstEnvColor.x, m_envColorTimer / m_envColorDuration),
				GetLerpFloat(m_startEnvColor.y, m_dstEnvColor.y, m_envColorTimer / m_envColorDuration),
				GetLerpFloat(m_startEnvColor.z, m_dstEnvColor.z, m_envColorTimer / m_envColorDuration),
				GetLerpFloat(m_startEnvColor.w, m_dstEnvColor.w, m_envColorTimer / m_envColorDuration)
			};


		}
	}

	Engine::CMeshShader* pMeshShader =
		static_cast<Engine::CMeshShader*>(Engine::CShaderManager::GetInstance()->GetShader((_int)Engine::EShaderID::MeshShader));
	pMeshShader->SetMultColor(color);
}

void CStageControlTower::SetEnvType(Env_Type envType)
{
	m_envColorChange = true;
	m_envType = envType;
	m_envColorTimer = 0.f;

	_float colorRatio = 0.f;

	switch (envType)
	{
	case CStageControlTower::NoColoring:
		m_envColorDuration = 0.25f;
		m_dstEnvColor = _float4(1.f, 1.f, 1.f, 1.f);
		break;
	case CStageControlTower::TheresaUlt:
		m_envColorDuration = 0.5f;
		colorRatio = 1.f;
		//m_dstEnvColor = _float4(0.863f * colorRatio, 0.078f * colorRatio, 0.235f * colorRatio, 1.f);
		m_dstEnvColor = _float4(1.5f, 0.7f, 0.7f, 1.f);
		break;
	case CStageControlTower::SakuraUlt:
		m_envColorDuration = 0.5f;
		colorRatio = 1.f;
		//m_dstEnvColor = _float4(0.635f * colorRatio, 0.392f * colorRatio, 0.435f * colorRatio, 1.f);
		m_dstEnvColor = _float4(1.1f, 0.8f, 0.8f, 1.f);
		break;
	case CStageControlTower::PerfectEvade:
		m_envColorDuration = 0.5f;
		colorRatio = 2.f;
		//m_dstEnvColor = _float4(0.024f * colorRatio, 0.075f * colorRatio, 0.341f * colorRatio, 1.f);
		m_dstEnvColor = _float4(0.7f, 0.7f, 1.1f, 1.f);
		break;
	default:
		break;
	}

}

_float CStageControlTower::GetPlayerDeltaTime()
{
	return m_pTimeSeeker->GetPlayerDeltaTime();
}

void CStageControlTower::SetDirectorMode(bool value)
{
	m_pActorController->SetDirectorMode(value);
	m_pCameraMan->SetDirectorControl(value);
}


#pragma endregion
