#include "stdafx.h"
#include "ChangmoScene.h"
#include "EmptyObject.h"
 
 
 
 

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
	Engine::ADD_TEXT(L"WOW1", L"asdfasdfasdfasdf", _float3(100, 100, -1), D3DXCOLOR(0, 0, 0, 1));

	{
		SP(Engine::CObject) spEmptyObject
			= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");
	
		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
		spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spEmptyObject->GetTransform()->SetSize(10, 10, 10);

		/*SP(Engine::CObject) spEmptyObject1
			= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube1");

		spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		spEmptyObject1->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall");
		spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spEmptyObject1->GetTransform()->SetParent(spEmptyObject->GetTransform());
		spEmptyObject1->GetTransform()->SetPosition(1, 0, 0);*/

		spEmptyObject =
			ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background1");

		spEmptyObject->AddComponent<Engine::CRectTexC>()->SetIsOrtho(true);
		spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Body");
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
		spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::RectTexShader);
		spEmptyObject->GetTransform()->SetSize(800, 600, 0);
		spEmptyObject->GetTransform()->AddPositionZ(0.f);

		spEmptyObject =
			ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background1");

		spEmptyObject->AddComponent<Engine::CRectTexC>();// ->SetIsOrtho(true);
		spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall");
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
		spEmptyObject->GetTransform()->SetSize(800, 600, 0);
		spEmptyObject->GetTransform()->AddPositionZ(0.5f);
	}

	
}

void CChangmoScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CChangmoScene::Update(void)
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