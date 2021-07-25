#include "stdafx.h"
#include "..\Header\Sakura_DamageMark.h"

_uint CSakura_DamageMark::m_s_uniqueID = 0;

CSakura_DamageMark::CSakura_DamageMark()
{
}


CSakura_DamageMark::~CSakura_DamageMark()
{
}

SP(CSakura_DamageMark) CSakura_DamageMark::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_DamageMark) spInstance(new CSakura_DamageMark, Engine::SmartDeleter<CSakura_DamageMark>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_DamageMark::MakeClone(void)
{
	SP(CSakura_DamageMark) spClone(new CSakura_DamageMark, Engine::SmartDeleter<CSakura_DamageMark>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CSakura_DamageMark::Awake(void)
{
	__super::Awake();
	m_spTexture->AddTexture(L"Sakura_DamageMark");
	m_spTexture->AddTexture(L"Sakura_DamageMark");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader);
	m_spGraphics->SetRenderID((_uint)Engine::ERenderID::Effect);
}

void CSakura_DamageMark::Start(void)
{
	__super::Start();
	m_fAlphaWidth = 12.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_maxXIndex = 12;
	m_maxYIndex = 1;
	m_fTIme = 0.f;
}

void CSakura_DamageMark::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CSakura_DamageMark::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);
	m_spTransform->SetPosition(m_pTargetObject->GetTransform()->GetPosition());
	m_spTransform->AddPositionY(m_pTargetObject->GetComponent<Engine::CMeshC>()->GetHalfYOffset() * 2.1f);
}

void CSakura_DamageMark::LateUpdate(void)
{
	__super::LateUpdate();

}

void CSakura_DamageMark::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->CommitChanges();
}

void CSakura_DamageMark::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CSakura_DamageMark::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CSakura_DamageMark::OnDestroy(void)
{
	__super::OnDestroy();

}

void CSakura_DamageMark::OnEnable(void)
{
	__super::OnEnable();

}

void CSakura_DamageMark::OnDisable(void)
{
	__super::OnDisable();

}

void CSakura_DamageMark::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CSakura_DamageMark::UpdateFrame(_float _frmSpeed)
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
			}
			else
			{
				m_TilingY++;
			}
		}
		m_fTIme = 0;
	}
}
