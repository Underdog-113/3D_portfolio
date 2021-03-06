#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class CRenderTarget;
class ENGINE_DLL CGraphicsManager final : public CEngine
{
	DECLARE_SINGLETON(CGraphicsManager)

public:
			void					Awake				(void) override;
			void					Start				(void);

			void					FixedUpdate			(void);
			void					Update				(void);
			void					LateUpdate			(void);	

			void					PreRender			(void);
			void					Render				(void);
			void					PostRender			(void);

			void					OnDestroy			(void);

			void					OnEnable			(void);
			void					OnDisable			(void);

public:
			void					AddToRenderList		(_int renderID, 
														 CObject* spObject);

			void					ClearRenderList		(void);

private:	
			void					InitDeferredBuffer	(void);
			void					InitBlurredBuffer	(void);

			void					RenderBase			(void);

			void					RenderNonAlpha		(void);
			void					RenderAlphaTest		(void);
			void                    RenderEffect		(void);
			void					RenderLights		(void);
			void					RenderDeferBlend	(void);
			void					RenderAlphaBlend	(void);
			void					RenderScreenEffect	(void);
			void					RenderBlur			(void);
			void					RenderBlurToRT		(CRenderTarget* pInputRT, CRenderTarget* pMiddleRT, CRenderTarget* pOutRT, 
														 _float rtSizeX, _float rtSiztY);
			void					RenderEmissive		(void);
			void					RenderFinal			(void);

			void					RenderWire			(void);
			void					RenderUI			(void);
			


private:
	typedef std::vector<CObject*> _RENDER_LIST;
			_RENDER_LIST		m_vRenderList[(_uint)ERenderID::NumOfRenderID];

	typedef LPDIRECT3DVERTEXBUFFER9 _VERTEX_BUFFER;
	typedef LPDIRECT3DINDEXBUFFER9  _INDEX_BUFFER;

	GETTOR_REF		(_VERTEX_BUFFER,		m_pVertexBuffer,		nullptr,		VertexBuffer)
	GETTOR_REF		(_INDEX_BUFFER,			m_pIndexBuffer,			nullptr,		IndexBuffer)

	GETTOR_REF		(_VERTEX_BUFFER,		m_pBlurVertexBuffer,	nullptr,		BlurVertexBuffer)
	GETTOR_REF		(_INDEX_BUFFER,			m_pBlurIndexBuffer,		nullptr,		BlurIndexBuffer)

	GETTOR_SETTOR	(_bool,					m_rtDebugOn,			false,			RtDebugOn)
};
END
#endif