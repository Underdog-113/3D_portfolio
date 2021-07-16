#include "stdafx.h"
#include "..\Header\Portal_Beam.h"

_uint CPortal_Beam::m_s_uniqueID = 0;

CPortal_Beam::CPortal_Beam()
{
}


CPortal_Beam::~CPortal_Beam()
{
}

SP(CPortal_Beam) CPortal_Beam::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CPortal_Beam) spInstance(new CPortal_Beam, Engine::SmartDeleter<CPortal_Beam>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPortal_Beam::MakeClone()
{
	SP(CPortal_Beam) spClone(new CPortal_Beam, Engine::SmartDeleter<CPortal_Beam>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CPortal_Beam::Awake()
{
	__super::Awake();
	_float _size = 0.01f;
	m_spTransform->SetSize(_float3(0.02f, 0.02f, 0.005f));
	m_spTransform->AddRotationX(D3DXToRadian(90));
}

void CPortal_Beam::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fUVSpeed = 0.f;
}

void CPortal_Beam::FixedUpdate()
{
	__super::FixedUpdate();

}

void CPortal_Beam::Update()
{
	__super::Update();

	m_fAlpha -= 2.3f * GET_DT;

	if (m_fAlpha <= 0.f)
	{
		this->SetDeleteThis(true);
	}

	m_spTransform->AddPositionY(0.5f * GET_DT);

}

void CPortal_Beam::LateUpdate()
{
	__super::LateUpdate();

}

void CPortal_Beam::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->SetBool("gPlayingAnim_UpDown", false);
	pEffect->SetBool("g_zWriteEnabled", false);

	pEffect->CommitChanges();
}

void CPortal_Beam::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CPortal_Beam::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CPortal_Beam::OnDestroy()
{
	__super::OnDestroy();

}

void CPortal_Beam::OnEnable()
{
	__super::OnEnable();

}

void CPortal_Beam::OnDisable()
{
	__super::OnDisable();

}

void CPortal_Beam::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
