#include "EngineStdafx.h"
#include "BackGroundShader.h"


USING(Engine)
CBackGroundShader::CBackGroundShader()
{
}

CBackGroundShader::~CBackGroundShader()
{
}

CShader * CBackGroundShader::Create(void)
{
	CBackGroundShader* pInstance = new CBackGroundShader;
	pInstance->Awake();

	return pInstance;
}

void CBackGroundShader::Free(void)
{
	__super::Free();
}

void CBackGroundShader::Awake(void)
{
	__super::Awake();
	CRenderTargetManager* pRTM = CRenderTargetManager::GetInstance();
	m_vRenderTargets[0] = pRTM->FindRenderTarget(L"Target_Albedo");
	m_vRenderTargets[1] = pRTM->FindRenderTarget(L"Target_Normal");
}

void CBackGroundShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	__super::SetUpConstantTable(spGC);
	SetupWorldViewProj(spGC);
	//if (spGC->GetRectTex()->GetIsOrtho())
		//SetupOrthoWVP(spGC);
	//else
		//

	SP(CTextureC) spTexture = spGC->GetTexture();
	m_pEffect->SetTexture("g_BaseTexture", spTexture->GetTexData()[spTexture->GetSetIndex()][spTexture->GetTexIndex()]->pTexture);

	m_pEffect->SetVector("g_color", &spTexture->GetColor());

}
