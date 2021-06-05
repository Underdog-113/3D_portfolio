#include "stdafx.h"
#include "DongScene.h"
#include "Image.h"
//#include "Button.h"
#include "Text.h"

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
		SP(Engine::CImage) image =
			std::dynamic_pointer_cast<Engine::CImage>(ADD_CLONE(L"Image", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.0f);
		image->GetTransform()->SetSize(_float3(800, 500, 0));
		image->GetTexture()->AddTexture(L"SealPatten3 #16871", 0);
		image->AddComponent<Engine::CTextC>()->AddFontData(L"�ٴ�", _float2(200, 200), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1));
	}

	{
		SP(Engine::CImage) image =
			std::dynamic_pointer_cast<Engine::CImage>(ADD_CLONE(L"Image", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.2f);
		image->GetTransform()->SetSize(_float3(800, 500, 0));
		image->GetTexture()->AddTexture(L"Stage_Image", 0);
		image->AddComponent<Engine::CTextC>()->AddFontData(L"�ϴ�", _float2(400, 300), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1));
	}

	{
		SP(Engine::CText) image =
			std::dynamic_pointer_cast<Engine::CText>(ADD_CLONE(L"Text", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.0f);
		image->GetText()->AddFontData(L"��", _float2(100, 300), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1));
	}

	/*{
		SP(Engine::CButton) image =
			std::dynamic_pointer_cast<Engine::CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.2f);
		image->GetTransform()->SetSize(_float3(800, 500, 0));
	}*/

	/*{
		SP(Engine::CButton<int>) image =
			std::dynamic_pointer_cast<Engine::CButton<int>>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.0f);
		image->SetFunctionData(10);
	}*/
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
