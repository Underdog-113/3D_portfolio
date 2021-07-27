#include "stdafx.h"
#include "..\Header\CharacterShader.h"


CCharacterShader::CCharacterShader()
{
}


CCharacterShader::~CCharacterShader()
{
}

Engine::CShader * CCharacterShader::Create(void)
{
	CCharacterShader* pInstance = new CCharacterShader;
	pInstance->Awake();

	return pInstance;
}

void CCharacterShader::Free(void)
{
	__super::Free();
	
}

void CCharacterShader::Awake(void)
{
	__super::Awake();
	Engine::CRenderTargetManager* pRTM = Engine::CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
	m_vRenderTargets[2] = pRTM->FindRenderTarget(L"Target_Depth");
	m_vRenderTargets[3] = pRTM->FindRenderTarget(L"Target_Emissive");
}

void CCharacterShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);

	if (spGC->GetColorReverse())
	{
		m_addColor = _float4(0.5f, 0.f, 0.f, 0.f);
	}
	m_pEffect->SetVector("g_color", &spGC->GetTexture()->GetColor());
	m_pEffect->SetVector("g_addColor", &m_addColor);
	m_pEffect->SetVector("g_multColor", &m_multColor);
}
