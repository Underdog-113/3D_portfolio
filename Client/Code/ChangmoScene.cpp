#include "stdafx.h"
#include "ChangmoScene.h"
#include "EmptyObject.h"
#include "SkyBox.h"
#include "Kiana.h"
#include "PhaseChanger.h"
#include "OneStagePhaseControl.h"

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

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
	
}

void CChangmoScene::Start(void)
{
	__super::Start();

	{
		SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

		m_spKiana = spKianaClone;
		m_pControlTower->AddSquadMember(m_spKiana);
		m_pControlTower->Start(CStageControlTower::WithoutUI);
		//m_pControlTower->Start(CStageControlTower::ALL);


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

		{
			SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");


			spCube->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CObbCollider::Create((_int)ECollisionID::Wall, _float3(3.f, 3.f, 3.f), _float3(4, 1.5f, 4), _float3(0, PI / 3, 0)));

			spCube->AddComponent<Engine::CDebugC>();
			spCube->AddComponent<Engine::CShaderC>();
		}

		{
			SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");


			spCube->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CObbCollider::Create((_int)ECollisionID::Floor, _float3(20.f, 1.f, 20.f), ZERO_VECTOR, _float3(PI/6, 0, 0)));

			spCube->AddComponent<Engine::CDebugC>();
			spCube->AddComponent<Engine::CShaderC>();
			spCube->GetTransform()->SetSize(10, 1, 10);
			spCube->GetTransform()->SetPosition(20, -1.f, 0);
		}


		SP(Engine::CObject) spSkyBox = ADD_CLONE(L"SkyBox", true);		



		m_spDummy = ADD_CLONE(L"MO_Sickle", true);
		m_spDummy->GetTransform()->SetPosition(0, 0, 5);

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
