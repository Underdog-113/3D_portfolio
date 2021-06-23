#include "stdafx.h"
#include "Valkyrie.h"

#include "StageControlTower.h"
#include "AttackBall.h"

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
	m_spDebug = AddComponent<Engine::CDebugC>();
}

void CValkyrie::Start(void)
{
	__super::Start();
	m_pCT = CStageControlTower::GetInstance();
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

void CValkyrie::UnActiveAttackBall()
{
	m_pAttackBall->SetIsEnabled(false);
}
