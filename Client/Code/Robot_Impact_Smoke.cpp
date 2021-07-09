#include "stdafx.h"
#include "..\Header\Robot_Impact_Smoke.h"

_uint CRobot_Impact_Smoke::m_s_uniqueID = 0;

CRobot_Impact_Smoke::CRobot_Impact_Smoke()
{
}


CRobot_Impact_Smoke::~CRobot_Impact_Smoke()
{
}

SP(CRobot_Impact_Smoke) CRobot_Impact_Smoke::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CRobot_Impact_Smoke) spInstance(new CRobot_Impact_Smoke, Engine::SmartDeleter<CRobot_Impact_Smoke>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CRobot_Impact_Smoke::MakeClone()
{
	SP(CRobot_Impact_Smoke) spClone(new CRobot_Impact_Smoke, Engine::SmartDeleter<CRobot_Impact_Smoke>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CRobot_Impact_Smoke::Awake()
{
	__super::Awake();

}

void CRobot_Impact_Smoke::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
	m_fTime = 0.f;
}

void CRobot_Impact_Smoke::FixedUpdate()
{
	__super::FixedUpdate();

}

void CRobot_Impact_Smoke::Update()
{
	__super::Update();

	if (m_fAlpha <= 0)
	{
		this->SetDeleteThis(true);
	}

	_float3 _size = _float3(0.3f, 0.3f, 0.3f);

	m_fAlpha -= 0.3f * GET_DT;
	m_fTime += 0.2f * GET_DT;
	m_spTransform->AddSize(_size * GET_DT);
}

void CRobot_Impact_Smoke::LateUpdate()
{
	__super::LateUpdate();

}

void CRobot_Impact_Smoke::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", m_fTime);
	pEffect->SetBool("gPlayingAnim", true);
}

void CRobot_Impact_Smoke::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CRobot_Impact_Smoke::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CRobot_Impact_Smoke::OnDestroy()
{
	__super::OnDestroy();

}

void CRobot_Impact_Smoke::OnEnable()
{
	__super::OnEnable();

}

void CRobot_Impact_Smoke::OnDisable()
{
	__super::OnDisable();

}

void CRobot_Impact_Smoke::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
