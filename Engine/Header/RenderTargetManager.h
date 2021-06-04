#ifndef RENDERTARGETMANAGER_H
#define RENDERTARGETMANAGER_H


//#include "Engine.h"
//#include "RenderTarget.h"
//
//BEGIN(Engine)
//class ENGINE_DLL CRenderTargetManager : public CEngine
//{
//	DECLARE_SINGLETON(CRenderTargetManager)
//
//public:
//					void				Awake			(void) override;
//					void				Start			(void);
//
//					
//
//	HRESULT		Ready_RenderTarget(LPDIRECT3DDEVICE9 pGraphicDev,
//									const _tchar* pTargetTag,
//									const _uint& iWidth, 
//									const _uint& iHeight,
//									D3DFORMAT Format, 
//									D3DXCOLOR Color);
//
//	HRESULT		Ready_MRT(const _tchar* pMRTTag, const _tchar* pTargetTag);
//
//	HRESULT		Begin_MRT(const _tchar* pMRTTag);
//	HRESULT		End_MRT(const _tchar* pMRTTag);
//
//	HRESULT		Ready_DebugBuffer(const _tchar* pTargetTag, const _float& fX, const _float& fY, const _float& fSizeX, const _float& fSizeY);
//	void		Render_DebugBuffer(const _tchar* pMRTTag);
//
//	void		Get_RenderTargeTexture(LPD3DXEFFECT& pEffect, const _tchar* pTargetTag, const char* pConstantTable);
//
//private:
//	CRenderTarget*			Find_RenderTarget(const _tchar* pTargetTag);
//	list<CRenderTarget*>*	Find_MRT(const _tchar* pMRTTag);
//
//private:
//	typedef std::unordered_map<std::wstring, CRenderTarget*> _RENDER_TARGETS;
//	typedef std::unordered_map<std::wstring, std::vector<CRenderTarget*>> _MULTI_RENDER_TARGETS;
//
//
//	_RENDER_TARGETS			m_mRenderTarget;;
//	_MULTI_RENDER_TARGETS	m_mMRT;
//
//	
//
//public:
//	virtual void	Free(void);
//};
//
//END
#endif // RenderTargetMgr_h__
