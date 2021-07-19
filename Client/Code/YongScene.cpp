#include "stdafx.h"
#include "YongScene.h"
#include "FRC.h"

#include "StageControlTower.h"
#include "Kiana.h"

#include "MonsterSpawnBeam.h"
#include "ScoutMeteor.h"
#include "Scout_Att_Range.h"
#include "Sakura_WSkill_Twist.h"
#include "Sakura_DashShade.h"
#include "..\..\Engine\Header\SoundManager.h"
CYongScene::CYongScene()
{
}


CYongScene::~CYongScene()
{
}

CClientScene * CYongScene::Create(void)
{
	CYongScene* pInstance = new CYongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CYongScene::Free(void)
{
	OnDestroy();

	delete this;
}

void CYongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	InitPrototypes();

	m_pController = CStageControlTower::GetInstance();
	m_pController->Awake();
}

void CYongScene::Start(void)
{
	__super::Start();
	{
		Engine::CSoundManager::GetInstance()->StopAll();
		// Kiana Ult
		/*SP(Engine::CObject) spMeshEffect
			= m_pObjectFactory->AddClone(L"Kiana_Ult_Eff", true, (_int)Engine::ELayerID::Effect, L"MeshEffect0");
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(L"Ring_Ground");
		spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"ring_ground");
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"ring_ground");
		spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);*/

		////SpawnAttackRange();
		//// Kiana Setting333
		//{
		//	SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

		//	m_spKiana = spKianaClone;
		//	m_pController->AddSquadMember(m_spKiana);
		//	m_pController->Start(CStageControlTower::WithoutUI);

		//	spKianaClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);

		//	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
		//	cam->SetTarget(m_spKiana);
		//	cam->SetTargetDist(4.f);
		//	CStageControlTower::GetInstance()->ActorControl_SetCurrentMainCam(cam);
		//}

		//// cube terrain
		//{

		//	SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");
		//
		//	spCube->AddComponent<Engine::CMeshC>()->SetMeshData(L"Sphere");
		//	spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
		//	spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		//
		//	spCube->AddComponent<Engine::CCollisionC>()->
		//		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 1.4f));
		//	spCube->GetComponent<Engine::CCollisionC>()->
		//		AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));
		//
		//	spCube->AddComponent<Engine::CDebugC>();
		//	spCube->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		//	spCube->AddComponent<Engine::CRigidBodyC>();
		//	spCube->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
		//	spCube->GetTransform()->SetSize(10, 1, 10);
		//	spCube->GetTransform()->SetPosition(0, -1, 0);

		//}

		//// add effects
		//CKiana* pKiana = (CKiana*)m_spKiana.get();
		//pKiana->SetEffect_Attack1(pKiana->CreateEffect(L"Kiana_Attack_0"));
		//pKiana->SetEffect_Attack2(pKiana->CreateEffect(L"Kiana_Attack_1"));
		//pKiana->SetEffect_Attack3(pKiana->CreateEffect(L"Kiana_Attack_2"));
		//pKiana->SetEffect_Attack4(pKiana->CreateEffect(L"Kiana_Attack_3"));
		//pKiana->SetEffect_Attack5(pKiana->CreateEffect(L"Kiana_Attack_3"));

		// Floor
		{
			SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");


			spCube->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CObbCollider::Create((_int)ECollisionID::Floor, _float3(20.f, 1.f, 20.f)));

			spCube->AddComponent<Engine::CDebugC>();
			spCube->AddComponent<Engine::CShaderC>();
			spCube->GetTransform()->SetSize(10, 1, 10);
			spCube->GetTransform()->SetPosition(0, -1.f, 0);
		}
	}
}

void CYongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CYongScene::Update(void)
{
	//m_pController->Update();
	__super::Update();

	if (Engine::IMKEY_DOWN(KEY_X))
	{
		
		SP(CMeshEffect_Client) spObj = 
			std::dynamic_pointer_cast<CMeshEffect_Client>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Cinema_Dome", true, (_uint)Engine::ELayerID::Effect));
		spObj->GetGraphics()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		//spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Ult_Ring", true, (_uint)Engine::ELayerID::Effect);
		// Bronya Smoke
		// 일정시간 마다 호출
		//SP(Engine::CObject) spObj;
		//for (_int i = 0; i < 3; ++i)
		//{
		//	_int iRand = rand() % 4;

		//	switch (iRand)
		//	{
		//	case 0:
		//		spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_RandomSmoke", true);
		//		spObj->GetTransform()->SetPosition(_float3(/* 브로냐의 위치 + */ _float(rand() % 3 - 0.2f), /* 브로냐의 위치 + */ _float(rand() % 2) - 0.3f,/* 브로냐의 위치 + */ _float(rand() % 3)));
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"Fx_Fire_01");
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"Fx_Fire_01");
		//		break;
		//	case 1:
		//		spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_RandomSmoke", true);
		//		spObj->GetTransform()->SetPosition(_float3(/* 브로냐의 위치 + */ _float(rand() % 3 - 0.2f), /* 브로냐의 위치 + */_float(rand() % 2) - 0.7f, /* 브로냐의 위치 + */_float(rand() % 3)));
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog03");
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog03");
		//		break;
		//	case 2:
		//		spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_RandomSmoke", true);
		//		spObj->GetTransform()->SetPosition(_float3(/* 브로냐의 위치 + */ _float(rand() % 3 - 0.2f),/* 브로냐의 위치 + */ _float(rand() % 2) - 0.2f,/* 브로냐의 위치 + */ _float(rand() % 3)));
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog03");
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog03");
		//		break;
		//	case 3:
		//		spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_RandomSmoke", true);
		//		spObj->GetTransform()->SetPosition(_float3(/* 브로냐의 위치 + */ _float(rand() % 3 - 0.2f),/* 브로냐의 위치 + */ _float(rand() % 2) - 0.2f,/* 브로냐의 위치 + */ _float(rand() % 3)));
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"Fx_Fire_01");
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"Fx_Fire_01");
		//		break;
		//	default:
		//		spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_RandomSmoke", true);
		//		spObj->GetTransform()->SetPosition(_float3(/* 브로냐의 위치 + */ _float(rand() % 3 - 0.2f), /* 브로냐의 위치 + */_float(rand() % 2) - 0.7f, /* 브로냐의 위치 + */_float(rand() % 3)));
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog04");
		//		spObj->GetComponent<Engine::CTextureC>()->AddTexture(L"fx_snowfield_fog04");
		//		break;
		//	}			
		//}				

	}
}

void CYongScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CYongScene::OnDestroy(void)
{
	__super::OnDestroy();

	//m_pController->DestroyInstance();
}

void CYongScene::OnEnable(void)
{
	__super::OnEnable();

}

void CYongScene::OnDisable(void)
{
	__super::OnDisable();

}

void CYongScene::InitPrototypes(void)
{
}
