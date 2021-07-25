#include "stdafx.h"
#include "ElevatorBaseShader.h"


CElevatorBaseShader::CElevatorBaseShader()
{
}


CElevatorBaseShader::~CElevatorBaseShader()
{
}

Engine::CShader * CElevatorBaseShader::Create(void)
{
	CElevatorBaseShader* pInstance = new CElevatorBaseShader;
	pInstance->Awake();

	return pInstance;
}

void CElevatorBaseShader::Free(void)
{
	__super::Free();
	
}

void CElevatorBaseShader::Awake(void)
{
	__super::Awake();
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
	m_vRenderTargets[3] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CElevatorBaseShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);
}
