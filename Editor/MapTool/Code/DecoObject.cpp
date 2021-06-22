#include "stdafx.h"
#include "DecoObject.h"


_uint CDecoObject::m_s_uniqueID = 0;
CDecoObject::CDecoObject()
{
}


CDecoObject::~CDecoObject()
{
	OnDestroy();
}

SP(CDecoObject) CDecoObject::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CDecoObject) spInstance(new CDecoObject, Engine::SmartDeleter<CDecoObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CDecoObject::MakeClone(void)
{
	SP(CDecoObject) spClone(new CDecoObject, Engine::SmartDeleter<CDecoObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();

	return spClone;
}

void CDecoObject::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)Engine::ELayerID::Decoration;
	m_dataID	= UNDEFINED;

	m_addExtra = true;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
}

void CDecoObject::Start(void)
{
	__super::Start();
	
}

void CDecoObject::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CDecoObject::Update(void)
{
	__super::Update();
	
}

void CDecoObject::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CDecoObject::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}


void CDecoObject::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CDecoObject::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CDecoObject::OnDestroy(void)
{
	__super::OnDestroy();
	
}

void CDecoObject::OnEnable(void)
{
	__super::OnEnable();
	
}

void CDecoObject::OnDisable(void)
{
	__super::OnDisable();
	
}

void CDecoObject::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
