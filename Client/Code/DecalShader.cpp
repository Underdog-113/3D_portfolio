#include "stdafx.h"
#include "DecalShader.h"


CDecalShader::CDecalShader()
{
}


CDecalShader::~CDecalShader()
{
}

Engine::CShader * CDecalShader::Create(void)
{
	CDecalShader* pInstance = new CDecalShader;
	pInstance->Awake();

	return pInstance;
}

void CDecalShader::Free(void)
{
	__super::Free();

}

void CDecalShader::Awake(void)
{
	__super::Awake();

	
}

void CDecalShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	
	LPDIRECT3DDEVICE9 pDevice = Engine::GET_DEVICE;
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetWorldMatrix();
	if (spGC->GetRectTex()->GetIsOrtho())
	{
		D3DXMatrixIdentity(&viewMat);
		projMat = Engine::GET_MAIN_CAM->GetOrthoMatrix();
	}
	else
	{
		viewMat = Engine::GET_MAIN_CAM->GetViewMatrix();
		projMat = Engine::GET_MAIN_CAM->GetProjMatrix();
	}
	m_pEffect->SetMatrix("g_matWorld", &worldMat);
	m_pEffect->SetMatrix("g_matView", &viewMat);
	m_pEffect->SetMatrix("g_matProj", &projMat);

	SP(Engine::CTextureC) spTexture = spGC->GetTexture();
	IDirect3DBaseTexture9* s = spTexture->GetTexData()[spTexture->GetSetIndex()][spTexture->GetTexIndex()]->pTexture;
	m_pEffect->SetTexture("g_BaseTexture", s);
	m_pEffect->CommitChanges();
}
