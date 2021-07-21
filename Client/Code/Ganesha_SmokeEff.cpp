#include "stdafx.h"
#include "..\Header\Ganesha_SmokeEff.h"

_uint CGanesha_SmokeEff::m_s_uniqueID = 0;

CGanesha_SmokeEff::CGanesha_SmokeEff()
{
}


CGanesha_SmokeEff::~CGanesha_SmokeEff()
{
}

SP(CGanesha_SmokeEff) CGanesha_SmokeEff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_SmokeEff) spInstance(new CGanesha_SmokeEff, Engine::SmartDeleter<CGanesha_SmokeEff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_SmokeEff::MakeClone(void)
{
	SP(CGanesha_SmokeEff) spClone(new CGanesha_SmokeEff, Engine::SmartDeleter<CGanesha_SmokeEff>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;
	return spClone;
}

void CGanesha_SmokeEff::Awake(void)
{
	__super::Awake();
	m_spTexture->AddTexture(L"hit_explosion5_new");
	m_spTexture->AddTexture(L"hit_explosion5_new");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
}

void CGanesha_SmokeEff::Start(void)
{
	__super::Start();

	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);


	m_fAlphaWidth = 7.f;
	m_fAlphaHeight = 3.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 7;
	m_maxYIndex = 2;
	m_fTIme = 0.f;
}

void CGanesha_SmokeEff::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CGanesha_SmokeEff::Update(void)
{
	__super::Update();

	UpdateFrame(0.03f);
}

void CGanesha_SmokeEff::LateUpdate(void)
{
	__super::LateUpdate();
}

void CGanesha_SmokeEff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->SetBool("g_zWriteEnable", true);

	pEffect->CommitChanges();
}

void CGanesha_SmokeEff::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CGanesha_SmokeEff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CGanesha_SmokeEff::OnDestroy(void)
{
	__super::OnDestroy();

}

void CGanesha_SmokeEff::OnEnable(void)
{
	__super::OnEnable();

}

void CGanesha_SmokeEff::OnDisable(void)
{
	__super::OnDisable();

}

void CGanesha_SmokeEff::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CGanesha_SmokeEff::UpdateFrame(_float _frmSpeed)
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
