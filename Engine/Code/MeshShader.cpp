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
	pDevice->GetTransform(D3DTS_VIEW, &viewMat);
	pDevice->GetTransform(D3DTS_PROJECTION, &projMat);

	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);
}
