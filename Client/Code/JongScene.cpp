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
	{
		// Kiana Body
		{
			SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

			m_spKiana = spKianaClone;
			m_pController->AddSquadMember(m_spKiana);
			m_pController->Start(CStageControlTower::WithoutUI);

			spKianaClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
		}


		auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
		cam->SetTarget(m_spKiana);
		cam->SetTargetDist(2.f);
		CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
	}
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
