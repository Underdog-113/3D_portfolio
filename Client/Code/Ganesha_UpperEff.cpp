#include "stdafx.h"
#include "..\Header\Ganesha_UpperEff.h"

_uint CGanesha_UpperEff::m_s_uniqueID = 0;


CGanesha_UpperEff::CGanesha_UpperEff()
{
}


CGanesha_UpperEff::~CGanesha_UpperEff()
{
}

SP(CGanesha_UpperEff) CGanesha_UpperEff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_UpperEff) spInstance(new CGanesha_UpperEff, Engine::SmartDeleter<CGanesha_UpperEff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_UpperEff::MakeClone(void)
{
	SP(CGanesha_UpperEff) spClone(new CGanesha_UpperEff, Engine::SmartDeleter<CGanesha_UpperEff>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;
	return spClone;
}

void CGanesha_UpperEff::Awake(void)
{
	__super::Awake();

}

void CGanesha_UpperEff::Start(void)
{
	__super::Start();

	// 텍스처 지정해야함.
	m_fAlphaWidth = 0.f;
	m_fAlphaHeight = 0.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 0;
	m_maxYIndex = 0;
	m_fTIme = 0.f;
}

void CGanesha_UpperEff::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CGanesha_UpperEff::Update(void)
{
	__super::Update();

	UpdateFrame(0.1f);
}

void CGanesha_UpperEff::LateUpdate(void)
{
	__super::LateUpdate();

}

void CGanesha_UpperEff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CGanesha_UpperEff::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CGanesha_UpperEff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CGanesha_UpperEff::OnDestroy(void)
{
	__super::OnDestroy();

}

void CGanesha_UpperEff::OnEnable(void)
{
	__super::OnEnable();

}

void CGanesha_UpperEff::OnDisable(void)
{
	__super::OnDisable();

}

void CGanesha_UpperEff::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CGanesha_UpperEff::UpdateFrame(_float _frmSpeed)
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
