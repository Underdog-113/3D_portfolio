#include "stdafx.h"
#include "WooScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"
#include "CameraManager.h"

#include "DynamicMeshData.h"
#include "AniCtrl.h"

#include "FSM_SpiderC.h"
#include "MO_Spider.h"

CWooScene::CWooScene()
{
}


CWooScene::~CWooScene()
{
}

CClientScene* CWooScene::Create(void)
{
	CWooScene* pInstance = new CWooScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CWooScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CWooScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
}

void CWooScene::Start(void)
{
	__super::Start();
	{
		// 쓰지 마세요오오옹
		{
			SP(Engine::CObject) spEmptyObject1
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Pivot");

			spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Pistol_USP45");
			spEmptyObject1->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject1->AddComponent<Engine::CTextureC>();
			spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject1->GetTransform()->SetSize(1, 1, 1);

			m_pivot = spEmptyObject1.get();

			Engine::CCameraManager::GetInstance()->GetCamera(L"JongSceneBasicCamera")->SetTarget(spEmptyObject1);
		}

		{
			SP(Engine::CObject) spSpiderClone = ADD_CLONE(L"MO_Spider", true, (_uint)ELayerID::Enemy, L"MO_Spider");
			spSpiderClone->GetTransform()->SetRotationY(D3DXToRadian(90));
			m_spSpider = spSpiderClone;
		}
	}
}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	__super::Update();
}

void CWooScene::LateUpdate(void)
{
	__super::LateUpdate();
}

void CWooScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CWooScene::OnEnable(void)
{
	__super::OnEnable();
}

void CWooScene::OnDisable(void)
{
	__super::OnDisable();
}

void CWooScene::InitPrototypes(void)
{
}
