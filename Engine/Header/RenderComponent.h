#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"

BEGIN(Engine)
class CObject;
class CGraphicsC;
class ENGINE_DLL CRenderComponent abstract : public CComponent
{
public:
	explicit					CRenderComponent		(void);
	virtual					   ~CRenderComponent		(void);

public:
	virtual		SP(CComponent)	MakeClone				(CObject* pObject) PURE;

	virtual		void			Awake					(void);
	virtual		void			Start					(SP(CComponent) spThis);
																			    
	virtual		void			FixedUpdate				(SP(CComponent) spThis) PURE;
	virtual		void			Update					(SP(CComponent) spThis) PURE;
	virtual		void			LateUpdate				(SP(CComponent) spThis) PURE;

	virtual		void			PreRender				(void) {}
	virtual		void			PreRender				(SP(CGraphicsC) spGC) {}
	virtual		void			PreRender				(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) {}

	virtual		void			Render					(void) {}
	virtual		void			Render					(SP(CGraphicsC) spGC) {}
	virtual		void			Render					(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) {}

	virtual		void			PostRender				(void) {}
	virtual		void			PostRender				(SP(CGraphicsC) spGC) {}
	virtual		void			PostRender				(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) {}

	virtual		void			OnDestroy				(void) PURE;
															   
	virtual		void			OnEnable				(void);
	virtual		void			OnDisable				(void);
};
END

#endif // !COMPONENT_H

