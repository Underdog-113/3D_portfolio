#include "stdafx.h"
#include "StageSelectionScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
#include "StageSelectionManager.h"
CStageSelectionScene::CStageSelectionScene()
{
}


CStageSelectionScene::~CStageSelectionScene()
{

}

CClientScene* CStageSelectionScene::Create(void)
{
	CStageSelectionScene* pInstance = new CStageSelectionScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CStageSelectionScene::Free(void)
{

	OnDestroy();
	delete this;
}

void CStageSelectionScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CStageSelectionScene::Start(void)
{
	__super::Start();

	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)Engine::ELayerID::UI, L"MainCanvas_image2"));
	image->GetTransform()->SetPositionZ(1.0f);
	image->GetTransform()->SetSize(_float3(25, 25, 0));
	image->GetTexture()->AddTexture(L"MousePoint", 0);
	image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
	image->AddComponent<CMousePointC>();

	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->PlayBGM(L"StageRoom.mp3");
	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// ·Îµå
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->TextLoad(this);
	Load->CanvasLoad(this);
	delete(Load);

	CStageSelectionManager::GetInstance()->Start(this);

}

void CStageSelectionScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CStageSelectionScene::Update(void)
{
	__super::Update();
	CStageSelectionManager::GetInstance()->Update();
}

void CStageSelectionScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CStageSelectionScene::OnDestroy(void)
{
	__super::OnDestroy();

	CStageSelectionManager::GetInstance()->OnDestroy();
	CStageSelectionManager::GetInstance()->DestroyInstance();
}

void CStageSelectionScene::OnEnable(void)
{
	__super::OnEnable();

}

void CStageSelectionScene::OnDisable(void)
{
	__super::OnDisable();

}

void CStageSelectionScene::InitPrototypes(void)
{
}
