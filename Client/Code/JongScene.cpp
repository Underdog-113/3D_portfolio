#include "stdafx.h"
#include "JongScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"

#include "DynamicMeshData.h"

#include "StageController.h"
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

	//m_pController = new CStageController;
	m_pController = CStageController::GetInstance();
	m_pController->Awake();
}

void CJongScene::Start(void)
{
		//Engine::CCameraManager::GetInstance()->GetMainCamera();
	__super::Start();
	{
		//Engine::GET_CUR_SCENE;
		{
			SP(Engine::CObject) spEmptyObject1
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Pivot");

			spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Pistol_USP45");
			spEmptyObject1->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject1->AddComponent<Engine::CTextureC>();
			spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject1->GetTransform()->SetSize(1, 1, 1);

			m_pivot = spEmptyObject1.get();

			auto cam = Engine::CCameraManager::GetInstance()->GetCamera(L"JongSceneBasicCamera");
			cam->SetTarget(spEmptyObject1);
			cam->SetTargetDist(6.f);
		}


		// Kiana Body
		{
			SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", false, (_uint)ELayerID::Player, L"Kiana");

			m_spKiana = spKianaClone;
			m_pController->AddSquadMember(m_spKiana);
			m_pController->Start();

		}

		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Map, L"122");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"mainmenu_warship");
			spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject->AddComponent<Engine::CTextureC>();
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			//spEmptyObject->GetTransform()->SetSize(100, 1, 10);
			//spEmptyObject->GetTransform()->SetRotationY(D3DXToRadian(-90));
			//spEmptyObject->GetTransform()->SetPositionY(-0.5);
		}
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
	m_pivot->GetTransform()->SetPosition(m_spKiana->GetTransform()->GetPosition());
	m_pivot->GetTransform()->SetPositionY(0.f);
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
	SP(CKiana) spKianaPrototype(CKiana::Create(false, this));
	ADD_PROTOTYPE(spKianaPrototype);

	SP(CKiana_CatPaw_Atk01) spPaw01(CKiana_CatPaw_Atk01::Create(false, this));
	ADD_PROTOTYPE(spPaw01);

	SP(CKiana_CatPaw_Atk02) spPaw02(CKiana_CatPaw_Atk02::Create(false, this));
	ADD_PROTOTYPE(spPaw02);

	SP(CKiana_CatPaw_Atk03) spPaw03(CKiana_CatPaw_Atk03::Create(false, this));
	ADD_PROTOTYPE(spPaw03);

	SP(CKiana_CatPaw_Atk04) spPaw04(CKiana_CatPaw_Atk04::Create(false, this));
	ADD_PROTOTYPE(spPaw04);

	SP(CKiana_CatPaw_Atk05) spPaw05(CKiana_CatPaw_Atk05::Create(false, this));
	ADD_PROTOTYPE(spPaw05);

	SP(CKiana_CatPaw_Ring_Atk01) spPawRing01(CKiana_CatPaw_Ring_Atk01::Create(false, this));
	ADD_PROTOTYPE(spPawRing01);

	SP(CKiana_Pistol_USP45) spPistol(CKiana_Pistol_USP45::Create(false, this));
	ADD_PROTOTYPE(spPistol);
}
