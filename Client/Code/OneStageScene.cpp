#include "stdafx.h"
#include "OneStageScene.h"

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

#include "OneStagePhaseControl.h"

#include "Monster.h"
#include "Layer.h"

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

	m_pControlTower = CStageControlTower::GetInstance();
	m_pControlTower->Awake();
	m_pControlTower->SetPhaseControl(new COneStagePhaseControl);
	m_pControlTower->GetPhaseControl()->SetControlTower(m_pControlTower);
}

void COneStageScene::Start(void)
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

void COneStageScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void COneStageScene::Update(void)
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

void COneStageScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void COneStageScene::OnDestroy(void)
{
	__super::OnDestroy();
	m_pBattleUIManager->OnDestroy();
	m_pBattleUIManager->DestroyInstance();


	m_vDummy.clear();
}

void COneStageScene::OnEnable(void)
{
	__super::OnEnable();
	m_pBattleUIManager->DestroyInstance();
}

void COneStageScene::OnDisable(void)
{
	__super::OnDisable();
}

void COneStageScene::SetupFromLoader(void)
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
	//Load->PortalLoad(this);
	delete(Load);
}

void COneStageScene::SetupMembers(void)
{
	// Kiana
	Create_ActorValkyrie();

	// Cam Target Set
	Create_SceneCamera();

	//Create_Dummy(_float3(43.3345f, -1.f, -0.075913f));

}

void COneStageScene::Create_ActorValkyrie(void)
{	
	SP(Engine::CObject) spStartValkyrie = m_pControlTower->SettingSquad(this);

	m_spValkyrie = spStartValkyrie;
	//m_spValkyrie->GetTransform()->SetPosition(46.3345f, -1.f, -0.075913f);
	m_spValkyrie->GetTransform()->SetPosition(5.f, 0.f, 0.f);
	m_spValkyrie->GetTransform()->AddRotationY(D3DXToRadian(-90.f));

	m_pControlTower->Start(CStageControlTower::ALL);

}

void COneStageScene::Create_SceneCamera(void)
{
	auto cam = Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera");
	cam->SetTarget(m_spValkyrie);
	CStageControlTower::GetInstance()->SetCurrentMainCam(cam);
}


void COneStageScene::InitPrototypes(void)
{

}

void COneStageScene::FindSkyObject()
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
