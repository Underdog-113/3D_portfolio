#include "EngineStdafx.h"
#include "WireShader.h"

USING(Engine)
CWireShader::CWireShader()
{
}


CWireShader::~CWireShader()
{
}

CShader * CWireShader::Create(void)
{
	CWireShader* pInstance = new CWireShader;
	pInstance->Awake();

	return pInstance;
}

void CWireShader::Free(void)
{
	__super::Free();
	
}

void CWireShader::Awake(void)
{
	__super::Awake();
	
}

void CWireShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	SetupWorldViewProj(spGC);
	m_pEffect->SetVector("g_color", &spGC->GetColor());
}
