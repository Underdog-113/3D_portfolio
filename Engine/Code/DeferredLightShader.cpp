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
	
}

void CDeferredLightShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
}
