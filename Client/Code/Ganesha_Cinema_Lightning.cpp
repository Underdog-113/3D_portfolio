#include "stdafx.h"
#include "..\Header\Ganesha_Cinema_Lightning.h"

_uint CGanesha_Cinema_Lightning::m_s_uniqueID = 0;

CGanesha_Cinema_Lightning::CGanesha_Cinema_Lightning()
{
}


CGanesha_Cinema_Lightning::~CGanesha_Cinema_Lightning()
{
}

SP(CGanesha_Cinema_Lightning) CGanesha_Cinema_Lightning::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_Cinema_Lightning) spInstance(new CGanesha_Cinema_Lightning, Engine::SmartDeleter<CGanesha_Cinema_Lightning>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_Cinema_Lightning::MakeClone(void)
{
	SP(CGanesha_Cinema_Lightning) spClone(new CGanesha_Cinema_Lightning, Engine::SmartDeleter<CGanesha_Cinema_Lightning>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = false;
	return spClone;
}

void CGanesha_Cinema_Lightning::Awake(void)
{
	__super::Awake();
	m_spTransform->AddSizeX(1.5f);
	m_spTransform->AddSizeY(-0.3f);
	m_spTexture->AddTexture(L"Sign");
	m_spTexture->AddTexture(L"Lighting01");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);

}

void CGanesha_Cinema_Lightning::Start(void)
{
	__super::Start();

	_int irand = rand() % 3;

	switch (irand)
	{
	case 0:
		m_spTexture->ChangeTexture(L"Sign", 0, 0);
		break;
	case 1:
		m_spTexture->ChangeTexture(L"LaserColor", 0, 0);
		break;
	case 2:
		m_spTexture->ChangeTexture(L"FlashBang", 0, 0);
		break;
	default:
		break;
	}

	//if (Engine::GET_CUR_SCENE->GetSceneID() == (_int)ESceneID::Ganesha_Cinema)
		m_spTransform->AddRotationZ(D3DXToRadian(rand() % 90 + 45));


	m_fAlphaWidth = 1.f;
	m_fAlphaHeight = 4.f;
	m_TilingX = 0;
	m_TilingY = 0;

	m_maxXIndex = 1;
	m_maxYIndex = 3;
	m_fTIme = 0.f;
}

void CGanesha_Cinema_Lightning::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CGanesha_Cinema_Lightning::Update(void)
{
	__super::Update();

	UpdateFrame(0.05f);
}

void CGanesha_Cinema_Lightning::LateUpdate(void)
{
	__super::LateUpdate();

}

void CGanesha_Cinema_Lightning::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->SetBool("g_zWriteEnable", true);

	pEffect->CommitChanges();
}

void CGanesha_Cinema_Lightning::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CGanesha_Cinema_Lightning::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CGanesha_Cinema_Lightning::OnDestroy(void)
{
	__super::OnDestroy();

}

void CGanesha_Cinema_Lightning::OnEnable(void)
{
	__super::OnEnable();

}

void CGanesha_Cinema_Lightning::OnDisable(void)
{
	__super::OnDisable();

}

void CGanesha_Cinema_Lightning::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}

void CGanesha_Cinema_Lightning::UpdateFrame(_float _frmSpeed)
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
