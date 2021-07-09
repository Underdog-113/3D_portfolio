#include "stdafx.h"
#include "TwoStageScene.h"

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

#include "TwoStagePhaseControl.h"

#include "Monster.h"

CTwoStageScene::CTwoStageScene()
{
}


CTwoStageScene::~CTwoStageScene()
{
}

CClientScene* CTwoStageScene::Create(void)
{
	CTwoStageScene* pInstance = new CTwoStageScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CTwoStageScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CTwoStageScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
	m_pControlTower->SetPhaseControl(new CTwoStagePhaseControl);
	m_pControlTower->GetPhaseControl()->SetControlTower(m_pControlTower);
}

void CTwoStageScene::Start(void)
{
	__super::Start();

	SetupFromLoader();
	SetupMembers();

	m_pBattleUIManager = CBattleUiManager::GetInstance();
	m_pBattleUIManager->Start(this);

}

void CTwoStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTwoStageScene::Update(void)
{
	__super::Update();

	if (Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	m_pControlTower->Update();
	m_pBattleUIManager->Update();
}

void CTwoStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CTwoStageScene::OnDestroy(void)
{
	__super::OnDestroy();
	m_pBattleUIManager->OnDestroy();
	m_pBattleUIManager->DestroyInstance();

	m_pControlTower->OnDestroy();
	m_pControlTower->DestroyInstance();
	m_pControlTower = nullptr;

	m_vDummy.clear();
}

void CTwoStageScene::OnEnable(void)
{
	__super::OnEnable();
	m_pBattleUIManager->DestroyInstance();
}

void CTwoStageScene::OnDisable(void)
{
	__super::OnDisable();
}

void CTwoStageScene::SetupFromLoader(void)
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
	//Load->PhaseChangerLoad(this);
	Load->PortalLoad(this);
	delete(Load);
}

void CTwoStageScene::SetupMembers(void)
{
	// Kiana
	Create_ActorValkyrie();

	// Cam Target Set
	Create_SceneCamera();

	//Create_Dummy(_float3(43.3345f, -1.f, -0.075913f));
}

void CTwoStageScene::Create_ActorValkyrie(void)
{
	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

	m_spValkyrie = spKianaClone;
	m_spValkyrie->GetTransform()->SetPosition(70.4f, -5.29f, -7.73f);
	m_pControlTower->AddSquadMember(m_spValkyrie);
	m_pControlTower->Start(CStageControlTower::ALL);

	SP(Engine::CObject) spTheresaClone = ADD_CLONE(L"Theresa", true, (_uint)ELayerID::Player, L"Theresa");

	m_pControlTower->AddSquadMember(spTheresaClone);
	static_cast<CValkyrie*>(spTheresaClone.get())->SetIsWait(true);

	SP(Engine::CObject) spSakuraClone = ADD_CLONE(L"Sakura", true, (_uint)ELayerID::Player, L"Sakura");

	m_pControlTower->AddSquadMember(spSakuraClone);
	static_cast<CValkyrie*>(spSakuraClone.get())->SetIsWait(true);

}

void CTwoStageScene::Create_SceneCamera(void)
{
	//Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spValkyrie);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
}

void CTwoStageScene::Create_Dummy(_float3 pos)
{
	auto dummy = ADD_CLONE(L"MO_Dummy", true, (_uint)ELayerID::Enemy, L"MO_Dummy");
	dummy->GetTransform()->SetPosition(pos);

	m_vDummy.emplace_back(dummy);
}

void CTwoStageScene::Create_Sickle(_float3 pos)
{
	SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	spSickleClone->GetTransform()->SetPosition(pos);
	std::dynamic_pointer_cast<CMonster>(spSickleClone)->SelectChannelID();
	m_vSickle.emplace_back(spSickleClone);
}

void CTwoStageScene::Create_Spider(_float3 pos)
{
	SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
	spSpiderClone->GetTransform()->SetPosition(pos);
	std::dynamic_pointer_cast<CMonster>(spSpiderClone)->SelectChannelID();
	m_vSpider.emplace_back(spSpiderClone);
}

void CTwoStageScene::InitPrototypes(void)
{

}

void CTwoStageScene::ForUITest()
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
		CBattleUiManager::GetInstance()->HitCount(5);
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
		CBattleUiManager::GetInstance()->MonsterState(L"", 1000, 900, 2, L"DOWN");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F4))
	{
		CBattleUiManager::GetInstance()->MonsterHpDown(10);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F5))
	{
		CBattleUiManager::GetInstance()->OnTargetUI(nullptr, 5.0f);
	}

	// 	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
	// 	{
	// 		CBattleUiManager::GetInstance()->BattleEnd();
	// 	}
}
