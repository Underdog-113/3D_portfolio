#include "stdafx.h"
#include "WooScene.h"
#include "EmptyObject.h"
#include "ObjectFactory.h"
#include "CameraManager.h"

#include "InputManager.h"
#include "DynamicMeshData.h"
#include "MeshData.h"

CWooScene::CWooScene()
{
}


CWooScene::~CWooScene()
{
}

Engine::CScene * CWooScene::Create(void)
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
	InitPrototypes();
}

void CWooScene::Start(void)
{
	__super::Start();
	{
		m_spSakura = m_pObjectFactory->AddClone(L"EmptyObject", true, (_int)ELayerID::Player, L"Character");

		m_spSakura->AddComponent<Engine::CMeshC>()->AddMeshData(L"Yae_Sakura");
		m_spSakura->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		m_spSakura->AddComponent<Engine::CTextureC>();
		m_spSakura->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);

		m_spSakura->GetTransform()->SetSize(30, 30, 30);
	}
}

void CWooScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CWooScene::Update(void)
{
	__super::Update();

	//Engine::CDynamicMesh* pDM = 
	//	static_cast<Engine::CDynamicMesh*>(m_spSakura->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]);

	//if (Engine::IMKEY_DOWN(KEY_RIGHT))
	//{
	//	if (59 <= m_iIndex)
	//		m_iIndex = 0;
	//	else
	//		++m_iIndex;

	//	pDM->ChangeAniSet(m_iIndex);

	//	std::cout << "index: " << m_iIndex << std::endl;
	//	std::cout << "================================" << std::endl;
	//}
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
