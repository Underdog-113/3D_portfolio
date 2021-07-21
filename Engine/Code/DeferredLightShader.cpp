#include "EngineStdafx.h"
#include "DeferredLightShader.h"


USING(Engine)
CDeferredLightShader::CDeferredLightShader()
{
}


CDeferredLightShader::~CDeferredLightShader()
{
}

CShader * CDeferredLightShader::Create(void)
{
	CDeferredLightShader* pInstance = new CDeferredLightShader;
	pInstance->Awake();

	return pInstance;
}

void CDeferredLightShader::Free(void)
{
	__super::Free();
	
}

void CDeferredLightShader::Awake(void)
{
	__super::Awake();
	CRenderTargetManager* pRTM = CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Shade");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Specular");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_LightDepth");
}

void CDeferredLightShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
}
