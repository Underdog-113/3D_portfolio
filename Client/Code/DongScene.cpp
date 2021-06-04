#include "stdafx.h"
#include "DongScene.h"
#include "TextC.h"
#include "TextObject.h"
#include "ImageObject.h"
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

	//*
	{
		SP(CImageObject) spEmptyObject
			= std::dynamic_pointer_cast<CImageObject>(m_pObjectFactory->AddClone(L"ImageObject", true, (_int)ELayerID::UI, L"Text0"));
		spEmptyObject->GetTransform()->SetSize(_float3(300, 500, 0));
		spEmptyObject->GetTexture()->AddTexture(L"Stage_Image", 0);
	}

	{
		SP(CImageObject) spEmptyObject
			= std::dynamic_pointer_cast<CImageObject>(m_pObjectFactory->AddClone(L"ImageObject", true, (_int)ELayerID::UI, L"Text0"));
		spEmptyObject->GetTransform()->SetSize(_float3(300, 500, 0));
		spEmptyObject->GetTexture()->AddTexture(L"SealPatten3 #16871", 0);
	}
	//*/

	SP(Engine::CObject) ss
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::UI, L"Text0");
	ss->GetTransform()->SetPosition(_float3(-260, 470, 0));
	ss->AddComponent<CDebugTextC>()->AddFontData(L"¹àÀº Àººû ¹Ì¼Ò", _float2(800, 800), 50, DT_RIGHT, D3DXCOLOR(0, 0, 0, 1));
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
