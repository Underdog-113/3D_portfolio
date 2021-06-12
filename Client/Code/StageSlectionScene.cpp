#include "stdafx.h"
#include "StageSelectionScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
CStageSelectionScene::CStageSelectionScene()
{
}


CStageSelectionScene::~CStageSelectionScene()
{
}

Engine::CScene* CStageSelectionScene::Create(void)
{
	CStageSelectionScene* pInstance = new CStageSelectionScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CStageSelectionScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CStageSelectionScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CStageSelectionScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background");

	// ·Îµå
}

void CStageSelectionScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	if (Engine::IMKEY_DOWN(KEY_F4))
	{
		CDataLoad* Load = new CDataLoad();
		Load->Setting();
		Load->Load(this);
		delete(Load);
	}
}

void CStageSelectionScene::Update(void)
{
	__super::Update();



	if (m_pLoading && m_pLoading->GetFinish())
	{
		Engine::CSceneManager::GetInstance()->SceneChange(m_pLoading->GetNextScene());
	}
}

void CStageSelectionScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CStageSelectionScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CStageSelectionScene::OnEnable(void)
{
	__super::OnEnable();

}

void CStageSelectionScene::OnDisable(void)
{
	__super::OnDisable();

}

void CStageSelectionScene::ChangeScene(Engine::CScene * pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CStageSelectionScene::InitPrototypes(void)
{
}
