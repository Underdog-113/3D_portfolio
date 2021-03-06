#ifndef STAGESELECTIONSCENE_H
#define STAGESELECTIONSCENE_H

#include "ClientScene.h"
class CLoading;
class CStageSelectionScene final :public CClientScene
{
private:
	explicit							CStageSelectionScene			(void);
									   ~CStageSelectionScene			(void);

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
};

#endif