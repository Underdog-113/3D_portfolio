#include "stdafx.h"
#include "DongScene.h"
#include "Image.h"
#include "Button.h"
#include "Slider.h"

CDongScene::CDongScene()
{
}


CDongScene::~CDongScene()
{
}

Engine::CScene* CDongScene::Create(void)
{
	CDongScene* pInstance = new CDongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CDongScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CDongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CDongScene::Start(void)
{
	__super::Start();
	SP(Engine::CObject) spEmpty =
		ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background");
	
	{
		SP(CButton) slider =
			std::dynamic_pointer_cast<CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"2"));
		slider->GetTransform()->SetPosition(_float3(200, 100, 0.0f));

	}
}

void CDongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CDongScene::Update(void)
{
	__super::Update();
}

void CDongScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CDongScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CDongScene::OnEnable(void)
{
	__super::OnEnable();

}

void CDongScene::OnDisable(void)
{
	__super::OnDisable();

}

void CDongScene::InitPrototypes(void)
{
}

void CDongScene::ObjectActivation(void)
{
	std::cout << a << std::endl;
}


// 버튼 예제
/*{
SP(CButton) image =
std::dynamic_pointer_cast<CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"0"));
image->GetTransform()->SetPosition(_float3(100,100, 0.0f));
image->GetTransform()->SetSize(_float3(100, 100, 0.0f));
image->SetButtonType(CButton::Press);
image->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"심해", _float2(0, 0), _float2(200, 200), 10, 0, D3DXCOLOR(1, 0, 0, 1), true);

CDongScene* aa = new CDongScene();
aa->a = 10;
image->AddFunceData<void(CDongScene::*)(), CDongScene*>(&CDongScene::ObjectActivation, aa);
}

{
SP(CButton) image =
std::dynamic_pointer_cast<CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"2"));
image->GetTransform()->SetPosition(_float3(200, 100, 0.2f));
image->GetTransform()->SetSize(_float3(100, 100, 0.0f));
image->SetButtonType(CButton::Down);
image->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"심해", _float2(0, 0), _float2(200, 200), 10, 0, D3DXCOLOR(1, 0, 0, 1), true);

CDongScene* aa = new CDongScene();
aa->a = 20;
image->AddFunceData<void(CDongScene::*)(), CDongScene*>(&CDongScene::ObjectActivation, aa);
}

{
SP(CButton) image =
std::dynamic_pointer_cast<CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"1"));
image->GetTransform()->SetPosition(_float3(300, 100, 0.1f));
image->GetTransform()->SetSize(_float3(100, 100, 0.0f));
image->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"심해", _float2(0, 0), _float2(200, 200), 10, 0, D3DXCOLOR(1, 0, 0, 1), true);

CDongScene* aa = new CDongScene();
aa->a = 30;
image->AddFunceData<void(CDongScene::*)(), CDongScene*>(&CDongScene::ObjectActivation, aa);
}*/

// 이미지 예제
/*{
SP(Engine::CImageObject) image =
std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"Image", true, (_int)ELayerID::UI, L"sdfsdf"));
image->GetTransform()->SetPositionZ(0.0f);
image->GetTransform()->SetSize(_float3(800, 500, 0));
image->GetTexture()->AddTexture(L"SealPatten3 #16871", 0);
image->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"바다", _float2(200, 200), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1), true);
}

{
SP(Engine::CImageObject) image =
std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"Image", true, (_int)ELayerID::UI, L"sdfsdf"));
image->GetTransform()->SetPositionZ(0.2f);
image->GetTransform()->SetSize(_float3(800, 500, 0));
image->GetTexture()->AddTexture(L"Stage_Image", 0);
image->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"하늘", _float2(300, 300), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1), true);
}

{
SP(Engine::CObject) image =
ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::UI, L"Background");
image->GetTransform()->SetPositionZ(0.0f);
image->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"심해", _float2(400, 300), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1), true);
image->GetComponent<Engine::CTextC>()->AddFontData(L"2", L"초심해", _float2(500, 300), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1), true);
}*/