#include "stdafx.h"
#include "..\Header\Kiana_WSkill_Shoot.h"

_uint CKiana_WSkill_Shoot::m_s_uniqueID = 0;

CKiana_WSkill_Shoot::CKiana_WSkill_Shoot()
{
}


CKiana_WSkill_Shoot::~CKiana_WSkill_Shoot()
{
}

SP(CKiana_WSkill_Shoot) CKiana_WSkill_Shoot::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_WSkill_Shoot) spInstance(new CKiana_WSkill_Shoot, Engine::SmartDeleter<CKiana_WSkill_Shoot>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_WSkill_Shoot::MakeClone(void)
{
	SP(CKiana_WSkill_Shoot) spClone(new CKiana_WSkill_Shoot, Engine::SmartDeleter<CKiana_WSkill_Shoot>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSizeX(3);
	spClone->m_spTransform->SetSizeY(2);
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CKiana_WSkill_Shoot::Awake(void)
{
	__super::Awake();

}

void CKiana_WSkill_Shoot::Start(void)
{
	__super::Start();
	m_fAlphaWidth = 2.f;
	m_fAlphaHeight = 2.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_maxXIndex = 2;
	m_maxYIndex = 1;
	m_fTIme = 0.f;
}

void CKiana_WSkill_Shoot::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CKiana_WSkill_Shoot::Update(void)
{
	__super::Update();
	UpdateFrame(0.05f);
}

void CKiana_WSkill_Shoot::LateUpdate(void)
{
	__super::LateUpdate();

}

void CKiana_WSkill_Shoot::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CKiana_WSkill_Shoot::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CKiana_WSkill_Shoot::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CKiana_WSkill_Shoot::OnDestroy(void)
{
	__super::OnDestroy();

}

void CKiana_WSkill_Shoot::OnEnable(void)
{
	__super::OnEnable();

}

void CKiana_WSkill_Shoot::OnDisable(void)
{
	__super::OnDisable();

}

void CKiana_WSkill_Shoot::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CKiana_WSkill_Shoot::UpdateFrame(_float _frmSpeed)
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
			}
			else
			{
				m_TilingY++;
			}
		}
		m_fTIme = 0;
	}
}
