#include "stdafx.h"
#include "StageControlTower.h"

#include "DamageObjectPool.h"
#include "InputManager.h"
#include "Layer.h"

#include "Valkyrie.h"
#include "Monster.h"

#include "UILinker.h"
#include "StatusDealer.h"
#include "ActorController.h"
#include "PhaseControl.h"

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

	if (m_spCurTarget->GetDeleteThis())
	{
		m_spCurTarget.reset();
		m_spCurTarget = nullptr;
	}


	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_1))
		SwitchValkyrie(Wait_1);
	if (Engine::CInputManager::GetInstance()->KeyDown(StageKey_Switch_2))
		SwitchValkyrie(Wait_2);
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

void CStageControlTower::FindTarget()
{
	Engine::CLayer* pLayer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers()[(_int)ELayerID::Enemy];
	std::vector<SP(Engine::CObject)> monsterList = pLayer->GetGameObjects();

	if (monsterList.empty())
		return;

	// 1. �켱 �÷��̾���� �Ÿ��� ��� ������
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

	// 2. ����� ������ ����� ���, �÷��̾� �տ� �ִ� �༮����


	// 3. ������ ���ΰ�, �ٸ��� ���� �ٽ� �缳��

	m_spCurTarget = spTarget;


	if (m_mode == WithoutUI)
		return;

	if (m_spCurTarget)
	{
		/// dkdkdkdkkd


		// ui interaction
		m_pLinker->MonsterInfoSet();
		
		// ui interaction
		m_pLinker->OnTargetMarker();
	}

	
}

void CStageControlTower::HitMonster(Engine::CObject * pValkyrie, Engine::CObject * pMonster, HitInfo info)
{
	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);
	CMonster* pM = static_cast<CMonster*>(pMonster);

	// 1. ������ ��ȯ ( �����ű��� ���� �����ּ��� )
	_float damage = 0.f;
	bool isDead = m_pDealer->Damage_VtoM(pV->GetStat(), pM->GetStat(), info.GetDamageRate(), &damage);
	m_pLinker->MonsterHpDown(damage);

	CDamageObjectPool::GetInstance()->AddDamage(
		pMonster,
		_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Blue");

	// 2. �����̴� ����

	// 3. ���� ��Ʈ �������� ( ������ �׾����� �����ɷ� )
	
	if (isDead)
	{
		// two many things
		pM->MonsterDead();
	}
	else
	{
		pM->ApplyHitInfo(info);
	}	

	// 4. �޺���?

	if (m_mode != WithoutUI)
		m_pLinker->Hit_Up();
	
	// 5. �÷��̾� sp ȹ��

	// 6. ������ ���� ������ ����ּ���

	// 7. ����Ʈ

	// 8. ����

}

void CStageControlTower::HitValkyrie(Engine::CObject * pMonster, Engine::CObject * pValkyrie, HitInfo info)
{
	CMonster* pM = static_cast<CMonster*>(pMonster);
	CValkyrie* pV = static_cast<CValkyrie*>(pValkyrie);

	// 1. ������ ��ȯ ( �����ű��� ���� �����ּ��� )
	_float damage = 0.f;
	bool isDead = m_pDealer->Damage_MtoV(pM->GetStat(), pV->GetStat(), info.GetDamageRate(), &damage);
	CDamageObjectPool::GetInstance()->AddDamage(
		pValkyrie,
		_float3(36, 51, 0), 36, 80.0f, 1, (_int)damage, L"Purple");

	// 2. �����̴� ����
	m_pLinker->PlayerHpSet();

	// 3. �÷��̾� ��Ʈ �������� ( ������ �׾����� �����ɷ� )

	if (isDead)
	{
	}
	else
	{
		pV->ApplyHitInfo(info);
	}

	// 4. ��Ʈ ����Ʈ

	// 5. ����
}

void CStageControlTower::SwitchValkyrie(Squad_Role role)
{
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

	// 1. ��� ���� �̹��� �ٲ��ְ�
	// 3. ��ų ui��
	// 4. ī�޶� Ÿ���� �ٲ��ֱ�


	m_pCurActor->SetIsEnabled(true);
	m_pCurActor->GetComponent<Engine::CStateMachineC>()->ChangeState(L"SwitchIn");
}
