#include "EngineStdafx.h"
#include "Light.h"
#include "WndApp.h"


USING(Engine)
CLight::CLight()
{
}


CLight::~CLight()
{
}

CLight * CLight::Create(D3DLIGHT9 * pLightInfo, const _int & index)
{
	CLight* pInstance = new CLight;
	pInstance->InitLight(pLightInfo, index);

	return pInstance;
}

void CLight::Free(void)
{
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();
	delete m_pLightInfo;

	delete this;
}

void CLight::InitLight(D3DLIGHT9 * pLightInfo, const _int & index)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	m_index = index;
	m_pLightInfo = pLightInfo;

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(_VertexScreen) * 4,
										   0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										   FVF_SCR,
										   D3DPOOL_MANAGED,
										   &m_pVertexBuffer,
										   NULL)))
	{
		MSG_BOX(__FILE__, L"Fail creating VertexBuffer in Initlight");
		ABORT;
	}


	if (FAILED(pDevice->CreateIndexBuffer(sizeof(INDEX16) * 2,
										  0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										  D3DFMT_INDEX16,
										  D3DPOOL_MANAGED,
										  &m_pIndexBuffer,
										  NULL)))
	{
		MSG_BOX(__FILE__, L"Fail creating IndexBuffer in Initlight");
		ABORT;
	}

	D3DVIEWPORT9 viewport;
	pDevice->GetViewport(&viewport);

	_VertexScreen* pVertices = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].position	= _float4(0.f, 0.f, 0.f, 1.f);
	pVertices[0].texUV		= _float2(0.f, 0.f);

	pVertices[1].position	= _float4((_float)viewport.Width, 0.f, 0.f, 1.f);
	pVertices[1].texUV		= _float2(1.f, 0.f);

	pVertices[2].position	= _float4((_float)viewport.Width, (_float)viewport.Height, 0.f, 1.f);
	pVertices[2].texUV		= _float2(1.f, 1.f);

	pVertices[3].position	= _float4(0.f, (_float)viewport.Height, 0.f, 1.f);
	pVertices[3].texUV		= _float2(0.f, 1.f);

	m_pVertexBuffer->Unlock();

	INDEX16* pIndices = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._0 = 0;
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 2;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 2;
	pIndices[1]._2 = 3;

	m_pIndexBuffer->Unlock();

	GenerateOrthoMatrix();
}

void CLight::UpdateLight(void)
{
}

void CLight::RenderLight(LPD3DXEFFECT pEffect)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	_uint iPass = 0;

	if (D3DLIGHT_DIRECTIONAL == m_pLightInfo->Type)
	{
		pEffect->SetVector("g_vLightDir", &_float4(m_pLightInfo->Direction, 0.f));
		iPass = 0;
	}

	else if (D3DLIGHT_POINT == m_pLightInfo->Type)
	{
		pEffect->SetVector("g_vLightPos", &_float4(m_pLightInfo->Position, 1.f));
		pEffect->SetFloat("g_fRange", m_pLightInfo->Range);
		iPass = 1;
	}

	pEffect->SetVector("g_vLightDiffuse", (_float4*)&m_pLightInfo->Diffuse);
	pEffect->SetVector("g_vLightAmbient", (_float4*)&m_pLightInfo->Ambient);

	_mat viewMat, projMat;
	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();
	D3DXMatrixInverse(&viewMat, NULL, &viewMat);
	D3DXMatrixInverse(&projMat, NULL, &projMat);

	pEffect->SetMatrix("g_matInvProj", &projMat);
	pEffect->SetMatrix("g_matInvView", &viewMat);

	pEffect->SetVector("g_vCamPos", (_float4*)&viewMat._41);

	pEffect->SetFloat("g_fPower", 20.f);


	pEffect->CommitChanges();

	pEffect->BeginPass(iPass);

	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(_VertexScreen));
	pDevice->SetFVF(FVF_SCR);
	pDevice->SetIndices(m_pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	pEffect->EndPass();
}

void CLight::GenerateOrthoMatrix(void)
{
	m_orthoMat;
	D3DXMatrixOrthoLH(&m_orthoMat, (_float)GET_WND_WIDTH, (_float)GET_WND_HEIGHT, 0.1f, 1000.f);
}
