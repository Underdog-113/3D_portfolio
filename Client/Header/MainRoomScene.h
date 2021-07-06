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

					


private:
					void				InitPrototypes		(void) override;
					void				ControlDeskSetrring	(void);
					void				ShakeControlDesk	(void);

					// for controldesk
					_float3				m_pos;
					_float3				m_upMax;
					_float3				m_downMax;
					_float3				m_rightMax[3];

					_bool				m_moveUp = false;
					_bool				m_moveDown = false;
					_bool				m_moveRight = false;
					_bool				m_moveLeft = false;

					std::vector<SP(Engine::CObject)> m_vControlDesk;
};

#endif