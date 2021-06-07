#include "stdafx.h"
#include "YongScene.h"
#include "FRC.h"


CYongScene::CYongScene()
{
}


CYongScene::~CYongScene()
{
}

Engine::CScene * CYongScene::Create(void)
{
	CYongScene* pInstance = new CYongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CYongScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CYongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CYongScene::Start(void)
{
	__super::Start();
	{
		m_pObjectFactory->AddClone(L"MO_Spider", true, (_int)ELayerID::Enemy, L"MO_Spider");
	}
}

void CYongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CYongScene::Update(void)
{
	__super::Update();
	
}

void CYongScene::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CYongScene::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CYongScene::OnEnable(void)
{
	__super::OnEnable();
	
}

void CYongScene::OnDisable(void)
{
	__super::OnDisable();
	
}

void CYongScene::InitPrototypes(void)
{
}
