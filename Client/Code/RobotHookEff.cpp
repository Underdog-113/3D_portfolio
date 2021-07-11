#include "stdafx.h"
#include "..\Header\RobotHookEff.h"

_uint CRobotHookEff::m_s_uniqueID = 0;

CRobotHookEff::CRobotHookEff()
{
}


CRobotHookEff::~CRobotHookEff()
{
}

SP(CRobotHookEff) CRobotHookEff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CRobotHookEff) spInstance(new CRobotHookEff, Engine::SmartDeleter<CRobotHookEff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CRobotHookEff::MakeClone(void)
{
	SP(CRobotHookEff) spClone(new CRobotHookEff, Engine::SmartDeleter<CRobotHookEff>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	return spClone;
}

void CRobotHookEff::Awake(void)
{
	__super::Awake();

}

void CRobotHookEff::Start(void)
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

void CRobotHookEff::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CRobotHookEff::Update(void)
{
	__super::Update();

	UpdateFrame(0.1f);

}

void CRobotHookEff::LateUpdate(void)
{
	__super::LateUpdate();

}

void CRobotHookEff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();

}

void CRobotHookEff::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CRobotHookEff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CRobotHookEff::OnDestroy(void)
{
	__super::OnDestroy();

}

void CRobotHookEff::OnEnable(void)
{
	__super::OnEnable();

}

void CRobotHookEff::OnDisable(void)
{
	__super::OnDisable();

}

void CRobotHookEff::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CRobotHookEff::UpdateFrame(_float _frmSpeed)
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
