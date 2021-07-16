#include "stdafx.h"
#include "..\Header\Sakura_WSkill_Smoke.h"

_uint CSakura_WSkill_Smoke::m_s_uniqueID = 0;

CSakura_WSkill_Smoke::CSakura_WSkill_Smoke()
{
}


CSakura_WSkill_Smoke::~CSakura_WSkill_Smoke()
{
}

SP(CSakura_WSkill_Smoke) CSakura_WSkill_Smoke::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_WSkill_Smoke) spInstance(new CSakura_WSkill_Smoke, Engine::SmartDeleter<CSakura_WSkill_Smoke>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_WSkill_Smoke::MakeClone(void)
{
	SP(CSakura_WSkill_Smoke) spClone(new CSakura_WSkill_Smoke, Engine::SmartDeleter<CSakura_WSkill_Smoke>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;
	return spClone;
}

void CSakura_WSkill_Smoke::Awake(void)
{
	__super::Awake();

}

void CSakura_WSkill_Smoke::Start(void)
{
	__super::Start();

	m_fAlphaWidth = 3.f;
	m_fAlphaHeight = 3.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 3;
	m_maxYIndex = 2;
	m_fTIme = 0.f;
}

void CSakura_WSkill_Smoke::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CSakura_WSkill_Smoke::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);
}

void CSakura_WSkill_Smoke::LateUpdate(void)
{
	__super::LateUpdate();

}

void CSakura_WSkill_Smoke::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CSakura_WSkill_Smoke::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CSakura_WSkill_Smoke::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CSakura_WSkill_Smoke::OnDestroy(void)
{
	__super::OnDestroy();

}

void CSakura_WSkill_Smoke::OnEnable(void)
{
	__super::OnEnable();

}

void CSakura_WSkill_Smoke::OnDisable(void)
{
	__super::OnDisable();

}

void CSakura_WSkill_Smoke::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CSakura_WSkill_Smoke::UpdateFrame(_float _frmSpeed)
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
				SetDeleteThis(true);
			}
			else
			{
				m_TilingY++;
			}
		}
		m_fTIme = 0;
	}
}
