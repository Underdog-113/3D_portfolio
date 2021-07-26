#include "stdafx.h"
#include "..\Header\KianaBranchSign.h"

_uint CKianaBranchSign::m_s_uniqueID = 0;

CKianaBranchSign::CKianaBranchSign()
{
}


CKianaBranchSign::~CKianaBranchSign()
{
}

SP(CKianaBranchSign) CKianaBranchSign::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKianaBranchSign) spInstance(new CKianaBranchSign, Engine::SmartDeleter<CKianaBranchSign>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKianaBranchSign::MakeClone(void)
{
	SP(CKianaBranchSign) spClone(new CKianaBranchSign, Engine::SmartDeleter<CKianaBranchSign>);

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

void CKianaBranchSign::Awake(void)
{
	__super::Awake();
	m_spTexture->AddTexture(L"YellowFlare");
	m_spTexture->AddTexture(L"YellowFlare");
	m_spShader->AddShader((_int)EShaderID::SoftEffectShader_Glow);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);

}

void CKianaBranchSign::Start(void)
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

void CKianaBranchSign::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CKianaBranchSign::Update(void)
{
	__super::Update();

	if (this->GetTransform()->GetSize().y <= 0)
	{
		this->SetDeleteThis(true);
	}
	float _size = 0.f;
	if (Engine::GET_CUR_SCENE->GetSceneID() == (_int)ESceneID::SupplyScene)
		_size = -3.5f * GET_DT;
	else
		_size = -10.5f * GET_PLAYER_DT;

	this->GetTransform()->AddSize(_float3(_size, _size, _size));
}

void CKianaBranchSign::LateUpdate(void)
{
	__super::LateUpdate();

}

void CKianaBranchSign::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);

	pEffect->SetInt("TilingX", m_TilingX);
	pEffect->SetInt("TilingY", m_TilingY);
	pEffect->SetFloat("gWidth", m_fAlphaWidth);
	pEffect->SetFloat("gHeight", m_fAlphaHeight);
	pEffect->SetFloat("gEmissionPow", 0.15f);
	pEffect->SetBool("g_zWriteEnable", true);
	pEffect->CommitChanges();
}

void CKianaBranchSign::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);

}

void CKianaBranchSign::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);

}

void CKianaBranchSign::OnDestroy(void)
{
	__super::OnDestroy();

}

void CKianaBranchSign::OnEnable(void)
{
	__super::OnEnable();

}

void CKianaBranchSign::OnDisable(void)
{
	__super::OnDisable();

}

void CKianaBranchSign::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
