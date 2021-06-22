#include "stdafx.h"
#include "Kiana_CatPaw_Atk02.h"

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

CKiana_CatPaw_Atk02::CKiana_CatPaw_Atk02()
{
}


CKiana_CatPaw_Atk02::~CKiana_CatPaw_Atk02()
{
	OnDestroy();
}

SP(CKiana_CatPaw_Atk02) CKiana_CatPaw_Atk02::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana_CatPaw_Atk02) spInstance(new CKiana_CatPaw_Atk02, Engine::SmartDeleter<CKiana_CatPaw_Atk02>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana_CatPaw_Atk02::MakeClone(void)
{
	SP(CKiana_CatPaw_Atk02) spClone(new CKiana_CatPaw_Atk02, Engine::SmartDeleter<CKiana_CatPaw_Atk02>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CKiana_CatPaw_Atk02::Awake(void)
{
	__super::Awake();
	m_layerID = (_int)ELayerID::Player;
	m_dataID = (_int)EDataID::Player;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();

}

void CKiana_CatPaw_Atk02::Start(void)
{
	__super::Start();

	m_spMesh->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetReplay(false);

	m_spCollision = AddComponent<Engine::CCollisionC>();

	m_layerID = (_int)ELayerID::Attack;
	m_collisionID = (_int)ECollisionID::PlayerAttack;
	m_spCollider = Engine::CSphereCollider::Create(m_collisionID, 1.f);
	m_spCollider->SetIsTrigger(true);
	m_spCollision->AddCollider(m_spCollider);

	AddComponent<Engine::CDebugC>();

	FindMidBone();
}

void CKiana_CatPaw_Atk02::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana_CatPaw_Atk02::Update(void)
{
	__super::Update();

	m_tempTimer += GET_DT;

	if (m_tempTimer > m_tempDuration)
	{
		m_tempTimer = 0.f;
		SetIsEnabled(false);
	}
	_mat rotMat;
	D3DXMatrixRotationYawPitchRoll(&rotMat, m_spTransform->GetRotation().y, m_spTransform->GetRotation().x, m_spTransform->GetRotation().z);

	_mat combMat = m_pMidBone_Frame->CombinedTransformMatrix;

	combMat = combMat * rotMat;
	_float3 pos = _float3(combMat._41, combMat._42, combMat._43);
	m_spCollider->SetOffset(pos);
}

void CKiana_CatPaw_Atk02::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana_CatPaw_Atk02::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk02::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk02::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana_CatPaw_Atk02::OnDestroy(void)
{
	delete m_pMidBone_World;
	__super::OnDestroy();
}

void CKiana_CatPaw_Atk02::OnEnable(void)
{
	m_spMesh->GetFirstMeshData_Dynamic()->ResetAnimation();
	__super::OnEnable();
}

void CKiana_CatPaw_Atk02::OnDisable(void)
{
	__super::OnDisable();
}

void CKiana_CatPaw_Atk02::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	Engine::CObject* pObject = pCollisionC->GetOwner();

	for (auto& object : m_vCollided)
	{
		if (pObject == object)
			return;
	}

	CValkyrie* pValkyrie = static_cast<CValkyrie*>(m_pOwner);
	CMonster* pMonster = static_cast<CMonster*>(pObject);

	CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo);
}

void CKiana_CatPaw_Atk02::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CKiana_CatPaw_Atk02::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CKiana_CatPaw_Atk02::SetBasicName(void)
{
}

void CKiana_CatPaw_Atk02::FindMidBone(void)
{
	m_pMidBone_Frame = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameByName("Bone003");
	m_pMidBone_BoneOffset = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameOffsetMatrix("Bone003");

	m_pMidBone_World = new _mat;
	*m_pMidBone_World = *m_pMidBone_BoneOffset * m_pMidBone_Frame->CombinedTransformMatrix;
}

void CKiana_CatPaw_Atk02::SetupPaw(CObject * pOwner, _mat * pParentMat, _float radius, HitInfo info)
{
	m_pOwner = pOwner;

	m_pParentMatrix = pParentMat;
	m_hitInfo = info;
}
