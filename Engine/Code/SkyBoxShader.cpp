#include "EngineStdafx.h"
#include "SkyBoxShader.h"


USING(Engine)
CSkyBoxShader::CSkyBoxShader()
{
}


CSkyBoxShader::~CSkyBoxShader()
{
}

CShader * CSkyBoxShader::Create(void)
{
	CSkyBoxShader* pInstance = new CSkyBoxShader;
	pInstance->Awake();

	return pInstance;
}

void CSkyBoxShader::Free(void)
{
	__super::Free();
}

void CSkyBoxShader::Awake(void)
{
	__super::Awake();
	
}

void CSkyBoxShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();

	viewMat = GET_MAIN_CAM->GetViewMatrix();
	projMat = GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);

	SP(CTextureC) spTexture = spGC->GetTexture();
	_TexData* pTex = spTexture->GetTexData()[spTexture->GetMeshIndex()][spTexture->GetTexIndex()];
	m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[spTexture->GetMeshIndex()][spTexture->GetTexIndex()]->pTexture);
}
