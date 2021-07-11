#ifndef LIGHT_H
#define LIGHT_H

BEGIN(Engine)
class ENGINE_DLL CLight
{
protected:
	explicit								CLight				(void);
										   ~CLight				(void);

public:
	static			CLight*					Create				(D3DLIGHT9* pLightInfo, const _int& index);
					void					Free				(void);

	virtual			void					InitLight			(D3DLIGHT9* pLightInfo, const _int& index);
	virtual			void					UpdateLight			(void);
	virtual			void					RenderLight			(LPD3DXEFFECT pEffect);
	
protected:
	typedef LPDIRECT3DVERTEXBUFFER9 _VERTEX_BUFFER;
	typedef LPDIRECT3DINDEXBUFFER9  _INDEX_BUFFER;

	GETTOR_REF		(_VERTEX_BUFFER,		m_pVertexBuffer,	nullptr,		VertexBuffer)
	GETTOR_REF		(_INDEX_BUFFER,			m_pIndexBuffer,		nullptr,		IndexBuffer)
	GETTOR			(D3DLIGHT9*,			m_pLightInfo,		{},				LightInfo)
	GETTOR			(_int,					m_index,			UNDEFINED,		Index)

};

END
#endif