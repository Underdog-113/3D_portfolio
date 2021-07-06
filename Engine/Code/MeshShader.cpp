#include "EngineStdafx.h"
#include "MeshShader.h"


USING(Engine)
CMeshShader::CMeshShader()
{
}


CMeshShader::~CMeshShader()
{
}

CShader * CMeshShader::Create(void)
{
	CMeshShader* pInstance = new CMeshShader;
	pInstance->Awake();
	
	return pInstance;
}

void CMeshShader::Free(void)
{
	__super::Free();
}

void CMeshShader::Awake(void)
{
	__super::Awake();
}

void CMeshShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	SetupWorldViewProj(spGC);



	if (spGC->GetColorReverse())
	{
		m_addColor = _float4(0.5f, 0.f, 0.f, 0.f);
	}

	m_pEffect->SetVector("g_addColor", &m_addColor);
}
