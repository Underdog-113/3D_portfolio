#ifndef CAMERALIGHT_H
#define CAMERALIGHT_H

#include "Light.h"

BEGIN(Engine)
class ENGINE_DLL CCameraLight final : public CLight
{
private:
	explicit								CCameraLight		(void);
										   ~CCameraLight		(void);

public:
	static			CLight*					Create				(D3DLIGHT9* pLightInfo, const _int& index);
					void					Free				(void);

					void					InitLight			(D3DLIGHT9* pLightInfo, const _int& index);
					void					UpdateLight			(void) override;
					void					RenderLight			(LPD3DXEFFECT pEffect);

protected:
	GETTOR			(_float,				m_timer,			0,			Timer)
	GETTOR			(_float,				m_timeLimit,		1.f,		TimeLimit)
};

END
#endif