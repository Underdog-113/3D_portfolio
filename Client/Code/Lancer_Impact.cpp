#include "stdafx.h"
#include "..\Header\Lancer_Impact.h"

_uint CLancer_Impact::m_s_uniqueID = 0;

CLancer_Impact::CLancer_Impact()
{
}


CLancer_Impact::~CLancer_Impact()
{
}

SP(CLancer_Impact) CLancer_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CLancer_Impact) spInstance(new CLancer_Impact, Engine::SmartDeleter<CLancer_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CLancer_Impact::MakeClone()
{
	SP(CLancer_Impact) spClone(new CLancer_Impact, Engine::SmartDeleter<CLancer_Impact>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSizeX(2.f);
	spClone->m_spTransform->SetSizeY(2.f);
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CLancer_Impact::Awake()
{
	__super::Awake();
	m_bBillboard = false;
}

void CLancer_Impact::Start()
{
	__super::Start();
	m_fAlphaWidth = 2.f;
	m_fAlphaHeight = 2.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 2;
	m_maxYIndex = 1;
	m_fTIme = 0.f;
	m_fSpeed = 5.f;
}

void CLancer_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CLancer_Impact::Update()
{
	__super::Update();

	m_spTransform->AddSizeX(2.f * GET_DT);
	m_spTransform->AddPosition(m_spTransform->GetRight() * GET_DT * 1.f);

	UpdateFrame(0.1f);
}

void CLancer_Impact::LateUpdate()
{
	__super::LateUpdate();

}

void CLancer_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
}

void CLancer_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CLancer_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CLancer_Impact::OnDestroy()
{
	__super::OnDestroy();

}

void CLancer_Impact::OnEnable()
{
	__super::OnEnable();

}

void CLancer_Impact::OnDisable()
{
	__super::OnDisable();

}

void CLancer_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CLancer_Impact::UpdateFrame(_float _frmSpeed)
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
