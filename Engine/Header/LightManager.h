#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "Light.h"
#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CLightManager : public CEngine
{
	DECLARE_SINGLETON(CLightManager)

public:
				void		Awake			(void) override;
				void		Start			(void);
				void		OnDestroy		(void);
				
public:
				void		AddLight		(const D3DLIGHT9* pLightInfo);
				void		RenderLights	(LPD3DXEFFECT& pEffect);

private:
	std::vector<CLight*> m_vLights;
};
END

#endif