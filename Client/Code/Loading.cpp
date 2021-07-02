#include "stdafx.h"
#include "Loading.h"
#include "DataLoad.h"

CLoading::CLoading()
{
}


CLoading::~CLoading()
{
}

_uint CLoading::ThreadMain(void * pArg)
{
	CLoading* pLoading = (CLoading*)pArg;

	_uint iFlag = 0;

	EnterCriticalSection(&pLoading->m_crt);

	pLoading->m_pNextScene->GetDataStore()->InitDataMap((_uint)EDataID::NumOfDataID);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"BasicObject", (_uint)EDataID::BasicObject);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"Player", (_uint)EDataID::Player);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"Scene", (_uint)EDataID::Scene);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"Enemy", (_uint)EDataID::Enemy);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"UI", (_uint)EDataID::UI);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"Stat", (_uint)EDataID::Stat);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"Monster", (_uint)EDataID::Monster);
	pLoading->m_pNextScene->GetDataStore()->AddDataSection(L"ClientObject", (_uint)EDataID::ClientObject);


	const std::wstring& sceneName = pLoading->m_pNextScene->GetObjectKey();
	pLoading->m_pNextScene->GetDataStore()->InitDataForScene(sceneName, pLoading->m_loadStaticResource);
	pLoading->m_pNextScene->GetMeshStore()->InitMeshForScene(sceneName, pLoading->m_loadStaticResource);
	pLoading->m_pNextScene->GetTextureStore()->InitTextureForScene(sceneName, pLoading->m_loadStaticResource);

	pLoading->m_pNextScene->InitPrototypes();
	pLoading->m_pNextScene->Start();
	pLoading->m_finish = true;
	
	LeaveCriticalSection(&pLoading->m_crt);
	_endthreadex(0);

	

	return iFlag;
}

CLoading * CLoading::Create(Engine::CScene* pNextScene, _bool loadStaticResource)
{
	CLoading* pInstance = new CLoading;

	pInstance->m_pNextScene			= pNextScene;
	pInstance->m_loadStaticResource = loadStaticResource;
	pInstance->StartLoading();
	return pInstance;
}

void CLoading::Free(void)
{
	WaitForSingleObject(m_threadHandle, INFINITE);
	CloseHandle(m_threadHandle);
	DeleteCriticalSection(&m_crt);
}

void CLoading::StartLoading(void)
{
	InitializeCriticalSection(&m_crt);
	m_threadHandle = (HANDLE)_beginthreadex(NULL, 0, ThreadMain, this, 0, NULL);
}


