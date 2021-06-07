#include "stdafx.h"
#include "EditorScene.h"

#include "MeshData.h"
#include "StaticMeshData.h"
#include "DynamicMeshData.h"

#include "Object.h"
#include "ObjectFactory.h"

#include "InputManager.h"
#include "TextureStore.h"
#include "Layer.h"
#include "DataStore.h"

#include "MainFrm.h"
#include "MapToolView.h"
#include "ToolMenuView.h"
#include "SceneManager.h"
#include "WndApp.h"

#pragma region Prototypes
#include "EmptyObject.h"
#include "Grid.h"
#include "Camera.h"
#pragma endregion

CEditorScene::CEditorScene()
{
}

CEditorScene::~CEditorScene()
{
}

Engine::CScene* CEditorScene::Create(void)
{
	Engine::CScene* pEditorScene = new CEditorScene;
	pEditorScene->Awake((_int)ELayerID::NumOfLayerID);

	return pEditorScene;
}

void CEditorScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CEditorScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	//DataStore Init
	m_pDataStore->InitDataMap((_uint)EDataID::NumOfDataID);
	m_pDataStore->AddDataSection(L"BasicObject", (_uint)EDataID::BasicObject);
	m_pDataStore->AddDataSection(L"Player", (_uint)EDataID::Player);
	m_pDataStore->AddDataSection(L"Scene", (_uint)EDataID::Scene);
	
	m_pDataStore->InitDataForScene(L"StaticScene", true);
	m_pMeshStore->InitMeshForScene(L"StaticScene", true);
	m_pTextureStore->InitTextureForScene(L"StaticScene", true);

	m_pDataStore->InitDataForScene(m_objectKey);
	m_pMeshStore->InitMeshForScene(m_objectKey);
	m_pTextureStore->InitTextureForScene(m_objectKey);

	InitPrototypes();

	m_pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_pMenuView = dynamic_cast<CToolMenuView*>(m_pMain->GetMainSplitter().GetPane(0, 1));
}

void CEditorScene::Start(void)
{
	__super::Start();

	//SP(Engine::CObject) spEmptyObject
	//	= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Kiana");

	//spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
	//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	//spEmptyObject->AddComponent<Engine::CTextureC>();
	//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//spEmptyObject->GetTransform()->SetSize(10, 10, 10);
	//spEmptyObject->GetTransform()->SetPosition(0.f, 0.f, 0.f);

	SP(Engine::CObject) spCube
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

	spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
	spCube->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
	spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spCube->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	spCube->GetTransform()->SetSize(1, 1, 1);
	spCube->GetTransform()->SetPosition(0.f, 0.f, 0.f);

	spCube = m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube1");

	spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
	spCube->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
	spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spCube->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	spCube->GetTransform()->SetSize(1, 1, 1);
	spCube->GetTransform()->SetPosition(3.f, 0.f, 0.f);

	spCube = m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube2");

	spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
	spCube->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
	spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spCube->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	spCube->GetTransform()->SetSize(1, 1, 1);
	spCube->GetTransform()->SetPosition(6.f, 0.f, 0.f);

	//SP(Engine::CObject) spMap
	//	= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Map, L"S02");

	//spMap->AddComponent<Engine::CMeshC>()->AddMeshData(L"S02_del");
	//spMap->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	//spMap->AddComponent<Engine::CTextureC>();
	//spMap->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	//spMap->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
}

void CEditorScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CEditorScene::Update(void)
{
	__super::Update();
	m_pMenuView->Update();

	InputSetting();
}

void CEditorScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CEditorScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CEditorScene::OnEnable(void)
{
	__super::OnEnable();
}

void CEditorScene::OnDisable(void)
{
	__super::OnDisable();
}

void CEditorScene::InitPrototypes(void)
{
	SP(Engine::CObject) spEmptyObjectPrototype(Engine::CEmptyObject::Create(true, this));
	ADD_PROTOTYPE(spEmptyObjectPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(true, this));
	ADD_PROTOTYPE(spCameraPrototype);
}

