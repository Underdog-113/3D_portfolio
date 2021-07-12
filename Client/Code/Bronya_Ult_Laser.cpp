#include "stdafx.h"
#include "..\Header\Bronya_Ult_Laser.h"

_uint CBronya_Ult_Laser::m_s_uniqueID = 0;

CBronya_Ult_Laser::CBronya_Ult_Laser()
{
}


CBronya_Ult_Laser::~CBronya_Ult_Laser()
{
}

SP(CBronya_Ult_Laser) CBronya_Ult_Laser::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Ult_Laser) spInstance(new CBronya_Ult_Laser, Engine::SmartDeleter<CBronya_Ult_Laser>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Ult_Laser::MakeClone()
{
	SP(CBronya_Ult_Laser) spClone(new CBronya_Ult_Laser, Engine::SmartDeleter<CBronya_Ult_Laser>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Ult_Laser::Awake()
{
	__super::Awake();
}

void CBronya_Ult_Laser::Start()
{
	__super::Start();

	m_fAlpha = 1.f;
	m_fTime = 0.f;
}

void CBronya_Ult_Laser::FixedUpdate()
{
	__super::FixedUpdate();

}

void CBronya_Ult_Laser::Update()
{
	__super::Update();

}

void CBronya_Ult_Laser::LateUpdate()
{
	__super::LateUpdate();

}

void CBronya_Ult_Laser::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fAlpha);

	pEffect->CommitChanges();
}

void CBronya_Ult_Laser::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);

}

void CBronya_Ult_Laser::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);

}

void CBronya_Ult_Laser::OnDestroy()
{
	__super::OnDestroy();

}

void CBronya_Ult_Laser::OnEnable()
{
	__super::OnEnable();

}

void CBronya_Ult_Laser::OnDisable()
{
	__super::OnDisable();

}

void CBronya_Ult_Laser::SetBasicName()
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);

}
