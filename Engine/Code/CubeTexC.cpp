#include "EngineStdafx.h"
#include "CubeTexC.h"

USING(Engine)
CCubeTexC::CCubeTexC()
{
}


CCubeTexC::~CCubeTexC()
{
	OnDestroy();
}

SP(CComponent) CCubeTexC::MakeClone(CObject * pObject)
{
	SP(CCubeTexC) spClone(new CCubeTexC);
	__super::InitVIBufferClone(spClone, pObject);
	
	return spClone;
}

void CCubeTexC::Awake(void)
{
	m_componentID = (_int)m_s_componentID;

	m_faceCount		= 12;
	m_vtxCount		= 8;
	m_vtxSize		= sizeof(VERTEX_VT3);
	m_FVF			= FVF_VT3;

	m_indexFormat	= D3DFMT_INDEX32;
	m_indexSize		= sizeof(INDEX32);

	__super::Awake();

	InitVertexBuffer();
	InitIndexBuffer();
}

void CCubeTexC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	
}

void CCubeTexC::FixedUpdate(SP(CComponent) spThis)
{
}

void CCubeTexC::Update(SP(CComponent) spThis)
{
}

void CCubeTexC::LateUpdate(SP(CComponent) spThis)
{
}


void CCubeTexC::PreRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	__super::PreRender();
}

void CCubeTexC::Render(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	__super::Render();
}

void CCubeTexC::PostRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	__super::PostRender();
}

void CCubeTexC::OnDestroy(void)
{
}

void CCubeTexC::OnEnable(void)
{
}

void CCubeTexC::OnDisable(void)
{
}

void CCubeTexC::InitVertexBuffer(void)
{
	
	VERTEX_VT3* pVertices = nullptr;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	
	// ¾Õ¸é
	pVertices[0].position = _float3(-0.5f, 0.5f, -0.5f);
	pVertices[0].texUV = pVertices[0].position;

	pVertices[1].position = _float3(0.5f, 0.5f, -0.5f);
	pVertices[1].texUV = pVertices[1].position;

	pVertices[2].position = _float3(0.5f, -0.5f, -0.5f);
	pVertices[2].texUV = pVertices[2].position;

	pVertices[3].position = _float3(-0.5f, -0.5f, -0.5f);
	pVertices[3].texUV = pVertices[3].position;

	// µÞ¸é
	pVertices[4].position = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[4].texUV = pVertices[4].position;

	pVertices[5].position = _float3(0.5f, 0.5f, 0.5f);
	pVertices[5].texUV = pVertices[5].position;

	pVertices[6].position = _float3(0.5f, -0.5f, 0.5f);
	pVertices[6].texUV = pVertices[6].position;

	pVertices[7].position = _float3(-0.5f, -0.5f, 0.5f);
	pVertices[7].texUV = pVertices[7].position;
	
	m_pVertexBuffer->Unlock();
}

void CCubeTexC::InitIndexBuffer(void)
{
	INDEX32*		pIndices = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	// X+
	pIndices[0]._0 = 1;
	pIndices[0]._1 = 5;
	pIndices[0]._2 = 6;

	pIndices[1]._0 = 1;
	pIndices[1]._1 = 6;
	pIndices[1]._2 = 2;
	// X-
	pIndices[2]._0 = 4;	
	pIndices[2]._1 = 0;	
	pIndices[2]._2 = 3;	

	pIndices[3]._0 = 4;
	pIndices[3]._1 = 3;
	pIndices[3]._2 = 7;

	// y+
	pIndices[4]._0 = 4;	
	pIndices[4]._1 = 5;	
	pIndices[4]._2 = 1;	

	pIndices[5]._0 = 4;
	pIndices[5]._1 = 1;
	pIndices[5]._2 = 0;

	// y-
	pIndices[6]._0 = 3;
	pIndices[6]._1 = 2;
	pIndices[6]._2 = 6;

	pIndices[7]._0 = 3;
	pIndices[7]._1 = 6;
	pIndices[7]._2 = 7;
	// z+
	pIndices[8]._0 = 7;	
	pIndices[8]._1 = 6;	
	pIndices[8]._2 = 5;	

	pIndices[9]._0 = 7;
	pIndices[9]._1 = 5;
	pIndices[9]._2 = 4;

	// z-
	pIndices[10]._0 = 0;	 
	pIndices[10]._1 = 1;	 
	pIndices[10]._2 = 2;	 

	pIndices[11]._0 = 0;
	pIndices[11]._1 = 2;
	pIndices[11]._2 = 3;

	m_pIndexBuffer->Unlock();
}
