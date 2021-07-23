#include "stdafx.h"
#include "..\Header\Sakura_EvadeSkill_Loop.h"

_uint CSakura_EvadeSkill_Loop::m_s_uniqueID = 0;

CSakura_EvadeSkill_Loop::CSakura_EvadeSkill_Loop()
{
}


CSakura_EvadeSkill_Loop::~CSakura_EvadeSkill_Loop()
{
}

SP(CSakura_EvadeSkill_Loop) CSakura_EvadeSkill_Loop::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_EvadeSkill_Loop) spInstance(new CSakura_EvadeSkill_Loop, Engine::SmartDeleter<CSakura_EvadeSkill_Loop>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_EvadeSkill_Loop::MakeClone()
{
	SP(CSakura_EvadeSkill_Loop) spClone(new CSakura_EvadeSkill_Loop, Engine::SmartDeleter<CSakura_EvadeSkill_Loop>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSakura_EvadeSkill_Loop::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Sakura_EvadeSkill");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Sakura_Dodge_Line");
	m_spTexture->AddTexture(L"Portal_beam_3");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CSakura_EvadeSkill_Loop::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fTime = 0.f;
	m_fSpeed = 0.f;
}

void CSakura_EvadeSkill_Loop::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_EvadeSkill_Loop::Update()
{
	__super::Update();
	m_fTime += GET_DT;
	m_fSpeed += 3.3f * GET_DT;

	if (m_fTime >= 0.7f)
	{
		this->SetDeleteThis(true);
		m_fTime = 0.f;
	}
}

void CSakura_EvadeSkill_Loop::LateUpdate()
{
	__super::LateUpdate();

}

void CSakura_EvadeSkill_Loop::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fSpeed);
	pEffect->SetBool("gPlayingAnim_UpDown", true);
	pEffect->CommitChanges();
}

void CSakura_EvadeSkill_Loop::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSakura_EvadeSkill_Loop::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSakura_EvadeSkill_Loop::OnDestroy()
{
	__super::OnDestroy();

}

void CSakura_EvadeSkill_Loop::OnEnable()
{
	__super::OnEnable();

}

void CSakura_EvadeSkill_Loop::OnDisable()
{
	__super::OnDisable();

}

void CSakura_EvadeSkill_Loop::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
