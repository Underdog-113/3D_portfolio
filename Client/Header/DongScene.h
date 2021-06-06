#ifndef DONGSCENE_H
#define DONGSCENE_H

#include "Scene.h"
class CDongScene final : public Engine::CScene
{
private:
	explicit							CDongScene			(void);
									   ~CDongScene			(void);

public:
	static			Engine::CScene*		Create				(void);
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
					void				ObjectActivation	(void);
					_int a = 10;
};

#endif