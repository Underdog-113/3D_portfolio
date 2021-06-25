#ifndef CLIENTSCENE_H
#define CLIENTSCENE_H

#include "Scene.h"
class CLoading;
class CClientScene abstract : public Engine::CScene
{
protected:
	explicit							CClientScene		(void);
	virtual							   ~CClientScene		(void);

public:
	virtual		void					Free				(void) PURE;
	virtual		void					Awake				(_int numOfLayers) override;
	virtual		void					Start				(void) override;
																   
	virtual		void					FixedUpdate			(void) override;
	virtual		void					Update				(void) override;
	virtual		void					LateUpdate			(void) override;	
																  
	virtual		void					OnDestroy			(void) override;
																   
	virtual		void					OnEnable			(void) override;
	virtual		void					OnDisable			(void) override;

public:
				void					ChangeScene			(CScene* pScene);
	virtual		void					InitPrototypes		(void) PURE;
	virtual		void					InitLights			(void) override;
protected:
	GETTOR_SETTOR	(CLoading*,			m_pLoading,			nullptr,		Loading)
};

#endif