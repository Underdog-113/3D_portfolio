#include "stdafx.h"
#include "..\Header\SpiderExplosion.h"

_uint CSpiderExplosion::m_s_uniqueID = 0;

CSpiderExplosion::CSpiderExplosion()
{
}


CSpiderExplosion::~CSpiderExplosion()
{
}

SP(CSpiderExplosion) CSpiderExplosion::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSpiderExplosion) spInstance(new CSpiderExplosion, Engine::SmartDeleter<CSpiderExplosion>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSpiderExplosion::MakeClone(void)
{
	SP(CSpiderExplosion) spClone(new CSpiderExplosion, Engine::SmartDeleter<CSpiderExplosion>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	return spClone;
}

void CSpiderExplosion::Awake(void)
{
	__super::Awake();
	m_spTransform->SetSizeX(6);
	m_spTransform->SetSizeY(10);
}

void CSpiderExplosion::Start(void)
{
	__super::Start();

	m_fAlphaWidth = 16.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 16;
	m_maxYIndex = 0;
	m_fTIme = 0.f;
}

void CSpiderExplosion::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CSpiderExplosion::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);
}

void CSpiderExplosion::LateUpdate(void)
{
	__super::LateUpdate();

}

void CSpiderExplosion::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
}

void CSpiderExplosion::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CSpiderExplosion::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CSpiderExplosion::OnDestroy(void)
{
	__super::OnDestroy();

}

void CSpiderExplosion::OnEnable(void)
{
	__super::OnEnable();

}

void CSpiderExplosion::OnDisable(void)
{
	__super::OnDisable();

}

void CSpiderExplosion::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CSpiderExplosion::UpdateFrame(_float _frmSpeed)
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
