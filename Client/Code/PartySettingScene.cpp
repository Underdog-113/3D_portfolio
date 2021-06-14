#include "stdafx.h"
#include "PartySettingScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
CPartySettingScene::CPartySettingScene()
{
}


CPartySettingScene::~CPartySettingScene()
{
}

CClientScene* CPartySettingScene::Create(void)
{
	CPartySettingScene* pInstance = new CPartySettingScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CPartySettingScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CPartySettingScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CPartySettingScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// 로드
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->Load(this);
	delete(Load);

	// (미완성)스크롤 뷰 예제

}

void CPartySettingScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CPartySettingScene::Update(void)
{
	__super::Update();
}

void CPartySettingScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CPartySettingScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CPartySettingScene::OnEnable(void)
{
	__super::OnEnable();

}

void CPartySettingScene::OnDisable(void)
{
	__super::OnDisable();

}

void CPartySettingScene::ChangeScene(CClientScene* pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CPartySettingScene::InitPrototypes(void)
{
}
