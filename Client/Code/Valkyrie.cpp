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
	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->SetOwner(this);
}

void CValkyrie::Start(void)
{
	__super::Start();
	m_pCT = CStageControlTower::GetInstance();
}
