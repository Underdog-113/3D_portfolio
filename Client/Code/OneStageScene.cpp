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
}

void COneStageScene::Start(void)
{
	__super::Start();

	SetupFromLoader();

	SetupMembers();

	m_pBattleUIManager = CBattleUiManager::GetInstance();
	m_pBattleUIManager->Start(this);

	m_pControlTower->Start();
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



	//ForUITest();
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
	Load->ToolLoad(this);
	delete(Load);

}

void COneStageScene::SetupMembers(void)
{
	// Kiana
	Create_ActorValkyrie();

	// Cam Target Set
	Create_SceneCamera();

	Create_Dummy(_float3(5.f, 0.f, 0.f));
	Create_Dummy(_float3(10.f, 0.f, 0.f));
	Create_Dummy(_float3(15.f, 0.f, 2.f));
	Create_Dummy(_float3(15.f, 0.f, -2.f));
	// Spider


}

void COneStageScene::Create_ActorValkyrie(void)
{
	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

	m_spValkyrie = spKianaClone;
	m_pControlTower->AddSquadMember(m_spValkyrie);
	m_pControlTower->Start(CStageControlTower::ALL);
}

void COneStageScene::Create_SceneCamera(void)
{
	//Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spValkyrie);
	cam->SetTargetDist(4.f);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);

	cam->SetMode(Engine::ECameraMode::TPS);
}

void COneStageScene::Create_Dummy(_float3 pos)
{
	auto dummy = ADD_CLONE(L"MO_Dummy", true, (_uint)ELayerID::Enemy, L"MO_Dummy");
	dummy->GetTransform()->SetPosition(pos);

	m_vDummy.emplace_back(dummy);
}


void COneStageScene::InitPrototypes(void)
{

}

void COneStageScene::ForUITest()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		CBattleUiManager::GetInstance()->PlayerSpDown(10);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
	{
		CBattleUiManager::GetInstance()->HitCount(8);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_3))
	{
		CBattleUiManager::GetInstance()->MonsterState(L"aaaa", 100, L"DOWN");
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
		CBattleUiManager::GetInstance()->PlayerChange(100, 100, L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Defalut", L"Defalut");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F4))
	{
		CBattleUiManager::GetInstance()->PlayerChange(100, 100, L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Defalut");
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
