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
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();

	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

	_float4 addColor(0, 0, 0, 0);

	if (spGC->GetColorReverse())
	{
		addColor = _float4(0.5f, 0.5f, 0.5f, 0.5f);
	}

	m_pEffect->SetVector("g_addColor", &addColor);
	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);
}
