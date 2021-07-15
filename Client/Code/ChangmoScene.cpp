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
		SP(Engine::CObject) spCube0 = ADD_CLONE(L"EmptyObject", true, (_uint)ELayerID::Player, L"Parent");
		spCube0->AddComponent<Engine::CMeshC>()->SetMeshData(L"Cube");
		spCube0->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall");
		spCube0->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spCube0->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		spCube0->AddComponent<Engine::CCollisionC>()->AddCollider(Engine::CSphereCollider::Create((_int)ECollisionID::EnemyHitBox));
		spCube0->AddComponent<Engine::CDebugC>();
	
		SP(Engine::CObject) spCube1 = ADD_CLONE(L"EmptyObject", true, (_uint)ELayerID::Player, L"Child");
		spCube1->AddComponent<Engine::CMeshC>()->SetMeshData(L"Cube");
		spCube1->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall");
		spCube1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spCube1->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		//spCube1->GetTransform()->SetParent(spCube0->GetTransform());
		spCube1->GetTransform()->SetPosition(2, 0, 0);
		spCube1->GetTransform()->SetParent(spCube0->GetTransform());
		spCube1->AddComponent<Engine::CCollisionC>()->AddCollider(Engine::CSphereCollider::Create((_int)ECollisionID::EnemyHitBox));
		spCube1->AddComponent<Engine::CDebugC>();
		//spCube1->GetTransform()->SetParentMatrix(&spCube0->GetTransform()->GetWorldMatrix());
	
	
		SP(Engine::CObject) spCube2 = ADD_CLONE(L"EmptyObject", true, (_uint)ELayerID::Player, L"no");
		spCube2->AddComponent<Engine::CMeshC>()->SetMeshData(L"Cube");
		spCube2->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall");
		spCube2->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spCube2->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		spCube2->AddComponent<Engine::CCollisionC>()->AddCollider(Engine::CSphereCollider::Create((_int)ECollisionID::EnemyHitBox));
		spCube2->AddComponent<Engine::CDebugC>();
		spCube2->GetTransform()->AddPositionX(5);
	}

	{
		//SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

		//m_spKiana = spKianaClone;
		//m_pControlTower->AddSquadMember(m_spKiana);
		//m_pControlTower->Start(CStageControlTower::WithoutUI);
		////m_pControlTower->Start(CStageControlTower::ALL);


		//auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
		//cam->SetTarget(spKianaClone);
		//cam->SetTargetDist(2.f);
		//CStageControlTower::GetInstance()->SetCurrentMainCam(cam);

		//cam->SetMode(Engine::ECameraMode::TPS);

		// cube terrain
		{
			SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");


			spCube->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CObbCollider::Create((_int)ECollisionID::Floor, _float3(20.f, 1.f, 20.f)));

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

		SP(Engine::CImageObject) spImageObject
			= std::dynamic_pointer_cast<Engine::CImageObject>(m_pObjectFactory->AddClone(L"ImageObject", true));
		spImageObject->GetTexture()->AddTexture(L"White");
		spImageObject->GetTransform()->SetPositionZ(0);
		spImageObject->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
		spImageObject->GetRectTex()->SetIsOrtho(true);
		spImageObject->GetTransform()->SetSize(100, 100, 1);
		spImageObject->AddComponent<Engine::CFadeInOutC>();
		//m_spDummy = ADD_CLONE(L"MO_Sickle", true);
		//m_spDummy->GetTransform()->SetPosition(0, 0, 5);

	}


}

void CChangmoScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CChangmoScene::Update(void)
{
	__super::Update();
	//CStageControlTower::GetInstance()->Update();

	

	if (Engine::IMKEY_DOWN(KEY_W))
		FindObjectByName(L"Parent")->AddComponent<Engine::CFadeInOutC>();//GetTransform()->SetForwardUp(_float3(1, 0, 0), _float3(0, 1, 1));
	if (Engine::IMKEY_PRESS(KEY_A))
		FindObjectByName(L"Parent")->GetTransform()->SetForwardUp(_float3(1, 0, 1), _float3(0, 1, 0));
	if (Engine::IMKEY_PRESS(KEY_RIGHT))
		FindObjectByName(L"Parent")->GetTransform()->AddRotationZ(PI / 90);
	if (Engine::IMKEY_PRESS(KEY_DOWN))
		FindObjectByName(L"Parent")->GetTransform()->AddRotationX(PI / 90);
	
	if (Engine::IMKEY_DOWN(KEY_E))
		FindObjectByName(L"Parent")->SetDeleteThis(true);
	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		FindObjectByName(L"Parent")->GetTransform()->SetPosition(0, 0, 0);
		FindObjectByName(L"Parent")->GetTransform()->SetRotation(0, 0, 0);
	}
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
