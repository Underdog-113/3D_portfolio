#include "EngineStdafx.h"
#include "CircularGaugeShader.h"


USING(Engine)
CCircularGaugeShader::CCircularGaugeShader()
{
}


CCircularGaugeShader::~CCircularGaugeShader()
{
}

CShader * CCircularGaugeShader::Create(void)
{
	CCircularGaugeShader* pInstance = new CCircularGaugeShader;
	pInstance->Awake();

	return pInstance;
}

void CCircularGaugeShader::Free(void)
{
	__super::Free();

}

void CCircularGaugeShader::Awake(void)
{
	__super::Awake();
}

void CCircularGaugeShader::SetUpConstantTable(SP(CGraphicsC) spGC)
{
	m_spSlider = static_cast<CSlider*>(spGC->GetOwner()->GetParent());

	_float minValue = m_spSlider->GetMinValue();
	_float value = m_spSlider->GetValue() - minValue;
	_float maxValue = m_spSlider->GetMaxValue() - minValue;

	std::cout << value << std::endl;

	// 비율구하기
	_float ratio = value / maxValue;

	m_pEffect->SetFloat("g_ratio", ratio);
	m_pEffect->SetInt("g_direction", (_int)m_spSlider->GetDirection());

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
