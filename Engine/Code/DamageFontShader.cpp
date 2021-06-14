#include "EngineStdafx.h"
#include "DamageFontShader.h"
#include "ImageObject.h"

USING(Engine)
CDamageFontShader::CDamageFontShader()
{
}


CDamageFontShader::~CDamageFontShader()
{
}

CShader * CDamageFontShader::Create(void)
{
	CDamageFontShader* pInstance = new CDamageFontShader;
	pInstance->Awake();

	return pInstance;
}

void CDamageFontShader::Free(void)
{
	__super::Free();

}

void CDamageFontShader::Awake(void)
{
	__super::Awake();
}

void CDamageFontShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	CImageObject* imageObject = static_cast<CImageObject*>(spGC->GetOwner()->GetParent());

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
		viewMat = GET_MAIN_CAM->GetViewMatrix();
		projMat = GET_MAIN_CAM->GetProjMatrix();
	}
	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);

	SP(CTextureC) spTexture = spGC->GetTexture();
	IDirect3DBaseTexture9* s = spTexture->GetTexData()[0][0]->pTexture;
	m_pEffect->SetTexture("g_BaseTexture", s);
	m_pEffect->CommitChanges();
}
