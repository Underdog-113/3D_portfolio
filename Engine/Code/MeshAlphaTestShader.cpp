#include "EngineStdafx.h"
#include "MeshAlphaTestShader.h"


USING(Engine)
CMeshAlphaTestShader::CMeshAlphaTestShader()
{
}


CMeshAlphaTestShader::~CMeshAlphaTestShader()
{
}

CShader * CMeshAlphaTestShader::Create(void)
{
	CMeshAlphaTestShader* pInstance = new CMeshAlphaTestShader;
	pInstance->Awake();
	
	return pInstance;
}

void CMeshAlphaTestShader::Free(void)
{
	__super::Free();
}

void CMeshAlphaTestShader::Awake(void)
{
	__super::Awake();
}

void CMeshAlphaTestShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);

	_float4 addColor(0, 0, 0, 0);

	if (spGC->GetColorReverse())
	{
		addColor = _float4(0.5f, 0.f, 0.f, 0.f);
	}

	m_pEffect->SetVector("g_addColor", &addColor);
}
