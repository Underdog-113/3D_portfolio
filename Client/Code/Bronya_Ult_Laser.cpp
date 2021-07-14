#include "stdafx.h"
#include "..\Header\Bronya_Ult_Laser.h"

_uint CBronya_Ult_Laser::m_s_uniqueID = 0;

CBronya_Ult_Laser::CBronya_Ult_Laser()
{
}


CBronya_Ult_Laser::~CBronya_Ult_Laser()
{
}

SP(CBronya_Ult_Laser) CBronya_Ult_Laser::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Laser) spInstance(new CBronya_Ult_Laser, Engine::SmartDeleter<CBronya_Ult_Laser>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Laser::MakeClone()
{
	SP(CBronya_Ult_Laser) spClone(new CBronya_Ult_Laser, Engine::SmartDeleter<CBronya_Ult_Laser>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CBronya_Ult_Laser::Awake()
{
	__super::Awake();

	m_fAlphaWidth = 3.f;
	m_fAlphaHeight = 2.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_maxXIndex = 3;
	m_maxYIndex = 1;
	m_fAlpha = 1.f;
	m_fTIme = 0.f;
}

void CBronya_Ult_Laser::Start()
{
	__super::Start();

}

void CBronya_Ult_Laser::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Laser::Update()
{
	__super::Update();

}

void CBronya_Ult_Laser::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Ult_Laser::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CBronya_Ult_Laser::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);


}

void CBronya_Ult_Laser::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Laser::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Ult_Laser::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Laser::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Ult_Laser::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CBronya_Ult_Laser::UpdateFrame(_float _frmSpeed)
{
	m_fTIme += GET_PURE_DT;

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
