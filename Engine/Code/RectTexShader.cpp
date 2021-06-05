#include "EngineStdafx.h"
#include "RectTexShader.h"


USING(Engine)
CRectTexShader::CRectTexShader()
{
}


CRectTexShader::~CRectTexShader()
{
}

CShader * CRectTexShader::Create(void)
{
	CRectTexShader* pInstance = new CRectTexShader;
	pInstance->Awake();

	return pInstance;
}

void CRectTexShader::Free(void)
{
	__super::Free();
}

void CRectTexShader::Awake(void)
{
	__super::Awake();
}

void CRectTexShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
	if (spGC->GetRectTex()->GetIsOrtho())
	{
		D3DXMatrixIdentity(&viewMat);
		projMat = GET_MAIN_CAM->GetOrthoMatrix();
	}
	else
	{
		pDevice->GetTransform(D3DTS_VIEW, &viewMat);
		pDevice->GetTransform(D3DTS_PROJECTION, &projMat);	
	}
	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);

	SP(CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[spTexture->GetMeshIndex()][spTexture->GetTexIndex()]->pTexture);
}
