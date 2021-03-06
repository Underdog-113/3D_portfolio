#include "stdafx.h"
#include "BossStageScene.h"

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

#include "BossStagePhaseControl.h"

#include "Monster.h"

CBossStageScene::CBossStageScene()
{
}


CBossStageScene::~CBossStageScene()
{
}

CClientScene* CBossStageScene::Create(void)
{
	CBossStageScene* pInstance = new CBossStageScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CBossStageScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CBossStageScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
	m_pControlTower->SetPhaseControl(new CBossStagePhaseControl);
	m_pControlTower->GetPhaseControl()->SetControlTower(m_pControlTower);
}

void CBossStageScene::Start(void)
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

	m_pBattleUIManager = CBattleUiManager::GetInstance();
	m_pBattleUIManager->Start(this);

	CStageControlTower::GetInstance()->GetCurrentActor()->SetIsEnabled(true);
}

void CBossStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBossStageScene::Update(void)
{
	__super::Update();

	if (Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	m_pControlTower->Update();
	m_pBattleUIManager->Update();

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_F1))
	{
		CBattleUiManager::GetInstance()->BattleEnd();
	}
}

void CBossStageScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CBossStageScene::OnDestroy(void)
{
	__super::OnDestroy();
	m_pBattleUIManager->OnDestroy();
	m_pBattleUIManager->DestroyInstance();

	CStageControlTower::DestroyInstance();
	m_pControlTower = nullptr;

	m_vDummy.clear();
}

void CBossStageScene::OnEnable(void)
{
	__super::OnEnable();
	m_pBattleUIManager->DestroyInstance();
}

void CBossStageScene::OnDisable(void)
{
	__super::OnDisable();
}

void CBossStageScene::SetupFromLoader(void)
{
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->TextLoad(this);
	Load->CanvasLoad(this);
	Load->MapLoad(this);
	//Load->PhaseChangerLoad(this);
	delete(Load);
}

void CBossStageScene::SetupMembers(void)
{
	// Kiana
	Create_ActorValkyrie();

	// Cam Target Set
	Create_SceneCamera();
}

void CBossStageScene::Create_ActorValkyrie(void)
{
	SP(Engine::CObject) spStartValkyrie = m_pControlTower->SettingSquad(this);

	m_spValkyrie = spStartValkyrie;
	//m_spValkyrie->GetTransform()->SetPosition(-19.2f, 0.248f, 0.1f);
	m_spValkyrie->GetTransform()->SetPosition(186.21f, -4.19f, -17.06f);

	m_pControlTower->Start(CStageControlTower::ALL);
}

void CBossStageScene::Create_SceneCamera(void)
{
	//Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spValkyrie);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
}

void CBossStageScene::InitPrototypes(void)
{

}
