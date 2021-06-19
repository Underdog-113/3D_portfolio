#ifndef YONGSCENE_H
#define YONGSCENE_H

#include "ClientScene.h"

class CYongScene final :public CClientScene
{
private:
	explicit							CYongScene			(void);
									   ~CYongScene			(void);

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

private:
					void				InitPrototypes		(void) override;


private:
	SP(Engine::CObject) m_spKiana;
private:
	CStageControlTower* m_pController = nullptr;
};

#endif