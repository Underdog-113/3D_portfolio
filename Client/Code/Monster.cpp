#include "stdafx.h"
#include "..\Header\Monster.h"

#include "AttackBall.h"
#include "AttackBox.h"

_uint CMonster::m_s_channelID = 0;

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

	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();

	m_spRigidBody = AddComponent<Engine::CRigidBodyC>();
	m_spCollision = AddComponent<Engine::CCollisionC>();
	m_spDebug = AddComponent<Engine::CDebugC>();

	m_spPatternMachine = AddComponent<CPatternMachineC>();
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

		stat.SetType(BaseStat::Mecha);

		m_pStat = new M_Stat;
		m_pStat->SetupStatus(&stat);
	}
	
	// select ChannelID for Sound
	SelectChannelID();
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
	
	ReturnChannelID();
	SAFE_DELETE(m_pStat);
	
	if(m_pAttackBall)
		m_pAttackBall->SetDeleteThis(true);
	if (m_pAttackBox)
		m_pAttackBox->SetDeleteThis(true);

	if (EChannelID::MONSTER_0 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_0;
	}
	else if (EChannelID::MONSTER_1 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_1;
	}
	else if (EChannelID::MONSTER_2 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_2;
	}
	else if (EChannelID::MONSTER_3 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_3;
	}
	else if (EChannelID::MONSTER_4 == m_channelID)
	{
		m_s_channelID ^= EMonChID::MON_4;
	}
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
void CMonster::ApplyHitInfo(HitInfo info)
{
}

void CMonster::ActiveAttackBall(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float radius)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);
	
	m_pAttackBall->SetupBall(this, pBoneMat, radius, info);
	m_pAttackBall->SetIsEnabled(true);
}

void CMonster::UnActiveAttackBall()
{
	m_pAttackBall->SetIsEnabled(false);
}

void CMonster::ActiveAttackBox(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat * pBoneMat, _float3 size, _float3 offset, _float3 rotOffset)
{
	HitInfo info;
	info.SetDamageRate(damageRate);
	info.SetStrengthType(strength);
	info.SetCrowdControlType(cc);

	m_pAttackBox->SetupBox(this, pBoneMat, size, offset, rotOffset, info);
	m_pAttackBox->SetIsEnabled(true);
}

void CMonster::UnActiveAttackBox()
{
	m_pAttackBox->SetIsEnabled(false);
}

void CMonster::MonsterDead()
{
}

void CMonster::SelectChannelID()
{
	if (!(m_s_channelID & EMonChID::MON_0))
	{
		m_channelID = EChannelID::MONSTER_0;
		m_hitChannelID = EChannelID::MONSTER_0_Hit;
		m_s_channelID |= EMonChID::MON_0;
	}
	else if (!(m_s_channelID & EMonChID::MON_1))
	{
		m_channelID = EChannelID::MONSTER_1;
		m_hitChannelID = EChannelID::MONSTER_1_Hit;
		m_s_channelID |= EMonChID::MON_1;
	}
	else if(!(m_s_channelID & EMonChID::MON_2))
	{
		m_channelID = EChannelID::MONSTER_2;
		m_hitChannelID = EChannelID::MONSTER_2_Hit;
		m_s_channelID |= EMonChID::MON_2;
	}
	else if (!(m_s_channelID & EMonChID::MON_3))
	{
		m_channelID = EChannelID::MONSTER_3;
		m_hitChannelID = EChannelID::MONSTER_3_Hit;
		m_s_channelID |= EMonChID::MON_3;
	}
	else if (!(m_s_channelID & EMonChID::MON_4))
	{
		m_channelID = EChannelID::MONSTER_4;
		m_hitChannelID = EChannelID::MONSTER_4_Hit;
		m_s_channelID |= EMonChID::MON_4;
	}
}

void CMonster::ReturnChannelID()
{
	Engine::CSoundManager::GetInstance()->StopSound((_uint)m_channelID);
}

/*
0000 0001 1
0000 0010 2
0000 0100 4
0000 1000 8
0001 0000 16

0000 1001

*/