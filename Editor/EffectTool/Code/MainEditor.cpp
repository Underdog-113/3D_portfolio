#include "stdafx.h"
#include "..\Header\MainEditor.h"

#include "CameraManager.h"
#include "GraphicsManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "FRC.h"
#include "EffectToolScene.h"
#include "WaterShader.h"
#include "EffectShader.h"
#include "DamageFontShader.h"
#include "CatPawShader.h"
#include "CircularGaugeShader.h"
#include "MeshTrailShader.h"
#include "DissolveShader.h"
#include "SpawnEffectShader.h"
#include "SoftEffectShader.h"
#include "AttackRangeShader.h"
#include "AlphaMaskShader.h"

#pragma region Shader


#pragma endregion


CMainEditor::CMainEditor()
{
}


CMainEditor::~CMainEditor()
{
	OnDestroy();
}

SP(CMainEditor) CMainEditor::Create()
{
	SP(CMainEditor) spMainEditor(new CMainEditor, Engine::SmartDeleter<CMainEditor>);

	return spMainEditor;
}

void CMainEditor::Awake()
{
	srand((_uint)time(NULL));

	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CCollisionManager::GetInstance()->Awake();
	Engine::CCameraManager::GetInstance()->Awake();
	Engine::CRenderTargetManager::GetInstance()->Awake();
	Engine::CTextManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->InitShaderList((_uint)EShaderID::NumOfShaderID);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CWaterShader::Create(), L"WaterShader", (_uint)EShaderID::WaterShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CEffectShader::Create(), L"EffectShader", (_uint)EShaderID::EffectShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CDamageFontShader::Create(), L"DamageFontShader", (_uint)EShaderID::DamageFontShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CCatPawShader::Create(), L"CatPawShader", (_uint)EShaderID::CatPawShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CCircularGaugeShader::Create(), L"CircularGaugeShader", (_uint)EShaderID::CircularGaugeShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CMeshTrailShader::Create(), L"MeshTrailShader", (_uint)EShaderID::MeshTrailShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CDissolveShader::Create(), L"DissolveShader", (_uint)EShaderID::DissolveShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CSpawnEffectShader::Create(), L"SpawnEffectShader", (_uint)EShaderID::SpawnEffectShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CSoftEffectShader::Create(), L"SoftEffectShader", (_uint)EShaderID::SoftEffectShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CAttackRangeShader::Create(), L"AttackRangeShader", (_uint)EShaderID::AttackRangeShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CAlphaMaskShader::Create(), L"AlphaMaskShader", (_uint)EShaderID::AlphaMaskShader);
}

void CMainEditor::Start()
{
	Engine::CGraphicsManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CEffectToolScene::Create());
	Engine::CCollisionManager::GetInstance()->Start((_int)ECollisionID::NumOfColliderID);
	Engine::CCameraManager::GetInstance()->Start();
	Engine::CRenderTargetManager::GetInstance()->Start();
	Engine::CTextManager::GetInstance()->Start();
}

void CMainEditor::FixedUpdate(void)
{
	Engine::CSceneManager::GetInstance()->FixedUpdate();
	Engine::CInputManager::GetInstance()->FixedUpdate();
	Engine::CGraphicsManager::GetInstance()->FixedUpdate();
}

void CMainEditor::Update(void)
{
	Engine::CInputManager::GetInstance()->Update();
	Engine::CSceneManager::GetInstance()->Update();
	Engine::CCameraManager::GetInstance()->Update();
	Engine::CGraphicsManager::GetInstance()->Update();
}

void CMainEditor::LateUpdate(void)
{
	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();
	Engine::CCameraManager::GetInstance()->LateUpdate();
	Engine::CGraphicsManager::GetInstance()->LateUpdate();
}

void CMainEditor::PreRender(void)
{
	Engine::TIME_MEASURE_START;

	Engine::CGraphicsManager::GetInstance()->PreRender();
	Engine::CTextManager::GetInstance()->Render();

	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainEditor::Render(void)
{
	Engine::CGraphicsManager::GetInstance()->Render();
	Engine::CTextManager::GetInstance()->Render();
}

void CMainEditor::PostRender(void)
{
	Engine::CGraphicsManager::GetInstance()->PostRender();
	Engine::CTextManager::GetInstance()->Render();
}

void CMainEditor::OnDestroy(void)
{
    Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CCollisionManager::GetInstance()->DestroyInstance();
	Engine::CCameraManager::GetInstance()->DestroyInstance();
	Engine::CRenderTargetManager::GetInstance()->DestroyInstance();
	Engine::CShaderManager::GetInstance()->DestroyInstance();
	Engine::CPSC_Manager::GetInstance()->DestroyInstance();
	Engine::CTextManager::GetInstance()->DestroyInstance();
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
}

void CMainEditor::OnEnable(void)
{
}

void CMainEditor::OnDisable(void)
{
}

