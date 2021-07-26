#include "EngineStdafx.h"
#include "..\Header\GlowShader.h"


USING(Engine)
CGlowShader::CGlowShader()
{
}


CGlowShader::~CGlowShader()
{
}

CShader * CGlowShader::Create(void)
{
	CGlowShader* pInstance = new CGlowShader;
	pInstance->Awake();

	return pInstance;
}

void CGlowShader::Free(void)
{
	__super::Free();
	
}

void CGlowShader::Awake(void)
{
	__super::Awake();

	CRenderTargetManager* pRTM = CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CGlowShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);

	m_pEffect->SetFloat("g_GlowCoef", spGC->GetGlowCoef());
	m_pEffect->CommitChanges();
}
