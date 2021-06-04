#include "stdafx.h"
#include "YongScene.h"
#include "EmptyObject.h"

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
		SP(Engine::CObject) spEmptyObject
			= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Yae_Sakura2");
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);


		
	}
}

void CYongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CYongScene::Update(void)
{
	__super::Update();
	SP(Engine::CObject) momBox = FindObjectByName(L"Cube0");

	if (Engine::IMKEY_PRESS(KEY_UP))
	{
		momBox->GetTransform()->MoveForward(0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_LEFT))
	{
		momBox->GetTransform()->AddRotationY(-0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_RIGHT))
	{
		momBox->GetTransform()->AddRotationY(0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_DOWN))
	{
		momBox->GetTransform()->AddRotationX(0.05f);
	}
	if (Engine::IMKEY_PRESS(KEY_E))
	{
		momBox->GetTransform()->AddRotationZ(0.05f);
	}
	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		momBox->SetDeleteThis(true);
	}
	
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
