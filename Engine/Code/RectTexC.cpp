#include "EngineStdafx.h"
#include "RectTexC.h"


USING(Engine)
CRectTexC::CRectTexC()
{
}


CRectTexC::~CRectTexC()
{
	OnDestroy();
}

SP(CComponent) CRectTexC::MakeClone(CObject * pObject)
{
	SP(CRectTexC) spClone(new CRectTexC);
	__super::InitVIBufferClone(spClone, pObject);
	spClone->m_isOrtho = m_isOrtho;

	return spClone;
}

void CRectTexC::Awake(void)
{
	m_componentID = (_int)m_s_componentID;

	m_faceCount		= 2;
	m_vtxCount		= 4;
	m_vtxSize		= sizeof(VERTEX_VNT);
	m_FVF			= FVF_VNT;

	m_indexFormat	= D3DFMT_INDEX32;
	m_indexSize		= sizeof(INDEX32);

	__super::Awake();

	InitVertexBuffer();
	InitIndexBuffer();
}

void CRectTexC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	
}

void CRectTexC::FixedUpdate(SP(CComponent) spThis)
{
}

void CRectTexC::Update(SP(CComponent) spThis)
{
}

void CRectTexC::LateUpdate(SP(CComponent) spThis)
{
}

void CRectTexC::PreRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	__super::PreRender();

}

void CRectTexC::Render(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	__super::Render();
}

void CRectTexC::PostRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	__super::PostRender();
}

void CRectTexC::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CRectTexC::OnEnable(void)
{
	__super::OnEnable();
	
}

void CRectTexC::OnDisable(void)
{
	__super::OnDisable();
	
}

void CRectTexC::InitVertexBuffer(void)
{
	VERTEX_VNT* vertices = nullptr;

	m_pVertexBuffer->Lock( 0, 0, (void**)& vertices, 0 );

	//Set the position
	vertices[0].position = D3DXVECTOR3(-0.5, 0.5, 0);
	vertices[1].position = D3DXVECTOR3(0.5, 0.5, 0);
	vertices[2].position = D3DXVECTOR3(0.5, -0.5, 0);
	vertices[3].position = D3DXVECTOR3(-0.5, -0.5, 0);

	//Set the texture information
	vertices[0].texUV = D3DXVECTOR2(0.0f, 0.0f);
	vertices[1].texUV = D3DXVECTOR2(1.0f, 0.0f);
	vertices[2].texUV = D3DXVECTOR2(1.0f, 1.0f);
	vertices[3].texUV = D3DXVECTOR2(0.0f, 1.0f);

	m_pVertexBuffer->Unlock();
}

void CRectTexC::InitIndexBuffer(void)
{
	INDEX32* index = nullptr;

	m_pIndexBuffer->Lock( 0, 0, (void**)&index, 0 );

    //Match the vertex buffer and texture info
	index[0]._0 = 0;
	index[0]._1 = 1;
	index[0]._2 = 2;

	index[1]._0 = 0;
	index[1]._1 = 2;
	index[1]._2 = 3;

	m_pIndexBuffer->Unlock();
}
