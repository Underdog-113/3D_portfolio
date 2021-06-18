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

SP(CSoftEffect) CSoftEffect::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSoftEffect) spInstance(new CSoftEffect, Engine::SmartDeleter<CSoftEffect>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSoftEffect::MakeClone(void)
{
	SP(CSoftEffect) spClone(new CSoftEffect, Engine::SmartDeleter<CSoftEffect>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	return spClone;
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
	m_xIndex = 0;
	m_yIndex = 0;
	m_fTIme = 0.f;
	m_isPlayingAnim = false;
}

void CSoftEffect::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CSoftEffect::Update(void)
{
	__super::Update();

	if (Engine::IMKEY_DOWN(KEY_SPACE))
	{
		if (m_isPlayingAnim)
		{
			m_isPlayingAnim = false;
		}
		else
			m_isPlayingAnim = true;
	}

	if (m_isPlayingAnim)
	{
		m_fTIme += GET_DT;

		if (m_fTIme >= 0.11f)
		{
			m_xIndex++;

			if (m_xIndex > 2)
			{
				m_xIndex = 0;

				if (m_yIndex > 1)
				{
					m_yIndex = 0;
				}
				else
				{
					m_yIndex++;
				}
			}
			m_fTIme = 0;
		}
	}
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

	m_spGraphics->GetTransform()->UpdateParentMatrix(&matBill);

	_float3 vPos = m_spGraphics->GetTransform()->GetPosition();
	_float3 camPos = Engine::GET_MAIN_CAM->GetTransform()->GetPosition();

	
	//Compute_ViewZ(&vPos);

	/////////////////////////

}

void CSoftEffect::PreRender(void)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->PreRender(m_spGraphics);
	}
}

void CSoftEffect::PreRender(LPD3DXEFFECT pEffect)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->PreRender(m_spGraphics, pEffect);
		pEffect->SetInt("xIndex", m_xIndex);
		pEffect->SetInt("yIndex", m_yIndex);
		pEffect->SetFloat("gWidth", m_fAlphaWidth);
		pEffect->SetFloat("gHeight", m_fAlphaHeight);
	}
}

void CSoftEffect::Render(void)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->Render(m_spGraphics);
	}
}

void CSoftEffect::Render(LPD3DXEFFECT pEffect)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->Render(m_spGraphics, pEffect);
	}
}

void CSoftEffect::PostRender(void)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->PostRender(m_spGraphics);
	}
}

void CSoftEffect::PostRender(LPD3DXEFFECT pEffect)
{
	if (!m_spTexture->GetTexData().empty())
	{
		m_spRectTex->PostRender(m_spGraphics, pEffect);
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
