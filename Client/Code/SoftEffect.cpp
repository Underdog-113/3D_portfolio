#include "stdafx.h"
#include "..\Header\SoftEffect.h"

_uint CSoftEffect::m_s_uniqueID = 0;

CSoftEffect::CSoftEffect()
{
}


CSoftEffect::~CSoftEffect()
{
	OnDestroy();
}

void CSoftEffect::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)Engine::ELayerID::Effect;
	m_addExtra = true;

	(m_spRectTex = AddComponent<Engine::CRectTexC>());
	(m_spGraphics = AddComponent<Engine::CGraphicsC>())->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTransform->SetCheckCamDistance(true);

}
void CSoftEffect::Start(void)
{
	__super::Start();
	m_fAlphaWidth = 1.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_fTIme = 0.f;
}

void CSoftEffect::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSoftEffect::Update(void)
{
	__super::Update();


}

void CSoftEffect::LateUpdate(void)
{
	__super::LateUpdate();

	// Billboard
	_mat matWorld, matView, matBill;

	matView = Engine::GET_MAIN_CAM->GetViewMatrix();

	D3DXMatrixIdentity(&matBill);

	memcpy(&matBill.m[0][0], &matView.m[0][0], sizeof(_float3));
	memcpy(&matBill.m[1][0], &matView.m[1][0], sizeof(_float3));
	memcpy(&matBill.m[2][0], &matView.m[2][0], sizeof(_float3));

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matWorld = m_spGraphics->GetTransform()->GetWorldMatrix();

	m_spGraphics->GetTransform()->SetWorldMatrix(matBill * matWorld);

}

void CSoftEffect::OnDestroy(void)
{
	__super::OnDestroy();
}

void CSoftEffect::OnEnable(void)
{
	__super::OnEnable();
}

void CSoftEffect::OnDisable(void)
{
	__super::OnDisable();
}

void CSoftEffect::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
