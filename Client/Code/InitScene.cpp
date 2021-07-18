#include "stdafx.h"
#include "InitScene.h"
#include "Loading.h"
#include "EmptyObject.h"

//Elevator
#include "ElevatorBase.h"
#include "ElevatorBack.h"
#include "ElevatorDoor.h"

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
#include "TwoStageScene.h"
#include "ThreeStageScene.h"
#include "BossStageScene.h"
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
	m_sceneID = (_int)ESceneID::Init;
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
    
	spCameraObject->GetTransform()->SetPosition(_float3(0.2f, 1.f,  -3.38f));
	spCameraObject->GetTransform()->SetRotation(_float3(0.f, 0.f, 0.0f));

	m_spElevatorBase = ADD_CLONE(L"ElevatorBase", false, (_int)Engine::ELayerID::Decoration);
	
	_float _fY = 0.f;
	for (_int i = 0; i < 2; ++i)
	{
		m_spElevatorBack = ADD_CLONE(L"ElevatorBack", false, (_int)Engine::ELayerID::Decoration);

		if (i == 0)
			m_spElevatorBack->GetComponent<Engine::CMeshC>()->SetMeshData(L"Elevator_Back");
		else
			m_spElevatorBack->GetComponent<Engine::CMeshC>()->SetMeshData(L"Elevator_Back_2");

		m_spElevatorBack->GetTransform()->AddPositionY(_fY);
		_fY += 16.f;
	}

	text = ADD_CLONE(L"TextObject", false, (_int)Engine::ELayerID::UI, L"");
	text->GetTransform()->SetPositionZ(0.5f);
	text->AddComponent<Engine::CTextC>()->AddFontData(L"데이터 갱신 중 0.0%", _float2(-170,240), _float2(0, 0), 25, DT_VCENTER + DT_LEFT + DT_NOCLIP, D3DXCOLOR(1,1,1,1), true);

	{
		slider =
			std::dynamic_pointer_cast<Engine::CSlider>(ADD_CLONE(L"Slider", false, (_int)Engine::ELayerID::UI, L"Slidr_0"));
		slider->GetTransform()->SetPosition(_float3(-65.0f, -200.0f, 0.0f));
		slider->SetDirection((Engine::CSlider::ESliderDirection::LeftToRight));

		SP(Engine::CImageObject) background =
			std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", false, (_int)Engine::ELayerID::UI, L"BackGround"));
		background->GetTransform()->SetPosition(slider->GetTransform()->GetPosition());
		background->GetTransform()->SetSize(_float3(500, 40, 0));
		background->GetTexture()->AddTexture(L"CannonSpDisable", 0);
		background->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);

		SP(Engine::CImageObject) fill =
			std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", false, (_int)Engine::ELayerID::UI, L"Fill"));
		fill->SetParent(slider.get());
		fill->GetTransform()->SetPosition(slider->GetTransform()->GetPosition());
		fill->GetTransform()->SetPositionZ(slider->GetTransform()->GetPosition().z);
		fill->GetTransform()->SetSize(_float3(500, 35, 0));
		fill->GetTexture()->AddTexture(L"CannonSpColor", 0);
		fill->GetShader()->
			AddShader(Engine::CShaderManager::GetInstance()->GetShaderID((L"SliderShader")));

		slider->AddSliderData(0, 100, 0, background, fill);
	}
}

void CInitScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CInitScene::Update(void)
{
	__super::Update();
	_float value = slider->GetValue();
	value = min(value + GET_DT * 8, 100);
	slider->SetValue(value);
	text->GetComponent<Engine::CTextC>()->ChangeMessage(L"데이터 갱신 중 " + std::to_wstring(value) + L"%");



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


	if (m_pLoading->GetFinish() && slider->GetValue() == slider->GetMaxValue())
	{
		if (m_selectNextScene)
		{
			Engine::CSceneManager::GetInstance()->SceneChange(m_pLoading->GetNextScene());
		}
		else
		{
			
			if (!m_init)
			{
				CDataManager::GetInstance()->Start();
				SP(Engine::CObject) spObj = ADD_CLONE(L"ElevatorDoor", false, (_int)Engine::ELayerID::Decoration);
				std::static_pointer_cast<CElevatorBase>(m_spElevatorBase)->SetLoadCheck(true);
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
			else if (Engine::IMKEY_DOWN(KEY_F4))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CMainRoomScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_DOWN(KEY_F5))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CYongScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_DOWN(KEY_1))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(COneStageScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_DOWN(KEY_2))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CTwoStageScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_DOWN(KEY_3))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CThreeStageScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_DOWN(KEY_4))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CBossStageScene::Create(), false);
				m_selectNextScene = true;
			}
			else if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_DOWN(KEY_5))
			{
				m_pLoading->GetNextScene()->Free();
				delete m_pLoading;
				m_pLoading = CLoading::Create(CMainRoomScene::Create(), false);
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
	SP(Engine::CTextObject) spTextObject(Engine::CTextObject::Create(false, this));
	GetObjectFactory()->AddPrototype(spTextObject);

	SP(Engine::CImageObject) spImageObject(Engine::CImageObject::Create(false, this));
	GetObjectFactory()->AddPrototype(spImageObject);

	SP(Engine::CSlider) spSliderObject(Engine::CSlider::Create(false, this));
	GetObjectFactory()->AddPrototype(spSliderObject);

	SP(Engine::CObject) spEmptyObjectPrototype(Engine::CEmptyObject::Create(false, this));
	ADD_PROTOTYPE(spEmptyObjectPrototype);

	SP(Engine::CCamera) spCameraPrototype(Engine::CCamera::Create(false, this));
	ADD_PROTOTYPE(spCameraPrototype);

	SP(Engine::CObject) spElevator_Base(CElevatorBase::Create(false, this));
	ADD_PROTOTYPE(spElevator_Base);

	SP(Engine::CObject) spElevator_Back(CElevatorBack::Create(false, this));
	ADD_PROTOTYPE(spElevator_Back);

	SP(Engine::CObject) spElevator_Door(CElevatorDoor::Create(false, this));
	ADD_PROTOTYPE(spElevator_Door);
}
