#include "stdafx.h"
#include "YongScene.h"
#include "FRC.h"

CYongScene::CYongScene()
{
}


CYongScene::~CYongScene()
{
}

Engine::CScene * CYongScene::Create(void)
{
	CYongScene* pInstance = new CYongScene;
	pInstance->Awake((_int)ELayerID::NumOfLayerID);

	return pInstance;
}

void CYongScene::Free(void)
{

	OnDestroy();

	delete this;
}

void CYongScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);

	

	/*spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
	spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);*/
	/*spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::Particle);
	spEmptyObject->AddComponent<Engine::CParticleSystemC>();*/


	InitPrototypes();
}

void CYongScene::Start(void)
{
	__super::Start();
	{
		SP(Engine::CObject) spEmptyObject = ADD_CLONE(L"EmptyObject", true, (_int)ELayerID::Map, L"Cube0");

		spEmptyObject->AddComponent<Engine::CMeshC>()->AddMeshData(L"waterplane");
		//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
		spEmptyObject->AddComponent<Engine::CTextureC>()->AddTexture(L"water", 0);
		spEmptyObject->AddComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::NonAlpha);
		spEmptyObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		
		spEmptyObject->GetTransform()->SetSize(2, 2, 2);
		spEmptyObject->GetTransform()->SetPosition(3, 0, 0);

		//m_pObjectFactory->AddClone(L"MO_Spider", true, (_int)ELayerID::Enemy, L"MO_Spider");
	}	
}

void CYongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CYongScene::Update(void)
{
	__super::Update();
}

void CYongScene::LateUpdate(void)
{
	__super::LateUpdate();

}

void CYongScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CYongScene::OnEnable(void)
{
	__super::OnEnable();
	
}

void CYongScene::OnDisable(void)
{
	__super::OnDisable();
	
}

void CYongScene::InitPrototypes(void)
{
}
