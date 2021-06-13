#include "stdafx.h"
#include "ChangmoScene.h"
#include "EmptyObject.h"
 
 
 
 

CChangmoScene::CChangmoScene()
{
}


CChangmoScene::~CChangmoScene()
{
}

CClientScene* CChangmoScene::Create(void)
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
			= ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");
	
		//spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
		//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		//spEmptyObject->AddComponent<Engine::CTextureC>();
		//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		//spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		//spEmptyObject->GetTransform()->SetSize(10, 10, 10);
		//
		//spEmptyObject
		//	= ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Map, L"Cube0");
		
		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Sphere");
		spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spEmptyObject->AddComponent<Engine::CCollisionC>()->SetCollisionID(2);
		spEmptyObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CAabbCollider::Create(_float3(2, 2, 2)));
		spEmptyObject->AddComponent<Engine::CDebugC>();
		spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		spEmptyObject->GetTransform()->SetSize(2, 2, 2);
		spEmptyObject->GetTransform()->SetPosition(0, 0, 0);

		//spEmptyObject
		//	= ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Map, L"Cube1");
		//
		//spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
		//spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
		//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		//spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		//spEmptyObject->GetTransform()->SetSize(2, 2, 2);
		//spEmptyObject->GetTransform()->SetPosition(6, 0, 0);
		//
		//spEmptyObject
		//	= ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Map, L"Cube2");
		//
		//spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
		//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		//spEmptyObject->AddComponent<Engine::CTextureC>();
		//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		////spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		//spEmptyObject->GetTransform()->SetSize(2, 2, 2);
		//spEmptyObject->GetTransform()->SetPosition(9, 0, 0);
		

		//SP(Engine::CObject) spEmptyObject1
		//	= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube1");
		//
		//spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
		//spEmptyObject1->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		//spEmptyObject1->AddComponent<Engine::CTextureC>();
		//spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		//spEmptyObject1->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		//spEmptyObject1->GetTransform()->SetPosition(0, 0, 3);
		//spEmptyObject1->GetTransform()->SetSize(3, 3, 3);

		//spEmptyObject =
		//	ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background1");
		//
		//spEmptyObject->AddComponent<Engine::CRectTexC>()->SetIsOrtho(true);
		//spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Body");
		//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
		//spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::RectTexShader);
		//spEmptyObject->GetTransform()->SetSize(800, 600, 0);
		//spEmptyObject->GetTransform()->AddPositionZ(0.f);
		//
		//spEmptyObject =
		//	ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background1");
		//
		//spEmptyObject->AddComponent<Engine::CRectTexC>();// ->SetIsOrtho(true);
		//spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall");
		//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
		//spEmptyObject->GetTransform()->SetSize(800, 600, 0);
		//spEmptyObject->GetTransform()->AddPositionZ(0.5f);
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
	_float3 intersection;
	if (Engine::IMKEY_DOWN(MOUSE_LEFT) && Engine::CInputManager::GetInstance()->MousePickingLocal((_int)ELayerID::Player, intersection))
	{
		int a = 5;
	}
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