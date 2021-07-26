#include "stdafx.h"
#include "..\Header\Sakura_EvadeSkill_Start.h"

_uint CSakura_EvadeSkill_Start::m_s_uniqueID = 0;

CSakura_EvadeSkill_Start::CSakura_EvadeSkill_Start()
{
}


CSakura_EvadeSkill_Start::~CSakura_EvadeSkill_Start()
{
}

SP(CSakura_EvadeSkill_Start) CSakura_EvadeSkill_Start::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_EvadeSkill_Start) spInstance(new CSakura_EvadeSkill_Start, Engine::SmartDeleter<CSakura_EvadeSkill_Start>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_EvadeSkill_Start::MakeClone()
{
	SP(CSakura_EvadeSkill_Start) spClone(new CSakura_EvadeSkill_Start, Engine::SmartDeleter<CSakura_EvadeSkill_Start>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSakura_EvadeSkill_Start::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Sakura_EvadeSkill_Start");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"Sakura_Dodge_Line");
	m_spTexture->AddTexture(L"Portal_beam_3");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CSakura_EvadeSkill_Start::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fTime = 0.f;
	m_fSpeed = 0.f;
}

void CSakura_EvadeSkill_Start::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_EvadeSkill_Start::Update()
{
	__super::Update();
	m_fTime += GET_PLAYER_DT;
	m_fSpeed += 0.7f * GET_PLAYER_DT;

	if (m_fTime >= 0.7f)
	{
		SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Sakura_EvadeSkill_Loop", true, (_uint)Engine::ELayerID::Effect);
		spObj->GetTransform()->SetPosition(m_spTransform->GetPosition());
		spObj->GetTransform()->SetSize(2.f, 2.f, 2.f);
		this->SetDeleteThis(true);	
		m_fTime = 0.f;
	}
}

void CSakura_EvadeSkill_Start::LateUpdate()
{
	__super::LateUpdate();

}

void CSakura_EvadeSkill_Start::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fSpeed);
	pEffect->SetBool("gPlayingAnim_UpDown", true);
	pEffect->CommitChanges();
}

void CSakura_EvadeSkill_Start::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSakura_EvadeSkill_Start::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSakura_EvadeSkill_Start::OnDestroy()
{
	__super::OnDestroy();

}

void CSakura_EvadeSkill_Start::OnEnable()
{
	__super::OnEnable();

}

void CSakura_EvadeSkill_Start::OnDisable()
{
	__super::OnDisable();

}

void CSakura_EvadeSkill_Start::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
