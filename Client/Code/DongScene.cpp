#include "stdafx.h"
#include "DongScene.h"
#include "Image.h"
#include "Button.h"
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

void SS(_float ss)
{
	_float s = ss;
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
		image->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"바다", _float2(200, 200), _float2(200, 200), 50, 0, D3DXCOLOR(1, 0, 0, 1), true);
	}

	{
		SP(Engine::CImage) image =
			std::dynamic_pointer_cast<Engine::CImage>(ADD_CLONE(L"Image", true, (_int)ELayerID::UI, L"sdfsdf"));
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
	}

	/*{
		SP(Engine::CButton) image =
			std::dynamic_pointer_cast<Engine::CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.2f);
		image->GetTransform()->SetSize(_float3(800, 500, 0));
	}*/

	{
		/*SP(CButton<_float>) image =
			std::dynamic_pointer_cast<CButton<_float>>(ADD_CLONE(L"Button<float>", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.0f);
		image->SetButtonType(CButton<_float>::EButton_Type::UP);
		image->SetFunctionDate(12.5f);
		image->m_functionGate += SS;*/
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