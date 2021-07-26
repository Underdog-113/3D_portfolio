#include "stdafx.h"
#include "..\Header\Ganesha_Charge_Eff.h"

#include "MB_Ganesha.h"

_uint CGanesha_Charge_Eff::m_s_uniqueID = 0;

CGanesha_Charge_Eff::CGanesha_Charge_Eff()
{
}


CGanesha_Charge_Eff::~CGanesha_Charge_Eff()
{
}

SP(CGanesha_Charge_Eff) CGanesha_Charge_Eff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_Charge_Eff) spInstance(new CGanesha_Charge_Eff, Engine::SmartDeleter<CGanesha_Charge_Eff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_Charge_Eff::MakeClone()
{
	SP(CGanesha_Charge_Eff) spClone(new CGanesha_Charge_Eff, Engine::SmartDeleter<CGanesha_Charge_Eff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CGanesha_Charge_Eff::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Ganesha_Charge");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Lancer_Eff_Color");
	m_spTexture->AddTexture(L"Ability_aura");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);

}

void CGanesha_Charge_Eff::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CGanesha_Charge_Eff::FixedUpdate()
{
	__super::FixedUpdate();

}

void CGanesha_Charge_Eff::Update()
{
	__super::Update();

	m_fTime += 3.f *  GET_DT;

	// °¡³×»þ Á×À¸¸é ÀÌÆåÆ® Áö¿ö
	if (nullptr != m_pOwner)
	{
		if (true == m_pOwner->GetComponent<CPatternMachineC>()->GetOnDie())
		{
			m_deleteThis = true;
			m_pOwner = nullptr;
			return;
		}
	}
}

void CGanesha_Charge_Eff::LateUpdate()
{
	__super::LateUpdate();

}

void CGanesha_Charge_Eff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fTime);
	pEffect->SetBool("gPlayingAnim", true);
}

void CGanesha_Charge_Eff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CGanesha_Charge_Eff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CGanesha_Charge_Eff::OnDestroy()
{
	__super::OnDestroy();

}

void CGanesha_Charge_Eff::OnEnable()
{
	__super::OnEnable();

}

void CGanesha_Charge_Eff::OnDisable()
{
	__super::OnDisable();

}

void CGanesha_Charge_Eff::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
