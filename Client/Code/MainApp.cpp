#include "stdafx.h"
#include "MainApp.h"
#include "Object.h"

#pragma region IncludeScenes
#include "InitScene.h"
#pragma endregion

#pragma region Prototypes
#include "Camera.h"
#pragma endregion


CMainApp::CMainApp(void)
{
}

CMainApp::~CMainApp(void)
{
}

SP(CMainApp) CMainApp::Create(void)
{
	SP(CMainApp) pMainApp(new CMainApp, Engine::SmartDeleter<CMainApp>);

	return pMainApp;
}
void CMainApp::Awake(void)
{
	srand((_uint)time(NULL));

	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSoundManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CCameraManager::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CPSC_Manager::GetInstance()->Awake();
	Engine::CCollisionManager::GetInstance()->Awake();
	Engine::CRenderTargetManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();

	//Client Manager
	CButtonManager::GetInstance()->Awake();
}

void CMainApp::Start(void)
{
	InitStaticPrototype();

	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CInitScene::Create());
	Engine::CCameraManager::GetInstance()->Start();
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CPSC_Manager::GetInstance()->Start();
	Engine::CCollisionManager::GetInstance()->Start((_int)EColliderID::NumOfColliderID);
	Engine::CRenderTargetManager::GetInstance()->Start();
}

void CMainApp::FixedUpdate(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CSceneManager::GetInstance()->FixedUpdate();
	Engine::CInputManager::GetInstance()->FixedUpdate();
	Engine::CGraphicsManager::GetInstance()->FixedUpdate();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::Update(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CInputManager::GetInstance()->Update();

	Engine::CSceneManager::GetInstance()->Update();
	CButtonManager::GetInstance()->Update();
	Engine::CCollisionManager::GetInstance()->Update();

	Engine::CCameraManager::GetInstance()->Update();
	Engine::CGraphicsManager::GetInstance()->Update();


	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::LateUpdate(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CCollisionManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();

	Engine::CCameraManager::GetInstance()->LateUpdate();
	Engine::CGraphicsManager::GetInstance()->LateUpdate();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::PreRender(void)
{
	_bool sceneChanged;
	if (sceneChanged = Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	Engine::TIME_MEASURE_START;
	
	Engine::CGraphicsManager::GetInstance()->PreRender();
	Engine::CTextManager::GetInstance()->PreRender();
	

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::Render(void)
{
	_bool sceneChanged;
	if (sceneChanged = Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	Engine::TIME_MEASURE_START;
	
	Engine::CGraphicsManager::GetInstance()->Render();
	Engine::CTextManager::GetInstance()->Render();


	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::PostRender(void)
{
	if (Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	Engine::TIME_MEASURE_START;
	
	Engine::CGraphicsManager::GetInstance()->PostRender();
	Engine::CTextManager::GetInstance()->PostRender();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CCollisionManager::GetInstance()->DestroyInstance();
	Engine::CSoundManager::GetInstance()->DestroyInstance();
	Engine::CCameraManager::GetInstance()->DestroyInstance();
	Engine::CRenderTargetManager::GetInstance()->DestroyInstance();
	Engine::CShaderManager::GetInstance()->DestroyInstance();
	Engine::CPSC_Manager::GetInstance()->DestroyInstance();

	//Client Manager
	CButtonManager::GetInstance()->DestroyInstance();
}

void CMainApp::OnEnable(void)
{

}

void CMainApp::OnDisable(void)
{
}

void CMainApp::InitStaticPrototype(void)
{

}
