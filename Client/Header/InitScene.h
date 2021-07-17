#ifndef INITSCENE_H
#define INITSCENE_H

#include "ClientScene.h"
class CLoading;
class CInitScene final : public CClientScene
{
private:
	explicit								CInitScene				(void);
										   ~CInitScene				(void);

public:
	static			CClientScene*			Create					(void);
					void					Free					(void) override;

					void					Awake					(_int numOfLayers) override;
					void					Start					(void) override;
																	   
					void					FixedUpdate				(void) override;
					void					Update					(void) override;
					void					LateUpdate				(void) override;	
					
					void					OnDestroy				(void) override;

					void					OnEnable				(void) override;	 
					void					OnDisable				(void) override;
					
public:
					void					InitPrototypes			(void) override;

	GETTOR			(CLoading*,				m_pLoading,				nullptr,		Loading)
	GETTOR			(_bool,					m_selectNextScene,		false,			SelectNextScene)
	GETTOR			(SP(Engine::CObject),	m_pBackground,			nullptr,		Background)

	_float m_fTempSoundLength = 0.f;
	_bool m_isStaticScene = false;
	_bool m_init = false;

private:
	SP(Engine::CObject) m_spElevatorBase;
};

#endif