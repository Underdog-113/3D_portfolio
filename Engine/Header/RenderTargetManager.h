#ifndef RENDERTARGETMANAGER_H
#define RENDERTARGETMANAGER_H


#include "Engine.h"
#include "RenderTarget.h"

BEGIN(Engine)
class ENGINE_DLL CRenderTargetManager : public CEngine
{
	DECLARE_SINGLETON(CRenderTargetManager)
	typedef std::unordered_map<std::wstring, CRenderTarget*> _RENDER_TARGETS;
	typedef std::vector<CRenderTarget*> _MULTI_RENDER_TARGET;
	typedef std::unordered_map<std::wstring, _MULTI_RENDER_TARGET> _MULTI_RENDER_TARGETS;
public:
					void					Awake					(void) override;
					void					Start					(void);

					void					OnDestroy				(void);

public:
					void					InitMRT					(const _tchar* mrtKey, const _tchar* targetKey);

					void					BeginMRT				(const _tchar* mrtKey);
					void					EndMRT					(const _tchar* mrtKey);

					void					InitDebugBufferMRT		(const _tchar* targetKey, 
																	 const _float& xPos,  const _float& yPos, 
																	 const _float& xSize, const _float& ySize);

					void					RenderDebugBufferMRT	(const _tchar* mrtKey);

					void					SetRenderTargetTexture	(LPD3DXEFFECT& pEffect, const _tchar* targetKey, const _char* contantTableKey);

public:
					void					AddRenderTarget			(const _tchar* targetKey, 
																	 const _uint& width, const _uint& height,
																	 D3DFORMAT format, D3DXCOLOR color);

private:
					CRenderTarget*			FindRenderTarget		(const _tchar* targetKey);
					_MULTI_RENDER_TARGET*	FindMRT					(const _tchar* mrtKey);

private:
					_RENDER_TARGETS			m_mRenderTarget;;
					_MULTI_RENDER_TARGETS	m_mMRT;

};

END
#endif // RenderTargetMgr_h__
