#include "stdafx.h"
#include "Valkyrie.h"

#include "StageControlTower.h"
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
