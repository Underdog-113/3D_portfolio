#include "stdafx.h"
#include "KianaBodyShader.h"


CKianaBodyShader::CKianaBodyShader()
{
}


CKianaBodyShader::~CKianaBodyShader()
{
}

Engine::CShader * CKianaBodyShader::Create(void)
{
	CKianaBodyShader* pInstance = new CKianaBodyShader;
	pInstance->Awake();

	return pInstance;
}

void CKianaBodyShader::Free(void)
{
	__super::Free();
	
}

void CKianaBodyShader::Awake(void)
{
	__super::Awake();
	
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
	m_vRenderTargets[3] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CKianaBodyShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);
}
