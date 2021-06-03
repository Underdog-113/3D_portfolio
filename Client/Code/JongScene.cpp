#include "stdafx.h"
#include "JongScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"

#include "DynamicMesh.h"

CJongScene::CJongScene()
{
}


CJongScene::~CJongScene()
{
}

Engine::CScene * CJongScene::Create(void)
{
	CJongScene* pInstance = new CJongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CJongScene::Free(void)
{
	OnDestroy();
	delete this;
}

void CJongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	InitPrototypes();
}

void CJongScene::Start(void)
{
	__super::Start();
	{
		//SP(Engine::CObject) spEmptyObject
		//	= Engine::ADD_CLONE(L"EmptyObject", this, true, L"Kiana", (_int)ELayerID::Player);

		//spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Robot_Attack_1_Left");
		//spEmptyObject->AddComponent<Engine::CTextureC>();
		//spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

		//spEmptyObject->GetTransform()->SetSize(100, 100, 100);

		SP(Engine::CObject) spEmptyObject
			= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"kiana");

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Spider");
		spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CTextureC>();
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spEmptyObject->GetTransform()->SetSize(50, 50, 50);

		m_obj = spEmptyObject.get();
	}
}

void CJongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CJongScene::Update(void)
{
	__super::Update();
	if (Engine::IMKEY_DOWN(KEY_TAB))
	{
		++num;
		Engine::CDynamicMesh* pDM = static_cast<Engine::CDynamicMesh*>(m_obj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
		pDM->ChangeAniSet(num);
	}
}

void CJongScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CJongScene::OnDestroy(void)
{
	__super::OnDestroy();

}

void CJongScene::OnEnable(void)
{
	__super::OnEnable();

}

void CJongScene::OnDisable(void)
{
	__super::OnDisable();

}

void CJongScene::InitPrototypes(void)
{
}
