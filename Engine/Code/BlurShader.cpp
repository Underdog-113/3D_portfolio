#include "EngineStdafx.h"
#include "BlurShader.h"

USING(Engine)
CBlurShader::CBlurShader()
{
}


CBlurShader::~CBlurShader()
{
}

CShader * CBlurShader::Create(void)
{
	CBlurShader* pInstance = new CBlurShader;
	pInstance->Awake();

	return pInstance;
}

void CBlurShader::Free(void)
{
	__super::Free();
	
}

void CBlurShader::Awake(void)
{
	__super::Awake();
	
}

void CBlurShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
}
