#include "stdafx.h"
#include "BronyaBullet.h"


CBronyaBullet::CBronyaBullet()
{
}


CBronyaBullet::~CBronyaBullet()
{
	OnDestroy();
}

SP(CBronyaBullet) CBronyaBullet::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CBronyaBullet) spInstance(new CBronyaBullet, Engine::SmartDeleter<CBronyaBullet>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CBronyaBullet::MakeClone(void)
{
	SP(CBronyaBullet) spClone(new CBronyaBullet, Engine::SmartDeleter<CBronyaBullet>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CBronyaBullet::Awake(void)
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

void CBronyaBullet::Start(void)
{
	__super::Start();
}

void CBronyaBullet::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CBronyaBullet::Update(void)
{
	__super::Update();
}

void CBronyaBullet::LateUpdate(void)
{
	__super::LateUpdate();

	//m_spTransform->SetLastWorldMatrix(*m_pParentMatrix);
}

void CBronyaBullet::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronyaBullet::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CBronyaBullet::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CBronyaBullet::OnDestroy(void)
{
	__super::OnDestroy();
}
void CBronyaBullet::OnEnable(void)
{
	__super::OnEnable();
}

void CBronyaBullet::OnDisable(void)
{
	__super::OnDisable();
}

void CBronyaBullet::SetBasicName(void)
{
}
