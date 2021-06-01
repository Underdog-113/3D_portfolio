#include "EngineStdafx.h"
#include "ObjectFactory.h"
#include "Object.h"
 
#include "Scene.h"
#include "Layer.h"

#pragma region EnginePrototypeHeaders
#include "EmptyObject.h"
#include "Camera.h"
#include "BoundingVolume.h"
#include "DebugCollider.h"
#include "Grid.h"
#pragma endregion

USING(Engine)

CObjectFactory::_PROTOTYPES CObjectFactory::m_s_mStaticPrototypes = {};
_uint CObjectFactory::m_s_usage = 0;

CObjectFactory::CObjectFactory(void)
{
}

CObjectFactory::~CObjectFactory(void)
{
}

CObjectFactory * CObjectFactory::Create(CScene* pOwnerScene)
{
	CObjectFactory* pInstance = new CObjectFactory;
	pInstance->m_pOwnerScene = pOwnerScene;
	pInstance->Awake();

	++m_s_usage;

	return pInstance;
}

void CObjectFactory::Free(void)
{
	--m_s_usage;
	OnDestroy();
	delete this;
}

void CObjectFactory::Awake(void)
{
	__super::Awake();
}

void CObjectFactory::Start(void)
{
}

void CObjectFactory::OnDestroy(void)
{
	for (auto& prototype : m_mCurPrototypes)
		prototype.second.reset();
	
	m_mCurPrototypes.clear();

	if (m_s_usage == 0)
	{
		for (auto& prototype : m_s_mStaticPrototypes)
			prototype.second.reset();
		m_s_mStaticPrototypes.clear();
	}
}

void CObjectFactory::OnEnable(void)
{
}

void CObjectFactory::OnDisable(void)
{
}

HRESULT CObjectFactory::AddPrototype(SP(CObject) pPrototype)
{
	if (pPrototype == nullptr)
		return E_FAIL;

	_PROTOTYPES* pCurPrototypes = nullptr;

	if (pPrototype->GetIsStatic())
		pCurPrototypes = &m_s_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;

	auto& it = pCurPrototypes->find(pPrototype->GetObjectKey());
	if (it == pCurPrototypes->end())
	{
		(*pCurPrototypes)[pPrototype->GetObjectKey()] = pPrototype;
	}
	else
	{
		MSG_BOX(__FILE__, (pPrototype->GetObjectKey() + L" is already in _PROTOTYPES").c_str());
		ABORT;
	}

	return S_OK;
}

SP(CObject) CObjectFactory::AddClone(const std::wstring & protoObjectKey,
									 _bool isStatic,
									 _int layerTag,
									 const std::wstring & name)
{
	_PROTOTYPES* pCurPrototypes = nullptr;

	if (isStatic)
		pCurPrototypes = &m_s_mStaticPrototypes;
	else
		pCurPrototypes = &m_mCurPrototypes;


	auto iter_find_prototype = pCurPrototypes->find(protoObjectKey);
	if (pCurPrototypes->end() == iter_find_prototype)
	{
		MSG_BOX(__FILE__, (protoObjectKey + L" is not found in AddClone").c_str());
		ABORT;
	}

	SP(CObject) spClone = iter_find_prototype->second->MakeClone();
	if (spClone == nullptr)
	{
		MSG_BOX(__FILE__, (protoObjectKey + L" failed to make clone in AddClone").c_str());
		ABORT;
	}

	_int layerID = spClone->GetLayerID();
	if (layerID == UNDEFINED)
		layerID = layerTag;

	std::vector<CLayer*> const* pLayers = &m_pOwnerScene->GetLayers();
	if (layerID < 0 || (_uint)layerID >= pLayers->size())
	{
		MSG_BOX(__FILE__, std::wstring(L"LayerID is out of range").c_str());
		ABORT;
	}
	(*pLayers)[layerID]->AddGameObject(spClone);
	spClone->SetScene(m_pOwnerScene);

	if (name == L"")
		spClone->SetBasicName();
	else
	{
		_bool isThereSameName = false;
		for (auto& gameObject : (*pLayers)[layerID]->GetGameObjects())
		{
			if (gameObject->GetName() == name)
			{
				isThereSameName = true;
				spClone->SetBasicName();
				break;
			}
		}

		if (isThereSameName == false)
			spClone->SetName(name);
	}

	return spClone;
}

void CObjectFactory::ClearCurPrototype(void)
{
	for (auto& prototype : m_mCurPrototypes)
	{
		prototype.second.reset();
	}
	m_mCurPrototypes.clear();
}


CObjectFactory::_PROTOTYPES & CObjectFactory::GetCurPrototype(void)
{
	return m_mCurPrototypes;
}

CObjectFactory::_PROTOTYPES & CObjectFactory::GetStaticPrototypes(void)
{
	return m_s_mStaticPrototypes;
}
