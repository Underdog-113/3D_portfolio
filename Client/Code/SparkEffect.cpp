#include "stdafx.h"
#include "..\Header\SparkEffect.h"

_uint CSparkEffect::m_s_uniqueID = 0;


CSparkEffect::CSparkEffect()
{
}


CSparkEffect::~CSparkEffect()
{
}

SP(CSparkEffect) CSparkEffect::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSparkEffect) spInstance(new CSparkEffect, Engine::SmartDeleter<CSparkEffect>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSparkEffect::MakeClone(void)
{
	SP(CSparkEffect) spClone(new CSparkEffect, Engine::SmartDeleter<CSparkEffect>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSizeX(5.f);
	spClone->m_spTransform->SetSizeY(1.f);
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CSparkEffect::Awake(void)
{
	__super::Awake();
	m_spTexture->AddTexture(L"Spark_v2");
	m_spTexture->AddTexture(L"Spark_v2");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader);
}

void CSparkEffect::Start(void)
{
	__super::Start();

	m_fAlphaWidth = 2.f;
	m_fAlphaHeight = 3.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 2;
	m_maxYIndex = 2;
	m_fTIme = 0.f;

	m_spTransform->SetRotationZ(D3DXToRadian(rand() % 100 + 45.f));

}

void CSparkEffect::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSparkEffect::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);
}

void CSparkEffect::LateUpdate(void)
{
	__super::LateUpdate();

	m_spTransform->AddPositionY(0.3f * GET_DT);

}

void CSparkEffect::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
}

void CSparkEffect::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);
}

void CSparkEffect::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);
}

void CSparkEffect::OnDestroy(void)
{
	__super::OnDestroy();
}

void CSparkEffect::OnEnable(void)
{
	__super::OnEnable();
}

void CSparkEffect::OnDisable(void)
{
	__super::OnDisable();
}

void CSparkEffect::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CSparkEffect::UpdateFrame(_float _frmSpeed)
{
	m_fTIme += GET_DT;

	if (m_fTIme >= _frmSpeed)
	{
		m_TilingX++;

		if (m_TilingX >= m_maxXIndex)
		{
			m_TilingX = 0;

			if (m_TilingY >= m_maxYIndex)
			{
				m_TilingY = 0;
				this->SetDeleteThis(true);
			}
			else
			{
				m_TilingY++;
			}
		}
		m_fTIme = 0;
	}
}
