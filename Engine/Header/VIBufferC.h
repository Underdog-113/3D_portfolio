#ifndef VIBUFFERC_H
#define VIBUFFERC_H

#include "RenderComponent.h"

BEGIN(Engine)
class ENGINE_DLL CVIBufferC abstract : public CRenderComponent
{
public:
	explicit								CVIBufferC			(void);
										   ~CVIBufferC			(void);

public:
	virtual			SP(CComponent)			MakeClone			(CObject* pObject) PURE;
					void					InitVIBufferClone	(SP(CVIBufferC) spClone, CObject* pOwner);

	virtual			void					Awake				(void);
	virtual			void					Start				(SP(CComponent) spThis);

	virtual			void					FixedUpdate			(SP(CComponent) spThis) PURE;
	virtual			void					Update				(SP(CComponent) spThis) PURE;
	virtual			void					LateUpdate			(SP(CComponent) spThis) PURE;

	virtual			void					PreRender			(void);
	virtual			void					Render				(void);
	virtual			void					PostRender			(void);

	virtual			void					OnDestroy			(void);

	virtual			void					OnEnable			(void);
	virtual			void					OnDisable			(void);

protected:
	typedef LPDIRECT3DVERTEXBUFFER9 _VERTEX_BUFFER;
	typedef LPDIRECT3DINDEXBUFFER9  _INDEX_BUFFER;

	GETTOR_REF		(_VERTEX_BUFFER,		m_pVertexBuffer,	nullptr,		VertexBuffer)
	GETTOR_REF		(_INDEX_BUFFER,			m_pIndexBuffer,		nullptr,		Index)

	GETTOR			(_ulong,				m_vtxSize,			UNDEFINED,		VertexSize)
	GETTOR			(_ulong,				m_vtxCount,			UNDEFINED,		VertexCount)
	GETTOR			(_ulong,				m_faceCount,		UNDEFINED,		FaceCount)
	GETTOR			(_ulong,				m_FVF,				UNDEFINED,		FVF)

	GETTOR			(_ulong,				m_indexSize,		UNDEFINED,		IndexSize)
	GETTOR			(D3DFORMAT,				m_indexFormat,		{},				IndexFormat)
};
END

#endif
