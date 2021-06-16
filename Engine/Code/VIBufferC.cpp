#include "EngineStdafx.h"
#include "VIBufferC.h"


USING(Engine)
CVIBufferC::CVIBufferC()
{
}


CVIBufferC::~CVIBufferC()
{
}

void CVIBufferC::InitVIBufferClone(SP(CVIBufferC) spClone, CObject * pOwner)
{
	__super::InitClone(spClone, pOwner);

	spClone->m_pVertexBuffer	= m_pVertexBuffer;
	spClone->m_pIndexBuffer		= m_pIndexBuffer;

	spClone->m_vtxSize			= m_vtxSize;
	spClone->m_vtxCount			= m_vtxCount;
	spClone->m_faceCount		= m_faceCount;
	spClone->m_FVF				= m_FVF;

	spClone->m_indexSize		= m_indexSize;
	spClone->m_indexFormat		= m_indexFormat;
}

void CVIBufferC::Awake(void)
{
	__super::Awake();
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	if(FAILED(pDevice->CreateVertexBuffer(m_vtxSize * m_vtxCount, 
										  0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										  NULL, 
										  D3DPOOL_MANAGED, 
										  &m_pVertexBuffer, 
										  NULL)))
	{
		MSG_BOX(__FILE__, L"Failed Creating VertexBuffer in CVIBufferC::Awake()");
		ABORT;
	}

	if(FAILED(pDevice->CreateIndexBuffer(m_indexSize * m_faceCount, 
										 0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										 m_indexFormat, 
										 D3DPOOL_MANAGED, 
										 &m_pIndexBuffer, 
										 NULL)))
	{
		MSG_BOX(__FILE__, L"Failed Creating IndexBuffer in CVIBufferC::Awake()");
		ABORT;
	}

}

void CVIBufferC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	
}

void CVIBufferC::PreRender(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, m_vtxSize);
	pDevice->SetFVF(m_FVF);
	pDevice->SetIndices(m_pIndexBuffer);
}

void CVIBufferC::Render(void)
{
	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vtxCount, 0, m_faceCount);
}

void CVIBufferC::PostRender(void)
{
}

void CVIBufferC::OnDestroy(void)
{
}

void CVIBufferC::OnEnable(void)
{
	__super::OnEnable();
	
}

void CVIBufferC::OnDisable(void)
{
	__super::OnDisable();
	
}