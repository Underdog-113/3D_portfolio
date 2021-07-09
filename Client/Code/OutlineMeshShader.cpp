#include "stdafx.h"
#include "..\Header\OutlineMeshShader.h"


COutlineMeshShader::COutlineMeshShader()
{
}


COutlineMeshShader::~COutlineMeshShader()
{
}

Engine::CShader * COutlineMeshShader::Create(void)
{
	COutlineMeshShader* pInstance = new COutlineMeshShader;
	pInstance->Awake();

	return pInstance;
}


void COutlineMeshShader::Free(void)
{
	__super::Free();
	
}

void COutlineMeshShader::Awake(void)
{
	__super::Awake();
	
}

void COutlineMeshShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	SetupWorldViewProj(spGC);
}
