#include "stdafx.h"
#include "OneStageScene.h"

#include "Loading.h"

#include "DamageObjectPool.h"
#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"

// import from jongscene
#include "Include_ForTest.h"

#include "OneStagePhaseControl.h"

#include "Monster.h"

COneStageScene::COneStageScene()
{
}


COneStageScene::~COneStageScene()
{
}

CClientScene* COneStageScene::Create(void)
{
	COneStageScene* pInstance = new COneStageScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void COneStageScene::Free(void)
{
	OnDestroy();
	delete this;
}

void COneStageScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
	m_pControlTower->SetPhaseControl(new COneStagePhaseControl);
	m_pControlTower->GetPhaseControl()->SetControlTower(m_pControlTower);
}

void COneStageScene::Start(void)
{
	__super::Start();

	SetupFromLoader();
	SetupMembers();

	m_pBattleUIManager = CBattleUiManager::GetInstance();
	m_pBattleUIManager->Start(this);


}

void COneStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void COneStageScene::Update(void)
{
	__super::Update();

	if (Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	m_pControlTower->Update();
	m_pBattleUIManager->Update();

	if (Engine::IMKEY_DOWN(KEY_1) && Engine::IMKEY_PRESS(KEY_R))
	{
		Create_Sickle(m_spValkyrie->GetTransform()->GetPosition() + _float3(3.f, 1.f, 0.f));
	}
	if (Engine::IMKEY_DOWN(KEY_2) && Engine::IMKEY_PRESS(KEY_R))
	{
		Create_Spider(m_spValkyrie->GetTransform()->GetPosition() + _float3(3.f, 1.f, 0.f));
	}

	if (true == m_bossSpawn)
	{
		/* Ganesha */
		SP(Engine::CObject) spGaneshaClone = ADD_CLONE(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha");
		std::dynamic_pointer_cast<CMonster>(spGaneshaClone)->SelectChannelID();
		spGaneshaClone->GetTransform()->SetPosition(-46, 15, 0);
		spGaneshaClone->GetTransform()->SetRotationY(D3DXToRadian(90));
		m_spGanesha = spGaneshaClone;

		m_bossSpawn = false;
	}
	else if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		m_spValkyrie->GetTransform()->SetPosition(-46, 15, 0);
	}
	else if (Engine::IMKEY_DOWN(KEY_E))
	{
		m_bossSpawn = true;
		m_onBoss = true;
	}

	std::cout << "kiana x : " <<
		m_spValkyrie->GetTransform()->GetPosition().x << ", y : " <<
		m_spValkyrie->GetTransform()->GetPosition().y << ", z : " <<
		m_spValkyrie->GetTransform()->GetPosition().z << std::endl;

	ForUITest();
}

void COneStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void COneStageScene::OnDestroy(void)
{
	__super::OnDestroy();
	m_pBattleUIManager->OnDestroy();
	m_pBattleUIManager->DestroyInstance();

	m_pControlTower->OnDestroy();
	m_pControlTower->DestroyInstance();
	m_pControlTower = nullptr;

	m_vDummy.clear();
}

void COneStageScene::OnEnable(void)
{
	__super::OnEnable();
	m_pBattleUIManager->DestroyInstance();
}

void COneStageScene::OnDisable(void)
{
	__super::OnDisable();

}


void COneStageScene::SetupFromLoader(void)
{
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	Load->MapLoad(this);
	Load->PhaseChangerLoad(this);
	delete(Load);

}

void COneStageScene::SetupMembers(void)
{
	// Kiana
	Create_ActorValkyrie();

	// Cam Target Set
	Create_SceneCamera();
	
}

void COneStageScene::Create_ActorValkyrie(void)
{
	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

	m_spValkyrie = spKianaClone;
	m_spValkyrie->GetTransform()->SetPosition(46.3345f, -1.f, -0.075913f);
	m_pControlTower->AddSquadMember(m_spValkyrie);
	m_pControlTower->Start(CStageControlTower::ALL);

	SP(Engine::CObject) spTheresaClone = ADD_CLONE(L"Theresa", true, (_uint)ELayerID::Player, L"Theresa");

	m_pControlTower->AddSquadMember(spTheresaClone);
	static_cast<CValkyrie*>(spTheresaClone.get())->SetIsWait(true);

	SP(Engine::CObject) spSakuraClone = ADD_CLONE(L"Sakura", true, (_uint)ELayerID::Player, L"Sakura");

	m_pControlTower->AddSquadMember(spSakuraClone);
	static_cast<CValkyrie*>(spSakuraClone.get())->SetIsWait(true);

}

void COneStageScene::Create_SceneCamera(void)
{
	//Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spValkyrie);
	cam->SetMaxDistTPS(2.f);
	CStageControlTower::GetInstance()->ActorControl_SetCurrentMainCam(cam);

	cam->SetMode(Engine::ECameraMode::TPS);
}

void COneStageScene::Create_Dummy(_float3 pos)
{
	auto dummy = ADD_CLONE(L"MO_Dummy", true, (_uint)ELayerID::Enemy, L"MO_Dummy");
	dummy->GetTransform()->SetPosition(pos);

	m_vDummy.emplace_back(dummy);
}

void COneStageScene::Create_Sickle(_float3 pos)
{
	SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	spSickleClone->GetTransform()->SetPosition(pos);
	std::dynamic_pointer_cast<CMonster>(spSickleClone)->SelectChannelID();
	m_vSickle.emplace_back(spSickleClone);
}

void COneStageScene::Create_Spider(_float3 pos)
{
	SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
	spSpiderClone->GetTransform()->SetPosition(pos);
	std::dynamic_pointer_cast<CMonster>(spSpiderClone)->SelectChannelID();
	m_vSpider.emplace_back(spSpiderClone);
}

void COneStageScene::InitPrototypes(void)
{

}

void COneStageScene::ForUITest()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		CBattleUiManager::GetInstance()->SpecialUICanvasOn();
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
	{
		CBattleUiManager::GetInstance()->SpecialUIUp();
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_3))
	{
		CBattleUiManager::GetInstance()->SpecialUIDwon();
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_4))
	{
		CBattleUiManager::GetInstance()->MonsterHpDown(30.0f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_5))
	{
		CBattleUiManager::GetInstance()->PlayerHp(100.0f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F1))
	{
		CBattleUiManager::GetInstance()->PlayerHpDown(0.5f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F2))
	{
		CBattleUiManager::GetInstance()->SkillExecution(2, 10, 10);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F3))
	{
		CBattleUiManager::GetInstance()->PlayerChange(L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Defalut", L"Defalut");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F4))
	{
		CBattleUiManager::GetInstance()->PlayerChange(L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Defalut");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F5))
	{
		CBattleUiManager::GetInstance()->TargetUI(nullptr, 5.0f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
	{
		CBattleUiManager::GetInstance()->BattleEnd();
	}
}
