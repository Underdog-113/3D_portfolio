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

	// ·Îµå
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->Load(this);
	delete(Load);

}

void CMainRoomScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMainRoomScene::Update(void)
{
	__super::Update();
}

void CMainRoomScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMainRoomScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CMainRoomScene::OnEnable(void)
{
	__super::OnEnable();

}

void CMainRoomScene::OnDisable(void)
{
	__super::OnDisable();

}

void CMainRoomScene::ChangeScene(CClientScene* pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CMainRoomScene::InitPrototypes(void)
{
}
