#include "stdafx.h"
#include "OutlineShader.h"


COutlineShader::COutlineShader()
{
}


COutlineShader::~COutlineShader()
{
}

Engine::CShader * COutlineShader::Create(void)
{
	COutlineShader* pInstance = new COutlineShader;
	pInstance->Awake();

	return pInstance;
}

void COutlineShader::Free(void)
{
	__super::Free();
}

void COutlineShader::Awake(void)
{
	__super::Awake();
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
}

void COutlineShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);
}
