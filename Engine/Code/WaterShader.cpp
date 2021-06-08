#include "EngineStdafx.h"
#include "..\Header\WaterShader.h"

USING(Engine)

CWaterShader::CWaterShader()
{
}

CShader * CWaterShader::Create()
{
	CWaterShader* pInstance = new CWaterShader;
	pInstance->Awake();

	return pInstance;
}

void CWaterShader::Free()
{
	__super::Free();
}

void CWaterShader::Awake()
{
	__super::Awake();
}

void CWaterShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{

}
