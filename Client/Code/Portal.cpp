#include "stdafx.h"
#include "Portal.h"

#include "Portal_Plane.h"
#include "PhaseControl.h"

_uint CPortal::m_s_uniqueID = 0;

CPortal::CPortal()
{
}


CPortal::~CPortal()
{
	OnDestroy();
}

SP(CPortal) CPortal::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CPortal) spInstance(new CPortal, Engine::SmartDeleter<CPortal>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CPortal::MakeClone(void)
{
	SP(CPortal) spClone(new CPortal, Engine::SmartDeleter<CPortal>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();

	return spClone;
}

void CPortal::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Map;
	m_dataID = (_int)EDataID::ClientObject;

	m_spMesh		= AddComponent<Engine::CMeshC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
}

void CPortal::Start(void)
{
	__super::Start();
	m_spCollision->GetColliders()[0]->SetIsTrigger(true);
	m_vEffect = std::dynamic_pointer_cast<CPortal_Plane>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Portal_Plane", true));
	m_vEffect->GetTransform()->SetPosition(m_spTransform->GetPosition());
	m_vEffect->GetTransform()->AddPositionY(-0.2f);
	m_spGraphics->SetIsEnabled(false);

	m_isEnter = false;
}

void CPortal::FixedUpdate(void)
{
	__super::FixedUpdate();
	
}

void CPortal::Update(void)
{
	__super::Update();
	
}

void CPortal::LateUpdate(void)
{
	__super::LateUpdate();
	
}

void CPortal::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CPortal::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CPortal::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CPortal::OnDestroy(void)
{
	__super::OnDestroy();
}

void CPortal::OnEnable(void)
{
	__super::OnEnable();
}

void CPortal::OnDisable(void)
{
	__super::OnDisable();
}

void CPortal::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	//pCollisionC->GetOwner()->GetTransform()->SetPosition(m_destPos);
	if (!m_isEnter)
	{
		m_isEnter = true;
		CStageControlTower::GetInstance()->GetPhaseControl()->IncreasePhase();
	}
}

void CPortal::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CPortal::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CPortal::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
