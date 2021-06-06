#include "EngineStdafx.h"
#include "DeferredBlendShader.h"


USING(Engine)
CDeferredBlendShader::CDeferredBlendShader()
{
}


CDeferredBlendShader::~CDeferredBlendShader()
{
}

CShader * CDeferredBlendShader::Create(void)
{
	CDeferredBlendShader* pInstance = new CDeferredBlendShader;
	pInstance->Awake();

	return pInstance;
}

void CDeferredBlendShader::Free(void)
{
	__super::Free();
	
}

void CDeferredBlendShader::Awake(void)
{
	__super::Awake();
	
}

void CDeferredBlendShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{

}
