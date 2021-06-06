#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "Light.h"
#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CLightManager : public CEngine
{
private:
	explicit						CLightManager	(void);
	virtual						   ~CLightManager	(void);
public:
	static		CLightManager*		Create			(void);
				void				Free			(void);

				void				Awake			(void) override;
				void				Start			(void);
				void				OnDestroy		(void);
				
public:
				void				AddLight		(D3DLIGHT9* pLightInfo);
				void				RenderLights	(LPD3DXEFFECT pEffect);

				void				ClearLights		(void);
private:
	std::vector<CLight*> m_vLights;
};
END

#endif