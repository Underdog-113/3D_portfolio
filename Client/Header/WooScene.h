#ifndef WOOSCENE_H
#define WOOSCENE_H

#include "Scene.h"
class CWooScene final : public Engine::CScene
{
private:
	explicit							CWooScene			(void);
									   ~CWooScene			(void);

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
};

#endif