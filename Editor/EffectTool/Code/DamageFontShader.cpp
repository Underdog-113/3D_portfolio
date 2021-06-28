#include "stdafx.h"
#include "DamageFontShader.h"
#include "ImageObject.h"

CDamageFontShader::CDamageFontShader()
{
}


CDamageFontShader::~CDamageFontShader()
{
}

Engine::CShader * CDamageFontShader::Create(void)
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

void CDamageFontShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	Engine::CImageObject* imageObject = static_cast<Engine::CImageObject*>(spGC->GetOwner()->GetParent());

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
	IDirect3DBaseTexture9* s = spTexture->GetTexData()[0][0]->pTexture;
	m_pEffect->SetTexture("g_BaseTexture", s);
	m_pEffect->CommitChanges();
}
