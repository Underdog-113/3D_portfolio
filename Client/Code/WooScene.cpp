#include "stdafx.h"
#include "WooScene.h"

#include "StageControlTower.h"
#include "Kiana.h"

/* for.Monster */
#include "FSM_SpiderC.h"
#include "MO_Spider.h"

#include "FSM_SickleC.h"
#include "MO_Sickle.h"

#include "FSM_GaneshaC.h"
#include "MB_Ganesha.h"

#include "PatternMachineC.h"
#include "ClientPatterns.h"
/**/

#include "DataLoad.h"

CWooScene::CWooScene()
{
}

CWooScene::~CWooScene()
{
	m_pController->DestroyInstance();
}

CClientScene* CWooScene::Create(void)
{
	CWooScene* pInstance = new CWooScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CWooScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CWooScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	InitPrototypes();

	m_pController = CStageControlTower::GetInstance();
	m_pController->Awake();
}

void CWooScene::Start(void)
{
	__super::Start();

	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	//Load->MapLoad(this);
	delete(Load);

	CBattleUiManager::GetInstance()->Start(this);

	TerrainSetting();

	PlayerSetting();
	//SpiderSetting();
	//SickleSetting();
	GaneshaSetting();
}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	static int a = 5;

	if (a == 5)
	{
		Engine::CTextManager::GetInstance()->AddText(L"SEX", L"", _float2(50, 50), _float2(100, 100), 30, 30, D3DXCOLOR(0, 0, 0, 1));
		a = 6;
	}

	__super::Update();

	


	m_pController->Update();

	if (Engine::IMKEY_DOWN(MOUSE_WHEEL))
	{
		std::dynamic_pointer_cast<CMonster>(m_spGanesha)->GetStat()->SetCurHp(0.f);
		m_spGanesha->GetComponent<CPatternMachineC>()->SetOnDie(true);
	}
}

void CWooScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CWooScene::OnDestroy(void)
{
	__super::OnDestroy();

	m_pController->DestroyInstance();
}

void CWooScene::OnEnable(void)
{
	__super::OnEnable();
}

void CWooScene::OnDisable(void)
{
	__super::OnDisable();
}

void CWooScene::InitPrototypes(void)
{
}

void CWooScene::PlayerSetting(void)
{
	/* Kiana Setting */
	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

	m_spKiana = spKianaClone;
	m_pController->AddSquadMember(m_spKiana);
	m_pController->Start(CStageControlTower::ALL);

	//spKianaClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);

	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spKiana);
	cam->SetTargetDist(2.f);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
}

void CWooScene::TerrainSetting(void)
{
	SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

	/*spCube->AddComponent<Engine::CMeshC>()->AddMeshData(L"Sphere");
	spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);*/
	spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

	spCube->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create((_int)ECollisionID::Floor, _float3(50, 0, 50)));
	spCube->GetComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));

	spCube->AddComponent<Engine::CDebugC>();
	spCube->AddComponent<Engine::CShaderC>()/*->AddShader((_int)Engine::EShaderID::MeshShader)*/;
	spCube->AddComponent<Engine::CRigidBodyC>();
	spCube->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
	spCube->GetTransform()->SetSize(10, 1, 10);
	spCube->GetTransform()->SetPosition(0, 0, 0);

	// 2
	m_pivot = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

	m_pivot->AddComponent<Engine::CMeshC>()->SetMeshData(L"Sphere");
	m_pivot->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
	m_pivot->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

	m_pivot->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 1.4f));
	m_pivot->GetComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));

	m_pivot->AddComponent<Engine::CDebugC>();
	m_pivot->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	m_pivot->AddComponent<Engine::CRigidBodyC>();
	m_pivot->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
	m_pivot->GetTransform()->SetSize(0.1f, 0.1f, 0.1f);

	//3		
	m_pivot_kiana = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");

	m_pivot_kiana->AddComponent<Engine::CMeshC>()->SetMeshData(L"Sphere");
	m_pivot_kiana->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
	m_pivot_kiana->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

	m_pivot_kiana->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 1.4f));
	m_pivot_kiana->GetComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));

	m_pivot_kiana->AddComponent<Engine::CDebugC>();
	m_pivot_kiana->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
	m_pivot_kiana->AddComponent<Engine::CRigidBodyC>();
	m_pivot_kiana->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
	m_pivot_kiana->GetTransform()->SetSize(0.1f, 0.1f, 0.1f);
}

void CWooScene::SickleSetting(void)
{
	/* Sickle */
	SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	spSickleClone->GetTransform()->SetPosition(0, 10, 2);
	spSickleClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSickleBornPattern::Create(), CSickleDiePattern::Create(), CSickleBasePattern::Create(), CSickleHitPattern::Create());
	m_spSickle = spSickleClone;
}

void CWooScene::GaneshaSetting(void)
{
	/* Ganesha */
	SP(Engine::CObject) spGaneshaClone = ADD_CLONE(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha");
	spGaneshaClone->GetTransform()->SetPosition(3, 0, 3);
	spGaneshaClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CGaneshaBornPattern::Create(), CGaneshaDiePattern::Create(), CGaneshaBasePattern::Create(), CGaneshaHitPattern::Create());
	//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaStampPattern::Create());
	//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaRoll01Pattern::Create());
	//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst01Pattern::Create());
	//spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst02Pattern::Create());
	m_spGanesha = spGaneshaClone;
}
 
void CWooScene::SpiderSetting(void)
{
	/* Spider */
	SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
	spSpiderClone->GetTransform()->SetPosition(-3, 0, -7);
	spSpiderClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSpiderBornPattern::Create(), CSpiderDiePattern::Create(), CSpiderBasePattern::Create(), CSpiderHitPattern::Create());
	m_spSpider = spSpiderClone;
}