void CEditorScene::InputSetting()
{
	// picking
	//if (Engine::IMKEY_DOWN(KEY_Z))
	//{
	//	m_pickingMode = !m_pickingMode;

	//	if (m_pickingMode)
	//		std::cout << "picking on" << std::endl;
	//	else
	//		std::cout << "picking off" << std::endl;
	//}

	_float3 intersection;

	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		Engine::CObject* pTarget = Engine::CInputManager::GetInstance()->MousePicking((_int)ELayerID::Player, intersection);

		if (true == m_createMode)
		{
			SP(Engine::CObject) spCube
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

			spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
			spCube->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spCube->AddComponent<Engine::CTextureC>();
			spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spCube->GetTransform()->SetSize(1, 1, 1);
			spCube->GetTransform()->SetPosition(intersection);

			std::cout << "create" << std::endl;
			m_pCurSelectedObject = spCube.get();
		}
		else if (nullptr != pTarget)
		{
			m_pCurSelectedObject = pTarget;
			std::wcout << pTarget->GetName() << std::endl;

			m_pMenuView->SetPosition(m_pCurSelectedObject->GetTransform()->GetPosition());
			m_pMenuView->SetRotation(m_pCurSelectedObject->GetTransform()->GetRotation());
			m_pMenuView->SetScale(m_pCurSelectedObject->GetTransform()->GetSize());
		}
		else
			std::wcout << "target not found" << std::endl;
	}

	// create
	if (Engine::IMKEY_DOWN(KEY_E))
	{
		if (false == m_createMode)
		{
			m_createMode = true;
			std::cout << "Create mode on" << std::endl;
		}
		else
		{
			m_createMode = false;
			std::cout << "Create mode off" << std::endl;
		}
	}

	if (false == m_pCurSelectedObject)
		return;

	// delete
	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		m_pCurSelectedObject->SetDeleteThis(true);
		std::cout << "del" << std::endl;
		m_pCurSelectedObject = nullptr;
	}

	// pos
	//if (Engine::IMKEY_DOWN(KEY_F5))
	//{
	//	_float3 objPos = m_pCurSelectedObject->GetTransform()->GetPosition();
	//	m_pCurSelectedObject->GetTransform()->SetSize(objPos.x + 0.1f, objPos.y + 0.1f, objPos.z + 0.1f);
	//}
	//else if (Engine::IMKEY_DOWN(KEY_F2))
	//{
	//	_float3 objPos = m_pCurSelectedObject->GetTransform()->GetPosition();
	//	m_pCurSelectedObject->GetTransform()->SetSize(objPos.x - 0.1f, objPos.y - 0.1f, objPos.z - 0.1f);
	//}

	// size
	//if (Engine::IMKEY_DOWN(KEY_F1))
	//{
	//	_float3 objSize = m_pCurSelectedObject->GetTransform()->GetSize();
	//	m_pCurSelectedObject->GetTransform()->SetSize(objSize.x + 0.1f, objSize.y + 0.1f, objSize.z + 0.1f);
	//}
	//else if (Engine::IMKEY_DOWN(KEY_F2))
	//{
	//	_float3 objSize = m_pCurSelectedObject->GetTransform()->GetSize();
	//	m_pCurSelectedObject->GetTransform()->SetSize(objSize.x - 0.1f, objSize.y - 0.1f, objSize.z - 0.1f);
	//}

	// rot
	//if (Engine::IMKEY_DOWN(KEY_F3))
	//{
	//	_float3 objRot = m_pCurSelectedObject->GetTransform()->GetRotation();
	//	m_pCurSelectedObject->GetTransform()->SetSize(objRot.x + 0.1f, objRot.y + 0.1f, objRot.z + 0.1f);
	//}
	//else if (Engine::IMKEY_DOWN(KEY_F4))
	//{
	//	_float3 objRot = m_pCurSelectedObject->GetTransform()->GetRotation();
	//	m_pCurSelectedObject->GetTransform()->SetSize(objRot.x - 0.1f, objRot.y - 0.1f, objRot.z - 0.1f);
	//}
}
