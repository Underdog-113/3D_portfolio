#include "EngineStdafx.h"
#include "..\Header\MeshTrailShader.h"
#include "Layer.h"

USING(Engine)

CMeshTrailShader::CMeshTrailShader()
{
}


CMeshTrailShader::~CMeshTrailShader()
{
}


CShader * CMeshTrailShader::Create()
{
	CMeshTrailShader* pInstance = new CMeshTrailShader;
	pInstance->Awake();

	return pInstance;
}

void CMeshTrailShader::Free()
{
	__super::Free();
}

void CMeshTrailShader::Awake()
{
	__super::Awake();
}

void CMeshTrailShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{

	_mat worldMat, viewMat, projMat, WVP;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("gWorld", &worldMat);
	m_pEffect->SetMatrix("gView", &viewMat);
	m_pEffect->SetMatrix("gProjection", &projMat);

	WVP = worldMat * viewMat * projMat;

	m_pEffect->SetMatrix("gWorldViewProjectionMatrix", &WVP);

	// Get Inverse Transpose of World Matrix
	_mat iTWM;
	D3DXMatrixInverse(&iTWM, 0, &worldMat);
	D3DXMatrixTranspose(&iTWM, &iTWM);

	m_pEffect->SetMatrix("gInvWorldMatrix", &worldMat);

	_float4 worldLightPos = _float4(500.f, 500.f, -500.f, 1.f);

	m_pEffect->SetVector("gWorldLightPosition", &worldLightPos);

	SP(CTextureC) spTexture = spGC->GetTexture();

	D3DMATERIAL9* pMtrl = &spGC->m_mtrl;

	m_pEffect->SetTexture("g_NoiseTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);
	m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][0]->pTexture);


}