#include "EngineStdafx.h"
#include "..\Header\EmissionShader.h"


USING(Engine)
CEmissionShader::CEmissionShader()
{
}


CEmissionShader::~CEmissionShader()
{
}

CShader * CEmissionShader::Create(void)
{
	CEmissionShader* pInstance = new CEmissionShader;
	pInstance->Awake();

	return pInstance;
}

void CEmissionShader::Free(void)
{
	__super::Free();
	
}

void CEmissionShader::Awake(void)
{
	__super::Awake();
	CRenderTargetManager* pRTM = CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Final");
}

void CEmissionShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
}
