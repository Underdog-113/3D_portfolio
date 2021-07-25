#include "stdafx.h"
#include "..\Header\Theresa_Ult_ChargeSmoke.h"


CTheresa_Ult_ChargeSmoke::CTheresa_Ult_ChargeSmoke()
{
}


CTheresa_Ult_ChargeSmoke::~CTheresa_Ult_ChargeSmoke()
{
}

SP(CTheresa_Ult_ChargeSmoke) CTheresa_Ult_ChargeSmoke::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_Ult_ChargeSmoke) spInstance(new CTheresa_Ult_ChargeSmoke, Engine::SmartDeleter<CTheresa_Ult_ChargeSmoke>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_Ult_ChargeSmoke::MakeClone()
{
	SP(CTheresa_Ult_ChargeSmoke) spClone(new CTheresa_Ult_ChargeSmoke, Engine::SmartDeleter<CTheresa_Ult_ChargeSmoke>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CTheresa_Ult_ChargeSmoke::Awake()
{
	__super::Awake();

	m_spMesh->SetMeshData(L"Ult_Smoke");
	m_spTexture->AddTexture(L"fx_snowfield_fog03");
	m_spTexture->AddTexture(L"fx_snowfield_fog03");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
}

void CTheresa_Ult_ChargeSmoke::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
}

void CTheresa_Ult_ChargeSmoke::FixedUpdate()
{
	__super::FixedUpdate();

}

void CTheresa_Ult_ChargeSmoke::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_fAlpha -= 0.5f * GET_PLAYER_DT;
	m_fUVSpeed += GET_PLAYER_DT;
}

void CTheresa_Ult_ChargeSmoke::LateUpdate()
{
	__super::LateUpdate();

}

void CTheresa_Ult_ChargeSmoke::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);
	pEffect->SetBool("gPlayingAnim", true);
	pEffect->CommitChanges();
}

void CTheresa_Ult_ChargeSmoke::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CTheresa_Ult_ChargeSmoke::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CTheresa_Ult_ChargeSmoke::OnDestroy()
{
	__super::OnDestroy();
	m_fAlpha = 1.f;
}

void CTheresa_Ult_ChargeSmoke::OnEnable()
{
	__super::OnEnable();

}

void CTheresa_Ult_ChargeSmoke::OnDisable()
{
	__super::OnDisable();

}

void CTheresa_Ult_ChargeSmoke::SetBasicName()
{
}
