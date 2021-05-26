#include "stdafx.h"
#include "WooScene.h"


CWooScene::CWooScene()
{
}


CWooScene::~CWooScene()
{
}

Engine::CScene * CWooScene::Create(void)
{
	CWooScene* pInstance = new CWooScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CWooScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CWooScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CWooScene::Start(void)
{
}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	__super::Update();

}

void CWooScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CWooScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CWooScene::OnEnable(void)
{
	__super::OnEnable();

}

void CWooScene::OnDisable(void)
{
	__super::OnDisable();

}

void CWooScene::InitPrototypes(void)
{
}
