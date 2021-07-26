#include "stdafx.h"
#include "..\Header\Stage3GlowShader.h"


CStage3GlowShader::CStage3GlowShader()
{
}


CStage3GlowShader::~CStage3GlowShader()
{
}

Engine::CShader * CStage3GlowShader::Create(void)
{
	CStage3GlowShader* pInstance = new CStage3GlowShader;
	pInstance->Awake();

	return pInstance;
}

void CStage3GlowShader::Free(void)
{
	__super::Free();

}

void CStage3GlowShader::Awake(void)
{
	__super::Awake();
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
	m_vRenderTargets[3] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CStage3GlowShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);

	if (spGC->GetColorReverse())
	{
		m_addColor = _float4(0.5f, 0.f, 0.f, 0.f);
	}
	m_pEffect->SetVector("g_color", &spGC->GetTexture()->GetColor());
	m_pEffect->SetVector("g_addColor", &m_addColor);
	m_pEffect->SetVector("g_multColor", &m_multColor);

	m_pEffect->SetFloat("g_glowCoef", spGC->GetGlowCoef());
}
