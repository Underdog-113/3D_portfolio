#include "stdafx.h"
#include "MainMapTool.h"

#include "CameraManager.h"
#include "CollisionManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
//#include "SoundManager.h"
#include "SceneManager.h"
#include "TextManager.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "FRC.h"

#pragma region IncludeScenes
#include "EditorScene.h"
#pragma endregion

CMainMapTool::CMainMapTool()
{
}

CMainMapTool::~CMainMapTool()
{
	OnDestroy();
}

SP(CMainMapTool) CMainMapTool::Create(void)
{
	SP(CMainMapTool) spMainEditor(new CMainMapTool, Engine::SmartDeleter<CMainMapTool>);
	
	return spMainEditor;
}

void CMainMapTool::Awake(void)
{
	srand((_uint)time(NULL));

	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CCollisionManager::GetInstance()->Awake();
	Engine::CCameraManager::GetInstance()->Awake();
	Engine::CTextManager::GetInstance()->Awake();
}

void CMainMapTool::Start(void)
{
	InitStaticPrototype();

	Engine::CGraphicsManager::GetInstance()->Start();
	//Engine::CShaderManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CEditorScene::Create());
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CCameraManager::GetInstance()->Start();
	Engine::CTextManager::GetInstance()->Start();

	Engine::CCollisionManager::GetInstance()->Start((_int)EColliderID::NumOfColliderID);
}

void CMainMapTool::FixedUpdate(void)
{
	Engine::CSceneManager::GetInstance()->FixedUpdate();
	Engine::CInputManager::GetInstance()->FixedUpdate();
	Engine::CGraphicsManager::GetInstance()->FixedUpdate();
}

void CMainMapTool::Update(void)
{
	Engine::CInputManager::GetInstance()->Update();
	Engine::CSceneManager::GetInstance()->Update();
	Engine::CCameraManager::GetInstance()->Update();
	Engine::CCollisionManager::GetInstance()->Update();
	Engine::CGraphicsManager::GetInstance()->Update();
}

void CMainMapTool::LateUpdate(void)
{
	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();
	Engine::CCameraManager::GetInstance()->LateUpdate();
	Engine::CCollisionManager::GetInstance()->LateUpdate();
	Engine::CGraphicsManager::GetInstance()->LateUpdate();
}

void CMainMapTool::PreRender(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->PreRender();
	Engine::CTextManager::GetInstance()->Render();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainMapTool::Render(void)
{
	Engine::CGraphicsManager::GetInstance()->Render();
	Engine::CTextManager::GetInstance()->Render();
}

void CMainMapTool::PostRender(void)
{
	Engine::CGraphicsManager::GetInstance()->PostRender();
	Engine::CTextManager::GetInstance()->Render();
}

void CMainMapTool::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
	Engine::CShaderManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CCollisionManager::GetInstance()->DestroyInstance();
	Engine::CCameraManager::GetInstance()->DestroyInstance();
	Engine::CTextManager::GetInstance()->DestroyInstance();
}

void CMainMapTool::OnEnable(void)
{
}

void CMainMapTool::OnDisable(void)
{
}

void CMainMapTool::InitStaticPrototype(void)
{
}
