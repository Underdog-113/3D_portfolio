#include "stdafx.h"
#include "TwoStageScene.h"

#include "Loading.h"

#include "DamageObjectPool.h"
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

#include "TwoStagePhaseControl.h"

#include "Monster.h"
#include "Layer.h"

CTwoStageScene::CTwoStageScene()
{
}


CTwoStageScene::~CTwoStageScene()
{
}

CClientScene* CTwoStageScene::Create(void)
{
	CTwoStageScene* pInstance = new CTwoStageScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CTwoStageScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CTwoStageScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
	m_pControlTower->SetPhaseControl(new CTwoStagePhaseControl);
	m_pControlTower->GetPhaseControl()->SetControlTower(m_pControlTower);
}

void CTwoStageScene::Start(void)
{
	__super::Start();
	
	SetupFromLoader();
	SetupMembers();
	FindSkyObject();

	m_pBattleUIManager = CBattleUiManager::GetInstance();
	m_pBattleUIManager->Start(this);

	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::BGM);
	Engine::CSoundManager::GetInstance()->PlayBGM(L"Stage2_Bgm.wav");
	Engine::CSoundManager::GetInstance()->SetVolume((_uint)Engine::EChannelID::BGM, 0.17f);
}

void CTwoStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTwoStageScene::Update(void)
{
	__super::Update();

	if (Engine::CSceneManager::GetInstance()->GetSceneChanged())
		return;

	m_pControlTower->Update();
	m_pBattleUIManager->Update();

	// Sky Rotation
	if (nullptr != m_spSky)
	{
		m_spSky->GetTransform()->SetRotationY(
			m_spSky->GetTransform()->GetRotation().y + 0.01f * GET_DT);
	}
}

void CTwoStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CTwoStageScene::OnDestroy(void)
{
	__super::OnDestroy();
	m_pBattleUIManager->OnDestroy();
	m_pBattleUIManager->DestroyInstance();

	m_vDummy.clear();
}

void CTwoStageScene::OnEnable(void)
{
	__super::OnEnable();
	m_pBattleUIManager->DestroyInstance();
}

void CTwoStageScene::OnDisable(void)
{
	__super::OnDisable();

}


void CTwoStageScene::SetupFromLoader(void)
{
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	Load->MapLoad(this);
	Load->PhaseChangerLoad(this);
	Load->PortalLoad(this);
	delete(Load);
}

void CTwoStageScene::SetupMembers(void)
{
	// Kiana
	Create_ActorValkyrie();

	// Cam Target Set
	Create_SceneCamera();
}

void CTwoStageScene::Create_ActorValkyrie(void)
{
	SP(Engine::CObject) spStartValkyrie = m_pControlTower->SettingSquad(this);

	m_spValkyrie = spStartValkyrie;
	m_spValkyrie->GetTransform()->SetPosition(-19.2f, 0.248f, 0.1f);

	m_pControlTower->Start(CStageControlTower::ALL);
}

void CTwoStageScene::Create_SceneCamera(void)
{
	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spValkyrie);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
}

void CTwoStageScene::InitPrototypes(void)
{

}

void CTwoStageScene::ForUITest()
{
	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_1))
	{
		CBattleUiManager::GetInstance()->SpecialUICanvasOn();
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_2))
	{
		CBattleUiManager::GetInstance()->SpecialUIUp();
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_3))
	{
		CBattleUiManager::GetInstance()->SpecialUIDwon();
	}

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_4))
	{
		CBattleUiManager::GetInstance()->HitCount(5);
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
		CBattleUiManager::GetInstance()->MonsterState(L"", 1000, 900, 2, L"DOWN",0,0);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F4))
	{
		CBattleUiManager::GetInstance()->MonsterHpDown(10);
	}

	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_F5))
	{
		CBattleUiManager::GetInstance()->OnTargetUI(nullptr, 5.0f);
	}

// 	if (Engine::CInputManager::GetInstance()->KeyPress(KEY_Q))
// 	{
// 		CBattleUiManager::GetInstance()->BattleEnd();
// 	}
}

void CTwoStageScene::FindSkyObject()
{
	auto& map = m_vLayers[(_uint)Engine::ELayerID::Decoration]->GetGameObjects();
	auto iter = map.begin();

	for (; iter != map.end(); ++iter)
	{
		auto& comp = (*iter)->GetComponents().begin();

		for (; comp != (*iter)->GetComponents().end(); ++comp)
		{
			if ((_uint)Engine::EComponentID::Mesh == (*comp).second->GetComponentID())
			{
				if (L"Stage02_Alpha_S02_Sky" == (*iter)->GetComponent<Engine::CMeshC>()->GetMeshData()->GetMeshKey())
				{
					m_spSky = *iter;
					m_spSky->GetTransform()->SetPosition(_float3(-60.57f, -12.917f, 0.f));
					return;
				}
			}
		}
	}
}
