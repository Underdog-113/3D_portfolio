#include "stdafx.h"
#include "InventoryScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
#include "InventoryManager.h"

CInventoryScene::CInventoryScene()
{
}


CInventoryScene::~CInventoryScene()
{
}


CClientScene* CInventoryScene::Create(void)
{
	CInventoryScene* pInstance = new CInventoryScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CInventoryScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CInventoryScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CInventoryScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// �ε�
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->ScrollViewLoad(this);
	Load->TextLoad(this);
	Load->CanvasLoad(this);
	delete(Load);

}

void CInventoryScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CInventoryScene::Update(void)
{
	__super::Update();

	if (!m_init)
	{
		CInventoryManager::GetInstance()->Start(this);
		m_init = true;
	}

	CInventoryManager::GetInstance()->Update();
}

void CInventoryScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CInventoryScene::OnDestroy(void)
{
	__super::OnDestroy();
	CInventoryManager::GetInstance()->DestroyInstance();
}

void CInventoryScene::OnEnable(void)
{
	__super::OnEnable();

}

void CInventoryScene::OnDisable(void)
{
	__super::OnDisable();

}


void CInventoryScene::InitPrototypes(void)
{
}