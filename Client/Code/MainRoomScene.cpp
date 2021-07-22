#include "stdafx.h"
#include "MainRoomScene.h"

#include "Loading.h"
#include "StageSelectionScene.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
#include "MainRoomManager.h"
#include "DecoObject.h"
#include "Layer.h"

#include "ElevatorBase.h"
#include "ElevatorDoor.h"

_bool CMainRoomScene::g_bFirstGameStart = false;

CMainRoomScene::CMainRoomScene()
{
}


CMainRoomScene::~CMainRoomScene()
{
}

CClientScene* CMainRoomScene::Create(void)
{
	CMainRoomScene* pInstance = new CMainRoomScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CMainRoomScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CMainRoomScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CMainRoomScene::Start(void)
{
	__super::Start();
	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->PlayBGM(L"Lobby.mp3");
	m_sceneID = (_int)ESceneID::MainRoom;
	
	// 로드
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->CanvasLoad(this);
	Load->TextLoad(this);
	Load->MapLoad(this);

	delete(Load);

	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)Engine::ELayerID::UI, L"MainCanvas_image2"));
	image->GetTransform()->SetPositionZ(0.9f);
	image->GetTransform()->SetSize(_float3(25, 25, 0));
	image->GetTexture()->AddTexture(L"MousePoint", 0);
	image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
	image->AddComponent<CMousePointC>();


	if (!g_bFirstGameStart)
	{
		Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);
		Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->GetTransform()->SetPosition(_float3(-0.286f, 0.175f, -5.44f));
		Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->GetTransform()->SetRotation(_float3(-0.0519f, 0.003f, 0.0f));

		SP(Engine::CObject) spobj = ADD_CLONE(L"ElevatorBase", true, (_int)Engine::ELayerID::Decoration);
		spobj->GetComponent<Engine::CTransformC>()->AddPositionZ(-2.5f);
		spobj->GetComponent<Engine::CTransformC>()->AddPositionY(-1.6f);
		spobj->GetComponent<Engine::CTransformC>()->AddPositionX(-0.4f);

		spobj = ADD_CLONE(L"ElevatorDoor", true, (_int)Engine::ELayerID::Decoration);

		static_cast<Engine::CCanvas*>(this->FindObjectByName(L"MainCanvas").get())->AddObjectFind();
		static_cast<Engine::CCanvas*>(this->FindObjectByName(L"MainCanvas").get())->SetIsEnabled(false);
		
		g_bFirstGameStart = true;
	}
	else
	{
		Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);
		Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->GetTransform()->SetPosition(_float3(-0.2f, 0.17f, -4.6f));
		Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->GetTransform()->SetRotation(_float3(0.f, 0.f, 0.0f));
	}



	// 경험치 스테미너 골드 다이아 이름 레벨
	CMainRoomManager::GetInstance()->Start(this);

	// get ControlDesk objects
	ControlDeskSetrring();

	SP(Engine::CObject) spObj;
	spObj = ADD_CLONE(L"MainRoomBG", true, (_int)Engine::ELayerID::Decoration);
	spObj->GetTransform()->SetPositionZ(100.f);
	spObj->GetTransform()->SetSizeX(10.f);
	spObj->GetTransform()->SetSizeY(5.f);

	for (_int i = 0; i < 10; ++i)
	{
		_float fX = 0.f;
		_float fY = rand() % 2 + 2.f * 0.5f;
		_float fZ = rand() % 50 + 50.f;

		_int irand = rand() % 2;

		switch (irand)
		{
		case 0:
			fX = 11.57f;
			break;
		case 1:
			fX = -11.3f;
			break;
		default:
			fX = -11.3f;
			break;
		}

		spObj = ADD_CLONE(L"CloudObject", true, (_int)Engine::ELayerID::Decoration);
		spObj->GetTransform()->SetPosition(fX, fY, fZ);

	}


}

void CMainRoomScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CMainRoomScene::Update(void)
{
	__super::Update();
	CMainRoomManager::GetInstance()->Update();

	ShakeControlDesk();

}

void CMainRoomScene::LateUpdate(void)
{

	__super::LateUpdate();

}

void CMainRoomScene::OnDestroy(void)
{
	__super::OnDestroy();
	CBattleEndManager::GetInstance()->DestroyInstance();

	CMainRoomManager::GetInstance()->OnDestroy();
	CMainRoomManager::GetInstance()->DestroyInstance();

	m_vControlDesk.clear();
}

void CMainRoomScene::OnEnable(void)
{
	__super::OnEnable();

}

void CMainRoomScene::OnDisable(void)
{
	__super::OnDisable();

}

void CMainRoomScene::ControlDeskSetrring(void)
{
	m_vControlDesk.emplace_back(m_vLayers[(_uint)Engine::ELayerID::Decoration]->GetGameObjects()[49]);
	m_vControlDesk.emplace_back(m_vLayers[(_uint)Engine::ELayerID::Decoration]->GetGameObjects()[50]);
	m_vControlDesk.emplace_back(m_vLayers[(_uint)Engine::ELayerID::Decoration]->GetGameObjects()[51]);

	m_upMax = m_vControlDesk[0]->GetTransform()->GetPosition();
	m_downMax = m_vControlDesk[0]->GetTransform()->GetPosition();

	m_rightMax[0].x = m_vControlDesk[0]->GetTransform()->GetPosition().x;
	m_rightMax[1].x = m_vControlDesk[0]->GetTransform()->GetPosition().x;
	m_rightMax[2].x = m_vControlDesk[0]->GetTransform()->GetPosition().x;

	m_upMax.y += 0.02f;
}

void CMainRoomScene::ShakeControlDesk(void)
{
	if (m_vControlDesk.empty())
		return;

	for (_int i = 0; i < 3; ++i)
	{
		_float3 oriPos = m_vControlDesk[i]->GetTransform()->GetPosition();

		if (m_upMax.y <= oriPos.y)
		{
			m_moveUp = false;
			m_moveDown = true;
		}
		else if (m_downMax.y >= oriPos.y)
		{
			m_moveDown = false;
			m_moveUp = true;
		}
		else if (m_rightMax[i].x + 0.02f <= oriPos.x)
		{
			m_moveRight = false;
			m_moveLeft = true;
		}
		else if (m_rightMax[i].x >= oriPos.x)
		{
			m_moveRight = true;
			m_moveLeft = false;
		}

		_uint pos = GetRandRange(1, 2);
		_float value = GetRandRange(1, 2) * 0.01f * GET_DT;

		switch (pos)
		{
		case 1: // x
		{
			if (true == m_moveRight)
			{
				m_vControlDesk[i]->GetTransform()->AddPositionX(value);
			}
			else if (true == m_moveLeft)
			{
				m_vControlDesk[i]->GetTransform()->AddPositionX(-value);
			}
		}
		break;
		case 2: // y
		{
			if (true == m_moveUp)
			{
				m_vControlDesk[i]->GetTransform()->AddPositionY(value);
			}
			else if (true == m_moveDown)
			{
				m_vControlDesk[i]->GetTransform()->AddPositionY(-value);
			}
		}
		break;
		}
	}
}


void CMainRoomScene::InitPrototypes(void)
{
	
}

