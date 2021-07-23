#include "EngineStdafx.h"
#include "FinalShader.h"

USING(Engine)
CFinalShader::CFinalShader()
{
}


CFinalShader::~CFinalShader()
{
}

CShader * CFinalShader::Create(void)
{
	CFinalShader* pInstance = new CFinalShader;
	pInstance->Awake();

	return pInstance;
}

void CFinalShader::Free(void)
{
	__super::Free();
	
}

void CFinalShader::Awake(void)
{
	__super::Awake();
}

void CFinalShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);	
}
