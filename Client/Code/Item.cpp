#include "stdafx.h"
#include "Item.h"

_uint CItem::m_s_uniqueID = 0;
CItem::CItem()
{
}


CItem::~CItem()
{
	OnDestroy();
}

SP(CItem) CItem::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CItem) spInstance(new CItem, Engine::SmartDeleter<CItem>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CItem::MakeClone(void)
{
	SP(CItem) spClone(new CItem, Engine::SmartDeleter<CItem>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();

	return spClone;
}

void CItem::Awake(void)
{
	__super::Awake();
	
	m_layerID	= (_int)Engine::ELayerID::Decoration;
	m_dataID	= UNDEFINED;

	m_addExtra = true;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spRigidBody	= AddComponent<Engine::CRigidBodyC>();
}

void CItem::Start(void)
{
	__super::Start();
	
}

void CItem::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CItem::Update(void)
{
	__super::Update();
	
}

void CItem::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CItem::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CItem::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CItem::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CItem::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CItem::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CItem::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CItem::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CItem::OnEnable(void)
{
	__super::OnEnable();
	
}

void CItem::OnDisable(void)
{
	__super::OnDisable();
	
}

void CItem::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
