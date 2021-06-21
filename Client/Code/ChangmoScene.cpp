#include "stdafx.h"
#include "ChangmoScene.h"
#include "EmptyObject.h"
#include "SkyBox.h"
#include "Kiana.h"


CChangmoScene::CChangmoScene()
{
}


CChangmoScene::~CChangmoScene()
{
}

CClientScene* CChangmoScene::Create(void)
{
	CChangmoScene* pInstance = new CChangmoScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CChangmoScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CChangmoScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	CStageControlTower::GetInstance()->Awake();
}

void CChangmoScene::Start(void)
{
	__super::Start();

	{
		SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");
		CStageControlTower::GetInstance()->AddSquadMember(spKianaClone);
		//m_pController->Start(CStageControlTower::WithoutUI);
		CStageControlTower::GetInstance()->Start(CStageControlTower::ALL);


		auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
		cam->SetTarget(spKianaClone);
		cam->SetTargetDist(2.f);
		CStageControlTower::GetInstance()->SetCurrentMainCam(cam);

		cam->SetMode(Engine::ECameraMode::TPS);

		// cube terrain
		{

			SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");


			spCube->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CAabbCollider::Create((_int)ECollisionID::Floor, _float3(20.f, 1.f, 20.f)));

			spCube->AddComponent<Engine::CDebugC>();
			spCube->AddComponent<Engine::CShaderC>();
			spCube->GetTransform()->SetSize(10, 1, 10);
			spCube->GetTransform()->SetPosition(0, -1.f, 0);

		}


		SP(Engine::CObject) spSkyBox = ADD_CLONE(L"SkyBox", true);		
	}


}

void CChangmoScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CChangmoScene::Update(void)
{
	__super::Update();
	CStageControlTower::GetInstance()->Update();
}

void CChangmoScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CChangmoScene::OnDestroy(void)
{
	__super::OnDestroy();
	CStageControlTower::GetInstance()->DestroyInstance();
}

void CChangmoScene::OnEnable(void)
{
	__super::OnEnable();
}

void CChangmoScene::OnDisable(void)
{
	__super::OnDisable();
}

void CChangmoScene::InitPrototypes(void)
{
}
