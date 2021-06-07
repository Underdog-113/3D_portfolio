#include "stdafx.h"
#include "YongScene.h"
#include "FRC.h"
#include "TestParticle.h"

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
	srand((unsigned int)time(0));
	Engine::BoundingBox boundingBox;
	boundingBox._min = _float3(-10.f, -10.f, -10.f);
	boundingBox._max = _float3(10.f, 10.f, 10.f);
	m_pTestParticle = new CTestParticle(&boundingBox, 3000);

	InitPrototypes();
}

void CYongScene::Start(void)
{
	__super::Start();
	{
		m_pObjectFactory->AddClone(L"MO_Spider", true, (_int)ELayerID::Enemy, L"MO_Spider");
	}	
}

void CYongScene::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CYongScene::Update(void)
{
	__super::Update();
	m_pTestParticle->Update();
}

void CYongScene::LateUpdate(void)
{
	__super::LateUpdate();
	m_pTestParticle->Render();

}

void CYongScene::OnDestroy(void)
{
	__super::OnDestroy();
	
	m_pTestParticle->Release();
	SAFE_DELETE(m_pTestParticle);
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
