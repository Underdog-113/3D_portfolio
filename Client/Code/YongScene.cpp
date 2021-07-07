#include "stdafx.h"
#include "YongScene.h"
#include "FRC.h"

#include "StageControlTower.h"
#include "Kiana.h"

#include "MonsterSpawnBeam.h"
#include "ScoutMeteor.h"
#include "Scout_Att_Range.h"
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

		//SP(CScout_Att_Range) spScoutRange = std::dynamic_pointer_cast<CScout_Att_Range>(m_pObjectFactory->AddClone(L"Scout_Att_Range", true, (_int)Engine::ELayerID::Effect, L"MeshEffect"));
		//spScoutRange->GetComponent<Engine::CMeshC>()->SetMeshData(L"Scout_Att_Range_Move");
		//spScoutRange->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
		//spScoutRange->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
		//spScoutRange->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
		//spScoutRange->GetComponent<Engine::CTextureC>()->AddTexture(L"Sign");
		//spScoutRange->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);

		//SP(Engine::CObject) spMeshEffect = m_pObjectFactory->AddClone(L"ScoutBall", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");
	

		Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ScoutCircleRange", true);
	
		/*	SP(CMonsterSpawnBeam) spMeshEffect =
				std::dynamic_pointer_cast<CMonsterSpawnBeam>(m_pObjectFactory->AddClone(L"MonsterSpawnBeam", true));

			spMeshEffect->GetMesh()->SetMeshData(L"SpawnBeam");
			spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
			spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Portal_beam_4");
			spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Portal_beam_4");
			spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Portal_beam_4");
			spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AlphaMaskShader);
			spMeshEffect->GetCollision()->AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, 0, 1), 2.5f));

			*/

		
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
