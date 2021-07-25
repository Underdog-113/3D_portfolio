#include "stdafx.h"
#include "..\Header\AlphaMaskGlowShader.h"


CAlphaMaskGlowShader::CAlphaMaskGlowShader()
{
}


CAlphaMaskGlowShader::~CAlphaMaskGlowShader()
{
}

Engine::CShader * CAlphaMaskGlowShader::Create()
{
	CAlphaMaskGlowShader* pInstance = new CAlphaMaskGlowShader;
	pInstance->Awake();

	return pInstance;
}

void CAlphaMaskGlowShader::Free()
{
	__super::Free();

}

void CAlphaMaskGlowShader::Awake()
{
	__super::Awake();

	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CAlphaMaskGlowShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	// Add Alpha variables to objects that use this shader.
	// Need to pEffect->SetFloat("gAlpha", Alpha variable) on render part.
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

	SP(Engine::CTextureC) spTexture = spGC->GetTexture();

	m_pEffect->SetTexture("g_DiffuseTex", spTexture->GetTexData()[spTexture->GetSetIndex()][0]->pTexture);
	m_pEffect->SetTexture("g_ServeTex", spTexture->GetTexData()[spTexture->GetSetIndex()][1]->pTexture);
}
