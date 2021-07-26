#include "stdafx.h"
#include "..\Header\SoftEffectShader_Glow.h"


CSoftEffectShader_Glow::CSoftEffectShader_Glow()
{
}


CSoftEffectShader_Glow::~CSoftEffectShader_Glow()
{
}

Engine::CShader * CSoftEffectShader_Glow::Create()
{
	CSoftEffectShader_Glow* pInstance = new CSoftEffectShader_Glow;
	pInstance->Awake();


	return pInstance;
}

void CSoftEffectShader_Glow::Free()
{
	__super::Free();

}

void CSoftEffectShader_Glow::Awake()
{
	__super::Awake();
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CSoftEffectShader_Glow::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
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
