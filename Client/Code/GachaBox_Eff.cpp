#include "stdafx.h"
#include "..\Header\GachaBox_Eff.h"

_uint CGachaBox_Eff::m_s_uniqueID = 0;


CGachaBox_Eff::CGachaBox_Eff()
{
}


CGachaBox_Eff::~CGachaBox_Eff()
{
	OnDestroy();
}

SP(CGachaBox_Eff) CGachaBox_Eff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGachaBox_Eff) spInstance(new CGachaBox_Eff, Engine::SmartDeleter<CGachaBox_Eff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGachaBox_Eff::MakeClone(void)
{
	SP(CGachaBox_Eff) spClone(new CGachaBox_Eff, Engine::SmartDeleter<CGachaBox_Eff>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CGachaBox_Eff::Awake(void)
{
	__super::Awake();

	m_spMesh->SetMeshData(L"Cloud");
	m_spMesh->SetIsEffectMesh(true);
	m_spTexture->AddTexture(L"GachaBox");
	m_spTexture->AddTexture(L"GachaBox");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskShader);
}

void CGachaBox_Eff::Start(void)
{
	__super::Start();
	Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::UI_ButtonUI);
	Engine::CSoundManager::GetInstance()->StartSound(L"GachaBoxOpen.wav", (_uint)Engine::EChannelID::UI_ButtonUI);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);

	m_fAlpha = 1.f;
}

void CGachaBox_Eff::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CGachaBox_Eff::Update(void)
{
	__super::Update();

	if (this->GetTransform()->GetSize().y >= 1.1f)
	{
		this->SetDeleteThis(true);
	}
	_float _size = 0.5f * GET_DT;

   m_spTransform->AddSize(_float3(_size, _size, _size));

}

void CGachaBox_Eff::LateUpdate(void)
{
	__super::LateUpdate();

}

void CGachaBox_Eff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);

	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_zWriteEnabled", false);
	pEffect->SetBool("g_AlphaTestEnabled", true);
	pEffect->CommitChanges();
}

void CGachaBox_Eff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);


}

void CGachaBox_Eff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);


}

void CGachaBox_Eff::OnDestroy(void)
{
	__super::OnDestroy();

}

void CGachaBox_Eff::OnEnable(void)
{
	__super::OnEnable();

}

void CGachaBox_Eff::OnDisable(void)
{
	__super::OnDisable();

}


void CGachaBox_Eff::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
