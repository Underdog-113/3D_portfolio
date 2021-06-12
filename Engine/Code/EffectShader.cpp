#include "EngineStdafx.h"
#include "..\Header\EffectShader.h"

USING(Engine)

CEffectShader::CEffectShader()
{
}


CEffectShader::~CEffectShader()
{
}

CShader * CEffectShader::Create()
{
	CEffectShader* pInstance = new CEffectShader;
	pInstance->Awake();

	return pInstance;
}

void CEffectShader::Free()
{
	__super::Free();
}

void CEffectShader::Awake()
{
	__super::Awake();
}

void CEffectShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	SP(CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_AlphaMaskTex", spTexture->GetTexData()[spTexture->GetMeshIndex()][0]->pTexture);

	m_vColor = D3DXVECTOR4(0, 0, 0, 1);

	m_pEffect->SetVector("g_BlendColor", &m_vColor);
	m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);
}
