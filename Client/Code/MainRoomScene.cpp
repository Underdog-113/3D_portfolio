#include "stdafx.h"
#include "MainRoomScene.h"

#include "Loading.h"
#include "StageSelectionScene.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
#include "MainRoomManager.h"
CMainRoomScene::CMainRoomScene()
{
}


CMainRoomScene::~CMainRoomScene()
{
}

CClientScene* CMainRoomScene::Create(void)
{
	CMainRoomScene* pInstance = new CMainRoomScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CMainRoomScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CMainRoomScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CMainRoomScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// 로드
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	delete(Load);

	// 경험치 스테미너 골드 다이아 이름 레벨
	CMainRoomManager::GetInstance()->Start(this);
}

void CMainRoomScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMainRoomScene::Update(void)
{
	__super::Update();
	CMainRoomManager::GetInstance()->Update();
}

void CMainRoomScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMainRoomScene::OnDestroy(void)
{
	__super::OnDestroy();
	
	CMainRoomManager::GetInstance()->OnDestroy();
	CMainRoomManager::GetInstance()->DestroyInstance();
}

void CMainRoomScene::OnEnable(void)
{
	__super::OnEnable();

}

void CMainRoomScene::OnDisable(void)
{
	__super::OnDisable();

}


void CMainRoomScene::InitPrototypes(void)
{
}

