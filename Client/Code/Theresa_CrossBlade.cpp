#include "stdafx.h"
#include "Theresa_CrossBlade.h"

#include "MeshC.h"

CTheresa_CrossBlade::CTheresa_CrossBlade()
{
}


CTheresa_CrossBlade::~CTheresa_CrossBlade()
{
	OnDestroy();
}

SP(CTheresa_CrossBlade) CTheresa_CrossBlade::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa_CrossBlade) spInstance(new CTheresa_CrossBlade, Engine::SmartDeleter<CTheresa_CrossBlade>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa_CrossBlade::MakeClone(void)
{
	SP(CTheresa_CrossBlade) spClone(new CTheresa_CrossBlade, Engine::SmartDeleter<CTheresa_CrossBlade>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	return spClone;
}

void CTheresa_CrossBlade::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::Player;
	m_dataID = (_int)EDataID::Player;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CTheresa_CrossBlade::Start(void)
{
	__super::Start();

	m_layerID = (_int)ELayerID::Attack;
}

void CTheresa_CrossBlade::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTheresa_CrossBlade::Update(void)
{
	__super::Update();
}

void CTheresa_CrossBlade::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTheresa_CrossBlade::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CTheresa_CrossBlade::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa_CrossBlade::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CTheresa_CrossBlade::OnDestroy(void)
{
	__super::OnDestroy();
}

void CTheresa_CrossBlade::OnEnable(void)
{
	__super::OnEnable();
}

void CTheresa_CrossBlade::OnDisable(void)
{
	__super::OnDisable();
}

void CTheresa_CrossBlade::SetBasicName(void)
{
}
