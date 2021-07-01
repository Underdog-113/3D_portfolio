#include "stdafx.h"
#include "AttackBox.h"
#include "Valkyrie.h"
#include "Monster.h"
#include "StageControlTower.h"


_uint CAttackBox::m_s_uniqueID = 0;
CAttackBox::CAttackBox()
{
}


CAttackBox::~CAttackBox()
{
	OnDestroy();
}

SP(CAttackBox) CAttackBox::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CAttackBox) spInstance(new CAttackBox, Engine::SmartDeleter<CAttackBox>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CAttackBox::MakeClone(void)
{
	SP(CAttackBox) spClone(new CAttackBox, Engine::SmartDeleter<CAttackBox>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();

	return spClone;
}

void CAttackBox::Awake(void)
{
	__super::Awake();

	m_layerID = (int)ELayerID::Attack;
	m_dataID = UNDEFINED;
	m_addExtra = true;
	m_isEnabled = false;

	m_spCollision = AddComponent<Engine::CCollisionC>();
}

void CAttackBox::Start(void)
{
	__super::Start();

	if (m_pOwner == nullptr)
	{
		MSG_BOX(__FILE__, L"Owner is empty in CAttackBox::Start()");
		ABORT;
	}

	if (m_pOwner->GetLayerID() == (int)ELayerID::Player)
	{
		m_collisionID = (int)ECollisionID::PlayerAttack;
	}
	else
	{
		m_collisionID = (int)ECollisionID::EnemyAttack;
	}

	auto col = Engine::CObbCollider::Create(m_collisionID);
	col->SetIsTrigger(true);
	m_spCollision->AddCollider(col);

	//m_spTransform->SetParent(m_pOwner->GetTransform());

	AddComponent<Engine::CGraphicsC>()->SetRenderID((int)Engine::ERenderID::NonAlpha);
	AddComponent<Engine::CDebugC>();
	AddComponent<Engine::CShaderC>();
}

void CAttackBox::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CAttackBox::Update(void)
{
	__super::Update();

}

void CAttackBox::LateUpdate(void)
{
	__super::LateUpdate();

	// 
	// 	_float3 ownerRot = m_pOwner->GetTransform()->GetRotation();
	// 	//m_spTransform->SetRotation(ownerRot);
	// 	_mat ownerYRotMat;
	// 	D3DXMatrixRotationY(&ownerYRotMat, m_pOwner->GetTransform()->GetRotation().y);
	// 
	// 	_mat combRotMat = *m_pParentMatrix;
	// 	//combRotMat._41 = 0.f;
	// 	//combRotMat._42 = 0.f;
	// 	//combRotMat._43 = 0.f;
	// 	//_mat invDefaultLook;
	// 	//D3DXMatrixRotationY(&invDefaultLook, D3DXToRadian(180.f));
	// 	//D3DXMatrixInverse(&invDefaultLook, NULL, &invDefaultLook);
	// 	combRotMat = combRotMat * ownerYRotMat;
	// 
	// 	m_spTransform->SetWorldMatrix(combRotMat);
	// 	m_spTransform->SetLastWorldMatrix(combRotMat);



	// 	_float3 rotOffset;
	// 	rotOffset.x = atan2(combRotMat._32, combRotMat._33);
	// 	rotOffset.y = atan2(-combRotMat._31, sqrtf(combRotMat._32 * combRotMat._32 + combRotMat._33* combRotMat._33));
	// 	rotOffset.z = atan2(combRotMat._21, combRotMat._11);
	// 
	// 	m_spTransform->SetRotation(rotOffset);

	// 	D3DXQUATERNION qLocal, qTheresaY;
	// 	D3DXQuaternionRotationMatrix(&qLocal, m_pParentMatrix);
	// 	D3DXQuaternionRotationAxis(&qTheresaY, &_float3(0.f, 1.f, 0.f), m_pOwner->GetTransform()->GetRotation().y);
	// 
	// 	D3DXQUATERNION qWorld;
	// 	qWorld = qLocal * qTheresaY;
	// 
	// 	_mat newWorldMat = GetQuatRotationMatrix(qWorld);
	// 	newWorldMat._41 = offsetPos.x;
	// 	newWorldMat._42 = offsetPos.y;
	// 	newWorldMat._43 = offsetPos.z;
	// 	m_spTransform->SetLastWorldMatrix(newWorldMat);


	//_float3 rotOffset = QuaternionToRadian(qWorld);
	//rotOffset.x = -atan2(ownerRotMat._32, ownerRotMat._33);
	//rotOffset.y = atan2(-ownerRotMat._31, sqrtf(ownerRotMat._32 * ownerRotMat._32 + ownerRotMat._33* ownerRotMat._33));
	//rotOffset.z = -atan2(ownerRotMat._21, ownerRotMat._11);


	//m_spTransform->SetRotation(rotOffset);
	//static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetRotOffset(rotOffset);


	//m_spTransform->UpdateParentMatrix(m_pParentMatrix);

	//_float3 pos = _float3(ownerRotMat._41, ownerRotMat._42, ownerRotMat._43);
	//m_spTransform->SetPosition(pos);
}

void CAttackBox::OnDestroy(void)
{
	__super::OnDestroy();



}

void CAttackBox::OnEnable(void)
{
	__super::OnEnable();
	if (m_spTransform)
		m_spTransform->SetPosition(0, 0, 0);


}

void CAttackBox::OnDisable(void)
{
	__super::OnDisable();

	if (m_spTransform)
		m_spTransform->SetPosition(0, 0, 0);
	m_vCollided.clear();
}

void CAttackBox::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	Engine::CObject* pObject = ci.pOtherCollider->GetOwner()->GetOwner();

	for (auto& object : m_vCollided)
	{
		if (pObject == object)
			return;
	}

	if (m_collisionID == (int)ECollisionID::PlayerAttack)
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(m_pOwner);
		CMonster* pMonster = static_cast<CMonster*>(pObject);

		CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo, ZERO_VECTOR);
	}
	else
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(pObject);
		CMonster* pMonster = static_cast<CMonster*>(m_pOwner);

		CStageControlTower::GetInstance()->HitValkyrie(pMonster, pValkyrie, m_hitInfo, ZERO_VECTOR);
	}
}

