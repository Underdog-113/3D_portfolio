#include "stdafx.h"
#include "MapObject.h"


_uint CMapObject::m_s_uniqueID = 0;

CMapObject::CMapObject()
{
}


CMapObject::~CMapObject()
{
	OnDestroy();
}

SP(CMapObject) CMapObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMapObject) spInstance(new CMapObject, Engine::SmartDeleter<CMapObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMapObject::MakeClone(void)
{
	SP(CMapObject) spClone(new CMapObject, Engine::SmartDeleter<CMapObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CMapObject::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Map;
	m_dataID = UNDEFINED;

	m_addExtra = true;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
}

void CMapObject::Start(void)
{
	__super::Start();

}

void CMapObject::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CMapObject::Update(void)
{
	__super::Update();

}

void CMapObject::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMapObject::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMapObject::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMapObject::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}


void CMapObject::OnDestroy(void)
{
	__super::OnDestroy();

}

void CMapObject::OnEnable(void)
{
	__super::OnEnable();

}

void CMapObject::OnDisable(void)
{
	__super::OnDisable();

}

void CMapObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
