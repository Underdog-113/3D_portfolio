#include "stdafx.h"
#include "Bronya_Weapon.h"


CBronya_Weapon::CBronya_Weapon()
{
}


CBronya_Weapon::~CBronya_Weapon()
{
	OnDestroy();
}

SP(CBronya_Weapon) CBronya_Weapon::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronya_Weapon) spInstance(new CBronya_Weapon, Engine::SmartDeleter<CBronya_Weapon>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronya_Weapon::MakeClone(void)
{
	SP(CBronya_Weapon) spClone(new CBronya_Weapon, Engine::SmartDeleter<CBronya_Weapon>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronya_Weapon::Awake(void)
{
	__super::Awake();
	m_dataID = (_int)EDataID::Enemy;
	m_layerID = (_int)ELayerID::Prop;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
}

void CBronya_Weapon::Start(void)
{
	__super::Start();
}

void CBronya_Weapon::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBronya_Weapon::Update(void)
{
	__super::Update();
}

void CBronya_Weapon::LateUpdate(void)
{
	__super::LateUpdate();

	//m_spTransform->SetLastWorldMatrix(*m_pParentMatrix);
}

void CBronya_Weapon::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronya_Weapon::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CBronya_Weapon::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronya_Weapon::OnDestroy(void)
{
	__super::OnDestroy();
}
void CBronya_Weapon::OnEnable(void)
{
	__super::OnEnable();
}

void CBronya_Weapon::OnDisable(void)
{
	__super::OnDisable();
}

void CBronya_Weapon::SetBasicName(void)
{
}
