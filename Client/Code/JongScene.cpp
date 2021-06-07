#include "stdafx.h"
#include "JongScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"

#include "DynamicMeshData.h"
#include "FSM_SpiderC.h"
#include "FSM_KianaC.h"

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
		{
			SP(Engine::CObject) spEmptyObject1
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Pivot");

			spEmptyObject1->AddComponent<Engine::CMeshC>()->AddMeshData(L"Pistol_USP45");
			spEmptyObject1->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject1->AddComponent<Engine::CTextureC>();
			spEmptyObject1->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject1->GetTransform()->SetSize(10, 10, 10);

			m_pivot = spEmptyObject1.get();
		}

		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"122");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Kiana");
			spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject->AddComponent<Engine::CTextureC>();
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaTest);
			spEmptyObject->GetTransform()->SetSize(5, 5, 5);

			spEmptyObject->AddComponent<CFSM_KianaC>();

			spEmptyObject->GetComponent<Engine::CMeshC>()->GetRootMotion()->SetIsRootMotion(true);
			Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(spEmptyObject->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
			pDM->GetAniCtrl()->SetReplay(true);

			m_obj = spEmptyObject.get();

			m_pivot->GetTransform()->SetParent(m_obj->GetTransform());
		}

		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Map, L"122");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"Cube");
			spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject->GetTransform()->SetSize(5, 5, 5);

		}
/*
		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"2");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"MB_Bronya_arsenal_end");
			spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject->AddComponent<Engine::CTextureC>();
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject->GetTransform()->SetSize(50, 50, 50);
			spEmptyObject->GetTransform()->SetPosition(50, 0, 0);
			m_obj1 = spEmptyObject.get();
		}

		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"3");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"MB_Bronya_arsenal_loop");
			spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject->AddComponent<Engine::CTextureC>();
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject->GetTransform()->SetSize(50, 50, 50);
			spEmptyObject->GetTransform()->SetPosition(100, 0, 0);
			m_obj2 = spEmptyObject.get();
		}

		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"4");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"MB_Bronya_Anim201");
			spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject->AddComponent<Engine::CTextureC>();
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject->GetTransform()->SetSize(50, 50, 50);
			spEmptyObject->GetTransform()->SetPosition(150, 0, 0);
			m_obj3 = spEmptyObject.get();
		}

		{
			SP(Engine::CObject) spEmptyObject
				= m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"5");

			spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"MB_Bronya_Anim201_bs");
			spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
			spEmptyObject->AddComponent<Engine::CTextureC>();
			spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
			spEmptyObject->GetTransform()->SetSize(50, 50, 50);
			spEmptyObject->GetTransform()->SetPosition(200, 0, 0);
			m_obj4 = spEmptyObject.get();
		}*/

	}
}

void CJongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CJongScene::Update(void)
{
	__super::Update();
//	if (Engine::IMKEY_DOWN(KEY_TAB))
//	{
//		++num;
//		Engine::CDynamicMeshData* pDM = static_cast<Engine::CDynamicMeshData*>(m_obj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//		pDM->ChangeAniSet(num);
///*
//		pDM = static_cast<Engine::CDynamicMeshData*>(m_obj1->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//		pDM->ChangeAniSet(num);
//
//		pDM = static_cast<Engine::CDynamicMeshData*>(m_obj2->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//		pDM->ChangeAniSet(num);
//
//		pDM = static_cast<Engine::CDynamicMeshData*>(m_obj3->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//		pDM->ChangeAniSet(num);
//
//		pDM = static_cast<Engine::CDynamicMeshData*>(m_obj4->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);
//		pDM->ChangeAniSet(num);*/
//
//	}
	//_mat mmmat = dynamic_pointer_cast<Engine::CDynamicMeshData*>(m_obj->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0])->GetRootFrame()->TransformationMatrix();
	//m_pivot->GetTransform()->SetPosition()
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
