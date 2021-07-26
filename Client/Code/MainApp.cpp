#include "stdafx.h"
#include "MainApp.h"
#include "Object.h"
#include "WndApp.h"
#pragma region IncludeScenes
#include "InitScene.h"
#pragma endregion

#pragma region objectpool
#include "DamageObjectPool.h"
#pragma endregion

#pragma region Shader
#include "WaterShader.h"
#include "DamageFontShader.h"
#include "CatPawShader.h"
#include "CircularGaugeShader.h"
#include "MeshTrailShader.h"
#include "DissolveShader.h"
#include "SpawnEffectShader.h"
#include "SoftEffectShader.h"
#include "AttackRangeShader.h"
#include "AlphaMaskShader.h"
#include "FireShader.h"
#include "LaserTrailShader.h"
#include "OutlineShader.h"
#include "FaceShader.h"
#include "KianaBodyShader.h"
#include "AlphaMaskGlowShader.h"
#include "SoftEffectShader_Glow.h"
#include "MeshTrailShader_Glow.h"
#include "DissolveShader_Glow.h"
#include "UltScrShader.h"
#include "ElevatorBaseShader.h"
#include "BronyaShader.h"
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
	//LoadSounds();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CCameraManager::GetInstance()->Awake();
	Engine::CGraphicsManager::GetInstance()->Awake();
	Engine::CPSC_Manager::GetInstance()->Awake();
	Engine::CCollisionManager::GetInstance()->Awake();
	Engine::CRenderTargetManager::GetInstance()->Awake();

	// Load Shader
	Engine::CShaderManager::GetInstance()->Awake();
	Engine::CShaderManager::GetInstance()->InitShaderList((_uint)EShaderID::NumOfShaderID);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CWaterShader::Create(), L"WaterShader", (_uint)EShaderID::WaterShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CDamageFontShader::Create(), L"DamageFontShader", (_uint)EShaderID::DamageFontShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CCatPawShader::Create(), L"CatPawShader", (_uint)EShaderID::CatPawShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CCircularGaugeShader::Create(), L"CircularGaugeShader", (_uint)EShaderID::CircularGaugeShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CMeshTrailShader::Create(), L"MeshTrailShader", (_uint)EShaderID::MeshTrailShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CDissolveShader::Create(), L"DissolveShader", (_uint)EShaderID::DissolveShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CSpawnEffectShader::Create(), L"SpawnEffectShader", (_uint)EShaderID::SpawnEffectShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CSoftEffectShader::Create(), L"SoftEffectShader", (_uint)EShaderID::SoftEffectShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CAttackRangeShader::Create(), L"AttackRangeShader", (_uint)EShaderID::AttackRangeShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CAlphaMaskShader::Create(), L"AlphaMaskShader", (_uint)EShaderID::AlphaMaskShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CFireShader::Create(), L"FireShader", (_uint)EShaderID::FireShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CLaserTrailShader::Create(), L"LaserTrail", (_uint)EShaderID::LaserShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(COutlineShader::Create(), L"OutlineShader", (_uint)EShaderID::OutlineShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CFaceShader::Create(), L"FaceShader", (_uint)EShaderID::FaceShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CKianaBodyShader::Create(), L"KianaBodyShader", (_uint)EShaderID::KianaBodyShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CAlphaMaskGlowShader::Create(), L"AlphaMaskGlowShader", (_uint)EShaderID::AlphaMaskGlowShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CSoftEffectShader_Glow::Create(), L"SoftEffectShader_Glow", (_uint)EShaderID::SoftEffectShader_Glow);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CMeshTrailShader_Glow::Create(), L"MeshTrailShader_Glow", (_uint)EShaderID::MeshTrailShader_Glow);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CDissolveShader_Glow::Create(), L"DissolveShader_Glow", (_uint)EShaderID::DissolveShader_Glow);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CUltScrShader::Create(), L"UltScrShader", (_uint)EShaderID::UltScrShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CElevatorBaseShader::Create(), L"ElevatorBaseShader", (_uint)EShaderID::ElevatorBaseShader);
	Engine::CShaderManager::GetInstance()->AddKeyAndShader(CBronyaShader::Create(), L"BronyaShader", (_uint)EShaderID::BronyaShader);

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
	Engine::CCollisionManager::GetInstance()->Start((_int)ECollisionID::NumOfColliderID);
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

	CDamageObjectPool::GetInstance()->Update();

	CDataManager::GetInstance()->Update();
	_float time = Engine::GET_ELAPSED_TIME;
}

void CMainApp::LateUpdate(void)
{
	if (Engine::IMKEY_DOWN(MOUSE_LEFT))
	{
		_float2 mousePos = Engine::CInputManager::GetInstance()->GetMousePos();
	}

	Engine::TIME_MEASURE_START;

	Engine::CInputManager::GetInstance()->LateUpdate();
	Engine::CCollisionManager::GetInstance()->LateUpdate();
	Engine::CSceneManager::GetInstance()->LateUpdate();

	Engine::CCameraManager::GetInstance()->LateUpdate();
	Engine::CGraphicsManager::GetInstance()->LateUpdate();
	Engine::CPSC_Manager::GetInstance()->LateUpdate();
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
	CStageControlTower::DestroyInstance();

	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CCollisionManager::GetInstance()->DestroyInstance();
	Engine::CSoundManager::GetInstance()->DestroyInstance();
	Engine::CCameraManager::GetInstance()->DestroyInstance();
	Engine::CRenderTargetManager::GetInstance()->DestroyInstance();
	Engine::CShaderManager::GetInstance()->DestroyInstance();
	Engine::CPSC_Manager::GetInstance()->DestroyInstance();
	//Engine::CPhysicsManager::GetInstance()->DestroyInstance();

	//Client Manager
	CButtonManager::GetInstance()->DestroyInstance();
	CDataManager::GetInstance()->DestroyInstance();

	CReadyToSortieManager::GetInstance()->DestroyInstance();
	CBattleEndManager::GetInstance()->DestroyInstance();
	CBattleUiManager::GetInstance()->DestroyInstance();
	CMainRoomManager::GetInstance()->DestroyInstance();
	CStageSelectionManager::GetInstance()->DestroyInstance();
	CValkyriegManager::GetInstance()->DestroyInstance();
	CInventoryManager::GetInstance()->DestroyInstance();
	CBattleEndManager::GetInstance()->DestroyInstance();
	CDropItemManager::GetInstance()->DestroyInstance();
	CSupplyManager::GetInstance()->DestroyInstance();
	//Object Pool
	CDamageObjectPool::GetInstance()->DestroyInstance();

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

void CMainApp::LoadSounds()
{
	//Engine::CSoundManager::GetInstance()->LoadSoundFile(L"BGM");
	//Engine::CSoundManager::GetInstance()->LoadSoundFile(L"Kiana");
}
