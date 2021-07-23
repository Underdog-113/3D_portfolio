#include "stdafx.h"
#include "BattleEndScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
#include "BattleEndManager.h"
CBattleEndScene::CBattleEndScene()
{
}


CBattleEndScene::~CBattleEndScene()
{
}

CClientScene* CBattleEndScene::Create(void)
{
	CBattleEndScene* pInstance = new CBattleEndScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CBattleEndScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CBattleEndScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CBattleEndScene::Start(void)
{
	__super::Start();

	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)Engine::ELayerID::UI, L""));
	image->GetTransform()->SetPositionZ(1.0f);
	image->GetTransform()->SetSize(_float3(25, 25, 0));
	image->GetTexture()->AddTexture(L"MousePoint", 0);
	image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
	image->AddComponent<CMousePointC>();

	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// ·Îµå
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->Load(this);
	Load->TextLoad(this);
	delete(Load);

	m_init = false;
}

void CBattleEndScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBattleEndScene::Update(void)
{
	__super::Update();

	if (!m_init)
	{
		CBattleEndManager::GetInstance()->Start(this);
		m_init = true;
	}


	CBattleEndManager::GetInstance()->Update();
}

void CBattleEndScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CBattleEndScene::OnDestroy(void)
{
	__super::OnDestroy();
	CBattleEndManager::GetInstance()->DestroyInstance();

	CStageControlTower::GetInstance()->OnDestroy();
	CStageControlTower::GetInstance()->DestroyInstance();
}

void CBattleEndScene::OnEnable(void)
{
	__super::OnEnable();

}

void CBattleEndScene::OnDisable(void)
{
	__super::OnDisable();

}


void CBattleEndScene::InitPrototypes(void)
{
}
