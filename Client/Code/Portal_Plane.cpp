#include "stdafx.h"
#include "..\Header\Portal_Plane.h"

_uint CPortal_Plane::m_s_uniqueID = 0;

CPortal_Plane::CPortal_Plane()
{
}


CPortal_Plane::~CPortal_Plane()
{
	OnDestroy();
}

SP(CPortal_Plane) CPortal_Plane::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CPortal_Plane) spInstance(new CPortal_Plane, Engine::SmartDeleter<CPortal_Plane>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPortal_Plane::MakeClone()
{
	SP(CPortal_Plane) spClone(new CPortal_Plane, Engine::SmartDeleter<CPortal_Plane>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CPortal_Plane::Awake()
{
	__super::Awake();
	_float _size = 0.05f;
	m_spTransform->SetSize(_size, _size, _size);

}

void CPortal_Plane::Start()
{
	__super::Start();

	m_spPortalBlue = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Portal_Blue", true, (_uint)Engine::ELayerID::Effect);
	m_spPortalBlue->GetTransform()->SetPosition(m_spTransform->GetPosition());
	m_spPortalBlue->GetTransform()->AddPositionY(0.01f);

	m_spPortalCircle = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Portal_Circle", true, (_uint)Engine::ELayerID::Effect);
	m_spPortalCircle->GetTransform()->SetPosition(m_spTransform->GetPosition());
	m_spPortalCircle->GetTransform()->SetPosition(m_spTransform->GetPosition());
	m_spPortalCircle->GetTransform()->AddPositionY(0.01f);


	m_fAlpha = 1.f;
}

void CPortal_Plane::FixedUpdate()
{
	__super::FixedUpdate();

}

void CPortal_Plane::Update()
{
	__super::Update();

	m_spTransform->AddRotation(m_spTransform->GetUp() * GET_DT * 10.f);
}

void CPortal_Plane::LateUpdate()
{
	__super::LateUpdate();

}

void CPortal_Plane::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fUVSpeed);
	pEffect->SetBool("gPlayingAnim", false);
	pEffect->SetBool("g_zWriteEnabled", true);

	pEffect->CommitChanges();
}

void CPortal_Plane::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CPortal_Plane::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CPortal_Plane::OnDestroy()
{
	__super::OnDestroy();

	if(m_spPortalBlue != nullptr)
		m_spPortalBlue->SetDeleteThis(true);

	if(m_spPortalCircle != nullptr)
		m_spPortalCircle->SetDeleteThis(true);

}

void CPortal_Plane::OnEnable()
{
	__super::OnEnable();

}

void CPortal_Plane::OnDisable()
{
	__super::OnDisable();

}

void CPortal_Plane::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
