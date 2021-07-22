#include "stdafx.h"
#include "..\Header\Robot_Plane.h"

_uint CRobot_Plane::m_s_uniqueID = 0;

CRobot_Plane::CRobot_Plane()
{
}


CRobot_Plane::~CRobot_Plane()
{
}

SP(CRobot_Plane) CRobot_Plane::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CRobot_Plane) spInstance(new CRobot_Plane, Engine::SmartDeleter<CRobot_Plane>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CRobot_Plane::MakeClone()
{
	SP(CRobot_Plane) spClone(new CRobot_Plane, Engine::SmartDeleter<CRobot_Plane>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CRobot_Plane::Awake()
{
	__super::Awake();
	m_spMesh->SetMeshData(L"Robot_Plane");
	m_spMesh->SetIsEffectMesh(true);
	m_spGraphics->SetRenderID((_int)Engine::ERenderID::Effect);
	m_spTexture->AddTexture(L"SkyColor");
	m_spTexture->AddTexture(L"SkyColor");
	m_spShader->AddShader((_int)EShaderID::AlphaMaskGlowShader);
}

void CRobot_Plane::Start()
{
	__super::Start();

}

void CRobot_Plane::FixedUpdate()
{
	__super::FixedUpdate();

}

void CRobot_Plane::Update()
{
	__super::Update();

	m_spTransform->AddRotationY(0.5f * GET_DT);

}

void CRobot_Plane::LateUpdate()
{
	__super::LateUpdate();

}

void CRobot_Plane::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", 1.f);
}

void CRobot_Plane::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CRobot_Plane::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CRobot_Plane::OnDestroy()
{
	__super::OnDestroy();

}

void CRobot_Plane::OnEnable()
{
	__super::OnEnable();

}

void CRobot_Plane::OnDisable()
{
	__super::OnDisable();

}

void CRobot_Plane::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
