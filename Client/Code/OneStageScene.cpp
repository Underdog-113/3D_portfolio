#include "stdafx.h"
#include "OneStageScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"

// import from jongscene
#include "Include_ForTest.h"

COneStageScene::COneStageScene()
{
}


COneStageScene::~COneStageScene()
{
}

CClientScene* COneStageScene::Create(void)
{
	COneStageScene* pInstance = new COneStageScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void COneStageScene::Free(void)
{
	OnDestroy();
	delete this;
}

void COneStageScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pController = CStageControlTower::GetInstance();
	m_pController->Awake();
}

void COneStageScene::Start(void)
{
	__super::Start();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	Start_SetupUI();

	Start_SetupMembers();

	//m_pController->Start();
}

void COneStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void COneStageScene::Update(void)
{
	__super::Update();

	m_pController->Update();
	

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
	    CBattleUiManager::GetInstance()->KeyPad(4);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
	{
	    CBattleUiManager::GetInstance()->HitCount(8);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_3))
	{
		CBattleUiManager::GetInstance()->MonsetrState(L"°æºñ ¸ÁÀÚ", 100, L"DOWN");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_4))
	{
	    CBattleUiManager::GetInstance()->MonsterHpDown(0.5f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_5))
	{
	    CBattleUiManager::GetInstance()->PlayerHp(100.0f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F1))
	{
	    CBattleUiManager::GetInstance()->PlayerHpDown(0.5f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F2))
	{
	    CBattleUiManager::GetInstance()->SkillExecution(0, 10, 1);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F3))
	{
	    CBattleUiManager::GetInstance()->PlayerChange(100, 100, L"Skill_Bronya_Weapon_14", L"Skill_Bronya_Weapon_15", L"Skill_Bronya_Weapon_16", L"Skill_Bronya_Weapon_17", L"Defalut", L"Defalut");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F4))
	{
	    CBattleUiManager::GetInstance()->PlayerChange(100, 100, L"Skill_Bronya_Weapon_14", L"Skill_Bronya_Weapon_15", L"Skill_Bronya_Weapon_16", L"Defalut");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F5))
	{
	    CBattleUiManager::GetInstance()->TargetUI(_float3(0,0,0), 5.0f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
	{
	    CBattleUiManager::GetInstance()->BattleEnd();
	}
}

void COneStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void COneStageScene::OnDestroy(void)
{
	__super::OnDestroy();
	CBattleUiManager::GetInstance()->OnDestroy();

	m_pController->DestroyInstance();
	m_pController = nullptr;
}

void COneStageScene::OnEnable(void)
{
	__super::OnEnable();
	CBattleUiManager::GetInstance()->OnDestroy();
}

void COneStageScene::OnDisable(void)
{
	__super::OnDisable();

}


void COneStageScene::Start_SetupUI(void)
{
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	Load->ToolLoad(this);
	delete(Load);

	CBattleUiManager::GetInstance()->Start(this);
}

void COneStageScene::Start_SetupMembers(void)
{
	// Kiana
	{
		SP(Engine::CObject) spKianaClone = ADD_CLONE(L"Kiana", true, (_uint)ELayerID::Player, L"Kiana");

		m_spValkyrie = spKianaClone;
		m_pController->AddSquadMember(m_spValkyrie);
		m_pController->Start();

		//spKianaClone->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
	}
	// Cam Target Set
	{
		auto cam = Engine::CCameraManager::GetInstance()->GetCamera(L"OneStageSceneBasicCamera");
		cam->SetTarget(m_spValkyrie);
		cam->SetTargetDist(2.f);
		CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
	}
	// Spider
	{
		SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
		spSpiderClone->GetTransform()->SetPosition(0, 0, 5);
		spSpiderClone->GetTransform()->SetRotationY(D3DXToRadian(90));
		m_spSpider = spSpiderClone;
	}
	// test map
	{
		//SP(Engine::CObject) spEmptyObject
		//	= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Map, L"122");

		//spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"mainmenu_warship");
		//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		//spEmptyObject->AddComponent<Engine::CTextureC>();
		//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	}
}

void COneStageScene::InitPrototypes(void)
{

}
