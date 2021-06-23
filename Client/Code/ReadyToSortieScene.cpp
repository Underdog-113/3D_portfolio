#include "stdafx.h"
#include "ReadyToSortieScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
#include "ReadyToSortieManager.h"
CReadyToSortieScene::CReadyToSortieScene()
{
}


CReadyToSortieScene::~CReadyToSortieScene()
{
}

CClientScene* CReadyToSortieScene::Create(void)
{
	CReadyToSortieScene* pInstance = new CReadyToSortieScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CReadyToSortieScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CReadyToSortieScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CReadyToSortieScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// ·Îµå
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	delete(Load);

	CReadyToSortieManager::GetInstance()->Start(this);
}

void CReadyToSortieScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CReadyToSortieScene::Update(void)
{
	__super::Update();
	CReadyToSortieManager::GetInstance()->Update();
}

void CReadyToSortieScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CReadyToSortieScene::OnDestroy(void)
{
	__super::OnDestroy();

	CReadyToSortieManager::GetInstance()->OnDestroy();
	CReadyToSortieManager::GetInstance()->DestroyInstance();
}

void CReadyToSortieScene::OnEnable(void)
{
	__super::OnEnable();

}

void CReadyToSortieScene::OnDisable(void)
{
	__super::OnDisable();

}


void CReadyToSortieScene::InitPrototypes(void)
{
}
