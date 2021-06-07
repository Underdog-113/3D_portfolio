#include "stdafx.h"
#include "DongScene.h"
#include "ImageObject.h"
#include "Button.h"
#include "Slider.h"
#include "Function.h"

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
		SP(Engine::CImageObject) image =
			std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"sdfsdf"));
		image->GetTransform()->SetPositionZ(0.0f);
		image->GetTransform()->SetSize(_float3(800, 600, 0));
		image->GetTexture()->AddTexture(L"SpaceShipBridge_DeepOcean", 0);
	}

	{
		SP(CButton) button =
			std::dynamic_pointer_cast<CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"0"));
		button->GetTransform()->SetPosition(_float3(300, 109, 0.0f));
		button->GetTransform()->SetSize(_float3(141, 152, 0.1f));
		button->SetButtonType(CButton::UP);
		button->GetTexture()->AddTexture(L"BtnAttack1", 0);
		button->AddFuncData<void(CFunction::*)(), CFunction*>(&CFunction::ChangeJongScene, &CFunction());
		button->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"출격", _float2(400, 300), _float2(0,0), 50, DT_LEFT + DT_NOCLIP, D3DXCOLOR(1, 0, 0, 1), true);
	}
	

	{
		SP(Engine::CSlider) slider =
			std::dynamic_pointer_cast<Engine::CSlider>(ADD_CLONE(L"Slider", true, (_int)ELayerID::UI, L"Slidr_0"));
		slider->GetTransform()->SetPosition(_float3(150, 100, 0.0f));
		slider->SetDirection((Engine::CSlider::ESliderDirection::BottomToTop));

		SP(Engine::CImageObject) background =
			std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"BackGround"));
		background->GetTransform()->SetPosition(slider->GetTransform()->GetPosition());
		background->GetTransform()->SetSize(_float3(104, 104, 0));
		background->GetTexture()->AddTexture(L"AvatarButtonFrame", 0);

		SP(Engine::CImageObject) fill =
			std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"Fill"));
		fill->SetParent(slider.get());
		fill->GetTransform()->SetPosition(slider->GetTransform()->GetPosition() + _float3(3.2f, -0.28f, -0.9f));
		fill->GetTransform()->SetPositionZ(slider->GetTransform()->GetPosition().z);
		fill->GetTransform()->SetSize(_float3(106, 98, 0));
		fill->GetTexture()->AddTexture(L"AvatarButtonHP_Bar", 0);
		fill->AddComponent<Engine::CShaderC>()->
			AddShader(Engine::CShaderManager::GetInstance()->GetShaderID((L"SliderShader")));

		slider->AddSliderData(100, 100, background, fill);
	}

	{
		SP(Engine::CSlider) slider =
			std::dynamic_pointer_cast<Engine::CSlider>(ADD_CLONE(L"Slider", true, (_int)ELayerID::UI, L"Slidr_0"));
		slider->GetTransform()->SetPosition(_float3(-150, 100, 0.0f));
		slider->SetDirection((Engine::CSlider::ESliderDirection::LeftToRight));

		SP(Engine::CImageObject) background =
			std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"BackGround"));
		background->GetTransform()->SetPosition(slider->GetTransform()->GetPosition());
		background->GetTransform()->SetSize(_float3(132, 13, 0));
		background->GetTexture()->AddTexture(L"BarHp", 0);

		SP(Engine::CImageObject) fill =
			std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"Fill"));
		fill->SetParent(slider.get());
		fill->GetTransform()->SetPosition(slider->GetTransform()->GetPosition());
		fill->GetTransform()->SetPositionZ(slider->GetTransform()->GetPosition().z);
		fill->GetTransform()->SetSize(_float3(128, 9, 0));
		fill->GetTexture()->AddTexture(L"BarHpFill", 0);
		fill->AddComponent<Engine::CShaderC>()->
			AddShader(Engine::CShaderManager::GetInstance()->GetShaderID((L"SliderShader")));

		slider->AddSliderData(100, 100, background, fill);
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


