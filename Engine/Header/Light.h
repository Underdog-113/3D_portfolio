#ifndef LIGHT_H
#define LIGHT_H

BEGIN(Engine)
class ENGINE_DLL CLight final
{
private:
	explicit								CLight				(void);
										   ~CLight				(void);

public:
	static			CLight*					Create				(const D3DLIGHT9* pLightInfo, const _int& index);
					void					Free				(void);

					void					InitLight			(const D3DLIGHT9* pLightInfo, const _int& index);
					void					RenderLight			(LPD3DXEFFECT& pEffect);
	
private:
	typedef LPDIRECT3DVERTEXBUFFER9 _VERTEX_BUFFER;
	typedef LPDIRECT3DINDEXBUFFER9  _INDEX_BUFFER;

	GETTOR_REF		(_VERTEX_BUFFER,		m_pVertexBuffer,	nullptr,		VertexBuffer)
	GETTOR_REF		(_INDEX_BUFFER,			m_pIndexBuffer,		nullptr,		IndexBuffer)
	GETTOR			(D3DLIGHT9,				m_lightInfo,		{},				LightInfo)
	GETTOR			(_int,					m_index,			UNDEFINED,		Index)

};

END
#endif