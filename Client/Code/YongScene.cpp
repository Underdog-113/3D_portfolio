#include "stdafx.h"
#include "YongScene.h"
#include "FRC.h"

#include "StageControlTower.h"
#include "Kiana.h"
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
		//SpawnAttackRange();
		// Kiana Setting
		{
			SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

			m_spKiana = spKianaClone;
			m_pController->AddSquadMember(m_spKiana);
			m_pController->Start(CStageControlTower::WithoutUI);

			spKianaClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);

			auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
			cam->SetTarget(m_spKiana);
			cam->SetTargetDist(4.f);
			CStageControlTower::GetInstance()->ActorControl_SetCurrentMainCam(cam);
		}

		// cube terrain
		{

			SP(Engine::CObject) spCube = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Player, L"Cube0");
		
			spCube->AddComponent<Engine::CMeshC>()->SetMeshData(L"Sphere");
			spCube->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
			spCube->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		
			spCube->AddComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::FloorRay, _float3(0, 0, 0), _float3(0, -1, 0), 1.4f));
			spCube->GetComponent<Engine::CCollisionC>()->
				AddCollider(Engine::CRayCollider::Create((_int)ECollisionID::WallRay, ZERO_VECTOR, FORWARD_VECTOR, 1.1f));
		
			spCube->AddComponent<Engine::CDebugC>();
			spCube->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
			spCube->AddComponent<Engine::CRigidBodyC>();
			spCube->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
			spCube->GetTransform()->SetSize(10, 1, 10);
			spCube->GetTransform()->SetPosition(0, -1, 0);

		}

		// add effects
		CKiana* pKiana = (CKiana*)m_spKiana.get();
		pKiana->SetEffect_Attack1(pKiana->CreateEffect(L"Kiana_Attack_0"));
		pKiana->SetEffect_Attack2(pKiana->CreateEffect(L"Kiana_Attack_1"));
		pKiana->SetEffect_Attack3(pKiana->CreateEffect(L"Kiana_Attack_2"));
		pKiana->SetEffect_Attack4(pKiana->CreateEffect(L"Kiana_Attack_3"));
		pKiana->SetEffect_Attack5(pKiana->CreateEffect(L"Kiana_Attack_3"));
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

void CYongScene::SpawnAttackRange()
{
	SP(Engine::CObject) spMeshEffect
		= this->GetObjectFactory()->AddClone(L"AttackRange_Circle", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");
}
