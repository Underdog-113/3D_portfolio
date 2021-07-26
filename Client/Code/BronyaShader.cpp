#include "stdafx.h"
#include "..\Header\BronyaShader.h"


CBronyaShader::CBronyaShader()
{
}


CBronyaShader::~CBronyaShader()
{
}

Engine::CShader * CBronyaShader::Create(void)
{
	CBronyaShader* pInstance = new CBronyaShader;
	pInstance->Awake();

	return pInstance;
}

void CBronyaShader::Free(void)
{
	__super::Free();

}

void CBronyaShader::Awake(void)
{
	__super::Awake();

	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
	//m_vRenderTargets[3] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CBronyaShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
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
}
