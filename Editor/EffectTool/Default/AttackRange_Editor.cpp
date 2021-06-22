#include "stdafx.h"
#include "AttackRange_Editor.h"

_uint CAttackRange_Editor::m_s_uniqueID = 0;

CAttackRange_Editor::CAttackRange_Editor()
{
}


CAttackRange_Editor::~CAttackRange_Editor()
{
	OnDestroy();
}

SP(CAttackRange_Editor) CAttackRange_Editor::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CAttackRange_Editor) spInstance(new CAttackRange_Editor, Engine::SmartDeleter<CAttackRange_Editor>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CAttackRange_Editor::MakeClone()
{
	SP(CAttackRange_Editor) spClone(new CAttackRange_Editor, Engine::SmartDeleter<CAttackRange_Editor>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetPosition(_float3(0.f, 0.f, 0.f));
	spClone->m_spTransform->SetRotation(_float3(0.f, 0.f, 0.f));
	spClone->GetComponent<Engine::CTransformC>()->SetPositionZ(2.f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CAttackRange_Editor::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CAttackRange_Editor::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CAttackRange_Editor::FixedUpdate()
{
	__super::FixedUpdate();
}

void CAttackRange_Editor::Update()
{
	__super::Update();

	if (Engine::IMKEY_PRESS(KEY_UP))
	{
		m_fAlpha += GET_DT;
	}
	if (Engine::IMKEY_PRESS(KEY_DOWN))
	{
		m_fAlpha -= GET_DT;
	}

}

void CAttackRange_Editor::LateUpdate()
{
	__super::LateUpdate();
}

void CAttackRange_Editor::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CAttackRange_Editor::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

	pEffect->SetFloat("gAlpha", m_fAlpha);
}

void CAttackRange_Editor::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CAttackRange_Editor::OnDestroy()
{
	__super::OnDestroy();
}

void CAttackRange_Editor::OnEnable()
{
	__super::OnEnable();
}

void CAttackRange_Editor::OnDisable()
{
	__super::OnDisable();
}

void CAttackRange_Editor::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
