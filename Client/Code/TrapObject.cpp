#include "stdafx.h"
#include "TrapObject.h"


_uint CTrapObject::m_s_uniqueID = 0;
CTrapObject::CTrapObject()
{
}


CTrapObject::~CTrapObject()
{
	OnDestroy();
}

SP(CTrapObject) CTrapObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTrapObject) spInstance(new CTrapObject, Engine::SmartDeleter<CTrapObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTrapObject::MakeClone(void)
{
	SP(CTrapObject) spClone(new CTrapObject, Engine::SmartDeleter<CTrapObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CTrapObject::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Map;
	m_dataID	= UNDEFINED;

	m_addExtra = true;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
}

void CTrapObject::Start(void)
{
	__super::Start();
	
}

void CTrapObject::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CTrapObject::Update(void)
{
	__super::Update();
	
}

void CTrapObject::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CTrapObject::PreRender(LPD3DXEFFECT pEffect)
{
}

void CTrapObject::Render(LPD3DXEFFECT pEffect)
{
}

void CTrapObject::PostRender(LPD3DXEFFECT pEffect)
{
}

void CTrapObject::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CTrapObject::OnEnable(void)
{
	__super::OnEnable();
	
}

void CTrapObject::OnDisable(void)
{
	__super::OnDisable();
	
}

void CTrapObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
