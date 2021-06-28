#include "EngineStdafx.h"
#include "..\Header\CelShader.h"

USING(Engine)

CCelShader::CCelShader()
{
}


CCelShader::~CCelShader()
{
}

CShader * CCelShader::Create()
{
	CCelShader* pInstance = new CCelShader;
	pInstance->Awake();

	return pInstance;
}

void CCelShader::Free()
{
	__super::Free();
}

void CCelShader::Awake()
{
	__super::Awake();
	m_fTime = 0.f;
	m_fUVSpeed = 0.25f;
}

void CCelShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{

	_mat worldMat, viewMat, projMat, WVP;

	worldMat = spGC->GetTransform()->GetWorldMatrix();
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

	_float4 SurfaceColor = _float4(0, 0, 0, 1);

	m_pEffect->SetVector("gSurfaceColor", &SurfaceColor);


	SP(CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_SubTex", spTexture->GetTexData()[spTexture->GetSetIndex()][1]->pTexture);

	D3DMATERIAL9* pMtrl = &spGC->GetMtrl();
	spGC->GetMesh()->GetFirstMeshData_Dynamic()->GetMeshContainers()[0]->pMaterials;

	size_t _dwMaterials = spGC->GetMesh()->GetMeshData()->GetSubsetCount();

	

	for (size_t i = 0; i < _dwMaterials; ++i)
	{	
		m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetSetIndex()][i]->pTexture);

		
		pMtrl++;
	}

}
