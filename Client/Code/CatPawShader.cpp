#include "stdafx.h"
#include "..\Header\CatPawShader.h"

CCatPawShader::CCatPawShader()
{
}


CCatPawShader::~CCatPawShader()
{
}

Engine::CShader * CCatPawShader::Create()
{
	CCatPawShader* pInstance = new CCatPawShader;
	pInstance->Awake();

	return pInstance;
}

void CCatPawShader::Free()
{
	__super::Free();
}

void CCatPawShader::Awake()
{
	__super::Awake();
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Emissive");

	m_fTime = 0.f;
	m_fUVSpeed = 0.25f;
}

void CCatPawShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
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

	_float4 SurfaceColor = _float4(0, 0, 0, 1);

	m_pEffect->SetVector("gSurfaceColor", &SurfaceColor);


	SP(Engine::CTextureC) spTexture = spGC->GetTexture();
	/*m_pEffect->SetTexture("g_SubTex", spTexture->GetTexData()[spTexture->GetSetIndex()][1]->pTexture);*/

	size_t _dwMaterials = spGC->GetMesh()->GetMeshData()->GetSubsetCount();
	

	for (size_t i = 0; i < _dwMaterials; ++i)
	{	
		m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetSetIndex()][i]->pTexture);		
	}


}
