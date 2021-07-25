#include "stdafx.h"
#include "..\Header\UltScrShader.h"


CUltScrShader::CUltScrShader()
{
}


CUltScrShader::~CUltScrShader()
{
}

Engine::CShader * CUltScrShader::Create(void)
{
	CUltScrShader* pInstance = new CUltScrShader;
	pInstance->Awake();

	return pInstance;
}

void CUltScrShader::Free(void)
{
	__super::Free();
	
}

void CUltScrShader::Awake(void)
{
	__super::Awake();
	
}

void CUltScrShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);


}
