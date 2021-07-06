#include "stdafx.h"
#include "..\Header\MonsterHitEffect.h"

_uint CMonsterHitEffect::m_s_uniqueID = 0;

CMonsterHitEffect::CMonsterHitEffect()
{
}


CMonsterHitEffect::~CMonsterHitEffect()
{
}

SP(CMonsterHitEffect) CMonsterHitEffect::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMonsterHitEffect) spInstance(new CMonsterHitEffect, Engine::SmartDeleter<CMonsterHitEffect>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMonsterHitEffect::MakeClone(void)
{
	SP(CMonsterHitEffect) spClone(new CMonsterHitEffect, Engine::SmartDeleter<CMonsterHitEffect>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	return spClone;
}

void CMonsterHitEffect::Awake(void)
{
	__super::Awake();	
}

void CMonsterHitEffect::Start(void)
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

void CMonsterHitEffect::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CMonsterHitEffect::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);
}

void CMonsterHitEffect::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMonsterHitEffect::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
}

void CMonsterHitEffect::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CMonsterHitEffect::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CMonsterHitEffect::OnDestroy(void)
{
	__super::OnDestroy();

}

void CMonsterHitEffect::OnEnable(void)
{
	__super::OnEnable();

}

void CMonsterHitEffect::OnDisable(void)
{
	__super::OnDisable();

}

void CMonsterHitEffect::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMonsterHitEffect::UpdateFrame(_float _frmSpeed)
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
