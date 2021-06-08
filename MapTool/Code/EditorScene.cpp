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
	m_pDataStore->AddDataSection(L"Enemy", (_uint)EDataID::Enemy);
	m_pDataStore->AddDataSection(L"UI", (_uint)EDataID::UI);

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

	SP(Engine::CObject) spCube
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

	spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
	spCube->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
	spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spCube->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	spCube->GetTransform()->SetSize(300, 1, 300);
	spCube->GetTransform()->SetPosition(0.f, 0.f, 0.f);
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

		if (true == m_createMode) // 클릭시 오브젝트 생성
		{
			std::wstring fileName(m_pMenuView->GetCurSelFileName());

			SP(Engine::CObject) spObj
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

			spObj->AddComponent<Engine::CMeshC>()->AddMeshData(Engine::RemoveExtension(fileName));
			spObj->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spObj->AddComponent<Engine::CTextureC>();
			spObj->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
			spObj->GetTransform()->SetSize(1, 1, 1);
			spObj->GetTransform()->SetPosition(intersection);

			std::cout << "create" << std::endl;
			m_pCurSelectedObject = spObj.get();
			m_pMenuView->m_curObjName.SetWindowTextW(m_pCurSelectedObject->GetName().c_str());
		}
		else if (nullptr != pTarget)
		{
			if (L"Cube0" == pTarget->GetName())
				return;

			m_pCurSelectedObject = pTarget;
			m_pMenuView->m_curObjName.SetWindowTextW(m_pCurSelectedObject->GetName().c_str());
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

	// delete
	if (nullptr != m_pCurSelectedObject && Engine::IMKEY_DOWN(KEY_DELETE))
	{
		m_pCurSelectedObject->SetDeleteThis(true);
		std::cout << "del" << std::endl;
		m_pCurSelectedObject = nullptr;
	}
}
