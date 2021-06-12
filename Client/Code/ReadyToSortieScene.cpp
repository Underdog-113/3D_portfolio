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
CReadyToSortieScene::CReadyToSortieScene()
{
}


CReadyToSortieScene::~CReadyToSortieScene()
{
}

Engine::CScene* CReadyToSortieScene::Create(void)
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
		ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background");

	// 로드

	if (Engine::IMKEY_DOWN(KEY_F4))
	{
		CDataLoad* Load = new CDataLoad();
		Load->Setting();
		Load->Load(this);
		delete(Load);
	}

	// (미완성)스크롤 뷰 예제

}

void CReadyToSortieScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CReadyToSortieScene::Update(void)
{
	__super::Update();
	if (m_pLoading && m_pLoading->GetFinish())
	{
		Engine::CSceneManager::GetInstance()->SceneChange(m_pLoading->GetNextScene());
	}
}

void CReadyToSortieScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CReadyToSortieScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CReadyToSortieScene::OnEnable(void)
{
	__super::OnEnable();

}

void CReadyToSortieScene::OnDisable(void)
{
	__super::OnDisable();

}

void CReadyToSortieScene::ChangeScene(Engine::CScene * pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CReadyToSortieScene::InitPrototypes(void)
{
}