void CAttackBox::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CAttackBox::OnCollisionExit(Engine::_CollisionInfo ci)
{
}

void CAttackBox::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	Engine::CObject* pObject = pCollisionC->GetOwner();

	for (auto& object : m_vCollided)
	{
		if (pObject == object)
			return;
	}

	m_vCollided.emplace_back(pObject);

	if (m_collisionID == (_int)ECollisionID::PlayerAttack)
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(m_pOwner);
		CMonster* pMonster = static_cast<CMonster*>(pObject);

		CStageControlTower::GetInstance()->HitMonster(pValkyrie, pMonster, m_hitInfo, ZERO_VECTOR);
	}
	else
	{
		CValkyrie* pValkyrie = static_cast<CValkyrie*>(pObject);
		CMonster* pMonster = static_cast<CMonster*>(m_pOwner);

		CStageControlTower::GetInstance()->HitValkyrie(pMonster, pValkyrie, m_hitInfo, ZERO_VECTOR);
	}
}

void CAttackBox::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBox::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CAttackBox::SetupBox(CObject * pOwner, _mat * pParentMat, _float3 size, _float3 offset, _float3 rotOffset, HitInfo info)
{
	m_pOwner = pOwner;

	//m_pParentMatrix = pParentMat;
	m_hitInfo = info;


	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetSize(size);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetHalfSize(size / 2.f);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetOffsetOrigin(offset);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetRotOffset(rotOffset);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->UpdateBS();
}

void CAttackBox::SetAttackInfo(CObject * pOwner, _mat * pParentMatrix, HitInfo info)
{
	m_pOwner = pOwner;

	m_pParentMatrix = pParentMatrix;
	m_hitInfo = info;
}

void CAttackBox::SetBoxRange(_float3 size, _float3 offset, _float3 rotOffset)
{
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetSize(size);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetHalfSize(size / 2.f);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetOffsetOrigin(offset);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->SetRotOffset(rotOffset);
	static_cast<Engine::CObbCollider*>(m_spCollision->GetColliders()[0].get())->UpdateBS();
}

