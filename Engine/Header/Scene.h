#ifndef SCENE_H
#define SCENE_H

#include "ObjectFactory.h"
#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"
#include "LightManager.h"


BEGIN(Engine)
class CLayer;
class CObject;
class ENGINE_DLL CScene abstract  
{
protected:
	explicit							CScene				(void);
	virtual							   ~CScene				(void);

public:
	virtual		void					Free				(void) PURE;
	virtual		void					Awake				(_int numOfLayers);
	virtual		void					Start				(void);
																   
	virtual		void					FixedUpdate			(void);
	virtual		void					Update				(void);
	virtual		void					LateUpdate			(void);	
																  
	virtual		void					OnDestroy			(void);
																   
	virtual		void					OnEnable			(void) PURE;
	virtual		void					OnDisable			(void) PURE;
				
				SP(CObject)				FindObjectByName	(std::wstring name);
				SP(CObject)				FindObjectWithKey	(std::wstring objectKey);
				_uint					FindObjectsWithKey	(std::wstring objectKey, 
															 std::vector<SP(CObject)>& gameObjects);

public:
				void					SetIsEnabled		(_bool isEnabled);
	virtual		void					InitPrototypes		(void) PURE;
	virtual		void					InitLights			(void);
protected:												   
				void					InitLayers			(_int numOfLayers);

	
protected:
	typedef std::vector<CLayer*> _LAYERS;
	GETTOR			(_LAYERS,					m_vLayers,			{},				Layers)
	GETTOR			(CObjectFactory*,			m_pObjectFactory,	nullptr,		ObjectFactory)
	GETTOR			(CDataStore*,				m_pDataStore,		nullptr,		DataStore)
	GETTOR			(CMeshStore*,				m_pMeshStore,		nullptr,		MeshStore)
	GETTOR			(CTextureStore*,			m_pTextureStore,	nullptr,		TextureStore)
	GETTOR			(CLightManager*,			m_pLightManager,	nullptr,		LightManager)

	GETTOR			(std::wstring,				m_objectKey,		L"",			ObjectKey)
	GETTOR			(_int,						m_sceneID,			-1,				SceneID)

	GETTOR			(_bool,						m_isAwaked,			false,			IsAwaked)
	GETTOR			(_bool,						m_isStarted,		false,			IsStarted)
	GETTOR			(_bool,						m_isEnabled,		true,			IsEnabled)
	GETTOR_SETTOR	(_bool,						m_SceneEvent,		false,			SceneEvent)

};
END

#endif