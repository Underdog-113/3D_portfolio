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

// for monster pattern
#include "PatternMachineC.h"
#include "ClientPatterns.h"

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

	SP(Engine::CObject) spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	spSickleClone->GetTransform()->SetPosition(25.0548f, -1.f, 0.421f);
	spSickleClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSickleBornPattern::Create(), CSickleDiePattern::Create(), CSickleBasePattern::Create(), CSickleHitPattern::Create());
	m_spSickle1 = spSickleClone;

	spSickleClone = ADD_CLONE(L"MO_Sickle", true, (_uint)ELayerID::Enemy, L"MO_Sickle");
	spSickleClone->GetTransform()->SetPosition(26.8889f, -1.f, -0.855956f);
	spSickleClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSickleBornPattern::Create(), CSickleDiePattern::Create(), CSickleBasePattern::Create(), CSickleHitPattern::Create());
	m_spSickle2 = spSickleClone;

	SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
	spSpiderClone->GetTransform()->SetPosition(29.1903f, -1.f, 0.606165f);
	spSpiderClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSpiderBornPattern::Create(), CSpiderDiePattern::Create(), CSpiderBasePattern::Create(), CSpiderHitPattern::Create());
	m_spSpider1 = spSpiderClone;

	spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
	spSpiderClone->GetTransform()->SetPosition(31.5491f, -1.f, -0.827802f);
	spSpiderClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CSpiderBornPattern::Create(), CSpiderDiePattern::Create(), CSpiderBasePattern::Create(), CSpiderHitPattern::Create());
	m_spSpider2 = spSpiderClone;
}

void COneStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void COneStageScene::Update(void)
{
	__super::Update();

	if (Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	m_pController->Update();
	CBattleUiManager::GetInstance()->Update();


	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		CBattleUiManager::GetInstance()->PlayerSpDown(10);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
	{
	    CBattleUiManager::GetInstance()->HitCount(8);
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_3))
	{
		CBattleUiManager::GetInstance()->MonsterState(L"ss ss", 100, L"DOWN");
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_4))
	{
	    CBattleUiManager::GetInstance()->MonsterHpDown(30.0f);
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
	    CBattleUiManager::GetInstance()->SkillExecution(2, 10, 10);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F3))
	{
	    CBattleUiManager::GetInstance()->PlayerChange(100, 100, L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Defalut", L"Defalut");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F4))
	{
	    CBattleUiManager::GetInstance()->PlayerChange(100, 100, L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Skill_Kiana_PT_001", L"Defalut");
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F5))
	{
	    CBattleUiManager::GetInstance()->TargetUI(nullptr, 5.0f);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
	{
	    CBattleUiManager::GetInstance()->BattleEnd();
	}

	if (true == m_bossSpawn)
	{
		/* Ganesha */
		SP(Engine::CObject) spGaneshaClone = ADD_CLONE(L"MB_Ganesha", true, (_uint)ELayerID::Enemy, L"MB_Ganesha");
		spGaneshaClone->GetTransform()->SetSize(2, 2, 2);
		spGaneshaClone->GetTransform()->SetPosition(-46, 15, 0);
		spGaneshaClone->GetTransform()->SetRotationY(D3DXToRadian(90));
		spGaneshaClone->AddComponent<CPatternMachineC>()->AddNecessaryPatterns(CGaneshaBornPattern::Create(), CGaneshaDiePattern::Create(), CGaneshaBasePattern::Create(), CGaneshaHitPattern::Create());
		spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaStampPattern::Create());
		spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaRoll01Pattern::Create());
		spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst01Pattern::Create());
		spGaneshaClone->GetComponent<CPatternMachineC>()->AddPattern(CGaneshaBurst02Pattern::Create());
		m_spGanesha = spGaneshaClone;

		m_bossSpawn = false;
	}
	else if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		m_spValkyrie->GetTransform()->SetPosition(-46, 15, 0);
	}
	else if (Engine::IMKEY_DOWN(KEY_R))
	{
		m_bossSpawn = true;
		m_onBoss = true;
	}
	
	std::cout << "kiana x : " << 
		m_spValkyrie->GetTransform()->GetPosition().x << ", y : " <<
		m_spValkyrie->GetTransform()->GetPosition().y << ", z : " <<
		m_spValkyrie->GetTransform()->GetPosition().z << std::endl;
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
		m_spValkyrie->GetTransform()->SetPosition(46.3345f, -1.f, -0.075913f);
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
		//SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
		//spSpiderClone->GetTransform()->SetPosition(0, 0, 5);
		//spSpiderClone->GetTransform()->SetRotationY(D3DXToRadian(90));
		//m_spSpider = spSpiderClone;
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
