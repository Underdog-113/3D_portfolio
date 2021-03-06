#include "stdafx.h"
#include "..\Header\SoftEffectShader.h"


CSoftEffectShader::CSoftEffectShader()
{
}


CSoftEffectShader::~CSoftEffectShader()
{
}

Engine::CShader * CSoftEffectShader::Create()
{
	CSoftEffectShader* pInstance = new CSoftEffectShader;
	pInstance->Awake();


	return pInstance;
}

void CSoftEffectShader::Free()
{
	__super::Free();
}

void CSoftEffectShader::Awake()
{
	__super::Awake();
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Final");

}

void CSoftEffectShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	_mat matWorld, matView, matProj;

	matWorld = spGC->GetTransform()->GetWorldMatrix();
	matView = Engine::GET_MAIN_CAM->GetViewMatrix();
	matProj = Engine::GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("g_matWorld", &matWorld);
	m_pEffect->SetMatrix("g_matView", &matView);
	m_pEffect->SetMatrix("g_matProj", &matProj);	

	SP(Engine::CTextureC) spTexture = spGC->GetTexture();

	m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[0][0]->pTexture);
	m_pEffect->SetTexture("g_ServeTexture", spTexture->GetTexData()[0][1]->pTexture);
}
