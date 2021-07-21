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

	m_sceneID = (_int)ESceneID::Ganesha_Cinema;

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

	CStageControlTower::DestroyInstance();

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
