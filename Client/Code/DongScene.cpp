#include "stdafx.h"
#include "DongScene.h"
#include "TextComponent.h"
#include "DebugTextComponent.h"
#include "TextObject.h"
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

	/*spEmpty->AddComponent<Engine::CBitmapC>();
	spEmpty->AddComponent<Engine::CTextureC>()->AddTexture(L"A");
	spEmpty->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::UI);
	spEmpty->GetTransform()->SetSize(800, 600, 0);*/

	/*
	SP(CTextObject) object = std::dynamic_pointer_cast<CTextObject>(m_pObjectFactory->AddClone(L"TextObject", true));
	object->GetTransform()->SetSize(800, 600, 0);
	//*/

	//*
	SP(Engine::CObject) spEmptyObject
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::UI, L"Text0");
	spEmptyObject->AddComponent<CTextComponent>()->AddFontData(L"A", 20,5, 400, D3DXCOLOR(1, 1, 1, 1));
	//*/

	SP(Engine::CObject) ss
		= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::UI, L"Text0");
	ss->AddComponent<CDebugTextComponent>()->AddFontData(L"sdfes", _float2(800, 800), 500, DT_RIGHT, D3DXCOLOR(0, 0, 0, 1));
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
