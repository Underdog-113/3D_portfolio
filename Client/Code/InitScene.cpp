#include "stdafx.h"
#include "InitScene.h"
#include "Loading.h"
#include "EmptyObject.h"

#pragma region PrivateScenes
#include "StaticScene.h"
#include "ChangmoScene.h"
#include "JongScene.h"
#include "WooScene.h"
#include "YongScene.h"
#include "DongScene.h"

#include "MainRoomScene.h"
#include "StageSelectionScene.h"
#include "OneStageScene.h"
#include "BattleEndScene.h"
#include "ReadyToSortieScene.h"
#pragma endregion
#include "SoundManager.h"


CInitScene::CInitScene()
{
}


CInitScene::~CInitScene()
{
}

CClientScene* CInitScene::Create(void)
{
	CInitScene* pInstance = new CInitScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CInitScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CInitScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	Engine::CSoundManager::GetInstance()->StartSound(L"Elevator.wav", (_uint)Engine::EChannelID::OUTGAME);
}

void CInitScene::Start(void)
{
	m_isStarted = true;
	//DataStore Init
	m_pDataStore->InitDataMap((_uint)EDataID::NumOfDataID);
	m_pDataStore->InitDataForScene(m_objectKey);
	m_pMeshStore->InitMeshForScene(m_objectKey);
	m_pTextureStore->InitTextureForScene(m_objectKey);

	InitPrototypes();

	m_pLoading = CLoading::Create(CStaticScene::Create(), true);

	SP(Engine::CCamera) spCameraObject =
		std::dynamic_pointer_cast<Engine::CCamera>(ADD_CLONE(L"Camera", false));
	spCameraObject->SetMode(Engine::ECameraMode::Edit);
	Engine::CCameraManager::GetInstance()->AddCamera(L"InitSceneBasicCamera", spCameraObject);
	Engine::CCameraManager::GetInstance()->SetMainCamera(spCameraObject);

	m_pBackground =
		ADD_CLONE(L"EmptyObject", false, (_int)Engine::ELayerID::UI, L"Background1");

	m_pBackground->AddComponent<Engine::CRectTexC>()->SetIsOrtho(true);
	m_pBackground->AddComponent<Engine::CTextureC>()->AddTexture(L"Agelimit");
	m_pBackground->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	m_pBackground->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::RectTexShader);
	m_pBackground->GetTransform()->SetSize(1440, 810, 1);

}

void CInitScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CInitScene::Update(void)
{
	__super::Update();

	if(!m_isStaticScene)
		m_fTempSoundLength += GET_DT;

	if (m_fTempSoundLength >= 2.f)
	{
		if (!m_isStaticScene)
		{
			Engine::CSoundManager::GetInstance()->PlayBGM(L"Elevator_Loop.wav");
			m_isStaticScene = true;
		}
		m_fTempSoundLength = 0.f;
	}

	if (m_pLoading->GetFinish())
	{
		if (m_selectNextScene)
		{
			Engine::CSceneManager::GetInstance()->SceneChange(m_pLoading->GetNextScene());
		}
		else
		{
			m_pBackground->GetComponent<Engine::CTextureC>()->ChangeTexture(L"Warning");

			if (!m_init)
			{
				CDataManager::GetInstance()->Start();
				m_init = true;
			}

			if (Engine::IMKEY_DOWN(KEY_F1))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CChangmoScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_DOWN(KEY_F2))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CJongScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_DOWN(KEY_F3))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CWooScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (!Engine::IMKEY_DOWN(KEY_F4))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CReadyToSortieScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_DOWN(KEY_F5))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CYongScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_DOWN(KEY_SHIFT))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(COneStageScene::Create(), false);
				m_selectNextScene = true;
			}
		}
	}
}

void CInitScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CInitScene::OnDestroy(void)
{
	__super::OnDestroy();
	Engine::CSoundManager::GetInstance()->StopAll();
	delete m_pLoading;
}

void CInitScene::OnEnable(void)
{
	__super::OnEnable();

}

void CInitScene::OnDisable(void)
{
	__super::OnDisable();

}

void CInitScene::InitPrototypes(void)
{
	SP(Engine::CObject) spEmptyObjectPrototype(Engine::CEmptyObject::Create(false, this));
	ADD_PROTOTYPE(spEmptyObjectPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(false, this));
	ADD_PROTOTYPE(spCameraPrototype);
}
