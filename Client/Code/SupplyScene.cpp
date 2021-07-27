#include "stdafx.h"
#include "SupplyScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"
#include "InventoryManager.h"

CSupplyScene::CSupplyScene()
{
}


CSupplyScene::~CSupplyScene()
{
}


CClientScene* CSupplyScene::Create(void)
{
	CSupplyScene* pInstance = new CSupplyScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CSupplyScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CSupplyScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CSupplyScene::Start(void)
{
	__super::Start();
	m_sceneID = (_int)ESceneID::SupplyScene;

	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)Engine::ELayerID::UI, L""));
	image->GetTransform()->SetPositionZ(1.0f);
	image->GetTransform()->SetSize(_float3(25, 25, 0));
	image->GetTexture()->AddTexture(L"MousePoint", 0);
	image->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
	image->AddComponent<CMousePointC>();

	Engine::CSoundManager::GetInstance()->StopAll();
	Engine::CSoundManager::GetInstance()->PlayBGM(L"Shop.mp3");
	Engine::CCameraManager::GetInstance()->GetCamera(m_objectKey + L"BasicCamera")->SetMode(Engine::ECameraMode::Edit);

	//SP(Engine::CObject) spEmpty =
	//	ADD_CLONE(L"EmptyObject", true, (_int)Engine::ELayerID::UI, L"Background");

	// ·Îµå
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->ScrollViewLoad(this);
	Load->TextLoad(this);
	Load->CanvasLoad(this);
	delete(Load);
}

void CSupplyScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSupplyScene::Update(void)
{
	__super::Update();

	if (!m_init)
	{
		CSupplyManager::GetInstance()->Start(this);
		m_init = true;
	}

	CSupplyManager::GetInstance()->Update();
}

void CSupplyScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CSupplyScene::OnDestroy(void)
{
	__super::OnDestroy();
	CSupplyManager::GetInstance()->DestroyInstance();
}

void CSupplyScene::OnEnable(void)
{
	__super::OnEnable();

}

void CSupplyScene::OnDisable(void)
{
	__super::OnDisable();

}

void CSupplyScene::InitLights(void)
{
	D3DLIGHT9* pLightInfo = new D3DLIGHT9;

	pLightInfo->Type = D3DLIGHT_DIRECTIONAL;
	pLightInfo->Direction = _float3(0.f, 0.f, 1.f);
	pLightInfo->Diffuse = D3DXCOLOR(.8f, .8f, .8f, 1.f);
	pLightInfo->Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pLightInfo->Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_pLightManager->AddCameraLight(pLightInfo);
}


void CSupplyScene::InitPrototypes(void)
{
}
