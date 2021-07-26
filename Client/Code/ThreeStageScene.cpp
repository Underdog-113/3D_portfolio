#include "stdafx.h"
#include "ThreeStageScene.h"

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

#include "ThreeStagePhaseControl.h"

#include "Monster.h"

CThreeStageScene::CThreeStageScene()
{
}


CThreeStageScene::~CThreeStageScene()
{
}

CClientScene* CThreeStageScene::Create(void)
{
	CThreeStageScene* pInstance = new CThreeStageScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CThreeStageScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CThreeStageScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
	m_pControlTower->SetPhaseControl(new CThreeStagePhaseControl);
	m_pControlTower->GetPhaseControl()->SetControlTower(m_pControlTower);
}

void CThreeStageScene::Start(void)
{
	__super::Start();

	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)Engine::ELayerID::UI, L""));
	image->GetTransform()->SetPositionZ(1.0f);
	image->GetTransform()->SetSize(_float3(25, 25, 0));
	image->GetTexture()->AddTexture(L"MousePoint", 0);
	image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
	image->AddComponent<CMousePointC>();

	SetupFromLoader();
	SetupMembers();
	SetupBoxes();

	m_pBattleUIManager = CBattleUiManager::GetInstance();
	m_pBattleUIManager->Start(this);

	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
	Engine::CSoundManager::GetInstance()->PlayBGM(L"Stage1_Bgm.wav");
	Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);

	m_pControlTower->GetCurrentActor()->SetIsEnabled(true);

	this->FindObjectByName(L"MainCanvas")->SetIsEnabled(true);
	CBattleUiManager::GetInstance()->QteOff(0);
	CBattleUiManager::GetInstance()->QteOff(1);
	CBattleUiManager::GetInstance()->SquadOff(this);
	CBattleUiManager::GetInstance()->WaitingPlayerSetting();

	Engine::CCanvas* ConversationCanvas = static_cast<Engine::CCanvas*>(this->FindObjectByName(L"ConversationCanvas").get());
	ConversationCanvas->AddObjectFind();
	ConversationCanvas->SetIsEnabled(false);
}

void CThreeStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CThreeStageScene::Update(void)
{
	__super::Update();

	if (Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	m_pControlTower->Update();
	m_pBattleUIManager->Update();
}

void CThreeStageScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CThreeStageScene::OnDestroy(void)
{
	__super::OnDestroy();
	m_pBattleUIManager->OnDestroy();
	m_pBattleUIManager->DestroyInstance();

	CStageControlTower::DestroyInstance();

}

void CThreeStageScene::OnEnable(void)
{
	__super::OnEnable();
	m_pBattleUIManager->DestroyInstance();
}

void CThreeStageScene::OnDisable(void)
{
	__super::OnDisable();
}

void CThreeStageScene::SetupFromLoader(void)
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
	Load->PortalLoad(this);
	Load->TrapLoad(this);
	delete(Load);
}

void CThreeStageScene::SetupMembers(void)
{
	// Kiana
	Create_ActorValkyrie();

	// Cam Target Set
	Create_SceneCamera();
}

void CThreeStageScene::SetupBoxes(void)
{
	SP(Engine::CObject) spBoxClone = ADD_CLONE(L"OJ_Box", true, (_uint)ELayerID::Enemy, L"OJ_Box");
	spBoxClone->GetTransform()->SetPosition(32.82f, -1.735f, 1.35f);
	std::dynamic_pointer_cast<CMonster>(spBoxClone)->SelectChannelID();
	m_vBox.emplace_back(spBoxClone);

	spBoxClone = ADD_CLONE(L"OJ_Box", true, (_uint)ELayerID::Enemy, L"OJ_Box");
	spBoxClone->GetTransform()->SetPosition(35.11f, -1.735f, 1.35f);
	std::dynamic_pointer_cast<CMonster>(spBoxClone)->SelectChannelID();
	m_vBox.emplace_back(spBoxClone);
}

void CThreeStageScene::Create_ActorValkyrie(void)
{
	SP(Engine::CObject) spStartValkyrie = m_pControlTower->SettingSquad(this);

	m_spValkyrie = spStartValkyrie;
	m_spValkyrie->GetTransform()->SetPosition(70.4f, -6.29f, -7.73f);
	m_spValkyrie->GetTransform()->AddRotationY(D3DXToRadian(-90.f));

	m_pControlTower->Start(CStageControlTower::ALL);
}

void CThreeStageScene::Create_SceneCamera(void)
{
	//Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spValkyrie);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
}

void CThreeStageScene::InitPrototypes(void)
{
}

void CThreeStageScene::ForUITest()
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
		CBattleUiManager::GetInstance()->MonsterState(L"", 1000, 900, 2, L"DOWN", 0, 0);
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
