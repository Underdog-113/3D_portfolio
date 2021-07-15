#include "stdafx.h"
#include "..\Header\Kiana_CatPaw_Abs.h"

#pragma region Engine
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "CollisionC.h"
#include "Collider.h"
#pragma endregion

#include "AttackBall.h"
#include "Valkyrie.h"
#include "Monster.h"

CKiana_CatPaw_Abs::CKiana_CatPaw_Abs()
{
}


CKiana_CatPaw_Abs::~CKiana_CatPaw_Abs()
{
}

void CKiana_CatPaw_Abs::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Prop;
	m_dataID = (_int)EDataID::Player;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CKiana_CatPaw_Abs::Start(void)
{
	__super::Start();


	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetReplay(false);

	m_spCollision = AddComponent<Engine::CCollisionC>();

	m_collisionID = (_int)ECollisionID::PlayerAttack;
	auto col = Engine::CSphereCollider::Create(m_collisionID, 1.f);
	m_spCollision->AddCollider(col);
	m_pCollider = (Engine::CSphereCollider*)col.get();
	m_pCollider->SetIsTrigger(true);

	AddComponent<Engine::CDebugC>();

	FindMidBone();
}

void CKiana_CatPaw_Abs::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_CatPaw_Abs::Update(void)
{
	__super::Update();

	m_fDissolveAlpha -= 1.f * GET_PLAYER_DT;

	if (m_fDissolveAlpha < 0.f)
	{
		m_fDissolveAlpha = 1.f;
		SetIsEnabled(false);
	}

	if (!m_isAnimEnd && m_spMesh->GetFirstMeshData_Dynamic()->GetAniTimeline() > 1.f)
	{
		m_isAnimEnd = true;
	}
	
	
	if (!m_isAnimEnd)
	{
		m_spTransform->SetPosition(m_pOwner->GetTransform()->GetPosition());
		m_spTransform->AddPosition(m_pawOffset + m_forwardOffset);
	}

	_mat rotMat;
	D3DXMatrixRotationYawPitchRoll(&rotMat, m_spTransform->GetRotation().y, m_spTransform->GetRotation().x, m_spTransform->GetRotation().z);

	_mat combMat = m_pMidBone_Frame->CombinedTransformMatrix;
	combMat = combMat * rotMat;
	_float3 pos = _float3(combMat._41, combMat._42, combMat._43);
	m_pCollider->SetOffset(pos);
}

void CKiana_CatPaw_Abs::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana_CatPaw_Abs::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
	pEffect->SetFloat("gAlpha", m_fDissolveAlpha);
}

void CKiana_CatPaw_Abs::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Abs::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Abs::OnDestroy(void)
{
	__super::OnDestroy();
}

void CKiana_CatPaw_Abs::OnEnable(void)
{
	__super::OnEnable();

	m_spTransform->SetPosition(m_pOwner->GetTransform()->GetPosition());
	m_spTransform->AddPosition(m_pawOffset + m_forwardOffset);
	m_spTransform->SetRotationY(m_pOwner->GetTransform()->GetRotation().y);

	m_spMesh->GetFirstMeshData_Dynamic()->ResetAnimation();
	m_isAnimEnd = false;
}

void CKiana_CatPaw_Abs::OnDisable(void)
{
	__super::OnDisable();
}

void CKiana_CatPaw_Abs::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	Engine::CObject* pObject = pCollisionC->GetOwner();

	for (auto& object : m_vCollided)
	{
		if (pObject == object)
			return;
	}

	CValkyrie* pValkyrie = static_cast<CValkyrie*>(m_pOwner);
	CMonster* pMonster = static_cast<CMonster*>(pObject);

	_float3 ballPos = m_spTransform->GetPosition();
	_float3 monPos = pMonster->GetTransform()->GetPosition();
	_float3 dir = monPos - ballPos;
	D3DXVec3Normalize(&dir, &dir);
	dir *= m_pCollider->GetRadius();

	CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo, ballPos + dir);
}

void CKiana_CatPaw_Abs::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CKiana_CatPaw_Abs::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CKiana_CatPaw_Abs::SetBasicName()
{
}

void CKiana_CatPaw_Abs::FindMidBone(void)
{
	m_pMidBone_Frame = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameByName("Bone002");
}

void CKiana_CatPaw_Abs::SetupPaw(CObject * pOwner, HitInfo info)
{
	m_pOwner = pOwner;
	m_hitInfo = info;
}
