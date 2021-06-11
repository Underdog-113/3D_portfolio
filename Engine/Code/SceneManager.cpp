#include "EngineStdafx.h"
#include "SceneManager.h" 
#include "Object.h"
#include "WndApp.h"
 
 

USING(Engine)
IMPLEMENT_SINGLETON(CSceneManager)
void CSceneManager::Awake(void)
{
	__super::Awake();
}

void CSceneManager::Start(void)
{
}

void CSceneManager::FixedUpdate(void)
{
	if (m_pCurScene != nullptr && m_pCurScene->GetIsEnabled())
	{
		m_pCurScene->FixedUpdate();
	}
}

void CSceneManager::Update(void)
{
	m_sceneChanged = false;
	if (m_pCurScene != nullptr && m_pCurScene->GetIsEnabled())
	{
		m_pCurScene->Update();
	}
}

void CSceneManager::LateUpdate(void)
{
	if (m_pCurScene != nullptr && m_pCurScene->GetIsEnabled())
	{
		m_pCurScene->LateUpdate();
	}
}



void CSceneManager::OnDestroy(void)
{
	m_pCurScene->Free();
}

void CSceneManager::OnEnable(void)
{
}

void CSceneManager::OnDisable(void)
{
}


void CSceneManager::SceneChange(CScene* pScene)
{
	CFRC::GetInstance()->OnDisable();
	if (m_pCurScene)
		m_pCurScene->Free();

	m_pCurScene = pScene;

	if(m_pCurScene->GetIsStarted() == false)
		m_pCurScene->Start();

	CFRC::GetInstance()->OnEnable();
	CCameraManager::GetInstance()->SetMainCamera(CCameraManager::GetInstance()->GetCamera(m_pCurScene->GetObjectKey() + L"BasicCamera"));
	m_sceneChanged = true;
}

void CSceneManager::OrganizeScene(_bool deleteCurScene)
{
	
}