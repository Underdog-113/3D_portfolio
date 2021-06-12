#include "stdafx.h"
#include "TwoStageScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
CTwoStageScene::CTwoStageScene()
{
}


CTwoStageScene::~CTwoStageScene()
{
}

Engine::CScene* CTwoStageScene::Create(void)
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
	InitPrototypes();
}

void CTwoStageScene::Start(void)
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

void CTwoStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTwoStageScene::Update(void)
{
	__super::Update();
	if (m_pLoading && m_pLoading->GetFinish())
	{
		Engine::CSceneManager::GetInstance()->SceneChange(m_pLoading->GetNextScene());
	}
}

void CTwoStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CTwoStageScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CTwoStageScene::OnEnable(void)
{
	__super::OnEnable();

}

void CTwoStageScene::OnDisable(void)
{
	__super::OnDisable();

}

void CTwoStageScene::ChangeScene(Engine::CScene * pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CTwoStageScene::InitPrototypes(void)
{
}
