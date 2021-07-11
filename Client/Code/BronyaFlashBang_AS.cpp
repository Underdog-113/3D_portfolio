#include "stdafx.h"
#include "..\Header\BronyaFlashBang_AS.h"

_uint CBronyaFlashBang_AS::m_s_uniqueID = 0;

CBronyaFlashBang_AS::CBronyaFlashBang_AS()
{
}


CBronyaFlashBang_AS::~CBronyaFlashBang_AS()
{
}

SP(CBronyaFlashBang_AS) CBronyaFlashBang_AS::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronyaFlashBang_AS) spInstance(new CBronyaFlashBang_AS, Engine::SmartDeleter<CBronyaFlashBang_AS>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronyaFlashBang_AS::MakeClone(void)
{
	SP(CBronyaFlashBang_AS) spClone(new CBronyaFlashBang_AS, Engine::SmartDeleter<CBronyaFlashBang_AS>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSize(1.f, 1.f, 1.f);
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spRectTex = spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_bBillboard = true;

	return spClone;
}

void CBronyaFlashBang_AS::Awake(void)
{
	__super::Awake();

}

void CBronyaFlashBang_AS::Start(void)
{
	__super::Start();
	m_fAlphaWidth = 1.f;
	m_fAlphaHeight = 1.f;
	m_TilingX = 0;
	m_TilingY = 0;
	m_maxXIndex = 1;
	m_maxYIndex = 0;
	m_fTIme = 0.f;
}

void CBronyaFlashBang_AS::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CBronyaFlashBang_AS::Update(void)
{
	__super::Update();

	if (this->GetTransform()->GetSize().y >= 3 || this->GetTransform()->GetSize().x >= 3)
	{
		this->SetDeleteThis(true);
	}

	_float _size = 3.5f * GET_DT;
	this->GetTransform()->AddSize(_float3(_size, _size, _size));

}

void CBronyaFlashBang_AS::LateUpdate(void)
{
	__super::LateUpdate();

}

void CBronyaFlashBang_AS::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);

	pEffect->CommitChanges();
}

void CBronyaFlashBang_AS::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CBronyaFlashBang_AS::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CBronyaFlashBang_AS::OnDestroy(void)
{
	__super::OnDestroy();

}

void CBronyaFlashBang_AS::OnEnable(void)
{
	__super::OnEnable();

}

void CBronyaFlashBang_AS::OnDisable(void)
{
	__super::OnDisable();

}

void CBronyaFlashBang_AS::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
