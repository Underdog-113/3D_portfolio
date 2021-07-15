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
	__super::SetUpConstantTable(spGC);
	
	if (spGC->GetRectTex()->GetIsOrtho())
		SetupOrthoWVP(spGC);
	else
		SetupWorldViewProj(spGC);

	SP(CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[spTexture->GetSetIndex()][spTexture->GetTexIndex()]->pTexture);

	m_pEffect->SetVector("g_color", &spTexture->GetColor());
}
