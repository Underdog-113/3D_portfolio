#include "stdafx.h"
#include "ThreeStageScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
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
	InitPrototypes();
}

void CThreeStageScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background");

	// 로드
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->Load(this);
	delete(Load);

	// (미완성)스크롤 뷰 예제

}

void CThreeStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CThreeStageScene::Update(void)
{
	__super::Update();
}

void CThreeStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CThreeStageScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CThreeStageScene::OnEnable(void)
{
	__super::OnEnable();

}

void CThreeStageScene::OnDisable(void)
{
	__super::OnDisable();

}

void CThreeStageScene::ChangeScene(CClientScene* pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CThreeStageScene::InitPrototypes(void)
{
}
