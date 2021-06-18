#include "EngineStdafx.h"
#include "..\Header\SoftEffectShader.h"

USING(Engine)

CSoftEffectShader::CSoftEffectShader()
{
}


CSoftEffectShader::~CSoftEffectShader()
{
}

CShader * CSoftEffectShader::Create()
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
}

void CSoftEffectShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	_mat matWorld, matView, matProj;

	matWorld = spGC->GetTransform()->GetLastWorldMatrix();
	matView = GET_MAIN_CAM->GetViewMatrix();
	matProj = GET_MAIN_CAM->GetProjMatrix();

	m_pEffect->SetMatrix("g_matWorld", &matWorld);
	m_pEffect->SetMatrix("g_matView", &matView);
	m_pEffect->SetMatrix("g_matProj", &matProj);	

	SP(CTextureC) spTexture = spGC->GetTexture();

	m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[0][0]->pTexture);
	CRenderTargetManager::GetInstance()->SetRenderTargetTexture(m_pEffect, L"Target_Depth", "g_DepthTexture");
}
