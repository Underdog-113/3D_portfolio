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
	InitPrototypes();
}

void CChangmoScene::Start(void)
{
	__super::Start();
	{
		SP(Engine::CObject) spEmptyObject
			= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Cube", (_int)ELayerID::Player);

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Katana_M13_78_4");
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	}
	{
		SP(Engine::CObject) spEmptyObject
			= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Cube", (_int)ELayerID::Player);

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"sibal");
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);


		spEmptyObject->GetTransform()->SetSize(100, 100, 100);
		//spEmptyObject->GetTransform()->SetRotationX(-PI / 2.f);
	}
	//{
	//	//¸ö¶×¾Æ¸® ¹× ÀüºÎ
	//	SP(Engine::CObject) pEmptyObject
	//		= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Character", (_int)ELayerID::Player);
	//
	//	SP(Engine::CMeshC) spMesh = pEmptyObject->AddComponent<Engine::CMeshC>();
	//	spMesh->AddMeshData(L"sakura_attack02_body");
	//
	//
	//	SP(Engine::CTextureC) spTexture = pEmptyObject->AddComponent<Engine::CTextureC>();
	//	spTexture->AddTexture(L"Katana_M13_78_4", 0);
	//	spTexture->AddTexture(L"Katana_M13_78_5", 0);
	//	spTexture->AddTexture(L"Avatar_Yae_sakura_C1_Texture_Body_Color", 0);
	//	spTexture->AddTexture(L"Avatar_Yae_sakura_C1_Texture_Body_Color", 0);
	//	spTexture->AddTexture(L"Avatar_Yae_sakura_C0_Texture_Face_Color", 0);
	//	spTexture->AddTexture(L"Avatar_Yae_sakura_C0_Texture_Hair_Color", 0);
	//	
	//
	//
	//	SP(Engine::CGraphicsC) spGraphics = pEmptyObject->AddComponent<Engine::CGraphicsC>();
	//	spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//
	//	pEmptyObject->GetTransform()->SetSize(100, 100, 100);
	//	pEmptyObject->GetTransform()->SetRotationX(-PI / 2.f);
	//}
	//
	//{
	//	//´«
	//	SP(Engine::CObject) pEmptyObject
	//		= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Character", (_int)ELayerID::Player);
	//
	//	SP(Engine::CMeshC) spMesh = pEmptyObject->AddComponent<Engine::CMeshC>();
	//	spMesh->AddMeshData(L"sakura_attack02_eye_R");
	//	spMesh->AddMeshData(L"sakura_attack02_eye_L");
	//	
	//
	//	SP(Engine::CTextureC) spTexture = pEmptyObject->AddComponent<Engine::CTextureC>();
	//	spTexture->AddTexture(L"1", 0);
	//	spTexture->AddTexture(L"1", 1);
	//	
	//
	//	SP(Engine::CGraphicsC) spGraphics = pEmptyObject->AddComponent<Engine::CGraphicsC>();
	//	spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	//
	//	pEmptyObject->GetTransform()->AddPositionZ(-0.1f);
	//	pEmptyObject->GetTransform()->SetSize(100, 100, 100);
	//	pEmptyObject->GetTransform()->SetRotationX(-PI / 2.f);
	//}
	//
	//{
	//	//ÀÔ
	//	SP(Engine::CObject) pEmptyObject
	//		= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Character", (_int)ELayerID::Player);
	//
	//	SP(Engine::CMeshC) spMesh = pEmptyObject->AddComponent<Engine::CMeshC>();
	//	spMesh->AddMeshData(L"sakura_attack02_mouth");
	//
	//	SP(Engine::CTextureC) spTexture = pEmptyObject->AddComponent<Engine::CTextureC>();
	//	spTexture->AddTexture(L"1 (1)", 0);
	//
	//	SP(Engine::CGraphicsC) spGraphics = pEmptyObject->AddComponent<Engine::CGraphicsC>();
	//	spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaTest);
	//
	//	pEmptyObject->GetTransform()->AddPositionY(0.f);
	//	pEmptyObject->GetTransform()->SetSize(100, 100, 100);
	//	pEmptyObject->GetTransform()->SetRotationX(-PI / 2.f);
	//}
	//
	//{
	//	//¾ó±¼
	//	SP(Engine::CObject) pEmptyObject
	//		= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Character", (_int)ELayerID::Player);
	//
	//	SP(Engine::CMeshC) spMesh = pEmptyObject->AddComponent<Engine::CMeshC>();
	//	spMesh->AddMeshData(L"Face");
	//
	//	SP(Engine::CTextureC) spTexture = pEmptyObject->AddComponent<Engine::CTextureC>();
	//	spTexture->AddTexture(L"Avatar_Theresa_Texture_Face_Color", 0);
	//
	//	SP(Engine::CGraphicsC) spGraphics = pEmptyObject->AddComponent<Engine::CGraphicsC>();
	//	spGraphics->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//
	//	pEmptyObject->GetTransform()->SetSize(100, 100, 100);
	//	pEmptyObject->GetTransform()->SetRotationX(-PI / 2.f);
	//}

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