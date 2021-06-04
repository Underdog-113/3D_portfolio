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

void CRectTexC::PreRender(SP(CGraphicsC) spGC)
{
	__super::PreRender();
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	SP(CTextureC) spTexture = spGC->GetTexture();

	_mat identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	pDevice->SetTransform(D3DTS_WORLD, &spGC->GetOwner()->GetTransform()->GetWorldMatrix());

	if (m_isOrtho)
	{
		pDevice->SetTransform(D3DTS_VIEW, &identityMatrix);
		pDevice->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetOrthoMatrix());
	}
	else
	{
		pDevice->SetTransform(D3DTS_VIEW, &GET_MAIN_CAM->GetViewMatrix());
		pDevice->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetProjMatrix());
	}

	pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, spGC->GetTexture()->GetColor());
	pDevice->
		SetTexture(0, spTexture->GetTexData()[spTexture->GetMeshIndex()][spTexture->GetTexIndex()]->pTexture);
}

void CRectTexC::Render(SP(CGraphicsC) spGC)
{
	__super::Render();
	GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void CRectTexC::PostRender(SP(CGraphicsC) spGC)
{
	__super::PostRender();
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetProjMatrix());
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
