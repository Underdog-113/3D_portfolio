#include "EngineStdafx.h"
#include "WireShader.h"

USING(Engine)
CWireShader::CWireShader()
{
}


CWireShader::~CWireShader()
{
}

CShader * CWireShader::Create(void)
{
	CWireShader* pInstance = new CWireShader;
	pInstance->Awake();

	return pInstance;
}

void CWireShader::Free(void)
{
	__super::Free();
	
}

void CWireShader::Awake(void)
{
	__super::Awake();
	CRenderTargetManager* pRTM = CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
}

void CWireShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);
	m_pEffect->SetVector("g_color", &spGC->GetColor());

	m_pEffect->CommitChanges();
}
