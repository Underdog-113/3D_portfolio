#include "EngineStdafx.h"
#include "DebugCollider.h"

#include "AabbCollider.h"
#include "SphereCollider.h"

USING(Engine)
_uint CDebugCollider::m_s_uniqueID = 0;

CDebugCollider::CDebugCollider()
{
}


CDebugCollider::~CDebugCollider()
{
	OnDestroy();
}

SP(CDebugCollider) CDebugCollider::Create(_bool isStatic, CScene* pScene)
{
	SP(CDebugCollider) spInstance(new CDebugCollider, Engine::SmartDeleter<CDebugCollider>);
	spInstance->SetIsStatic(true);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CDebugCollider::MakeClone(void)
{
	SP(CDebugCollider) spClone(new CDebugCollider, Engine::SmartDeleter<CDebugCollider>);
	CObject::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	return spClone;
}

void CDebugCollider::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::Debug;
}

void CDebugCollider::Start(void)
{
	__super::Start();


	switch (m_pCollider->GetColliderType())
	{
	case (_int)EColliderType::Ray:
	{
		m_spMesh->SetMeshData(L"Cube");
		CRayCollider* pRay = static_cast<CRayCollider*>(m_pCollider);
		m_spTransform->AddPosition(pRay->GetDirection() * pRay->GetLength() / 2.f);
		m_spTransform->SetForward(pRay->GetDirection());
		m_spTransform->SetSize(0.01f, 0.01f, pRay->GetLength());
		break;
	}

	case (_int)EColliderType::Sphere:
	{
		m_spMesh->SetMeshData(L"Sphere");

		CSphereCollider* pShpere = static_cast<CSphereCollider*>(m_pCollider);
		m_spTransform->SetSize(pShpere->GetRadius() * 2, pShpere->GetRadius() * 2, pShpere->GetRadius() * 2);
		break;
	}

	case (_int)EColliderType::AABB:
	{
		m_spMesh->SetMeshData(L"Cube");
		CAabbCollider* pAabb = static_cast<CAabbCollider*>(m_pCollider);
		m_spTransform->SetSize(pAabb->GetSize());
		break;
	}

	case (_int)EColliderType::OBB:
	{
		m_spMesh->SetMeshData(L"Cube");
		CObbCollider* pObb = static_cast<CObbCollider*>(m_pCollider);
		m_spTransform->SetRotation(m_pCollider->GetOwner()->GetOwner()->GetTransform()->GetRotation() + pObb->GetRotOffset());
		m_spTransform->SetSize(pObb->GetSize());
		break;
	}

	default:
		break;
	}

	m_offset = m_pCollider->GetOffset();
}

void CDebugCollider::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CDebugCollider::Update(void)
{
	__super::Update();
}

void CDebugCollider::LateUpdate(void)
{
	m_spTransform->SetPosition(m_pOwner->GetTransform()->GetLastPosition() + m_pCollider->GetOffset());
	
	switch (m_pCollider->GetColliderType())
	{
	case (_int)EColliderType::Ray:
	{
		CRayCollider* pRay = static_cast<CRayCollider*>(m_pCollider);
		m_spTransform->AddPosition(pRay->GetDirection() * pRay->GetLength() / 2.f);
		m_spTransform->SetForward(pRay->GetDirection());
		m_spTransform->SetSize(0.01f, 0.01f, pRay->GetLength());
		break;
	}

	case (_int)EColliderType::Sphere:
	{
		CSphereCollider* pShpere = static_cast<CSphereCollider*>(m_pCollider);
		m_spTransform->SetSize(pShpere->GetRadius() * 2, pShpere->GetRadius() * 2, pShpere->GetRadius() * 2);
		break;
	}

	case (_int)EColliderType::AABB:
	{
		CAabbCollider* pAabb = static_cast<CAabbCollider*>(m_pCollider);
		m_spTransform->SetSize(pAabb->GetSize());
		break;
	}

	case (_int)EColliderType::OBB:
	{
		CObbCollider* pObb = static_cast<CObbCollider*>(m_pCollider);
		m_spTransform->SetRotation(m_pCollider->GetOwner()->GetTransform()->GetRotation() + pObb->GetRotOffset());
		m_spTransform->SetSize(pObb->GetSize());
		break;
	}

	default:
		break;
	}

	__super::LateUpdate();
}

void CDebugCollider::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CDebugCollider::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CDebugCollider::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CDebugCollider::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDebugCollider::OnEnable(void)
{
	__super::OnEnable();
}

void CDebugCollider::OnDisable(void)
{
	__super::OnDisable();
}

void CDebugCollider::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
