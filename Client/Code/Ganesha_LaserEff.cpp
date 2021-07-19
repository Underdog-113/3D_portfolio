#include "stdafx.h"
#include "..\Header\Ganesha_LaserEff.h"

_uint CGanesha_LaserEff::m_s_uniqueID = 0;

CGanesha_LaserEff::CGanesha_LaserEff()
{
}


CGanesha_LaserEff::~CGanesha_LaserEff()
{
}

SP(CGanesha_LaserEff) CGanesha_LaserEff::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CGanesha_LaserEff) spInstance(new CGanesha_LaserEff, Engine::SmartDeleter<CGanesha_LaserEff>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CGanesha_LaserEff::MakeClone()
{
	SP(CGanesha_LaserEff) spClone(new CGanesha_LaserEff, Engine::SmartDeleter<CGanesha_LaserEff>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spTransform->SetSizeY(1.5f);
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CGanesha_LaserEff::Awake()
{
	__super::Awake();

}

void CGanesha_LaserEff::Start()
{
	__super::Start();
	m_fAlpha = 1.f;
}

void CGanesha_LaserEff::FixedUpdate()
{
	__super::FixedUpdate();

}

void CGanesha_LaserEff::Update()
{
	__super::Update();
	
	m_fTime += GET_DT;
}

void CGanesha_LaserEff::LateUpdate()
{
	__super::LateUpdate();

}

void CGanesha_LaserEff::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);
	pEffect->SetFloat("gSpeed", -6.f * m_fTime);
	pEffect->SetBool("gPlayingAnim", true);
	pEffect->CommitChanges();
}

void CGanesha_LaserEff::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CGanesha_LaserEff::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CGanesha_LaserEff::OnDestroy()
{
	__super::OnDestroy();

}

void CGanesha_LaserEff::OnEnable()
{
	__super::OnEnable();

}

void CGanesha_LaserEff::OnDisable()
{
	__super::OnDisable();

}

void CGanesha_LaserEff::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
