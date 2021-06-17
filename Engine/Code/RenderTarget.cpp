#include "EngineStdafx.h"
#include "RenderTarget.h"

USING(Engine)

CRenderTarget::CRenderTarget(void)
{
}

CRenderTarget::~CRenderTarget(void)
{
}

CRenderTarget * CRenderTarget::Create(_uint const & width, _uint const & height, D3DFORMAT format, D3DXCOLOR color)
{
	CRenderTarget* pInstance = new CRenderTarget;
	pInstance->m_width		= width;
	pInstance->m_height		= height;
	pInstance->m_format		= format;
	pInstance->m_clearColor = color;
	
	pInstance->Awake();

	return pInstance;
}

void CRenderTarget::Free(void)
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
	SafeRelease(m_pOldSurface);
	SafeRelease(m_pCurSurface);

	delete this;
}

void CRenderTarget::Awake(void)
{
	if (FAILED(D3DXCreateTexture(GET_DEVICE, 
								 m_width, m_height,
								 1, 
								 D3DUSAGE_RENDERTARGET, 
								 m_format, 
								 D3DPOOL_DEFAULT, 
								 &m_pTargetTexture)))
	{
		MSG_BOX(__FILE__, L"Failed Creating TargetTexture in CRenderTarget::Awake()");
		ABORT;
	}

	m_pTargetTexture->GetSurfaceLevel(0, &m_pCurSurface);
	SafeRelease(m_pTargetTexture);
}

void CRenderTarget::Start(void)
{
}

void CRenderTarget::SetUpOnDevice(const _uint & index)
{
	GET_DEVICE->GetRenderTarget(index, &m_pOldSurface);
	GET_DEVICE->SetRenderTarget(index, m_pCurSurface);
}

void CRenderTarget::ReleaseOnDevice(const _uint & index)
{
	GET_DEVICE->SetRenderTarget(index, m_pOldSurface);
	SafeRelease(m_pOldSurface);
}

void CRenderTarget::ClearRenderTarget(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->GetRenderTarget(0, &m_pOldSurface);
	pDevice->SetRenderTarget(0, m_pCurSurface);
	
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_clearColor, 0.f, 1);

	pDevice->SetRenderTarget(0, m_pOldSurface);
	SafeRelease(m_pOldSurface);	
}

void CRenderTarget::SetRenderTargetTexture(LPD3DXEFFECT & pEffect, std::string constantTableName)
{
	pEffect->SetTexture(constantTableName.c_str(), m_pTargetTexture);
}

void CRenderTarget::ReadyDebugBuffer(const _float & xPos, const _float & yPos, const _float & xSize, const _float & ySize)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(_VertexScreen) * 4,
										   0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										   FVF_SCR,
										   D3DPOOL_MANAGED,
										   &m_pVertexBuffer,
										   NULL)))
	{
		MSG_BOX(__FILE__, L"Failed Creating VertexBuffer in CRenderTarget::ReadyDebugBuffer");
		ABORT;
	}


	if (FAILED(pDevice->CreateIndexBuffer(sizeof(INDEX16) * 2,
										  0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										  D3DFMT_INDEX16,
										  D3DPOOL_MANAGED,
										  &m_pIndexBuffer,
										  NULL)))
	{
		MSG_BOX(__FILE__, L"Failed Creating IndexBuffer in CRenderTarget::ReadyDebugBuffer");
		ABORT;
	}

	_VertexScreen*		pVertices = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].position = _float4(xPos - 0.5f, yPos - 0.5f, 0.f, 1.f);
	pVertices[0].texUV = _float2(0.f, 0.f);

	pVertices[1].position = _float4(xPos + xSize - 0.5f, yPos - 0.5f, 0.f, 1.f);
	pVertices[1].texUV = _float2(1.f, 0.f);

	pVertices[2].position = _float4(xPos + xSize - 0.5f, yPos + ySize - 0.5f, 0.f, 1.f);
	pVertices[2].texUV = _float2(1.f, 1.f);

	pVertices[3].position = _float4(xPos - 0.5f, yPos + ySize - 0.5f, 0.f, 1.f);
	pVertices[3].texUV = _float2(0.f, 1.f);

	m_pVertexBuffer->Unlock();

	INDEX16*		pIndices = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._0 = 0;
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 2;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 2;
	pIndices[1]._2 = 3;

	m_pIndexBuffer->Unlock();
}

void CRenderTarget::RenderDebugBuffer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetTexture(0, m_pTargetTexture);

	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(_VertexScreen));
	pDevice->SetFVF(FVF_SCR);
	pDevice->SetIndices(m_pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
