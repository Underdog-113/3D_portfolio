#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CRenderTarget final : public CEngine
{
private:
	explicit							CRenderTarget			(void);
									   ~CRenderTarget			(void);


public:
	static			CRenderTarget*		Create					(_uint const& width, _uint const& height,
																 D3DFORMAT format, D3DXCOLOR color);
					void				Free					(void);


					void				Awake					(void);
					void				Start					(void);

public:
	

					void				SetUpOnDevice			(const _uint& index);
					void				ReleaseOnDevice			(const _uint& index);
					void				ClearRenderTarget		(void);
					void				SetRenderTargetTexture	(LPD3DXEFFECT& pEffect, std::string constantTableName);

					void				ReadyDebugBuffer		(const _float& xPos, const _float& yPos, 
																 const _float& xSize, const _float& ySize);
					void				RenderDebugBuffer		(void);

private:
	typedef LPDIRECT3DVERTEXBUFFER9	_VERTEX_BUFFER;
	typedef LPDIRECT3DINDEXBUFFER9	_INDEX_BUFFER;
	typedef LPDIRECT3DTEXTURE9		_TEXTURE;
	typedef LPDIRECT3DSURFACE9		_SURFACE;

	GETTOR			(_VERTEX_BUFFER,		m_pVertexBuffer,		nullptr,		VertexBuffer)
	GETTOR			(_INDEX_BUFFER,			m_pIndexBuffer,			nullptr,		IndexBuffer)

	GETTOR			(_TEXTURE,				m_pTargetTexture,		nullptr,		TargetTexture)
	GETTOR			(_SURFACE,				m_pCurSurface,			nullptr,		CurSurface)
	GETTOR			(_SURFACE,				m_pOldSurface,			nullptr,		OldSurface)

	GETTOR_SETTOR	(_uint,					m_width,				0,				Width)
	GETTOR_SETTOR	(_uint,					m_height,				0,				Height)
	GETTOR_SETTOR	(D3DFORMAT,				m_format,				{},				Format)
	GETTOR_SETTOR	(D3DXCOLOR,				m_clearColor,			{},				CColor)
};

END
#endif // RenderTarget_h__
