#include "stdafx.h"
#include "..\Header\TestParticle.h"

_uint CTestParticle::m_s_uniqueID = 0;

CTestParticle::CTestParticle()
{
}


CTestParticle::~CTestParticle()
{
	OnDestroy();
}

SP(CTestParticle) CTestParticle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTestParticle) spInstance(new CTestParticle, Engine::SmartDeleter<CTestParticle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTestParticle::MakeClone()
{
	SP(CTestParticle) spClone(new CTestParticle, Engine::SmartDeleter<CTestParticle>);

	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spParticleSystem = spClone->GetComponent<Engine::CParticleSystemC>();

	return spClone;
}

void CTestParticle::Awake()
{
	__super::Awake();
	m_spParticleSystem = AddComponent<Engine::CParticleSystemC>();
	m_spParticleSystem->SetvParticlesminPos(_float3(-1.f, -10.f, -1.f));
	m_spParticleSystem->SetvParticlesmaxPos(_float3(1.f, 10.f, 1.f));
	
}

void CTestParticle::Start()
{
	__super::Start();
	m_fLiftTime = 0.f;
}

void CTestParticle::FixedUpdate()
{
	__super::FixedUpdate();
}

void CTestParticle::Update()
{
	__super::Update();

	/*if (m_fLiftTime >= 3.f)
	{
		this->SetDeleteThis(true);
		m_fLiftTime = 0.f;
	}

	m_fLiftTime += GET_DT;*/

}

void CTestParticle::LateUpdate()
{
	__super::LateUpdate();
}

void CTestParticle::PreRender(LPD3DXEFFECT pEffect)
{
	__super::PreRender(pEffect);
}

void CTestParticle::Render(LPD3DXEFFECT pEffect)
{
	__super::Render(pEffect);
}

void CTestParticle::PostRender(LPD3DXEFFECT pEffect)
{
	__super::PostRender(pEffect);
}

void CTestParticle::OnDestroy()
{
	__super::OnDestroy();
}

void CTestParticle::OnEnable()
{
	__super::OnEnable();
}

void CTestParticle::OnDisable()
{
	__super::OnDisable();
}

void CTestParticle::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
