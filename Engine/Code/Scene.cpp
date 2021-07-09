#include "EngineStdafx.h"
#include "Scene.h"
#include "Layer.h"
#include "Object.h"
#include "WndApp.h"

USING(Engine)
CScene::CScene(void)
{
}
CScene::~CScene(void)
{
}

void CScene::Awake(_int numOfLayers)
{
	m_isAwaked = true;


	m_objectKey			= GetCurClassName(this);
	m_pObjectFactory	= CObjectFactory::Create(this);

	m_pDataStore		= CDataStore::Create();
	m_pMeshStore		= CMeshStore::Create();
	m_pTextureStore		= CTextureStore::Create();
	m_pLightManager		= CLightManager::Create();
	
	SetWindowTextA(Engine::GET_HANDLE, WStrToStr(m_objectKey).c_str());

	InitLights();
	InitLayers(numOfLayers);
}

void CScene::Start(void)
{
	m_isStarted = true;

	SP(CCamera) spCameraObject =
		std::dynamic_pointer_cast<CCamera>(m_pObjectFactory->AddClone(L"Camera", true));

	CCameraManager::GetInstance()->AddCamera(m_objectKey + L"BasicCamera", spCameraObject);
}

void CScene::FixedUpdate(void)
{
	for (auto& layer : m_vLayers)
	{
		if (layer->GetEnable())
			layer->FixedUpdate();
	}
}

void CScene::Update(void)
{
	for (auto& layer : m_vLayers)
	{
		if(layer->GetEnable())
			layer->Update();
	}
}

void CScene::LateUpdate(void)
{
	for (auto& layer : m_vLayers)
	{
		if (layer->GetEnable())
			layer->LateUpdate();
	}
}

void CScene::OnDestroy(void)
{
	for (auto& layer : m_vLayers)
		layer->Free();

	if (m_isStarted)
	{
		CCameraManager::GetInstance()->DeleteCamera(m_objectKey + L"BasicCamera");
		CCameraManager::GetInstance()->SetMainCamera(nullptr);
	}

	m_pObjectFactory->Free();
	m_pObjectFactory = nullptr;

	m_pDataStore->Free();
	m_pDataStore = nullptr;

	m_pMeshStore->Free();
	m_pMeshStore = nullptr;

	m_pTextureStore->Free();
	m_pTextureStore = nullptr;

	m_pLightManager->Free();
	m_pLightManager = nullptr;

	CTextManager::GetInstance()->ClearForScene();
}

void CScene::OnEnable(void)
{
	m_isEnabled = true;
}

void CScene::OnDisable(void)
{
	m_isEnabled = false;
}

SP(CObject) CScene::FindObjectByName(std::wstring name)
{
	for (auto& layer : m_vLayers)
	{
		for (auto& gameObject : layer->GetGameObjects())
		{
			if (gameObject->GetName() == name)
				return gameObject;
		}
	}
	return nullptr;
}

SP(CObject) CScene::FindObjectWithKey(std::wstring objectKey)
{
	for (auto& layer : m_vLayers)
	{
		for (auto& gameObject : layer->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				return gameObject;
		}
	}
	return nullptr;
}

_uint CScene::FindObjectsWithKey(std::wstring objectKey, std::vector<SP(CObject)>& gameObjects)
{
	for (auto& layer : m_vLayers)
	{
		for (auto& gameObject : layer->GetGameObjects())
		{
			if (gameObject->GetObjectKey() == objectKey)
				gameObjects.push_back(gameObject);
		}
	}
	return (_uint)gameObjects.size();
}

void CScene::SetIsEnabled(_bool isEnabled)
{
	if (m_isEnabled == isEnabled)
		return;

	if (isEnabled == true)
		OnEnable();
	else
		OnDisable();
}

void CScene::InitLights(void)
{
	D3DLIGHT9* pLightInfo = new D3DLIGHT9;

	pLightInfo->Type = D3DLIGHT_DIRECTIONAL;
	pLightInfo->Direction = _float3(1.f, -1.f, 0.f);
	pLightInfo->Diffuse = D3DXCOLOR(1.4f, 1.4f, 1.4f, 1.f);
	pLightInfo->Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	pLightInfo->Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);


	//m_pLightManager->AddLight(pLightInfo);
	//
	//pLightInfo = new D3DLIGHT9;
	//pLightInfo->Type = D3DLIGHT_POINT;
	//pLightInfo->Position = _float3(10.f, 5.f, 10.f);
	//pLightInfo->Diffuse = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	//pLightInfo->Ambient = D3DXCOLOR(0.2f, 0.f, 0.f, 1.f);
	//pLightInfo->Specular = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	//pLightInfo->Range = 10.f;
	//
	//m_pLightManager->AddLight(pLightInfo);
	//
	//
	//pLightInfo = new D3DLIGHT9;
	//pLightInfo->Type = D3DLIGHT_POINT;
	//pLightInfo->Position = _float3(15.f, 5.f, 15.f);
	//pLightInfo->Diffuse = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);
	//pLightInfo->Ambient = D3DXCOLOR(0.f, 0.f, 0.2f, 1.f);
	//pLightInfo->Specular = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);
	//pLightInfo->Range = 10.f;

	m_pLightManager->AddLight(pLightInfo);
}

void CScene::InitLayers(_int numOfLayers)
{
	m_vLayers.reserve(numOfLayers);

	for (_int i = 0; i < numOfLayers; ++i)
		m_vLayers.emplace_back(CLayer::Create(i, this));

	return;
}