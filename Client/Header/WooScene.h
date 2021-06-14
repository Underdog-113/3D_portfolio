#ifndef WOOSCENE_H
#define WOOSCENE_H

#include "ClientScene.h"
class CWooScene final :public CClientScene
{
private:
	explicit							CWooScene			(void);
									   ~CWooScene			(void);

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

					SP(Engine::CObject) m_spSakura = nullptr;
					_uint m_iIndex = 0;
};

#endif