#include "EngineStdafx.h"
#include "DebugObject.h"


USING(Engine)
CDebugObject::CDebugObject()
{
}


CDebugObject::~CDebugObject()
{
}

void CDebugObject::Awake(void)
{
	__super::Awake();
	m_dataID = (_int)EDataID::Object;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
}

void CDebugObject::Start(void)
{
	__super::Start();

	m_spMesh		= GetComponent<Engine::CMeshC>();
	m_spGraphics	= GetComponent<Engine::CGraphicsC>();
	m_spShader		= GetComponent<Engine::CShaderC>();
}

void CDebugObject::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CDebugObject::Update(void)
{
	__super::Update();
	
	nameSibal = m_pOwner->GetName();
	if(m_pOwner)
		m_isEnabled = m_pOwner->GetIsEnabled();
}

void CDebugObject::LateUpdate(void)
{
	__super::LateUpdate();
}

void CDebugObject::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDebugObject::OnEnable(void)
{
	__super::OnEnable();
}

void CDebugObject::OnDisable(void)
{
	__super::OnDisable();
}