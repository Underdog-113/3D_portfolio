#include "EngineStdafx.h"
#include "DecoObject.h"


USING(Engine)
_uint CDecoObject::m_s_uniqueID = 0;
CDecoObject::CDecoObject()
{
}


CDecoObject::~CDecoObject()
{
	OnDestroy();
}

SP(CDecoObject) CDecoObject::Create(_bool isStatic, CScene * pScene)
{
	SP(CDecoObject) spInstance(new CDecoObject, SmartDeleter<CDecoObject>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(CObject) CDecoObject::MakeClone(void)
{
	SP(CDecoObject) spClone(new CDecoObject, SmartDeleter<CDecoObject>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<CGraphicsC>();

	return spClone;
}

void CDecoObject::Awake(void)
{
	__super::Awake();

	m_layerID	= (_int)ELayerID::Decoration;
	m_dataID	= UNDEFINED;

	m_spMesh		= AddComponent<CMeshC>();
	m_spTexture		= AddComponent<CTextureC>();
	m_spGraphics	= AddComponent<CGraphicsC>();
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
