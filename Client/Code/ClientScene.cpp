#include "stdafx.h"
#include "ClientScene.h"
#include "Loading.h"

CClientScene::CClientScene()
{
}

CClientScene::~CClientScene()
{
}


void CClientScene::Awake(_int numOfLayers)
{
	__super::Awake(numOfLayers);
	
}

void CClientScene::Start(void)
{
	__super::Start();
	
}

void CClientScene::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CClientScene::Update(void)
{
	__super::Update();
	if (m_pLoading && m_pLoading->GetFinish())
	{
		Engine::CSceneManager::GetInstance()->SceneChange(m_pLoading->GetNextScene());
	}
}

void CClientScene::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CClientScene::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CClientScene::OnEnable(void)
{
	__super::OnEnable();
	
}

void CClientScene::OnDisable(void)
{
	__super::OnDisable();
	
}

void CClientScene::ChangeScene(CScene * pScene)
{
	m_pLoading = CLoading::Create(pScene, false);
}

void CClientScene::InitLights(void)
{
	__super::InitLights();
	
}
