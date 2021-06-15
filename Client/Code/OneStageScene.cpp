#include "stdafx.h"
#include "OneStageScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
COneStageScene::COneStageScene()
{
}


COneStageScene::~COneStageScene()
{
}

CClientScene* COneStageScene::Create(void)
{
	COneStageScene* pInstance = new COneStageScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void COneStageScene::Free(void)
{
	OnDestroy();
	delete this;
}

void COneStageScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void COneStageScene::Start(void)
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

	CBattleUiManager::GetInstance()->Start(this);
}

void COneStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void COneStageScene::Update(void)
{
	__super::Update();

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		CBattleUiManager::GetInstance()->KeyPad(8);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
	{
		CBattleUiManager::GetInstance()->HitCount(8);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_3))
	{
		CBattleUiManager::GetInstance()->MonsetrState(L"½½±êÀÌ", 100, L"DOWN");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_4))
	{
		CBattleUiManager::GetInstance()->MonsterHpDown(0.5f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_5))
	{
		CBattleUiManager::GetInstance()->PlayerHp(100.0f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F1))
	{
		CBattleUiManager::GetInstance()->PlayerHpDown(0.5f);
	}
}

void COneStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void COneStageScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void COneStageScene::OnEnable(void)
{
	__super::OnEnable();
	CBattleUiManager::GetInstance()->OnDestroy();
}

void COneStageScene::OnDisable(void)
{
	__super::OnDisable();

}

void COneStageScene::ChangeScene(CClientScene* pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void COneStageScene::InitPrototypes(void)
{
}
