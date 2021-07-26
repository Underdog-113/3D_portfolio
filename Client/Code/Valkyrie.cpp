#include "stdafx.h"
#include "Valkyrie.h"

#include "StageControlTower.h"
#include "ActorController.h"
#include "AttackBall.h"
#include "AttackBox.h"

_uint CValkyrie::m_s_uniqueID = 0;

CValkyrie::CValkyrie()
{
}

void CValkyrie::Awake(void)
{
	__super::Awake();

	m_dataID = (_int)EDataID::Player;
	m_layerID = (_int)ELayerID::Player;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();

	m_spRigidBody = AddComponent<Engine::CRigidBodyC>();
	m_spCollision = AddComponent<Engine::CCollisionC>();
	//m_spDebug = AddComponent<Engine::CDebugC>();
}

void CValkyrie::Start(void)
{
	__super::Start();
	m_pCT = CStageControlTower::GetInstance();

	m_skillTimer = m_pStat->GetSkillCoolTime();
	m_ultraTimer = m_pStat->GetUltraCoolTime();
	m_switchTimer = 4.f;
}

void CValkyrie::Update(void)
{
	__super::Update();

	if (m_ultraTimer < m_pStat->GetUltraCoolTime())
		m_ultraTimer += GET_PLAYER_DT;

	if (m_skillTimer < m_pStat->GetSkillCoolTime())
		m_skillTimer += GET_PLAYER_DT;

	if (m_isStun)
	{
		m_stunTimer += GET_PLAYER_DT;
		if (m_stunTimer > m_stunDuration)
		{
			m_spStateMachine->ChangeState(L"StandBy");
			m_isStun = false;
		}
	}
}

void CValkyrie::CoolTimeUpdate(void)
{
	if (m_ultraTimer < m_pStat->GetUltraCoolTime())
		m_ultraTimer += GET_PLAYER_DT;

	if (m_skillTimer < m_pStat->GetSkillCoolTime())
		m_skillTimer += GET_PLAYER_DT;

	if (m_switchTimer < 4.f)
		m_switchTimer += GET_PLAYER_DT;
}

void CValkyrie::OnTriggerEnter(Engine::CCollisionC const * pCollisionC)
{
	for (auto pCollider : pCollisionC->GetColliders())
	{
		if (pCollider->GetCollisionID() == (_uint)ECollisionID::EnemyAttack)
		{
			if (m_isEvade)
				CStageControlTower::GetInstance()->OnPerfectEvadeMode();
			break;
		}
	}
}

void CValkyrie::OnTriggerStay(Engine::CCollisionC const * pCollisionC)
{
}

void CValkyrie::OnTriggerExit(Engine::CCollisionC const * pCollisionC)
{
}

void CValkyrie::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	if (m_pCT->GetActorController()->m_rotateByTarget &&
		ci.pOtherCollider->GetCollisionID() == (_uint)ECollisionID::EnemyHitBox)
		m_spMesh->GetRootMotion()->SetIsRemoveMovement(true);


	if (ci.pOtherCollider->GetCollisionID() == (_uint)ECollisionID::EnemyAttack)
	{
		if (m_isEvade)
			CStageControlTower::GetInstance()->OnPerfectEvadeMode();
	}
}

void CValkyrie::OnCollisionStay(Engine::_CollisionInfo ci)
{
}

void CValkyrie::OnCollisionExit(Engine::_CollisionInfo ci)
{
	if (!m_pCT->GetActorController()->m_rotateByTarget ||
		ci.pOtherCollider->GetCollisionID() == (_uint)ECollisionID::EnemyHitBox)
		m_spMesh->GetRootMotion()->SetIsRemoveMovement(false);

}

void CValkyrie::ApplyHitInfo(HitInfo info)
{
}

void CValkyrie::CreateAttackBall(CAttackBall ** ppAttackBall)
{
	*ppAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	(*ppAttackBall)->SetOwner(this);
}

void CValkyrie::ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat* pBoneMat, _float radius)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	m_pAttackBall->SetupBall(this, pBoneMat, radius, info);
	m_pAttackBall->SetIsEnabled(true);
}

void CValkyrie::ActiveAttackBall(CAttackBall * pAttackBall, _float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float radius, _float3 offset)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	pAttackBall->SetOffset(offset);
	pAttackBall->SetupBall(this, pBoneMat, radius, info);
	pAttackBall->SetIsEnabled(true);
}

void CValkyrie::UnActiveAttackBall()
{
	m_pAttackBall->SetIsEnabled(false);
}

void CValkyrie::ActiveAttackBox(CAttackBox * pAttackBox, _float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	pAttackBox->SetAttackInfo(this, pBoneMat, info);
	pAttackBox->SetIsEnabled(true);
}

void CValkyrie::CreatePivotMatrix(_mat** ppPivotMatrix, Engine::D3DXFRAME_DERIVED** ppFrame, std::string frameName)
{
	*ppFrame = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameByName(frameName);
	//auto test = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameOffsetMatrix("");

	*ppPivotMatrix = new _mat;
	**ppPivotMatrix = (*ppFrame)->CombinedTransformMatrix;
}

void CValkyrie::UpdatePivotMatrix(_mat* pPivotMatrix, Engine::D3DXFRAME_DERIVED * pFrame)
{
	_mat combMat = pFrame->CombinedTransformMatrix;
	_float3 rootMotionPos = m_spMesh->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	*pPivotMatrix = combMat * m_spTransform->GetWorldMatrix();
}

void CValkyrie::OnHitbox()
{
	auto cols = m_spCollision->GetColliders();
	for (auto col : cols)
	{
		if (col->GetCollisionID() == (_uint)ECollisionID::PlayerHitBox)
		{
			col->SetIsEnabled(true);
			//col->SetIsTrigger(false);
			break;
		}
	}
}

void CValkyrie::OffHitbox()
{
	auto cols = m_spCollision->GetColliders();
	for (auto col : cols)
	{
		if (col->GetCollisionID() == (_uint)ECollisionID::PlayerHitBox)
		{
			col->SetIsEnabled(false);
			//col->SetIsTrigger(true);
			break;
		}
	}
}

Engine::CCollider * CValkyrie::GetHitbox()
{
	auto cols = m_spCollision->GetColliders();
	for (auto col : cols)
	{
		if (col->GetCollisionID() == (_uint)ECollisionID::PlayerHitBox)
		{
			return col.get();
		}
	}
	return nullptr;
}

Engine::CRayCollider * CValkyrie::GetFloorRay()
{
	auto cols = m_spCollision->GetColliders();
	for (auto col : cols)
	{
		if (col->GetCollisionID() == (_uint)ECollisionID::FloorRay)
		{
			return static_cast<Engine::CRayCollider*>(col.get());
		}
	}
	return nullptr;
}

_bool CValkyrie::CheckUltraUseable(void)
{
	if (m_ultraTimer < m_pStat->GetUltraCoolTime())
		return true;

	if (m_pStat->GetCurSp() < m_pStat->GetUltraCost())
		return true;

	return true;
}

_bool CValkyrie::CheckSkillUseable(void)
{
	if (m_skillTimer < m_pStat->GetSkillCoolTime())
		return false;

	if (m_pStat->GetCurSp() < m_pStat->GetSkillCost())
		return false;

	return true;
}

_bool CValkyrie::CheckSwitchable()
{
	if (m_switchTimer < 4.f)
		return false;

	return true;
}

void CValkyrie::SetStunState(_float stunTime)
{
	m_stunDuration = stunTime;
	m_stunTimer = 0.f;
	m_isStun = true;

	m_spStateMachine->ChangeState(L"Stun");
}