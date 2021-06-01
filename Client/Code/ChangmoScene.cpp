#include "stdafx.h"
#include "ChangmoScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"
#include "CameraManager.h"
 

CChangmoScene::CChangmoScene()
{
}


CChangmoScene::~CChangmoScene()
{
}

Engine::CScene* CChangmoScene::Create(void)
{
	CChangmoScene* pInstance = new CChangmoScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CChangmoScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CChangmoScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
}

void CChangmoScene::Start(void)
{
	__super::Start();
	{
		SP(Engine::CObject) spEmptyObject
			= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube");
	
		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Katana_M13_78_4");
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	}
	{
		SP(Engine::CObject) spEmptyObject
			= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Character");
	
		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Theresa_C5");
		spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	
	
		spEmptyObject->GetTransform()->SetSize(1, 1, 1);
		//spEmptyObject->GetTransform()->SetRotationX(-PI / 2.f);
	}
	
	

}

void CChangmoScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CChangmoScene::Update(void)
{
	__super::Update();
}

void CChangmoScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CChangmoScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CChangmoScene::OnEnable(void)
{
	__super::OnEnable();
}

void CChangmoScene::OnDisable(void)
{
	__super::OnDisable();
}

void CChangmoScene::InitPrototypes(void)
{
}