_mat CAttackBox::GetQuatRotationMatrix(D3DXQUATERNION rotation)
{
	_float3 right = { 1.f,0.f,0.f };
	_float3 up = { 0.f,1.f,0.f };
	_float3 look = { 0.f,0.f,1.f };

	/* rotate */
	GetQuatRotationX(&right, right, rotation);
	GetQuatRotationY(&right, right, rotation);
	GetQuatRotationZ(&right, right, rotation);

	GetQuatRotationX(&up, up, rotation);
	GetQuatRotationY(&up, up, rotation);
	GetQuatRotationZ(&up, up, rotation);

	GetQuatRotationX(&look, look, rotation);
	GetQuatRotationY(&look, look, rotation);
	GetQuatRotationZ(&look, look, rotation);

	_mat worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	memcpy(&worldMatrix.m[0][0], &right, sizeof(_float3));
	memcpy(&worldMatrix.m[1][0], &up, sizeof(_float3));
	memcpy(&worldMatrix.m[2][0], &look, sizeof(_float3));
	memcpy(&worldMatrix.m[3][0], &ZERO_VECTOR, sizeof(_float3));

	return worldMatrix;
}

void CAttackBox::GetQuatRotationX(_float3 * pOut, _float3 in, D3DXQUATERNION rotation)
{
	// roll (x-axis rotation)
	double sinR_cosP = 2 * (rotation.w * rotation.x + rotation.y * rotation.z);
	double cosR_cosP = 1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y);
	float radian = (float)atan2(sinR_cosP, cosR_cosP);

	/*
	1	0	0	0
	0	c	s	0
	0	-s	c	0
	0	0	0	1
	*/

	pOut->y = in.y * cosf(radian) - in.z * sinf(radian);
	pOut->z = in.y * sinf(radian) + in.z * cosf(radian);
}

void CAttackBox::GetQuatRotationY(_float3 * pOut, _float3 in, D3DXQUATERNION rotation)
{
	// pitch (y-axis rotation)
	double sinP = 2 * (rotation.w * rotation.y - rotation.z * rotation.x);
	float radian = 0.f;
	if (std::abs(sinP) >= 1)
		radian = (float)copysign(D3DX_PI * 0.5f, sinP);	// use 90 degrees if out of range
	else
		radian = (float)asin(sinP);

	/*
	c	0	-s	0
	0	1	0	0
	s	0	c	0
	0	0	0	1
	*/


	pOut->x = in.x * cosf(radian) + in.z * sinf(radian);
	pOut->z = in.x * -sinf(radian) + in.z * cosf(radian);
}

void CAttackBox::GetQuatRotationZ(_float3 * pOut, _float3 in, D3DXQUATERNION rotation)
{
	// yaw (z-axis rotation)
	double sinY_cosP = 2 * (rotation.w * rotation.z + rotation.x * rotation.y);
	double cosY_cosP = 1 - 2 * (rotation.y * rotation.y + rotation.z * rotation.z);
	float radian = (float)atan2(sinY_cosP, cosY_cosP);

	/*
	c	s	0	0
	-s	c	0	0
	0	0	1	0
	0	0	0	1
	*/


	pOut->x = in.x * cosf(radian) - in.y * sinf(radian);
	pOut->y = in.x * sinf(radian) + in.y * cosf(radian);
}

_float3 CAttackBox::QuaternionToRadian(D3DXQUATERNION rotation)
{
	double roll, pitch, yaw;

	// roll (x-axis rotation)
	double sinR_cosP = 2 * (rotation.w * rotation.x + rotation.y * rotation.z);
	double cosR_cosP = 1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y);
	roll = atan2(sinR_cosP, cosR_cosP);

	// pitch (y-axis rotation)
	double sinP = 2 * (rotation.w * rotation.y - rotation.z * rotation.x);
	if (std::abs(sinP) >= 1)
		pitch = copysign(D3DX_PI * 0.5f, sinP);	// use 90 degrees if out of range
	else
		pitch = asin(sinP);

	// yaw (z-axis rotation)
	double sinY_cosP = 2 * (rotation.w * rotation.z + rotation.x * rotation.y);
	double cosY_cosP = 1 - 2 * (rotation.y * rotation.y + rotation.z * rotation.z);
	yaw = atan2(sinY_cosP, cosY_cosP);

	return _float3((FLOAT)roll, (FLOAT)pitch, (FLOAT)yaw);
}

void CAttackBox::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
