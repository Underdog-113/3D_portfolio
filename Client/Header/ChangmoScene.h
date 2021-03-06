#ifndef CHANGMOSCENE_H
#define CHANGMOSCENE_H

#include "ClientScene.h"

class CChangmoScene final : public CClientScene
{
private:
	explicit							CChangmoScene		(void);
									   ~CChangmoScene		(void);

public:
	static			CClientScene*		Create				(void);
					void				Free				(void) override;

					void				Awake				(_int numOfLayers) override;
					void				Start				(void) override;
															   
					void				FixedUpdate			(void) override;
					void				Update				(void) override;
					void				LateUpdate			(void) override;	
					
					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;	 
					void				OnDisable			(void) override;

public:
					void				InitPrototypes		(void) override;
					
private:
	SP(Engine::CObject) m_spKiana;
	SP(Engine::CObject) m_spDummy;

	CStageControlTower* m_pControlTower = nullptr;
};

#endif