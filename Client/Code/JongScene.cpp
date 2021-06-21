#include "stdafx.h"
#include "JongScene.h"
#include "ObjectFactory.h"

#include "DynamicMeshData.h"

#include "StageControlTower.h"
#include "FSM_KianaC.h"
#include "Kiana.h"
#include "AniCtrl.h"

#include "Kiana_CatPaw_Atk01.h"
#include "Kiana_CatPaw_Atk02.h"
#include "Kiana_CatPaw_Atk03.h"
#include "Kiana_CatPaw_Atk04.h"
#include "Kiana_CatPaw_Atk05.h"

#include "Kiana_CatPaw_Ring_Atk01.h"
#include "Kiana_Pistol_USP45.h"

#include "DataLoad.h"

CJongScene::CJongScene()
{
}


CJongScene::~CJongScene()
{
}

CClientScene* CJongScene::Create(void)
{
	CJongScene* pInstance = new CJongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CJongScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CJongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pController = CStageControlTower::GetInstance();
	m_pController->Awake();
}

void CJongScene::Start(void)
{
	__super::Start();

	KianaTest();
	CollisionDummy();

	SetupStageUI();
}

void CJongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CJongScene::Update(void)
{
	__super::Update();
	m_pController->Update();
	//m_pivot->GetTransform()->SetPosition(m_spKiana->GetTransform()->GetPosition());
	//m_pivot->GetTransform()->SetPositionY(0.f);
}

void CJongScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CJongScene::OnDestroy(void)
{
	__super::OnDestroy();

	m_pController->DestroyInstance();
	m_pController = nullptr;
}

void CJongScene::OnEnable(void)
{
	__super::OnEnable();

}

void CJongScene::OnDisable(void)
{
	__super::OnDisable();

}

void CJongScene::InitPrototypes(void)
{
}

void CJongScene::KianaTest()
{
	// Kiana Body

	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

	m_spKiana = spKianaClone;
	m_pController->AddSquadMember(m_spKiana);
	//m_pController->Start(CStageControlTower::WithoutUI);
	m_pController->Start(CStageControlTower::ALL);


	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spKiana);
	cam->SetTargetDist(2.f);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);


	// cube terrain
	{

		SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");


		spCube->AddComponent<Engine::CCollisionC>()->
			AddCollider(Engine::CAabbCollider::Create((_int)ECollisionID::Floor, _float3(20.f, 1.f, 20.f)));

		spCube->AddComponent<Engine::CDebugC>();
		spCube->AddComponent<Engine::CShaderC>();
		spCube->GetTransform()->SetSize(10, 1, 10);
		spCube->GetTransform()->SetPosition(0, -0.5f, 0);

	}


}

void CJongScene::TheresaTest()
{
	// Theresa

	SP(Engine::CObject) spTheresaClone = ADD_CLONE(L"Theresa", true, (_uint)ELayerID::Player, L"Theresa");

	m_spTheresa = spTheresaClone;
	m_pController->AddSquadMember(m_spTheresa);
	m_pController->Start(CStageControlTower::WithoutUI);

	spTheresaClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);

	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spTheresa);
	cam->SetTargetDist(4.f);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
}

void CJongScene::CollisionDummy()
{
	SP(Engine::CObject) spDummy = ADD_CLONE(L"MO_Dummy", true, (_uint)ELayerID::Enemy, L"MO_Dummy");
	spDummy->GetTransform()->SetPosition(0, 0, 5);
	m_spDummy = spDummy;
}

void CJongScene::SetupStageUI()
{
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	//Load->ToolLoad(this);
	delete(Load);

	CBattleUiManager::GetInstance()->Start(this);
}
