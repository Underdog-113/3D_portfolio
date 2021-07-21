#include "EngineStdafx.h"
#include "ShadowShader.h"


USING(Engine)
CShadowShader::CShadowShader()
{
}


CShadowShader::~CShadowShader()
{
}

CShader * CShadowShader::Create(void)
{
	CShadowShader* pInstance = new CShadowShader;
	pInstance->Awake();

	return pInstance;
}

void CShadowShader::Free(void)
{
	__super::Free();
	
}

void CShadowShader::Awake(void)
{
	__super::Awake();
	
}

void CShadowShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	
}
