#include "stdafx.h"
#include "OutlineShader.h"


COutlineShader::COutlineShader()
{
}


COutlineShader::~COutlineShader()
{
}

Engine::CShader * COutlineShader::Create(void)
{
	COutlineShader* pInstance = new COutlineShader;
	pInstance->Awake();

	return pInstance;
}

void COutlineShader::Free(void)
{
	__super::Free();
}

void COutlineShader::Awake(void)
{
	__super::Awake();
	
}

void COutlineShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	SetupWorldViewProj(spGC);
}
