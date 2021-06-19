#ifndef RECTTEXC_H
#define RECTTEXC_H

#include "VIBufferC.h"

BEGIN(Engine)
class ENGINE_DLL CRectTexC final : public CVIBufferC
{
public:
	explicit								CRectTexC			(void);
										   ~CRectTexC			(void);

public:
					SP(CComponent)			MakeClone			(CObject* pObject) override;
					void					Awake				(void) override;
					void					Start				(SP(CComponent) spThis) override;

					void					FixedUpdate			(SP(CComponent) spThis) override;
					void					Update				(SP(CComponent) spThis) override;
					void					LateUpdate			(SP(CComponent) spThis) override;

					void					PreRender			(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;
					void					Render				(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;
					void					PostRender			(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

					void					OnDestroy			(void) override;

					void					OnEnable			(void) override;
					void					OnDisable			(void) override;

private:
					void					InitVertexBuffer	(void);
					void					InitIndexBuffer		(void);
public:
	static const	EComponentID			m_s_componentID = EComponentID::RectTex;
private:
	GETTOR_SETTOR	(_bool,					m_isOrtho,			false,			IsOrtho)
};
END

#endif
