#include "stdafx.h"
#include "EditorScene.h"
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

	//m_pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	//m_pEditorView = dynamic_cast<CMy3DEditorView*>(m_pMain->m_mainSplitter.GetPane(0, 0));
	//m_pInspectorView = dynamic_cast<CInspectorView*>(m_pMain->m_mainSplitter.GetPane(0, 1));
}

void CEditorScene::Start(void)
{
	__super::Start();

	SP(Engine::CObject) spEmptyObject
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

	spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
	spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spEmptyObject->AddComponent<Engine::CTextureC>();
	spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spEmptyObject->GetTransform()->SetSize(10, 10, 10);
}

void CEditorScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CEditorScene::Update(void)
{
	__super::Update();
	m_pMenuView->Update();
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
	GetObjectFactory()->AddPrototype(spEmptyObjectPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(true, this));
	ADD_PROTOTYPE(spCameraPrototype);
}