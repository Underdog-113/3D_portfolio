#include "stdafx.h"
#include "PartySettingScene.h"

#include "Loading.h"

#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "ButtonFunction.h"
#include "ScrollViewObject.h"
#include "Canvas.h"

#include "TextManager.h"
#include "DataLoad.h"

CPartySettingScene::CPartySettingScene()
{
}


CPartySettingScene::~CPartySettingScene()
{
}


CClientScene* CPartySettingScene::Create(void)
{
	CPartySettingScene* pInstance = new CPartySettingScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CPartySettingScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CPartySettingScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CPartySettingScene::Start(void)
{
	__super::Start();
	m_sceneID = (_int)ESceneID::PartySettingScene;

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

	// ?ε?
	CDataLoad* Load = new CDataLoad();
	Load->Setting();
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->SliderLoad(this);
	Load->ScrollViewLoad(this);
	Load->TextLoad(this);
	Load->CanvasLoad(this);
	delete(Load);

}

void CPartySettingScene::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CPartySettingScene::Update(void)
{
	__super::Update();

	if (!m_init)
	{
		CValkyriegManager::GetInstance()->Start(this);
		m_init = true;
	}

	CValkyriegManager::GetInstance()->Update();
}

void CPartySettingScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CPartySettingScene::OnDestroy(void)
{
	__super::OnDestroy();
	CValkyriegManager::GetInstance()->DestroyInstance();
}

void CPartySettingScene::OnEnable(void)
{
	__super::OnEnable();

}

void CPartySettingScene::OnDisable(void)
{
	__super::OnDisable();

}

void CPartySettingScene::InitLights(void)
{
	D3DLIGHT9* pLightInfo = new D3DLIGHT9;

	pLightInfo->Type = D3DLIGHT_DIRECTIONAL;
	pLightInfo->Direction = _float3(1.f, -1.f, 0.f);
	pLightInfo->Diffuse = D3DXCOLOR(.8f, .8f, .8f, 1.f);
	pLightInfo->Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pLightInfo->Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_pLightManager->AddCameraLight(pLightInfo);
}


void CPartySettingScene::InitPrototypes(void)
{
}
