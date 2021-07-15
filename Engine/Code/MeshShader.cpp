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

	CRenderTargetManager* pRTM = CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
	m_vRenderTargets[3] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CMeshShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);

	if (spGC->GetColorReverse())
	{
		m_addColor = _float4(0.5f, 0.f, 0.f, 0.f);
	}
	m_pEffect->SetVector("g_color", &spGC->GetTexture()->GetColor());
	m_pEffect->SetVector("g_addColor", &m_addColor);
}
