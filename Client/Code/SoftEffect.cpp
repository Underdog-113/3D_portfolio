#include "stdafx.h"
#include "..\Header\SoftEffect.h"

_uint CSoftEffect::m_s_uniqueID = 0;

CSoftEffect::CSoftEffect() : m_bBillboard(false)
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

	if (m_bBillboard)
	{
		//Billboard
	_mat matWorld, matView, matBill;

	matView = Engine::GET_MAIN_CAM->GetViewMatrix();

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matWorld = m_spGraphics->GetTransform()->GetWorldMatrix();

	m_spGraphics->GetTransform()->SetWorldMatrix(matBill * matWorld);
	}
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