// 이미지 버튼 슬라이더 예제
/*
{
	SP(Engine::CImageObject) image =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"sdfsdf"));
	image->GetTransform()->SetPositionZ(0.0f);
	image->GetTransform()->SetSize(_float3(800, 600, 0));
	image->GetTexture()->AddTexture(L"SpaceShipBridge_DeepOcean", 0);
}

{
	SP(CButton) button =
		std::dynamic_pointer_cast<CButton>(ADD_CLONE(L"Button", true, (_int)ELayerID::UI, L"0"));
	button->GetTransform()->SetPosition(_float3(0, 0, 0.0f));
	button->GetTransform()->SetSize(_float3(141, 152, 0.1f));
	button->SetButtonType(CButton::UP);
	button->GetTexture()->AddTexture(L"BtnAttack1", 0);
	button->AddFuncData<void(CFunction::*)(), CFunction*>(&CFunction::ChangeJongScene, &CFunction());
	button->AddComponent<Engine::CTextC>()->AddFontData(L"1", L"출격", _float2(400, 300), _float2(0, 0), 50, DT_LEFT + DT_NOCLIP, D3DXCOLOR(1, 0, 0, 1), true);
}


{
	SP(Engine::CSlider) slider =
		std::dynamic_pointer_cast<Engine::CSlider>(ADD_CLONE(L"Slider", true, (_int)ELayerID::UI, L"Slidr_0"));
	slider->GetTransform()->SetPosition(_float3(200, 100, 0.0f));
	slider->SetDirection((Engine::CSlider::ESliderDirection::BottomToTop));

	SP(Engine::CImageObject) background =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"BackGround"));
	background->GetTransform()->SetPosition(slider->GetTransform()->GetPosition());
	background->GetTransform()->SetSize(_float3(104, 104, 0));
	background->GetTexture()->AddTexture(L"AvatarButtonFrame", 0);

	SP(Engine::CImageObject) fill =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"Fill"));
	fill->GetTransform()->SetPosition(slider->GetTransform()->GetPosition() + _float3(3.2f, -0.28f, -0.9f));
	fill->GetTransform()->SetPositionZ(slider->GetTransform()->GetPosition().z);
	fill->GetTransform()->SetSize(_float3(106, 98, 0));
	fill->GetTexture()->AddTexture(L"AvatarButtonHP_Bar", 0);
	fill->AddComponent<Engine::CShaderC>()->
		AddShader(Engine::CShaderManager::GetInstance()->GetShaderID((L"SliderShader")))->
		SetOwnerObject(slider.get());

	slider->AddSliderData(100, 100, background, fill);
}

{
	SP(Engine::CSlider) slider =
		std::dynamic_pointer_cast<Engine::CSlider>(ADD_CLONE(L"Slider", true, (_int)ELayerID::UI, L"Slidr_0"));
	slider->GetTransform()->SetPosition(_float3(100, 100, 0.0f));
	slider->SetDirection((Engine::CSlider::ESliderDirection::LeftToRight));

	SP(Engine::CImageObject) background =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"BackGround"));
	background->GetTransform()->SetPosition(slider->GetTransform()->GetPosition());
	background->GetTransform()->SetSize(_float3(132, 13, 0));
	background->GetTexture()->AddTexture(L"BarHp", 0);

	SP(Engine::CImageObject) fill =
		std::dynamic_pointer_cast<Engine::CImageObject>(ADD_CLONE(L"ImageObject", true, (_int)ELayerID::UI, L"Fill"));
	fill->GetTransform()->SetPosition(slider->GetTransform()->GetPosition() + _float3(3.2f, -0.28f, -0.9f));
	fill->GetTransform()->SetPositionZ(slider->GetTransform()->GetPosition().z);
	fill->GetTransform()->SetSize(_float3(128, 9, 0));
	fill->GetTexture()->AddTexture(L"BarHpFill", 0);
	fill->AddComponent<Engine::CShaderC>()->
		AddShader(Engine::CShaderManager::GetInstance()->GetShaderID((L"SliderShader")))->
		SetOwnerObject(slider.get());

	slider->AddSliderData(100, 100, background, fill);
}
*/