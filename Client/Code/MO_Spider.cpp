#include "stdafx.h"
#include "..\Header\MO_Spider.h"

_uint CMO_Spider::m_s_uniqueID = 0;

CMO_Spider::CMO_Spider()
{
}

SP(Engine::CObject) CMO_Spider::MakeClone(void)
{
	SP(CMO_Spider) spClone(new CMO_Spider, Engine::SmartDeleter<CMO_Spider>);

	__super::InitClone(spClone);

	spClone->m_spTransform = GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = GetComponent<Engine::CMeshC>();
	spClone->m_spTexture = GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics = GetComponent<Engine::CGraphicsC>();
	spClone->m_spFSM = GetComponent<FSM_SpiderC>();
	return spClone;
}

void CMO_Spider::Awake(void)
{
	__super::Awake();	

	m_layerID = (_int)ELayerID::Enemy;
	m_dataID =  (_int)EDataID::Enemy;

	m_spMesh = AddComponent<Engine::CMeshC>();	
	m_spMesh->SetInitTex(true);
	m_spTexture  = AddComponent<Engine::CTextureC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spFSM		 = AddComponent<FSM_SpiderC>();



}

void CMO_Spider::Start(void)
{
	__super::Start();
	
}

void CMO_Spider::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Spider::Update(void)
{
	__super::Update();
}

void CMO_Spider::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Spider::PreRender(void)
{
	m_spComponentToRender->PreRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Spider::Render(void)
{
	m_spComponentToRender->Render(GetComponent<Engine::CGraphicsC>());
}

void CMO_Spider::PostRender(void)
{
	m_spComponentToRender->PostRender(GetComponent<Engine::CGraphicsC>());
}

void CMO_Spider::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Spider::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Spider::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Spider::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Spider::Chase_Target(_float DeltaTime)
{
}

SP(CMO_Spider) CMO_Spider::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Spider) spInstance(new CMO_Spider, Engine::SmartDeleter<CMO_Spider>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}