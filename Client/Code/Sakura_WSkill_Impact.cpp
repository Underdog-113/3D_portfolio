#include "stdafx.h"
#include "..\Header\Sakura_WSkill_Impact.h"

_uint CSakura_WSkill_Impact::m_s_uniqueID = 0;

CSakura_WSkill_Impact::CSakura_WSkill_Impact()
{
}


CSakura_WSkill_Impact::~CSakura_WSkill_Impact()
{
}

SP(CSakura_WSkill_Impact) CSakura_WSkill_Impact::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CSakura_WSkill_Impact) spInstance(new CSakura_WSkill_Impact, Engine::SmartDeleter<CSakura_WSkill_Impact>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CSakura_WSkill_Impact::MakeClone()
{
	SP(CSakura_WSkill_Impact) spClone(new CSakura_WSkill_Impact, Engine::SmartDeleter<CSakura_WSkill_Impact>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CSakura_WSkill_Impact::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Bronya_Impact");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Wave01");
	m_spTexture->AddTexture(L"Wave01");
	m_spShader->AddShader((_int)EShaderID::DissolveShader);

}

void CSakura_WSkill_Impact::Start()
{
	__super::Start();

	SP(Engine::CObject) spSmoke = Engine::GET_CUR_SCENE->ADD_CLONE(L"Sakura_WSkill_Smoke", true);
	spSmoke->GetTransform()->SetPosition(this->GetTransform()->GetPosition());

	m_fAlpha = 1.f;

}

void CSakura_WSkill_Impact::FixedUpdate()
{
	__super::FixedUpdate();

}

void CSakura_WSkill_Impact::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	m_spTransform->AddSizeX(0.1f * GET_PLAYER_DT);
	m_spTransform->AddSizeY(0.5f * GET_PLAYER_DT);
	m_spTransform->AddSizeZ(0.1f * GET_PLAYER_DT);

	m_fAlpha -= 2.5f * GET_PLAYER_DT;
}

void CSakura_WSkill_Impact::LateUpdate()
{
	__super::LateUpdate();

}

void CSakura_WSkill_Impact::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gTrailCheck", false);
	pEffect->CommitChanges();
}

void CSakura_WSkill_Impact::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CSakura_WSkill_Impact::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CSakura_WSkill_Impact::OnDestroy()
{
	__super::OnDestroy();

}

void CSakura_WSkill_Impact::OnEnable()
{
	__super::OnEnable();

}

void CSakura_WSkill_Impact::OnDisable()
{
	__super::OnDisable();

}

void CSakura_WSkill_Impact::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
