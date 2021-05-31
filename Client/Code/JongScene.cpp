#include "stdafx.h"
#include "JongScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"


CJongScene::CJongScene()
{
}


CJongScene::~CJongScene()
{
}

Engine::CScene * CJongScene::Create(void)
{
	CJongScene* pInstance = new CJongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CJongScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CJongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CJongScene::Start(void)
{
	__super::Start();
	{
		SP(Engine::CObject) spEmptyObject
			= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Kiana", (_int)ELayerID::Player);

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"1to2");
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	}
}

void CJongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CJongScene::Update(void)
{
	__super::Update();

}

void CJongScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CJongScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CJongScene::OnEnable(void)
{
	__super::OnEnable();

}

void CJongScene::OnDisable(void)
{
	__super::OnDisable();

}

void CJongScene::InitPrototypes(void)
{
}
