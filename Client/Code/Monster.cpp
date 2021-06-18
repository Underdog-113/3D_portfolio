#include "stdafx.h"
#include "..\Header\Monster.h"


CMonster::CMonster()
{
}

SP(Engine::CObject) CMonster::MakeClone(void)
{
	return SP(CObject)();
}

void CMonster::Awake(void)
{
	__super::Awake();

	m_dataID = (_int)EDataID::Enemy;
	m_layerID = (_int)ELayerID::Enemy;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
}

void CMonster::Start(void)
{
	__super::Start();


	if (!m_pStat)
	{
		BaseStat stat;
		stat.SetBaseHp(321.f);
		stat.SetBaseAtk(60.f);
		stat.SetBaseDef(22.f);

		stat.SetGrowHp(10.f);
		stat.SetGrowAtk(1.2f);
		stat.SetGrowDef(1.f);

		m_pStat = new M_Stat;
		m_pStat->SetupStatus(&stat);
	}
		
}

void CMonster::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMonster::Update(void)
{
	__super::Update();
}

void CMonster::LateUpdate(void)
{
	__super::LateUpdate();
}

void CMonster::OnDestroy(void)
{
	__super::OnDestroy();

	SAFE_DELETE(m_pStat);
}

void CMonster::OnEnable(void)
{
	__super::OnEnable();
}

void CMonster::OnDisable(void)
{
	__super::OnDisable();
}

void CMonster::SetBasicName(void)
{
}
