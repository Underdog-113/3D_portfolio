#ifndef YONGSCENE_H
#define YONGSCENE_H

BEGIN(Engine)
class CParticle;
END
class CTestParticle;

#include "Scene.h"

class CYongScene final : public Engine::CScene
{
private:
	explicit							CYongScene			(void);
									   ~CYongScene			(void);

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

private:
	Engine::CParticle* m_pTestParticle = nullptr;

};

#endif