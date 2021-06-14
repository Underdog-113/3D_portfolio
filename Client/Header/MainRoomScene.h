#ifndef MAINROOMSCENE_H
#define MAINROOMSCENE_H

#include "ClientScene.h"
class CLoading;
class CMainRoomScene final :public CClientScene
{
private:
	explicit							CMainRoomScene			(void);
									   ~CMainRoomScene			(void);

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
					void				ChangeScene			(CClientScene* pScene);

private:
					void				InitPrototypes		(void) override;
};

#endif