#include "stdafx.h"
#include "BattleEndScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
CBattleEndScene::CBattleEndScene()
{
}


CBattleEndScene::~CBattleEndScene()
{
}

CClientScene* CBattleEndScene::Create(void)
{
	CBattleEndScene* pInstance = new CBattleEndScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CBattleEndScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CBattleEndScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CBattleEndScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// 로드
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->Load(this);
	Load->TextLoad(this);
	delete(Load);

	// (미완성)스크롤 뷰 예제

}

void CBattleEndScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBattleEndScene::Update(void)
{
	__super::Update();

}

void CBattleEndScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CBattleEndScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CBattleEndScene::OnEnable(void)
{
	__super::OnEnable();

}

void CBattleEndScene::OnDisable(void)
{
	__super::OnDisable();

}

void CBattleEndScene::ChangeScene(CClientScene* pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CBattleEndScene::InitPrototypes(void)
{
}
