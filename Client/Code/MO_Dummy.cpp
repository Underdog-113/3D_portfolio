#include "stdafx.h"
#include "..\Header\MO_Dummy.h"

#include "FSM_SpiderC.h"
#include "FSMDefine_Spider.h"

#include "DynamicMeshData.h"

_uint CMO_Dummy::m_s_uniqueID = 0;

CMO_Dummy::CMO_Dummy()
{
}

CMO_Dummy::~CMO_Dummy()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Dummy::MakeClone(void)
{
	SP(CMO_Dummy) spClone(new CMO_Dummy, Engine::SmartDeleter<CMO_Dummy>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	//spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	//spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	//spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();
		
	return spClone;
}

void CMO_Dummy::Awake(void)
{
	__super::Awake();
		
}

void CMO_Dummy::Start(void)
{
	__super::Start();

	m_spRigidBody = AddComponent<Engine::CRigidBodyC>();
	m_spCollision = AddComponent<Engine::CCollisionC>();
	m_spDebug = AddComponent<Engine::CDebugC>();

	m_spCollision->
		AddCollider(Engine::CRayCollider::Create(
		(_int)ECollisionID::FloorRay,
			_float3(0.f,1.f,0.f),
			_float3(0.f,-1.f,0.f),
			1.f));

	m_spCollision->
		AddCollider(Engine::CSphereCollider::Create(
		(_int)ECollisionID::EnemyHitBox,
			0.5f,
			_float3(0.f,0.5f,0.f)));

	m_spTransform->SetSize(2.f, 2.f, 2.f);
	m_spTransform->SetRotationY(D3DXToRadian(90));

	//m_spMesh->OnRootMotion();
}

void CMO_Dummy::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Dummy::Update(void)
{
	__super::Update();
}

void CMO_Dummy::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMO_Dummy::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CMO_Dummy::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CMO_Dummy::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CMO_Dummy::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CMO_Dummy::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CMO_Dummy::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Dummy::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMO_Dummy::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Dummy::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Dummy::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Dummy::ApplyHitInfo(HitInfo info)
{
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage:
		break;
	case HitInfo::Str_Low:
		m_spMesh->GetFirstMeshData_Dynamic()->ChangeAniSet(Index_Hit_L);
		break;
	case HitInfo::Str_High:
		m_spMesh->GetFirstMeshData_Dynamic()->ChangeAniSet(Index_Hit_H);
		break;
	case HitInfo::Str_Airborne:
		break;
	}

	// stateffect
}

void CMO_Dummy::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0; D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}


SP(CMO_Dummy) CMO_Dummy::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Dummy) spInstance(new CMO_Dummy, Engine::SmartDeleter<CMO_Dummy>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}