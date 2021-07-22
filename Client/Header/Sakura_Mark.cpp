#include "stdafx.h"
#include "Sakura_Mark.h"

_uint CSakura_Mark::m_s_uniqueID = 0;

CSakura_Mark::CSakura_Mark()
{
}


CSakura_Mark::~CSakura_Mark()
{
}

SP(CSakura_Mark) CSakura_Mark::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_Mark) spInstance(new CSakura_Mark, Engine::SmartDeleter<CSakura_Mark>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_Mark::MakeClone(void)
{
	SP(CSakura_Mark) spClone(new CSakura_Mark, Engine::SmartDeleter<CSakura_Mark>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CSakura_Mark::Awake(void)
{
	__super::Awake();
	m_spTexture->AddTexture(L"SakuraMark");
	m_spTexture->AddTexture(L"SakuraMark");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader);
}

void CSakura_Mark::Start(void)
{
	__super::Start();
	m_fAlphaWidth = 4.f;
	m_fAlphaHeight = 4.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_maxXIndex = 4;
	m_maxYIndex = 3;
	m_fTIme = 0.f;
}

void CSakura_Mark::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CSakura_Mark::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);
}

void CSakura_Mark::LateUpdate(void)
{
	__super::LateUpdate();

}

void CSakura_Mark::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CSakura_Mark::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CSakura_Mark::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CSakura_Mark::OnDestroy(void)
{
	__super::OnDestroy();

}

void CSakura_Mark::OnEnable(void)
{
	__super::OnEnable();

}

void CSakura_Mark::OnDisable(void)
{
	__super::OnDisable();

}

void CSakura_Mark::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CSakura_Mark::UpdateFrame(_float _frmSpeed)
{
	m_fTIme += GET_PLAYER_DT;

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
