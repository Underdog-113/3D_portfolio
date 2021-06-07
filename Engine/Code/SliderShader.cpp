#include "EngineStdafx.h"
#include "SliderShader.h"


USING(Engine)
CSliderShader::CSliderShader()
{
}


CSliderShader::~CSliderShader()
{
}

CShader * CSliderShader::Create(void)
{
	CSliderShader* pInstance = new CSliderShader;
	pInstance->Awake();

	return pInstance;
}

void CSliderShader::Free(void)
{
	__super::Free();

}

void CSliderShader::Awake(void)
{
	__super::Awake();

}

void CSliderShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
}
