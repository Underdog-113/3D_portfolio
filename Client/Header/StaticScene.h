#ifndef STATICSCENE_H
#define STATICSCENE_H

#include "ClientScene.h"
class CStaticScene final : public CClientScene
{
private:
	explicit							CStaticScene			(void);
									   ~CStaticScene			(void);

public:
	static			CClientScene*		Create					(void);
					void				Free					(void) override;

					void				Awake					(_int numOfLayers) override;
					void				Start					(void) override;
																   
					void				FixedUpdate				(void) override;
					void				Update					(void) override;
					void				LateUpdate				(void) override;	
					
					void				OnDestroy				(void) override;

					void				OnEnable				(void) override;	 
					void				OnDisable				(void) override;
					
public:
					void				InitSettings			(void);
					void				InitPrototypes			(void) override;
private:
					void				InitUiPrototypes		(void);
					void				InitMonsterPrototypes	(void);
					void				InitValkyriePrototypes	(void);
	GETTOR			(CLoading*,			m_pLoading,				nullptr,		Loading)
};

#endif