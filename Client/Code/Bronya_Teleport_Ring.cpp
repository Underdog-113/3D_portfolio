#include "stdafx.h"
#include "..\Header\Bronya_Teleport_Ring.h"

_uint CBronya_Teleport_Ring::m_s_uniqueID = 0;

CBronya_Teleport_Ring::CBronya_Teleport_Ring()
{
}


CBronya_Teleport_Ring::~CBronya_Teleport_Ring()
{
}

SP(CBronya_Teleport_Ring) CBronya_Teleport_Ring::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Teleport_Ring) spInstance(new CBronya_Teleport_Ring, Engine::SmartDeleter<CBronya_Teleport_Ring>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Teleport_Ring::MakeClone(void)
{
	SP(CBronya_Teleport_Ring) spClone(new CBronya_Teleport_Ring, Engine::SmartDeleter<CBronya_Teleport_Ring>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CBronya_Teleport_Ring::Awake(void)
{
	__super::Awake();
	m_spTexture->AddTexture(L"Global_Ring01_3x3");
	m_spTexture->AddTexture(L"Global_Ring01_3x3");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
}

void CBronya_Teleport_Ring::Start(void)
{
	__super::Start();
	m_fAlphaWidth = 3.f;
	m_fAlphaHeight = 3.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_maxXIndex = 3;
	m_maxYIndex = 2;
	m_fTIme = 0.f;
}

void CBronya_Teleport_Ring::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CBronya_Teleport_Ring::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);

}

void CBronya_Teleport_Ring::LateUpdate(void)
{
	__super::LateUpdate();

	
}

void CBronya_Teleport_Ring::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->SetFloat("gEmissionPow", 0.1f);
	pEffect->CommitChanges();
}

void CBronya_Teleport_Ring::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);


}

void CBronya_Teleport_Ring::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);
}

void CBronya_Teleport_Ring::OnDestroy(void)
{
	__super::OnDestroy();

}

void CBronya_Teleport_Ring::OnEnable(void)
{
	__super::OnEnable();

}

void CBronya_Teleport_Ring::OnDisable(void)
{
	__super::OnDisable();

}

void CBronya_Teleport_Ring::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CBronya_Teleport_Ring::UpdateFrame(_float _frmSpeed)
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
				this->SetDeleteThis(true);
			}
			else
			{
				m_TilingY++;
			}
		}
		m_fTIme = 0;
	}
}