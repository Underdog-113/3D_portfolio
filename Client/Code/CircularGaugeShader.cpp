#include "stdafx.h"
#include "CircularGaugeShader.h"



CCircularGaugeShader::CCircularGaugeShader()
{
}


CCircularGaugeShader::~CCircularGaugeShader()
{
}

Engine::CShader * CCircularGaugeShader::Create(void)
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

//_float value = m_spSlider->GetMaxValue() - ((m_spSlider->GetMaxValue()  - m_spSlider->GetValue()) * 2); // 1 ~ -1값으로 비율이 구해져서 현재 벨류를 2배로 내렸다.
void CCircularGaugeShader::SetUpConstantTable(SP(Engine::CGraphicsC) spGC)
{
	m_spSlider = static_cast<Engine::CSlider*>(spGC->GetOwner()->GetParent());

	_float minValue = m_spSlider->GetMinValue();
	_float maxValue = m_spSlider->GetMaxValue() - minValue;
	_float value = (m_spSlider->GetValue() - minValue);

	// 비율구하기
	_float ratio = (value / maxValue);

	std::cout << "비율 : " << ratio << std::endl;

	// 1 ~ 0의값을 조정해야함
	m_pEffect->SetFloat("g_maxValue", m_spSlider->GetCircularMaxValue());
	m_pEffect->SetFloat("g_minValue", m_spSlider->GetCircularMinValue());

	m_pEffect->SetFloat("g_ratio", ratio);
	m_pEffect->SetInt("g_direction", (_int)m_spSlider->GetDirection());

	LPDIRECT3DDEVICE9 pDevice = Engine::GET_DEVICE;
	_mat worldMat, viewMat, projMat;

	worldMat = spGC->GetTransform()->GetLastWorldMatrix();
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
