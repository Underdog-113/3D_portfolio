#ifndef RENDERTARGETMANAGER_H
#define RENDERTARGETMANAGER_H


#include "Engine.h"
#include "RenderTarget.h"

BEGIN(Engine)
class ENGINE_DLL CRenderTargetManager : public CEngine
{
	DECLARE_SINGLETON(CRenderTargetManager)

public:
					void				Awake			(void) override;
					void				Start			(void);

					void				OnDestroy		(void);

public:
					void				InitMRT			(std::wstring mrtKey, std::wstring targetKey);
					void				EndMRT			(std::wstring mrtKey);

					void				InitDebugBufferMRT		(std::wstring targetKey, 
																 _float& xPos, _float& yPos, 
																 _float& xSize, _float& ySize);

					void				RenderDebugBufferMRT	(std::wstring mrtKey);

					void				SetRenderTargetTexture	(LPD3DXEFFECT& pEffect, std::wstring targetKey, std::string contantTableKey);

	HRESULT		Ready_RenderTarget(LPDIRECT3DDEVICE9 pGraphicDev,
									const _tchar* pTargetTag,
									const _uint& iWidth, 
									const _uint& iHeight,
									D3DFORMAT Format, 
									D3DXCOLOR Color);

	HRESULT		InitMRT(const _tchar* pMRTTag, const _tchar* pTargetTag);

	HRESULT		BeginMRT(const _tchar* pMRTTag);
	HRESULT		EndMRT(const _tchar* pMRTTag);

	HRESULT		InitDebugBufferMRT(const _tchar* pTargetTag, const _float& fX, const _float& fY, const _float& fSizeX, const _float& fSizeY);
	void		RenderDebugBufferMRT(const _tchar* pMRTTag);

	void		SetRenderTargetTexture(LPD3DXEFFECT& pEffect, const _tchar* pTargetTag, const char* pConstantTable);

private:
	CRenderTarget*			FindRenderTarget(const _tchar* pTargetTag);
	std::vector<CRenderTarget*>*	FindMRT(const _tchar* pMRTTag);

private:
	typedef std::unordered_map<std::wstring, CRenderTarget*> _RENDER_TARGETS;
	typedef std::unordered_map<std::wstring, std::vector<CRenderTarget*>> _MULTI_RENDER_TARGETS;


	_RENDER_TARGETS			m_mRenderTarget;;
	_MULTI_RENDER_TARGETS	m_mMRT;

	

public:
	virtual void	Free(void);
};

END
#endif // RenderTargetMgr_h__
