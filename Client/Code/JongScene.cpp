#include "stdafx.h"
#include "JongScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"

#include "DynamicMeshData.h"

#include "StageController.h"
#include "FSM_KianaC.h"
#include "Kiana.h"
#include "AniCtrl.h"

CJongScene::CJongScene()
{
}


CJongScene::~CJongScene()
{
	delete m_pController;
	m_pController->DestroyInstance();
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
	
	m_pController = new CStageController;
	m_pController = CStageController::GetInstance();
	m_pController->Awake();	
}

void CJongScene::Start(void)
{
		//Engine::CCameraManager::GetInstance()->GetMainCamera();
	__super::Start();
	{
		//Engine::GET_CUR_SCENE;	// 쓰지 마세요오오옹
		{
			SP(Engine::CObject) spEmptyObject1
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Pivot");

			spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Pistol_USP45");
			spEmptyObject1->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject1->AddComponent<Engine::CTextureC>();
			spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject1->GetTransform()->SetSize(1, 1, 1);

			m_pivot = spEmptyObject1.get();

			Engine::CCameraManager::GetInstance()->GetCamera(L"JongSceneBasicCamera")->SetTarget(spEmptyObject1);
		}

		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Kiana");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana_decl");
			spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject->AddComponent<Engine::CTextureC>();
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject->GetTransform()->SetSize(1, 1, 1);

			spEmptyObject->AddComponent<CFSM_KianaC>();

			spEmptyObject->GetComponent<Engine::CMeshC>()->OnRootMotion();

			m_pKiana = spEmptyObject;

			//m_pivot->GetTransform()->SetParent(m_pKiana->GetTransform());
			m_pController->AddSquadMember(m_pKiana);

		}

		// Kiana Body
		{
			SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", false, (_uint)ELayerID::Player, L"Kiana");

			m_spKiana = spKianaClone;
			m_pController->AddSquadMember(m_spKiana);
			m_pController->Start();
		}

		// Catpaw ATK01
		{
			m_spCatPaw = m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"CatPaw_ATK01");

			m_spCatPaw->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana_CatPaw_Atk01");
			m_spCatPaw->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			m_spCatPaw->AddComponent<Engine::CTextureC>();
			m_spCatPaw->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			m_spCatPaw->GetTransform()->SetSize(1, 1, 1);
			m_spCatPaw->GetTransform()->AddPositionY(1.f);
		}

		{
			SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", false, (_uint)ELayerID::Player, L"Kiana");

			m_spKiana = spKianaClone;
			m_pController->AddSquadMember(m_spKiana);
			m_pController->Start();
		}

		// Catpaw ATK01
		{
			m_spCatPaw = m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"testcatpaw");

			m_spCatPaw->AddComponent<Engine::CMeshC>()->AddMeshData(L"CatPaw_Atk03");
			m_spCatPaw->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			m_spCatPaw->AddComponent<Engine::CTextureC>();
			m_spCatPaw->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			m_spCatPaw->GetTransform()->SetSize(1, 1, 1);
			m_spCatPaw->GetTransform()->AddPositionY(1.f);
			m_spCatPaw->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetReplay(true);
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
}
