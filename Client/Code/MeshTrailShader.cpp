#include "stdafx.h"
#include "..\Header\MeshTrailShader.h"
#include "Layer.h"


CMeshTrailShader::CMeshTrailShader()
{
}


CMeshTrailShader::~CMeshTrailShader()
{
}


Engine::CShader * CMeshTrailShader::Create()
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

void CMeshTrailShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{

	_mat worldMat, viewMat, projMat, WVP;

	worldMat = spGC->GetTransform()->GetWorldMatrix();
	viewMat = Engine::GET_MAIN_CAM->GetViewMatrix();
	projMat = Engine::GET_MAIN_CAM->GetProjMatrix();

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

	SP(Engine::CTextureC) spTexture = spGC->GetTexture();

	m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetSetIndex()][0]->pTexture);
	m_pEffect->SetTexture("g_ServeTex", spTexture->GetTexData()[spTexture->GetSetIndex()][1]->pTexture);
	m_pEffect->SetTexture("g_AlphaTex", spTexture->GetTexData()[spTexture->GetSetIndex()][2]->pTexture);

}
