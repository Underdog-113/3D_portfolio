#include "stdafx.h"
#include "..\Header\Scout_Att_Range_Hold.h"

_uint CScout_Att_Range_Hold::m_s_uniqueID = 0;

CScout_Att_Range_Hold::CScout_Att_Range_Hold()
{
}


CScout_Att_Range_Hold::~CScout_Att_Range_Hold()
{
}

SP(CScout_Att_Range_Hold) CScout_Att_Range_Hold::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CScout_Att_Range_Hold) spInstance(new CScout_Att_Range_Hold, Engine::SmartDeleter<CScout_Att_Range_Hold>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CScout_Att_Range_Hold::MakeClone()
{
	SP(CScout_Att_Range_Hold) spClone(new CScout_Att_Range_Hold, Engine::SmartDeleter<CScout_Att_Range_Hold>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CScout_Att_Range_Hold::Awake()
{
	__super::Awake();
}

void CScout_Att_Range_Hold::Start()
{
	__super::Start();
	m_fAlpha = 0.3f;

}

void CScout_Att_Range_Hold::FixedUpdate()
{
	__super::FixedUpdate();

}

void CScout_Att_Range_Hold::Update()
{
	__super::Update();
}

void CScout_Att_Range_Hold::LateUpdate()
{
	__super::LateUpdate();
}

void CScout_Att_Range_Hold::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("g_bAlphaCtrl", false);
	pEffect->CommitChanges();
}

void CScout_Att_Range_Hold::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CScout_Att_Range_Hold::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CScout_Att_Range_Hold::OnDestroy()
{
	__super::OnDestroy();
}

void CScout_Att_Range_Hold::OnEnable()
{
	__super::OnEnable();
}

void CScout_Att_Range_Hold::OnDisable()
{
	__super::OnDisable();
}

void CScout_Att_Range_Hold::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
