#include "stdafx.h"
#include "WooScene.h"

#include "DataLoad.h"

/* for.Monster */
#include "MO_Spider.h"
#include "MO_Sickle.h"
#include "MO_Scout.h"
#include "MO_Lancer.h"
#include "MO_Robot.h"
#include "MO_Ninza.h"
#include "MB_Ganesha.h"
#include "MB_Bronya.h"

/* for.Player */
#include "StageControlTower.h"
#include "Kiana.h"

#include "AniCtrl.h"

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
	//Load->PhaseChangerLoad(this);
	delete(Load);

	CBattleUiManager::GetInstance()->Start(this);

	// ¸Ê Å°¸é ²À ÁÖ¼®!!!!!!!!!!!!!!
	TerrainSetting();

	PlayerSetting();
	//SpiderSetting();
	//SickleSetting();
	//GaneshaSetting();
	//ScoutSetting(); // ÇÏ´ÃÀÇ ¿ÕÀÚÁö..
	//LancerSetting();
	//RobotSetting();
	//NinzaSetting();
	BronyaSetting();
}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	__super::Update();

	m_pController->Update();

	//if (Engine::IMKEY_DOWN(KEY_Q))
	//{
	//	switch (m_index)
	//	{
	//	case 0:
	//		LancerSetting();
	//		break;
	//	case 1:
	//		RobotSetting();
	//		break;
	//	case 2:
	//		ScoutSetting();
	//		break;
	//	}

	//	++m_index;

	//	if (m_index >= 3)
	//		m_index = 0;
	//}

	//if (Engine::IMKEY_DOWN(KEY_E))
	//{
	//	if ()
	//}
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
	CStageControlTower::GetInstance()->ActorControl_SetCurrentMainCam(cam);
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
	//SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	//spSickleClone->GetTransform()->SetPosition(0, 10, 2);
	//std::dynamic_pointer_cast<CMonster>(spSickleClone)->SelectChannelID();
	//m_spSickle = spSickleClone;

	SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	spSickleClone->GetTransform()->SetPosition(0, 0, 3);
	std::dynamic_pointer_cast<CMonster>(spSickleClone)->SelectChannelID();
	m_vSickles.emplace_back(spSickleClone);

	//spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	//spSickleClone->GetTransform()->SetPosition(5, 0, 5);
	//std::dynamic_pointer_cast<CMonster>(spSickleClone)->SelectChannelID();
	//m_vSickles.emplace_back(spSickleClone);

	//spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	//spSickleClone->GetTransform()->SetPosition(2, 0, 2);
	//std::dynamic_pointer_cast<CMonster>(spSickleClone)->SelectChannelID();
	//m_vSickles.emplace_back(spSickleClone);

	//spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	//spSickleClone->GetTransform()->SetPosition(5, 0, 7);
	//std::dynamic_pointer_cast<CMonster>(spSickleClone)->SelectChannelID();
	//m_vSickles.emplace_back(spSickleClone);
}

void CWooScene::GaneshaSetting(void)
{
	/* Ganesha */
	SP(Engine::CObject) spGaneshaClone = ADD_CLONE(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha");
	spGaneshaClone->GetTransform()->SetPosition(3, 0, 3);
	std::dynamic_pointer_cast<CMonster>(spGaneshaClone)->SelectChannelID();
	m_spGanesha = spGaneshaClone;
}

void CWooScene::BronyaSetting(void)
{
	/* Bronya */
	SP(Engine::CObject) spBronyaClone = ADD_CLONE(L"MB_Bronya", true, (_uint)ELayerID::Enemy, L"MB_Bronya");
	spBronyaClone->GetTransform()->SetPosition(0, 0, 0);
	std::dynamic_pointer_cast<CMonster>(spBronyaClone)->SelectChannelID();
	m_spBronya = spBronyaClone;

	/* Weapon */
	SP(Engine::CObject) spWeaponClone = ADD_CLONE(L"Bronya_Weapon", true, (_uint)ELayerID::Enemy, L"Bronya_Weapon");
	m_spBronyaWeapon = spWeaponClone;
}
 
void CWooScene::SpiderSetting(void)
{
	/* Spider */
	SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
	spSpiderClone->GetTransform()->SetPosition(-3, 0, -7);
	std::dynamic_pointer_cast<CMonster>(spSpiderClone)->SelectChannelID();
	m_spSpider = spSpiderClone;
}

void CWooScene::ScoutSetting(void)
{
	/* Scout */
	SP(Engine::CObject) spScoutClone = ADD_CLONE(L"MO_Scout", true, (_uint)ELayerID::Enemy, L"MO_Scout");
	spScoutClone->GetTransform()->SetPosition(3, 0, 3);
	std::dynamic_pointer_cast<CMonster>(spScoutClone)->SelectChannelID();
	m_spScout = spScoutClone;
}

void CWooScene::LancerSetting(void)
{
	/* Lancer */
	SP(Engine::CObject) spLancerClone = ADD_CLONE(L"MO_Lancer", true, (_uint)ELayerID::Enemy, L"MO_Lancer");
	spLancerClone->GetTransform()->SetPosition(3, 0, 3);
	std::dynamic_pointer_cast<CMonster>(spLancerClone)->SelectChannelID();
	m_spLancer = spLancerClone;
}

void CWooScene::RobotSetting(void)
{
	/* Robot */
	SP(Engine::CObject) spRobotClone = ADD_CLONE(L"MO_Robot", true, (_uint)ELayerID::Enemy, L"MO_Robot");
	spRobotClone->GetTransform()->SetPosition(3, 0, 3);
	std::dynamic_pointer_cast<CMonster>(spRobotClone)->SelectChannelID();
	m_spRobot = spRobotClone;
}

void CWooScene::NinzaSetting(void)
{
	/* Ninza */
	SP(Engine::CObject) spNinzaClone = ADD_CLONE(L"MO_Ninza", true, (_uint)ELayerID::Enemy, L"MO_Ninza");
	spNinzaClone->GetTransform()->SetPosition(0,0,0);
	std::dynamic_pointer_cast<CMonster>(spNinzaClone)->SelectChannelID();
	m_spNinza = spNinzaClone;

	//m_spNinza->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0.1f);
}
