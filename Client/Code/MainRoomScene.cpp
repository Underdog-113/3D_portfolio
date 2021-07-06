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

#include "Layer.h"

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

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

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

	// 경험치 스테미너 골드 다이아 이름 레벨
	CMainRoomManager::GetInstance()->Start(this);

	// get ControlDesk objects
	ControlDeskSetrring();

	// kiana pos
	// -0.31, -0.64, -2.9
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

