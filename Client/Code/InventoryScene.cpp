#include "stdafx.h"
#include "InventoryScene.h"

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

CInventoryScene::CInventoryScene()
{
}


CInventoryScene::~CInventoryScene()
{
}


CClientScene* CInventoryScene::Create(void)
{
	CInventoryScene* pInstance = new CInventoryScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CInventoryScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CInventoryScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CInventoryScene::Start(void)
{
	__super::Start();

	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)Engine::ELayerID::UI, L"MainCanvas_image2"));
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
	Load->ButtonLoad(this);
	Load->ImageLoad(this);
	Load->ScrollViewLoad(this);
	Load->TextLoad(this);
	Load->CanvasLoad(this);
	delete(Load);

	this->FindObjectByName(L"MainCanvas_ScrollView_0")->GetTransform()->SetSize(_float3(1093, 653, 0.1f));
}

void CInventoryScene::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CInventoryScene::Update(void)
{
	__super::Update();

	if (!m_init)
	{
		CInventoryManager::GetInstance()->Start(this);
		m_init = true;
	}

	CInventoryManager::GetInstance()->Update();
}

void CInventoryScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CInventoryScene::OnDestroy(void)
{
	__super::OnDestroy();
	CInventoryManager::GetInstance()->DestroyInstance();
}

void CInventoryScene::OnEnable(void)
{
	__super::OnEnable();

}

void CInventoryScene::OnDisable(void)
{
	__super::OnDisable();

}


void CInventoryScene::InitPrototypes(void)
{
}
