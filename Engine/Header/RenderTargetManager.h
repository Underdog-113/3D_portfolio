#ifndef RENDERTARGETMANAGER_H
#define RENDERTARGETMANAGER_H


#include "Engine.h"
#include "RenderTarget.h"

BEGIN(Engine)
class ENGINE_DLL CRenderTargetManager : public CEngine
{
	DECLARE_SINGLETON(CRenderTargetManager)
	
public:
					void						Awake					(void) override;
					void						Start					(void);

					void						OnDestroy				(void);

public:
					void						RenderDebugBuffer		(void);

					void						SetRenderTargetTexture	(LPD3DXEFFECT& pEffect, const _tchar* targetKey, const _char* contantTableKey);

public:
					CRenderTarget*				AddRenderTarget			(const _tchar* targetKey, 
																		 const _uint& width, const _uint& height,
																		 D3DFORMAT format, D3DXCOLOR color);
					CRenderTarget*				FindRenderTarget		(const _tchar* targetKey);

					void						ClearRenderTargets		(void);
					void						ReleaseCurRenderTargets	(void);
					void						SetUpRenderTarget		(const _uint& index, CRenderTarget* pRenderTarget);
					
private:
	typedef std::unordered_map<std::wstring, CRenderTarget*>			_RENDER_TARGETS;
	typedef std::vector<CRenderTarget*>									_CUR_RENDER_TARGETS;
	GETTOR			(_RENDER_TARGETS,			m_mRenderTarget,		{},			RenderTargets)
	GETTOR			(_CUR_RENDER_TARGETS,		m_vCurRenderTargets,	{},			CurRenderTargets)
};

END
#endif // RenderTargetMgr_h__
